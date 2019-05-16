package ml.varpeti.hf02

import android.app.IntentService
import android.content.Intent
import java.util.*

class UUIDService : IntentService("UUIDService")
{
    override fun onHandleIntent(intent: Intent?)
    {
        for (p in 1..100)
        {
            for (i in 0..99999)
            {
                UUID.randomUUID()
            }
            val data = Intent()
            data.putExtra("name", 0)
            data.putExtra("progress", p)
            data.action = "ml.varpeti.hf02.MainActivity"
            sendBroadcast(data)
        }
    }
}