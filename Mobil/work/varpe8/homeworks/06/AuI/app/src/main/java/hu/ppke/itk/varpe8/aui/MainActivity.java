package hu.ppke.itk.varpe8.aui;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String[]btnNames=getResources().getStringArray(R.array.btnNames);
        String[]btnClick=getResources().getStringArray(R.array.btnClick);

        LinearLayout ll01 = (LinearLayout)findViewById(R.id.ll01);
        for (int i = 0; i < btnNames.length; i++) {
            Button b = new Button(this);
            b.setId(i);
            b.setText(btnNames[i]);
            b.setTag(btnClick[i]);
            b.setOnClickListener(this);
            ll01.addView(b);
        }

        //Mentett szöveg visszaállítása
        TextView tw = (TextView)findViewById(R.id.tw01);
        if (savedInstanceState != null){
            tw.setText(savedInstanceState.getCharSequence("tw"));
        }
    }

    //Button eventek
    @Override
    public void onClick(View v) {
        String msg = (String)v.getTag();
        Log.i("\\|/",msg);
        TextView tw = (TextView)findViewById(R.id.tw01);
        tw.setText(msg);
    }

    //Szöveg lemetése
    @Override
    protected void onSaveInstanceState(Bundle savedInstanceState) {
        super.onSaveInstanceState(savedInstanceState);
        TextView tw = (TextView)findViewById(R.id.tw01);
        savedInstanceState.putCharSequence("tw",tw.getText());
    }
}
