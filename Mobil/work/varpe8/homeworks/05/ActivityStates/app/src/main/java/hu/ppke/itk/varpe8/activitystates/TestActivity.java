package hu.ppke.itk.varpe8.activitystates;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;

public class TestActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_test);
        Log.i("TestActivity","\\|/ onCreate");
    }

    @Override
    protected void onDestroy() {
        Log.i("TestActivity","\\|/ onDestroy");
        super.onDestroy();
    }

    @Override
    protected void onStart() {
        Log.i("TestActivity","\\|/ onStart");
        super.onStart();
    }

    @Override
    protected void onStop() {
        Log.i("TestActivity","\\|/ onStop");
        super.onStop();
    }

    @Override
    protected void onPause() {
        Log.i("TestActivity","\\|/ onPause");
        super.onPause();
    }

    @Override
    protected void onResume() {
        Log.i("TestActivity","\\|/ onResume");
        super.onResume();
    }

    // Átváltok gombnyomásra a "NextActivity"-re
    public void switchActivity(View view) {
        Intent intent = new Intent(this, NextActivity.class);
        startActivity(intent);
    }

    public void softExit(View view) {
        Intent intent = new Intent(Intent.ACTION_MAIN);
        intent.addCategory(Intent.CATEGORY_HOME);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(intent);
    }

    public void HardExit(View view) {
        System.exit(0);
    }

    public void fin(View view) {
        finish();
    }


}
