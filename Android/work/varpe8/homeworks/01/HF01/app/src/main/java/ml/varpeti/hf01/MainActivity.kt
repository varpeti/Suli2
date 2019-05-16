package ml.varpeti.hf01

import android.app.Activity
import android.graphics.Color
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.Button
import android.widget.LinearLayout
import android.widget.TextView
import android.content.Intent
import android.widget.Toast





class MainActivity : AppCompatActivity()
{
    val colorOf = arrayOf("#ffffff","#00ff00")

    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        //Mentett szöveg visszaállítása

        val fruits = resources.getStringArray(R.array.fruits)
        val ll01 = findViewById(R.id.ll01) as LinearLayout
        for (i in fruits.indices)
        {
            val b = Button(this)
            b.id = i
            b.setText(fruits[i])
            b.setBackgroundColor(Color.parseColor(colorOf[0]))
            b.tag = 0

            b.setOnClickListener {
                val btn = it as Button
                val name = btn.text as String
                var ci = btn.tag as Int
                Log.i("\\|/", name+" "+btn.tag)

                if (ci==1)
                {
                    ci=0
                    btn.setBackgroundColor(Color.parseColor(colorOf[ci]))
                    btn.tag = ci

                    //Shopping Cart
                    val tw = findViewById<TextView>(R.id.tw01)
                    tw.text = ""+((tw.text as String).toInt()-1)
                }
                else
                {
                    val int = Intent(this, ItemViewActivity::class.java)
                    int.putExtra("name", name)
                    int.putExtra("id", i)

                    startActivityForResult(int,0)
                }
            }

            ll01.addView(b)
        }
        //Shopping Cart
        val tw = findViewById<TextView>(R.id.tw01)
        tw.text = "0"

    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?)
    {
        if (resultCode == Activity.RESULT_OK && requestCode == 0)
        {
            if (data!!.hasExtra("id"))
            {
                val id = data.extras.getInt("id")
                val ci = data.extras.getInt("status",0)
                val b = findViewById<Button>(resources.getIdentifier(""+id, "id", getPackageName()))
                if (ci==1)
                {
                    b.tag = ci
                    Log.i("\\|/", "res: "+id+" "+ci)
                    b.setBackgroundColor(Color.parseColor(colorOf[ci]))
                    val tw = findViewById<TextView>(R.id.tw01)
                    tw.text = ""+((tw.text as String).toInt()+1)
                }

            }
        }
    }

    //Lementés TODO
    override fun onSaveInstanceState(savedInstanceState: Bundle)
    {
        super.onSaveInstanceState(savedInstanceState)
        val fruits = resources.getStringArray(R.array.fruits)
        for (i in fruits.indices)
        {
            val b = findViewById<Button>(resources.getIdentifier(""+i, "id", getPackageName()))
            var ci = b.tag as Int
            //Log.i("\\|/", ""+ci)
            savedInstanceState.putInt("b"+i+"color",ci)
        }
    }

}

