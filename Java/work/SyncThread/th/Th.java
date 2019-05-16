package th;

import th.*;

public class Th implements Runnable 
{
    Complex z = new Complex();
    Boolean b = new Boolean(true);

    public void run ()
    {
        while(true)
        {
            if (b) z.set(0,5); else z.set(5,0);
        }
    }
    
    public Th(Complex _z, Boolean _b)
    {
        z=_z;
        b=_b;
        new Thread(this).start();
    }
}