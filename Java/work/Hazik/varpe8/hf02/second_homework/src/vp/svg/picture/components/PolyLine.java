package vp.svg.picture.components;

import java.io.*;
import java.util.ArrayList;

import vp.io.BuffWriter;

public class PolyLine implements Component {

    private ArrayList<Float> coords;

    //public PolyLine(Float... coords){}  //Csak azért hogy sexy legyen? Ah nem kell ez nekem, majd másor :D
    
    public PolyLine(ArrayList<Float> _coords)
    {
        coords = new ArrayList<Float>(_coords);
        System.out.println("PolyLine:");
        for (int i=0;i<_coords.size();i+=2) {
            System.out.println("\t"+i+". (x:"+_coords.get(i)+" y:"+_coords.get(i+1)+")");
        }
    }

    public void write(Writer output,int indent) throws IOException 
    {
        StringBuilder codeBuilder = new StringBuilder("<polyline points='");
        codeBuilder.append(getPointX(0)).append(',').append(getPointY(0));
        for (int i = 1; i < getNumberOfPoints(); i++) 
        {
            codeBuilder.append(' ').append(getPointX(i)).append(',').append(getPointY(i));
        }
        codeBuilder.append("' style='fill:none;stroke:black;stroke-width:2'/>");
        
        BuffWriter.addNewLine(output,codeBuilder.toString(),indent);
    }
    
    public float getPointX(int i){return (float)coords.get(i*2);}
    public float getPointY(int i){return (float)coords.get(i*2+1);}
    public int getNumberOfPoints(){return coords.size()/2;}

    public void translate(float dx, float dy)
    {
        for (int i=0;i<coords.size();i+=2) 
        {
            coords.set(i,   coords.get(i)   + dx); 
            coords.set(i+1, coords.get(i+1) + dy);
        }
    }
    public void flipHorizontal(float axis)
    {
        for (int i=0;i<coords.size();i+=2) flip((float)coords.get(i),axis);
    }
    public void flipVertical(float axis)
    {
        for (int i=1;i<coords.size();i+=2) flip((float)coords.get(i),axis);
    }

}
