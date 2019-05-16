package hu.ppke.itk.java.second.diskio;

import java.io.*;
import java.util.*;

/**
 * FileSpy osztály fájlok lekérdezhetőségének demonstrálására
 * @author zelgala
 *
 */
public class FileSpy {
  public static void main(String[] args) {
	String fajl = "data.txt";
	File f = new File(fajl);
	if (f.exists( )) {
		System.out.println("Name: " + f.getName( ));
		System.out.println("Absolute path: " + f.getAbsolutePath( ));
		if (f.canWrite()) 
			System.out.println(f.getName( ) + " is writable.");
		if (f.canRead()) 
			System.out.println(f.getName( ) + " is readable.");
		if (f.isFile( )) {
		  System.out.println(f.getName( ) + " is a file.");
		}
		else if (f.isDirectory( )) {
		  System.out.println(f.getName( ) + " is a directory.");
		}
		else {
		  System.out.println("What is this?");
		}
		if (f.isAbsolute( )) {
		  System.out.println(f.getPath( ) + " is an absolute path.");
		}
		else {
		  System.out.println(f.getPath( ) + " is not an absolute path.");
		}
		long lm = f.lastModified( );
		if (lm != 0) 
			System.out.println("Last Modified at " + new Date(lm));
		long length = f.length( );
		if (length != 0) {
		  System.out.println(f.getName( ) + " is " + length + " bytes long.");
		}
    } else {
    	System.out.println("I'm sorry. I can't find the file " + fajl);
    }
    
	String dir = "dir";
	File d = new File(dir);
	if(d.exists()){
		System.out.println(dir + "directory:");
		String[] files = d.list();
		for(String file : files){
			System.out.print(file+"; ");
		}
	}
	else System.out.println("The directory doesn't exists!");
  }
}


