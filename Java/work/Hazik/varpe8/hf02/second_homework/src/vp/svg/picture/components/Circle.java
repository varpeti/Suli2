package vp.svg.picture.components;


import java.io.*;

import vp.io.BuffWriter;

public class Circle implements Component {
    private float x,y,r;

    public Circle(float _x, float _y, float _r)
    {
        x=_x; y=_y; r=_r;
        System.out.println("Circle: x:"+x+" y:"+y+" r:"+r);
    }

    public void write(Writer output,int indent) throws IOException 
    {
        BuffWriter.addNewLine(output,"<circle cx='" + getCenterX() + "' cy='" + getCenterY() + "' r='" + getRadius() + "' stroke='black' fill='black' />",indent);
    }

    public float getCenterX(){return x;}
    public float getCenterY(){return y;}
    public float getRadius(){return r;}

    public void translate(float dx,float dy){x+=dx;y+=dy;}
    public void flipHorizontal(float axis){y=flip(y,axis);}
    public void flipVertical(float axis){x=flip(x,axis);}
}
