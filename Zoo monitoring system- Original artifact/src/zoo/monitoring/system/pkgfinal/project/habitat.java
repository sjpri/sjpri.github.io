
package zoo.monitoring.system.pkgfinal.project;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 *
 * @author Priscilla
 */
public class habitat {
    public static void habitat() throws FileNotFoundException   {
        int lineNum = 1;
        String habitatSelection = null;
        String currentLine = null;
        
        //Initialize user and file scanner
        Scanner scnr = new Scanner(System.in);
        Scanner habitatScnr = new Scanner(new FileInputStream("habitatfile.txt"));
        
        //Read file till the end
        while (habitatScnr.hasNextLine())   {
            currentLine = habitatScnr.nextLine();
            //If "Details" included in line
            if (currentLine.contains("Details on"))   {
                System.out.println(lineNum + ". " + currentLine);
                lineNum ++;
            }
        }
    }
}
