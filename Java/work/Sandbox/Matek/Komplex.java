package Matek;

public class Komplex
{
    //Változók

    private double re;
    private double im;

    //Konstruktorok

    public Komplex()
    {
        this(0.0,0.0);
    }

    public Komplex(double _re, double _im)
    {
        this.re = _re;
        this.im = _im;
    }

    //Setter,Getter

    public double getRe() {
      return this.re;
    }

    public double getIm() {
      return this.im;
    }

    public void set(double _re, double _im)
    {
        this.re = _re;
        this.im = _im;
    }

    public void setRe(double _re)
    {
        this.re = _re;
    }

    public void setIm(double _im)
    {
        this.im = _im;
    }

    //Műveletek

    public static Komplex add(Komplex a, Komplex b) {
        return new Komplex(a.re + b.re, a.im + b.im);
    }

    public static Komplex sub(Komplex a, Komplex b) {
        return new Komplex(a.re - b.re, a.im - b.im);
    }

    //TODO: mul div

    //Print

    public String toString() {
        return "(" + this.re + ";" + this.im + ")";
    }
}