package vp.svg.picture.components;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.Writer;

public interface Component {
    public void write(Writer output,int indent) throws IOException;
    public void translate(float dx, float dy);
    public void flipHorizontal(float axis);
    public void flipVertical(float axis);

    default public float flip(float a, float da)
    {
        return (a>da) ? a+2*(da-a) : a-2*(a-da);
    }

}