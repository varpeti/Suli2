package hu.ppke.itk.java.second.diskio;

import java.io.File;
import javax.swing.JFileChooser;

public class FileChooserDialog {
	public static void main(String[] args) {
		JFileChooser fileopen = new JFileChooser();
		// lehetséges paraméterek: JFileChooser.FILES_ONLY,
		// JFileChooser.DIRECTORIES_ONLY,
		// JFileChooser.FILES_AND_DIRECTORIES
		fileopen.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
		// A dialógusablak megnyitása. Visszatérési értékek:
		// JFileChooser.APPROVE_OPTION, ha a felhasználó kiválasztott egy
		// fájlt/könyvtárat,
		// JFileChooser.CANCEL_OPTION, ha a felhasználó nem választott.
		int ret = fileopen.showDialog(null, "Save"); // A második paraméter
														// jelenik meg a
														// dialógusablak
														// fejlécén és az
														// elfogadó gombon
		if (ret == JFileChooser.APPROVE_OPTION) {
			// A kiválasztott fájl lekérdezése
			File file = fileopen.getSelectedFile();
			// A kiválasztott fájl elérési útjának kiírása
			System.out.println(file);
		}
	}
}
