/**
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
package hu.ppke.itk.java.second.string;

/**
 * This class test the performance of {@link String#concat(String)} method.
 */
public class ConcatString1 {

	/**
	 * Run to test.
	 * 
	 * @param args
	 *            number of test to run
	 */
	public static void main(String[] args) {

		long avg = 0;
		int iter = (args.length > 0) ? Integer.parseInt(args[0]) : 10;
		for (int i = 0; i < iter; i++) {
			long a = System.currentTimeMillis();
			String s = "[";

			for (int j = 1; j <= 10000; j++) {
				if (j > 1)
					s = s.concat(",");
				s = s.concat(Integer.toString(j, 10));
			}
			s = s.concat("]");

			long time = System.currentTimeMillis() - a;
			System.out.print(time);
			System.out.print(",");
			avg += time;
		}
		System.out.println("avg: " + (avg / iter));
	}
}
