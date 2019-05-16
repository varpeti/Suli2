package ml.varpeti.hf08

import android.Manifest
import android.annotation.SuppressLint
import android.content.Context
import android.content.pm.PackageManager
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.graphics.SurfaceTexture
import android.hardware.camera2.CameraManager
import android.os.Bundle
import android.os.Environment
import android.support.v4.app.ActivityCompat
import android.support.v4.content.ContextCompat
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.view.TextureView
import android.view.View
import android.widget.Toast
import com.google.firebase.database.DatabaseReference
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.ml.vision.FirebaseVision
import com.google.firebase.ml.vision.common.FirebaseVisionImage
import com.google.gson.Gson
import kotlinx.android.synthetic.main.main.*
import java.io.File
import java.io.FileWriter
import java.io.IOException
import java.util.*


class Main : AppCompatActivity()
{

    var myCamera : MyCamera? = null

    private lateinit var database: FirebaseDatabase
    private lateinit var reference: DatabaseReference
    val ex = Environment.getExternalStorageDirectory()

    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.main)

        database = FirebaseDatabase.getInstance()
        reference = database.getReference("BIs")

        checkPermission()

        val bm = BitmapFactory.decodeResource(resources, R.raw.qr01)
        mineInfoFromBitmap(bm)
    }

    private fun checkPermission()
    {
        //Jogok meglétének ellenőrzése, ha nincs kérünk (szép sorba)
        when
        {
            ContextCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED -> ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.CAMERA),0)
            ContextCompat.checkSelfPermission(this, Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED -> ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.READ_EXTERNAL_STORAGE),0)
            ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED -> ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.WRITE_EXTERNAL_STORAGE),0)
            else -> Thread(Runnable(function = { startPreview() }), "startPreviewAsync").start()
        }

    }

    private fun startPreview()
    {

        //findViewById<>() a gyengéknek való :D
        preview.surfaceTextureListener = object : TextureView.SurfaceTextureListener
        {
            override fun onSurfaceTextureSizeChanged(surface: SurfaceTexture?, width: Int, height: Int) {}

            override fun onSurfaceTextureUpdated(surface: SurfaceTexture?) {}

            override fun onSurfaceTextureDestroyed(surface: SurfaceTexture?): Boolean
            {
                return true
            }

            @SuppressLint("MissingPermission")
            override fun onSurfaceTextureAvailable(surface: SurfaceTexture?, width: Int, height: Int)
            {
                // Ha elérhető kisterameljük a preview viewra
                val cameraManager = getSystemService(Context.CAMERA_SERVICE) as CameraManager
                val cameraId = cameraManager.cameraIdList.first()
                myCamera = MyCamera(preview, width, height)
                cameraManager.openCamera(cameraId, myCamera, null)
            }

        }

    }

    override fun onPause()
    {
        super.onPause()

        // Bezárjuk a kamerát ha nem kell
        if (myCamera != null)
        {
            myCamera!!.close()
        }
        finish()
    }

    // Tapintásra (megpróbálja) kibányásszni a bar/qr kódot
    fun cheees(v : View)
    {

        val myBitmap = preview.bitmap

        /*val location = File(ex.absolutePath + "/HF08") //Külön mappa
        location.mkdir()
        val dest = File(location, System.currentTimeMillis().toString() + ".png") //png lesz

        try
        {
            val fos = FileOutputStream(dest)

            myBitmap.compress(Bitmap.CompressFormat.PNG, 100, fos)
            fos.flush()
            fos.close()
        }
        catch (e: IOException)
        {
            Log.e("error", e.message)
            e.printStackTrace()
        }*/

        //Előző kép beállítása
        prev.setImageBitmap(myBitmap)

        mineInfoFromBitmap(myBitmap)

    }

    private fun mineInfoFromBitmap(bitmap:Bitmap)
    {
        val image = FirebaseVisionImage.fromBitmap(bitmap)
        val detector = FirebaseVision.getInstance().visionBarcodeDetector

        detector.detectInImage(image).addOnSuccessListener{ barcodes ->
            for (barcode in barcodes)
            {
                val date = Date() //Date
                val rawValue = barcode.rawValue //Information
                val format = barcode.format // Type of the code
                val type = barcode.valueType // Type of the value

                val msg = "$rawValue $format $type $date"
                Log.i("|||", msg)
                Toast.makeText(this, msg, Toast.LENGTH_LONG).show()

                //Store history

                val barcodeinfo = BarcodeInfo(rawValue, format, type, date)

                val barcodeInfos = HashMap<String, Any>()
                barcodeInfos[UUID.randomUUID().toString()] = barcodeinfo

                reference.updateChildren(barcodeInfos)

                // Save as Json using Gson

                val gson = Gson()
                val json = gson.toJson(barcodeinfo)
                Log.i("|||", json)

                val writer: FileWriter // Write a file.
                try {
                    val location = File(ex.absolutePath + "/HF08") //Külön mappa
                    location.mkdir()
                    writer = FileWriter(ex.absolutePath + "/HF08/${System.currentTimeMillis()}.json")
                    writer.write(json)
                    writer.close()
                } catch (e:IOException) {
                    e.printStackTrace()
                }

            }
        }.addOnFailureListener { e ->
            e.printStackTrace() //TODO better ex handling
            Log.i("|||","fail")
        }

        Log.i("|||","mine")

    }

    // Ha kértünk jogot:
    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<String>, grantResults: IntArray)
    {
        when (requestCode)
        {
            0 ->
            {
                //Ha üres a grantResults akkor nem kaptuk meg
                if ((grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED))
                {
                    // YEAH van jogunk, recreate() hogy menjen tovább
                    recreate()
                }
                else
                {
                    // Nem kell jog, minek az? Az app se kell:
                    finish()
                }
                return
            }
            // Egyéb requestek
            else ->
            {
                // Ignoráljuk őket
            }
        }
    }

}
