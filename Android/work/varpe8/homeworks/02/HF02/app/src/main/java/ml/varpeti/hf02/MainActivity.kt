package ml.varpeti.hf02

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.content.Intent
import android.content.BroadcastReceiver
import android.content.Context
import android.widget.ProgressBar
import android.content.IntentFilter
import java.util.*
import android.os.AsyncTask




class MainActivity : AppCompatActivity() {
    lateinit var buttons: Array<Button>
    lateinit var progressBars: Array<ProgressBar>
    lateinit var time: Array<Long>

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        buttons = arrayOf(
            findViewById<Button>(R.id.b1),
            findViewById<Button>(R.id.b2),
            findViewById<Button>(R.id.b3),
            findViewById<Button>(R.id.b4)
        )
        progressBars = arrayOf(
            findViewById<ProgressBar>(R.id.pb1),
            findViewById<ProgressBar>(R.id.pb2),
            findViewById<ProgressBar>(R.id.pb3),
            findViewById<ProgressBar>(R.id.pb4)
        )
        time = arrayOf(0, 0, 0, 0)

        //Service
        buttons[0].setOnClickListener {
            val int = Intent(this@MainActivity, UUIDService::class.java)
            startService(int)
            time[0] = System.currentTimeMillis()
            // Elindít a háttérben egy Servicet,
            // aminek az élete nem függ a Main Activitytől,
            // még egy indítás esetén felstackeleődik (utánna indul el)
            // hozzá lehet bindelni egy activityhez
        }

        //AsyncTask
        buttons[1].setOnClickListener {
            UUIDAsyncTask().execute(99999)
            time[1] = System.currentTimeMillis()
            // Elindít a háttérben egy AsyncTaskot,
            // aminek az élete nem függ a Main Activitytől,
            // de a progresst és az eredményt az eredetinek küldi vissza
            // még egy indítás esetén felstackeleődik (utánna indul el)
            // Le lehet lőni (cancel),
            // le lehet lérdezi a státuszát (status),
            // lehet várni a végeredményre (get), akár timeouttal
        }

        //AsyncTaskLoader
        buttons[2].setOnClickListener {
            val atlic = UUIDAsyncTaskLoaderIC(this)
            atlic.startLoading()
            time[2] = System.currentTimeMillis()
            // Elindít a háttérben egy "AsyncTaskot",
            // aminek az élete nem függ a Main Activitytől,
            // még egy indítás esetén elindul még egy
            // le lehet lérdezi a státuszát (hasResult),
            // és a végeredményét (result)
        }

        //Thread
        buttons[3].setOnClickListener {
            var thread = Thread(UUIDThread(), "UUIDThread")
            thread.start()
            time[3] = System.currentTimeMillis()
            // Elindít a háttérben egy Threadet,
            // aminek az élete nem függ a Main Activitytől,
            // még egy indítás esetén elindul még egy
            // Nem lehet elérni a vieweket
        }


        //Broadcast üzenetek elkapása
        val filter = IntentFilter("ml.varpeti.hf02.MainActivity")
        this.registerReceiver(Receiver(), filter)
    }

    //Ez kapja el a progress üzeneteket.
    private inner class Receiver : BroadcastReceiver() {
        override fun onReceive(con: Context, int: Intent) {
            val name = int.extras!!.getInt("name")
            val progress = int.extras!!.getInt("progress")
            progressBars[name].setProgress(progress)
            buttons[name].text = (System.currentTimeMillis() - time[name]).toString()

            //Annak letiltása hogy még 1x elinduljon közben/utánna.
            buttons[name].setOnClickListener {}
        }
    }

    //Thread, inner class mert külön classba kötülményes contextet rakni
    private inner class UUIDThread : Runnable
    {
        override fun run()
        {
            for (p in 1..100)
            {
                for (i in 0..99999)
                {
                    UUID.randomUUID()
                }

                //Only the original thread that created a view hierarchy can touch its views.
                val data = Intent()
                data.putExtra("name", 3)
                data.putExtra("progress", p)
                data.action = "ml.varpeti.hf02.MainActivity"
                sendBroadcast(data)
            }
        }
    }

    //AsyncTask
    private inner class UUIDAsyncTask : AsyncTask<Int,Int,Int>()
    {

        override fun doInBackground(vararg params: Int?): Int
        {
            for(p in 1..100)
            {
                for (i in 0..99999)
                {
                    UUID.randomUUID()
                }
                publishProgress(p)
            }
            return 100
        }

        override fun onProgressUpdate(vararg values: Int?)
        {
            //szintaxis csemege
            values[0]?.let {
                progressBars[1].setProgress(it)
                buttons[1].text = (System.currentTimeMillis() - time[1]).toString()
            }
        }

        override fun onPreExecute()
        {
            buttons[1].setOnClickListener {}
            super.onPreExecute()
        }
    }

    //AsyncTaskLoader
    private class UUIDAsyncTaskLoaderIC(context: Context) : UUIDAsyncTaskLoader<Int>(context)
    {
        override fun loadInBackground(): Int
        {
            for (p in 1..100)
            {
                for (i in 0..99999)
                {
                    UUID.randomUUID()
                }
                val data = Intent()
                data.putExtra("name", 2)
                data.putExtra("progress", p)
                data.action = "ml.varpeti.hf02.MainActivity"
                context.sendBroadcast(data)
            }
            return 100
        }
    }

}
