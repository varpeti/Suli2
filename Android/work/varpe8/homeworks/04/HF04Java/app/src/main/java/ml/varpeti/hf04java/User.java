package ml.varpeti.hf04java;

public class User
{
    String name;
    String email;
    String description;

    public User(String name, String email, String description)
    {
        this.name=name;
        this.email=email;
        this.description=description;
    }

    public User()
    {
        // Firebasenek kell
    }

}
