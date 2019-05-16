package ml.varpeti.hf04java;

import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import java.util.ArrayList;

public class RecyclerViewAdapter extends RecyclerView.Adapter<RecyclerViewAdapter.ViewHolder>
{

    ArrayList<User> SubjectNames;

    View view1;

    public RecyclerViewAdapter(ArrayList<User> SubjectNames1)
    {

        this.SubjectNames = SubjectNames1;
    }

    @Override
    public RecyclerViewAdapter.ViewHolder onCreateViewHolder(ViewGroup viewGroup, int i)
    {

        view1  = LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.user, viewGroup, false);

        return new ViewHolder(view1);
    }

    @Override
    public void onBindViewHolder(RecyclerViewAdapter.ViewHolder Viewholder, int i)
    {

        Viewholder.name.setText(SubjectNames.get(i).name);
        Viewholder.email.setText(SubjectNames.get(i).email);
        Viewholder.description.setText(SubjectNames.get(i).description);
    }

    @Override
    public int getItemCount()
    {

        return SubjectNames.size();
    }

    public class ViewHolder extends RecyclerView.ViewHolder
    {

        TextView name;
        TextView email;
        TextView description;
        public ViewHolder(View view)
        {

            super(view);
            name = (TextView)view.findViewById(R.id.name);
            email = (TextView)view.findViewById(R.id.email);
            description = (TextView)view.findViewById(R.id.description);
        }
    }

}