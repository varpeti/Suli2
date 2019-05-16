package hu.ppke.itk.java.second.regex;

import java.util.Scanner;

public class SampleScanner {
	public static void main(String[] args){
	
	    String input = "1 fish 2 fish red fish blue fish";
	    
	    Scanner s = new Scanner(input);
	    s.useDelimiter("\\s*fish\\s*");
	    
	    System.out.println(s.nextInt());
	    System.out.println(s.nextInt());
	    System.out.println(s.next());
	    System.out.println(s.next());
	    
	    s.close();
	}
}
