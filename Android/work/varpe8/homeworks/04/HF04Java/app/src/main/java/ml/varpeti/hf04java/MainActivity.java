package ml.varpeti.hf04java;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.EditText;

import com.google.android.gms.tasks.OnSuccessListener;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import java.util.HashMap;
import java.util.UUID;

public class MainActivity extends AppCompatActivity
{
    FirebaseDatabase database;
    DatabaseReference reference;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState); // Megtartja forgatásnál az adatokat
        setContentView(R.layout.activity_main);

        database = FirebaseDatabase.getInstance();
        reference = database.getReference("users");
    }

    public void onSend(View v)
    {
        String name = ((EditText)findViewById(R.id.name)).getText().toString();
        String email = ((EditText)findViewById(R.id.email)).getText().toString();
        String description = ((EditText)findViewById(R.id.description)).getText().toString();
        User user = new User(name,email,description);

        HashMap<String,Object> users = new HashMap<>();
        users.put(UUID.randomUUID().toString(),user);

        reference.updateChildren(users).addOnSuccessListener(new OnSuccessListener<Void>()
        {
            @Override
            public void onSuccess(Void aVoid)
            {
                Intent intent = new Intent(MainActivity.this,ShowUsersActivity.class);
                startActivity(intent);
            }
        });

    }

}
