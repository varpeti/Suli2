package hu.ppke.itk.java.second.assertion;

import java.util.Scanner;

/**
 * Assert példaprogram. Feltételezzük, hogy a bemenetre egy integer-t kapunk,
 * egy bizonyos tartományon belül (0-10). Ha ezen kívül kapunk valamit, akkor
 * kivétel váltódik ki. Ne felejtsük el a Run Configuration-t beállítani!
 * 
 * @author xtry
 * 
 */
public class AssertionSample {
	public static void main(String[] args) {
		// beolvasunk a billentyűzetről
		Scanner input = new Scanner(System.in);

		System.out.println("Adj meg egy számot 0 és 10 között: ");
		// feltételezzük, hogy integerrel lesz dolgun
		int number = input.nextInt();

		// megköveteljük, hogy mikor lesz jó a number-ünk:
		// ha nem 0-10 között adunk meg egész számot, akkor kivétel váltódik ki
		assert (number >= 0 && number <= 10) : "rossz szám: " + number + "! A számnak 0-10 között KELL lennie!";

		System.out.printf("Az általad megadott szám: %d\n", number);

		input.close();
	}

}
