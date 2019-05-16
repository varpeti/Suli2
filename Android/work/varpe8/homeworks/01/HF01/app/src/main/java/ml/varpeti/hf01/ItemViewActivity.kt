package ml.varpeti.hf01

import android.app.Activity
import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.widget.Button
import android.widget.TextView


class ItemViewActivity : AppCompatActivity()
{
    var status = 0
    var id = 0

    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.item_view)

        val extras = intent.extras ?: return
        val name = extras.getString("name","")
        id = extras.getInt("id",0)
        status = 0

        val tw = findViewById<TextView>(R.id.tw02)
        tw.text = name;

        val bok = findViewById<Button>(R.id.bok)
        bok.setOnClickListener {
            status = 1
            finish()
        }

    }

    override fun finish()
    {
	
        Log.i("\\|/", "fin: "+id+" "+status)
        val data = Intent()
		// Extras should be defined as constants
        data.putExtra("id",id)
        data.putExtra("status",status)
        setResult(Activity.RESULT_OK, data)
        super.finish()
    }
}