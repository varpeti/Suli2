import th.*;

public class Main {

	public static void main(String[] args) {
		Complex z = new Complex() ;

		new Th(z,true );
        new Th(z,false);
		while (true)
		{
			double[] x = z.get() ;
			if (x[0] != 0 && x[1] != 0)
			{
				System.out.println("Hibát találtunk: " + x[0] + " " + x[1]);
			}
		}
	}

}
