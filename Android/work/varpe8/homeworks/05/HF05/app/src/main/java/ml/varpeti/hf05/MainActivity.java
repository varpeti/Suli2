package ml.varpeti.hf05;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class MainActivity extends AppCompatActivity
{
    RecyclerView rw;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // RecyclerView
        rw = findViewById(R.id.rw);
        rw.setLayoutManager(new LinearLayoutManager(this));

        // Networking szóval külön szál
        new Thread(new Runnable(){@Override public void run(){getCountries();}}).start(); //Szebb kotlinba...
    }

    private void getCountries()
    {
        // Lekérjük a Json filet
        String countriesS = "";
        try
        {
            URL u = new URL("http://users.itk.ppke.hu/%7Ematad/country_list.json");
            URLConnection urlConnection = u.openConnection();
            urlConnection.setConnectTimeout(10000);
            InputStream is = urlConnection.getInputStream();
            countriesS = convertStreamToString(is);
            //Log.i("|||",countriesS.length()+"");
        }
        catch (IOException e)
        {
            Log.e("|||","err "+e.getMessage()); //TODO exception handling
        }

        // JSONObject a gyengéknek való és azoknak akik tudják hogy létezik mielött teljesen megírták regexel...
        // Vagy nem lusták használni a kedvenc kerső motorjukat
        // Vagy utálnak dokumentációt olvasni, és a jól bevált (de mágia) módszert alkalmazzák helyette
        // Vagy akik azt akarják hogy ne legyen a kód olvasható
        // Vagy ...

        ArrayList<Country> countries = new ArrayList<>();

        // Bonyolultab regex kell mert lehet hiányos a Json file #"latlng":[],"name":"United States Minor Outlying Islands"
        // Még arra is kész ha nem egy sorba lenne.

        // Kiolvassauk az összes country-t.
        Pattern cP = Pattern.compile("\\{(\"[^}]*\\}[,\\]])",Pattern.MULTILINE | Pattern.DOTALL);
        Matcher cM = cP.matcher(countriesS);
        while(cM.find())
        {
            String cS = cM.group(1).trim();
            //Log.i("|||",cS);

            //Kiszedjük a nevet belőle
            Pattern nameP = Pattern.compile("\"name\":\"([^\"]*)\"",Pattern.MULTILINE | Pattern.DOTALL);
            Matcher nameM = nameP.matcher(cS);

            //Majd a kép url-jét
            Pattern imgP = Pattern.compile("\"imageUrl\":\"([^\"]*)\"",Pattern.MULTILINE | Pattern.DOTALL);
            Matcher imgM = imgP.matcher(cS);

            // Majd a latitude-t és longitude-t.
            Pattern latlngP = Pattern.compile("\"latlng\":\\[([+-]?\\d*\\.?\\d*),([+-]?\\d*\\.?\\d*)\\]",Pattern.MULTILINE | Pattern.DOTALL);
            Matcher latlngM = latlngP.matcher(cS);

            Country c = new Country();
            if (nameM.find())
            {
                c.nameS = nameM.group(1).trim();
            }
            if (imgM.find())
            {
                c.imgS = imgM.group(1).trim();
            }
            if (latlngM.find())
            {
                c.lat   = Float.parseFloat(latlngM.group(1).trim());
                c.lng   = Float.parseFloat(latlngM.group(2).trim());
            }

            countries.add(c); //Hozzá adjuk a listához

            //Log.i("|||",c.toString());
        }

        // Beállítjuk a RecyclerView adapteret (a main threadre postoljuk)
        final RecyclerView.Adapter adapter = new RecyclerViewAdapter(countries,this);
        rw.post(new Runnable() {@Override public void run(){rw.setAdapter(adapter);}}); //Kotlinban ez is szebb...


    }

    //Csak simán mintha fileból olvasnánk
    private String convertStreamToString(InputStream is) throws IOException
    {
        BufferedReader reader = new BufferedReader(new InputStreamReader(is));
        StringBuilder sb = new StringBuilder();

        try
        {
            String line = null;
            while ((line = reader.readLine()) != null)
            {
                sb.append(line).append('\n');
            }
        }
        finally
        {
            is.close();
        }
        return sb.toString();
    }
}
