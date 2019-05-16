package ml.varpeti.hf07

import android.Manifest
import android.content.Context
import android.content.pm.PackageManager
import android.graphics.*
import android.hardware.camera2.CameraManager
import android.os.Bundle
import android.os.Environment
import android.support.v4.app.ActivityCompat
import android.support.v4.content.ContextCompat
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.view.TextureView
import android.view.View
import kotlinx.android.synthetic.main.activity_main.*
import java.io.File
import java.io.FileOutputStream
import java.io.IOException


class MainActivity : AppCompatActivity()
{

    var myCamera : MyCamera? = null

    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        checkPermission()
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

    // Tapintásra lementi a képet
    fun cheees(v : View)
    {

        val myBitmap = preview.bitmap

        //External storage
        val ex = Environment.getExternalStorageDirectory()
        val location = File(ex.absolutePath + "/HF07") //Külön mappa
        location.mkdir()
        val dest = File(location, System.currentTimeMillis().toString() + ".png") //png lesz

        /*
        val takePictureIntent = Intent(MediaStore.ACTION_IMAGE_CAPTURE)
        takePictureIntent.putExtra(MediaStore.EXTRA_OUTPUT, Uri.fromFile(dest))
        startActivityForResult(takePictureIntent, 0)
        */

        // Lehet pontosan állítani a felbontást (=TextureView felbontása), és a onSurfaceTextureUpdated() metódusban pedig Bitmap manipulálással lehet "filtereket" rárakni egyből
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
        }

        //Előző kép beállítása
        prev.setImageBitmap(myBitmap)
        /*
            (csak 1-et specifikált a feladat)
            Ha kéne több is meghívnám rá a kép lementésekor az Intent.ACTION_MEDIA_SCANNER_SCAN_FILE intentet.
            És meghívnám a galériát/filemanagert a HF07 albumba/mappába ha a prev-re kattintanak.
            Vagy egy külön activity-t ahol beolvasom a mappa összes képét.
         */

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
