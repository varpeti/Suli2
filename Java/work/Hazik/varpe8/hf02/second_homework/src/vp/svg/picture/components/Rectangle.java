package vp.svg.picture.components;

import java.io.*;

import vp.io.BuffWriter;

public class Rectangle implements Component {
    private float x,y,w,h;

    public Rectangle(float _x, float _y, float _w, float _h)
    {
        x=_x;y=_y;w=_w;h=_h;
        System.out.println("Rectangle: x:"+x+" y:"+y+" w:"+w+" h:"+h);
    }


    public void write(Writer output,int indent) throws IOException 
    {
        BuffWriter.addNewLine(output,"<rect x='" + getTopLeftX() + "' y='" + getTopLeftY() + "' " + "width='" + getWidth() + "' height='" + getHeight() + "' " + "stroke='black' " + "fill='black' />",indent);
    }

    public float getTopLeftX(){return x;}
    public float getTopLeftY(){return y;}
    public float getHeight(){return w;}
    public float getWidth(){return h;}

    public void translate(float dx,float dy){x+=dx;y+=dy;}
    public void flipHorizontal(float axis){y=flip(y,axis);}
    public void flipVertical(float axis){x=flip(x,axis);}
}
