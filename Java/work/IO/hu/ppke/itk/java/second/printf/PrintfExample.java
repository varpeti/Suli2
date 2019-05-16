/**
 * masodik_gyak
 * Copyright (C) 2007
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
package hu.ppke.itk.java.second.printf;

import java.util.*;

public class PrintfExample {

	public static void main(String[] args) {
		for (Locale l : Locale.getAvailableLocales()) {
			System.out.print(l.toString() + " ");
		}
		System.out.println("\n");

		Date date = new Date();
		Locale l = new Locale("hu","HU");
		System.out.println(l.getDisplayCountry());
		System.out.printf(l,"Az int: %5d\n", 100);
		System.out.printf(l,"Egyik double: %.12f\n", Math.PI);
		System.out.printf(l,"Másik double: %.2e\n", 0.0001121);
		System.out.printf(l,"%4$2s %3$2s %2$2s %1$2s", "a", "b", "c", "d");
		System.out.printf(l,"\nHelyi idő: %tT", Calendar.getInstance());
		System.out.printf(l,"\nDátum: %1$tY. %1$tB %1$td. %1$tA\n\n", date);
		
		l = new Locale("en_US","US");
		System.out.println(l.getDisplayCountry());
		System.out.printf(l,"A double: %.12f\n", Math.PI);
		System.out.printf(l,"Date: %1$tY. %1$tB %1$td. %1$tA\n\n", date);
		
		l = new Locale("fr","FR");
		System.out.println(l.getDisplayCountry());
		System.out.printf(l,"Un double: %.12f\n", Math.PI);	
		System.out.printf(l,"Date: %1$tY. %1$tB %1$td. %1$tA", date);
	}
}
