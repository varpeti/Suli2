package ml.varpeti.hf03

import android.net.Uri
import android.os.Bundle
import android.provider.ContactsContract
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.widget.Button
import android.widget.ImageView
import android.widget.TextView
import android.content.Intent


class ShowContactActivity : AppCompatActivity()
{
    var id : String? = null
    var lookUpKey : String? = null

    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.show_contact)

        //Lekérjük az ID-t és a LookUpKey-t
        val extras = intent.extras ?: return
        id = extras.getString("id")
        lookUpKey = extras.getString("lookUpKey")

        if (id==null || lookUpKey==null) finish() //Ha nincs ID, lookUpKey baj van.

        //<3 Thread
        Thread(Runnable(function = {loadAContact(id!!)}), "loadAContactAsync").start()

        // Edit gomb
        findViewById<Button>(R.id.edit).setOnClickListener{

            //Ezzel az intentel hívjuk meg a jelenlegi contactot editálásra
            val editIntent = Intent(Intent.ACTION_EDIT).apply {
                setDataAndType(ContactsContract.Contacts.getLookupUri(id!!.toLong(),lookUpKey!!), ContactsContract.Contacts.CONTENT_ITEM_TYPE)
            }
            //Workaround az ismert hibára:
            //When your app sends an edit intent to the contacts app, and users edit and save a contact, when they click Back they see the contacts list screen. To navigate back to your app, they have to click Recents and choose your app.
            editIntent.putExtra("finishActivityOnSaveCompleted", true)

            //AAAAAAAAAAND OPEEEEEENNNNNNN! - Claptrap //https://youtu.be/CCwP2oERPtc?t=173
            startActivityForResult(editIntent,0)
        }

    }

    fun loadAContact(id : String)
    {
        // Név, photo | cím(ek) | telefonszám(ok) | e-mail cím(ek) hez cursor.
        val contactCursor = contentResolver.query(ContactsContract.Contacts.CONTENT_URI,null,"_ID like '$id'",null,null)!!
        val addressCursor = contentResolver.query(ContactsContract.CommonDataKinds.StructuredPostal.CONTENT_URI,null,"CONTACT_ID like '$id'",null,null)!!
        val phoneCursor   = contentResolver.query(ContactsContract.CommonDataKinds.Phone.CONTENT_URI,           null,"CONTACT_ID like '$id'",null,null)!!
        val emailCursor   = contentResolver.query(ContactsContract.CommonDataKinds.Email.CONTENT_URI,           null,"CONTACT_ID like '$id'",null,null)!!


        //Ha valami elromlik is zárjuk le a cursorokat
        try
        {
            // Elvileg csak egy kéne hogy legyen...
            while (contactCursor.moveToNext())
            {
                //Adatok lekérése
                val nameS   = contactCursor.getString(contactCursor.getColumnIndex(ContactsContract.Contacts.DISPLAY_NAME))
                val photoS  = contactCursor.getString(contactCursor.getColumnIndex(ContactsContract.Contacts.PHOTO_URI))

                //val hasphone = cursor.getString(cursor.getColumnIndex(ContactsContract.Contacts.HAS_PHONE_NUMBER))

                //Log.i("HF03|||", "$id - $nameS")
                //Log.i("HF03|||", "\t$photoS")

                // Kép URI készítés, beállítás
                val photo = findViewById<ImageView>(R.id.photo)
                if (photoS!=null)
                {
                    photo.post(Runnable(){
                        photo.setImageURI(Uri.parse(photoS))
                    })
                }

                // Név beállítása
                val name = findViewById<TextView>(R.id.name)
                if (nameS!=null)
                {
                    name.post(Runnable(){
                        name.text=nameS
                    })
                }

                // Cím(ek) lekérése beállítása
                val address = findViewById<TextView>(R.id.address)
                address.post(Runnable(){ address.text="" })
                while (addressCursor.moveToNext())
                {
                    val street   = addressCursor.getString(addressCursor.getColumnIndex(ContactsContract.CommonDataKinds.StructuredPostal.STREET))
                    val city     = addressCursor.getString(addressCursor.getColumnIndex(ContactsContract.CommonDataKinds.StructuredPostal.CITY))
                    val postcode = addressCursor.getString(addressCursor.getColumnIndex(ContactsContract.CommonDataKinds.StructuredPostal.POSTCODE))

                    //Log.i("HF03|||", "\t$street $city $postcode")
                    address.post(Runnable(){ address.text="($street, $city, $postcode) ${address.text}" })
                }

                // Telefonszám(ok) lekérése beállítása
                val phoneNumber = findViewById<TextView>(R.id.number)
                phoneNumber.post(Runnable(){ phoneNumber.text="" })
                while (phoneCursor.moveToNext())
                {
                    val phoneNumberS = phoneCursor.getString(phoneCursor.getColumnIndex(ContactsContract.CommonDataKinds.Phone.NUMBER))
                    //Log.i("HF03|||", "\t$phoneNumberS")

                    phoneNumber.post(Runnable(){ phoneNumber.text= "($phoneNumberS) ${phoneNumber.text}" })
                }

                // E-mail cím(ek) lekérése beállítása
                val emailAddress = findViewById<TextView>(R.id.email)
                emailAddress.post(Runnable(){ emailAddress.text="" })
                while (emailCursor.moveToNext())
                {
                    val emailAddressS = emailCursor.getString(emailCursor.getColumnIndex(ContactsContract.CommonDataKinds.Email.ADDRESS))
                    //Log.i("HF03|||", "\t$emailAddressS")
                    emailAddress.post(Runnable(){ emailAddress.text="($emailAddressS) ${emailAddress.text}" })
                }
            }

        }
        finally
        {
            contactCursor.close()
            addressCursor.close()
            phoneCursor.close()
            emailCursor.close()
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?)
    {
        //Ha visszatér az editből refresheli az magát.
        //resultCode = 0 canceled | = -1 saved
        this.recreate()
    }
}