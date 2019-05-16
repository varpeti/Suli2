package ml.varpeti.hf06

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.TextView

class MainActivity : AppCompatActivity() {

    val bincalc = BinaryCalc()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    fun b2tw(tw: TextView, s: CharSequence)
    {
        when (s)
        {
            "0"      -> if (tw.text.length<31) tw.text = "${tw.text}0"
            "1"      -> if (tw.text.length<31) tw.text = "${tw.text}1"
            "\u232b" -> if (tw.text.isNotEmpty()) tw.text = tw.text.substring(0, tw.text.length - 1)
            "DEL"    -> tw.text = ""
        }
    }


    fun onClickB0(view : View)
    {
        val v = view as Button
        val tw = findViewById<TextView>(R.id.b0)
        b2tw(tw,v.text)
    }

    fun onClickB1(view : View)
    {
        val v = view as Button
        val tw = findViewById<TextView>(R.id.b1)
        b2tw(tw,v.text)
    }

    fun onClickB2(view : View)
    {
        val v = view as Button
        val b0 = findViewById<TextView>(R.id.b0)
        val b1 = findViewById<TextView>(R.id.b1)
        val b2 = findViewById<TextView>(R.id.b2)

        val b0t = when
        {
            b0.text.isEmpty()   -> "0"
            b0.text=="-"        -> "0"
            else                -> b0.text
        }
        val b1t = when
        {
            b1.text.isEmpty()   -> "0"
            b1.text=="-"        -> "0"
            else                -> b1.text
        }

        when (v.text)
        {
            "+" -> b2.text = bincalc.add(b0t,b1t)
            "-" -> b2.text = bincalc.sub(b0t,b1t)
            "\u2b09" -> b0.text = b2.text
            "\u2b08" -> b1.text = b2.text
        }
    }

    public override fun onSaveInstanceState(savedInstanceState: Bundle)
    {
        super.onSaveInstanceState(savedInstanceState)
        val b0 = findViewById<TextView>(R.id.b0)
        val b1 = findViewById<TextView>(R.id.b1)
        val b2 = findViewById<TextView>(R.id.b2)
        savedInstanceState.putString("b0", b0.text.toString())
        savedInstanceState.putString("b1", b1.text.toString())
        savedInstanceState.putString("b2", b2.text.toString())
    }

    public override fun onRestoreInstanceState(savedInstanceState: Bundle?)
    {
        super.onRestoreInstanceState(savedInstanceState)
        val b0 = findViewById<TextView>(R.id.b0)
        val b1 = findViewById<TextView>(R.id.b1)
        val b2 = findViewById<TextView>(R.id.b2)
        if (savedInstanceState != null)
        {
            b0.text = savedInstanceState.getString("b0") ?: ""
            b1.text = savedInstanceState.getString("b1") ?: ""
            b2.text = savedInstanceState.getString("b2") ?: ""
        }
    }
}
