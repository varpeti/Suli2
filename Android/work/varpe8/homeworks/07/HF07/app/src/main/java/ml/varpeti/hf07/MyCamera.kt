package ml.varpeti.hf07

import android.hardware.camera2.CameraCaptureSession
import android.hardware.camera2.CameraDevice
import android.util.Log
import android.view.Surface
import android.view.TextureView

class MyCamera(private val textureView: TextureView, private val width: Int, private val height: Int) : CameraDevice.StateCallback()
{
    var myCameraDevice : CameraDevice? = null

    override fun onOpened(camera: CameraDevice)
    {
        myCameraDevice = camera // Lementem hogy le tudjam zárni egy függvény hívással
        val surfaceTexture = textureView.surfaceTexture
        surfaceTexture.setDefaultBufferSize(width, height)
        val surface = Surface(surfaceTexture)
        val captureRequest = camera.createCaptureRequest(CameraDevice.TEMPLATE_PREVIEW)
        captureRequest.addTarget(surface)

        camera.createCaptureSession(
            listOf(surface),
            object : CameraCaptureSession.StateCallback()
            {
                override fun onConfigureFailed(session: CameraCaptureSession)
                {
                    Log.i("|||", "onConfigureFailed")
                }

                override fun onConfigured(session: CameraCaptureSession)
                {
                    session.setRepeatingRequest(captureRequest.build(), null, null)
                }

            },
            null
        )
    }

    // Hiba vagy kilépés esetén bezárjuk a kamerát
    override fun onDisconnected(camera: CameraDevice)
    {
        camera.close()
        Log.i("|||", "onDisconnected")
    }

    override fun onError(camera: CameraDevice, error: Int)
    {
        camera.close()
        Log.i("|||", "onError")
    }

    // onPause fogja hívni.
    fun close()
    {
        if  (myCameraDevice!=  null)
        {
            myCameraDevice!!.close()
            myCameraDevice = null
        }
    }

}