package ml.varpeti.hf05google;

import android.support.v4.app.FragmentActivity;
import android.os.Bundle;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

public class MapsActivity extends FragmentActivity implements OnMapReadyCallback {

    private GoogleMap mMap;

    float lat = .0f;
    float lng = .0f;
    String name = "Null Island - The busiest place that don't exist";

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        if (getIntent().hasExtra("lat"))
        {
            Bundle ed = getIntent().getExtras();
            lat = ed.getFloat("lat");
        }
        if (getIntent().hasExtra("lng"))
        {
            Bundle ed = getIntent().getExtras();
            lng = ed.getFloat("lng");
        }
        if (getIntent().hasExtra("name"))
        {
            Bundle ed = getIntent().getExtras();
            name = ed.getString("name");
        }

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);
        // Obtain the SupportMapFragment and get notified when the map is ready to be used.
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager()
                .findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);
    }


    /**
     * Manipulates the map once available.
     * This callback is triggered when the map is ready to be used.
     * This is where we can add markers or lines, add listeners or move the camera. In this case,
     * we just add a marker near Sydney, Australia.
     * If Google Play services is not installed on the device, the user will be prompted to install
     * it inside the SupportMapFragment. This method will only be triggered once the user has
     * installed Google Play services and returned to the app.
     */
    @Override
    public void onMapReady(GoogleMap googleMap)
    {
        mMap = googleMap;

        LatLng mark = new LatLng(lat, lng);
        // set markert position, title, description
        mMap.addMarker(new MarkerOptions().position(mark).title(name).snippet(lat+", "+lng));

        //Move the camera and zoom [Min 2.0f-21.0f Max]
        //mMap.moveCamera(CameraUpdateFactory.newLatLng(mark));
        mMap.animateCamera(CameraUpdateFactory.newLatLngZoom(mark, 5.0f));
    }
}
