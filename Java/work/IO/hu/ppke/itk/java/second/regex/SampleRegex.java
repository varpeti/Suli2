package hu.ppke.itk.java.second.regex;

import hu.ppke.itk.java.second.io.ReadWrite;

import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Az előző SampleRegex fájlt felhasználva kell az itt hiányzó dolgokat megírni.
 * Kérjünk be adatot a billentyűzetről, az első feladatban használt függvényt felhasználva.
 * Először a keresési intervallumot, utána az ellenőrizendő szót kérjük be. 
 * @author xtry
 *
 */

public class SampleRegex {

    public static void main(String[] args) {

    	try {
    		System.out.println("Enter your regex: ");
            Pattern pattern = Pattern.compile(ReadWrite.readFromKeyboard());
			
            System.out.println("Enter input string to search: ");
            Matcher matcher = pattern.matcher(ReadWrite.readFromKeyboard());

            boolean found = false;
            while (matcher.find()) {
                System.out.printf("I found the text \"%s\" starting at " +
                   "index %d and ending at index %d.%n",
                    matcher.group(), matcher.start(), matcher.end());
                found = true;
            }
            if(!found){
                System.out.println("No match found.%n");
            }
        } catch (IOException e) {
			e.printStackTrace();
		}
    }
}
