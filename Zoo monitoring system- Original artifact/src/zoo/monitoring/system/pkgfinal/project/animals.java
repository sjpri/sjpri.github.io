package zoo.monitoring.system.pkgfinal.project;

/**
 *
 * @author Priscilla
 */
import java.io.*;
import java.util.Scanner;

public class animals {

    public static void animals() throws FileNotFoundException {
        int lineNum = 1;
        String animalSelection = null;
        String currentLine = null;

        //Initialize user and file scanner
        Scanner scnr = new Scanner(System.in);
        Scanner animalScnr = new Scanner(new FileInputStream("animalfile.txt"));   

        //Read file till the end
        while (animalScnr.hasNextLine()) {
            currentLine = animalScnr.nextLine();
            if (currentLine.contains("Details on")) {
                System.out.println(lineNum + ". " + currentLine);
                lineNum++;
            }
        } 

    }
}
