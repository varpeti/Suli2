package th;

public class Complex 
{
    private double re;
    private double im;

    public synchronized void set(double re, double im) 
    {   
        System.out.print("Begin "+re);
        this.re = re;
        try{Thread.sleep(1000);}catch (Exception e) {}
        this.im = im;
        System.out.println("End "+re);
    }
    
    public double[] get() 
    {
        double[] result = {re, im};
        return result;
    }
}