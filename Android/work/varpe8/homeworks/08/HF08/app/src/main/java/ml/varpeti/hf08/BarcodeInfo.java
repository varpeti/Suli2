package ml.varpeti.hf08;

import java.util.Date;

public class BarcodeInfo
{
    String rawValue;
    int format;
    int type;
    Date date;

    public BarcodeInfo(String rawValue, int format, int type, Date date)
    {
        this.rawValue=rawValue;
        this.format=format;
        this.type=type;
        this.date=date;
    }

    public BarcodeInfo()
    {
        // Firebasenek kell
    }

}
