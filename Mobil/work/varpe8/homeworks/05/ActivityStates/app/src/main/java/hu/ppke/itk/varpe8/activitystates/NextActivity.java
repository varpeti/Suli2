package hu.ppke.itk.varpe8.activitystates;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class NextActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_next);
    }

    // Visszaváltok gombnyomásra a "TestActivity"-re
    public void switchActivity(View view) {
        Intent intent = new Intent(this, TestActivity.class);
        startActivity(intent);
    }

}
