package ml.varpeti.hf05;

public class Country
{
    //TODO private?
    // Ez nem egy "osztály" ez inkább egy típus, egy "struckt" (c) vagy "record" (tp)

    public String nameS;
    public String imgS;
    public float lat;
    public float lng;

    public String toString()
    {
        return "{"+nameS+", "+imgS+",["+lat+","+lng+"]"+"}";
    }
}
