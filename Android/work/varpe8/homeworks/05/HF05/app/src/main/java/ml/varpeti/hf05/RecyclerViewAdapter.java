package ml.varpeti.hf05;

import android.content.Context;
import android.content.Intent;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;

public class RecyclerViewAdapter extends RecyclerView.Adapter<RecyclerViewAdapter.ViewHolder>
{

    ArrayList<Country> SubjectNames;

    View view1;
    Context context;

    public RecyclerViewAdapter(ArrayList<Country> SubjectNames1, Context context)
    {

        this.SubjectNames = SubjectNames1;
        this.context = context;
    }

    @Override
    public RecyclerViewAdapter.ViewHolder onCreateViewHolder(ViewGroup viewGroup, int i)
    {
        view1 = LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.country, viewGroup, false);

        view1.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                TextView name = (TextView)v.findViewById(R.id.name);
                Log.i("|||",name.getText().toString());

                TextView lat = (TextView)v.findViewById(R.id.lat);
                TextView lng = (TextView)v.findViewById(R.id.lng);

                Intent intent = context.getPackageManager().getLaunchIntentForPackage("ml.varpeti.hf05google");
                if (intent==null) return; //TODO megkérni a usert hogy telepítse a hf05Google appot
                intent.putExtra("name",name.getText().toString());
                intent.putExtra("lat",Float.parseFloat(lat.getText().toString()));
                intent.putExtra("lng",Float.parseFloat(lng.getText().toString()));
                context.startActivity(intent);
            }
        });

        return new ViewHolder(view1);
    }

    @Override
    public void onBindViewHolder(RecyclerViewAdapter.ViewHolder Viewholder, int i)
    {
        Viewholder.name.setText(SubjectNames.get(i).nameS);
        new DownloadImageTask(Viewholder.img).execute(SubjectNames.get(i).imgS);
        Viewholder.lat.setText(""+SubjectNames.get(i).lat);
        Viewholder.lng.setText(""+SubjectNames.get(i).lng);
    }

    @Override
    public int getItemCount()
    {

        return SubjectNames.size();
    }

    public class ViewHolder extends RecyclerView.ViewHolder
    {

        TextView name;
        ImageView img;
        TextView lat;
        TextView lng;
        public ViewHolder(View view)
        {
            super(view);
            name = (TextView)view.findViewById(R.id.name);
            img = (ImageView) view.findViewById(R.id.img);
            lat = (TextView)view.findViewById(R.id.lat);
            lng = (TextView)view.findViewById(R.id.lng);
        }
    }

}