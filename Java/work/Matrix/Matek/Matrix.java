package Matek;

import java.util.ArrayList;
import java.util.Arrays;

public class Matrix {
    public ArrayList< ArrayList<Integer> > m = new ArrayList< ArrayList<Integer> >();

    public Matrix add(Matrix other)
    {
        Matrix ret = new Matrix();
        for (int y = 0;y<this.m.size();y++) {
            ArrayList<Integer> seg = new ArrayList<Integer>();
            for (int x = 0;x<this.m.get(0).size();x++) {
                seg.add( this.m.get(y).get(x)+other.m.get(y).get(x) );
            }
            ret.m.add(seg);
        }
        return ret;
    }

    public void new_col(Integer[] x)
    {
        ArrayList<Integer> seg = new ArrayList<Integer>();
        seg.addAll(Arrays.asList(x));
        this.m.add(seg);
    }

    public Integer get(int x,int y)
    {
        return this.m.get(y).get(x);
    }

    public String toString()
    {
        return this.m.toString();
    }

    public Matrix()
    {
    }
}