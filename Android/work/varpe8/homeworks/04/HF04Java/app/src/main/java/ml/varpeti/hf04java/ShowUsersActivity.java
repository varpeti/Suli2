package ml.varpeti.hf04java;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;

public class ShowUsersActivity extends AppCompatActivity
{
    FirebaseDatabase database;
    DatabaseReference reference;
    RecyclerView rw;


    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_show_users);

        database = FirebaseDatabase.getInstance();
        reference = database.getReference("users");

        rw = findViewById(R.id.rw);
        rw.setLayoutManager(new LinearLayoutManager(this));

        reference.addValueEventListener(postListener());

    }

    ValueEventListener postListener()
    {
         return new ValueEventListener()
         {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot)
            {
                ArrayList<User> users = new ArrayList<>();

                for (DataSnapshot ds: dataSnapshot.getChildren())
                {
                    User user = ds.getValue(User.class);
                    Log.i("|||",user.name);
                    users.add(user);

                }
                RecyclerView.Adapter adapter = new RecyclerViewAdapter(users);
                rw.setAdapter(adapter);
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {
                //TODO
            }
        };
    }
}
