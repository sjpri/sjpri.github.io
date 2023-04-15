
package zoo.monitoring.system.pkgfinal.project;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;
import javax.swing.JOptionPane;

/**
 *
 * @author Priscilla
 */
public class habitatSelected {
    public static void habitatSelected() throws FileNotFoundException   {
        Scanner scnr = new Scanner(System.in);
        Scanner habitatOfChoice = new Scanner(new FileInputStream("habitatfile.txt"));
        String currentLine = null;
        
        //Initialize a scanner for user Input
        String habitatSelection = scnr.nextLine();
        
        while (habitatOfChoice.hasNextLine())   {
            currentLine = habitatOfChoice.nextLine();
            //If file matcches user input
            if (currentLine.contains(habitatSelection))   {
                System.out.println(currentLine);
                
                //Call out strings for name, age, health and feeding
                String temp = habitatOfChoice.nextLine();
                String food = habitatOfChoice.nextLine();
                String clean = habitatOfChoice.nextLine();
                
                System.out.println(temp);
                
                //Remove "*" from string and add alert to dialog box
                if (food.contains("*****"))   {
                    food = food.replace("*****", "");
                    JOptionPane.showMessageDialog(null, food, "ALERT", JOptionPane.ERROR_MESSAGE);
                }
                else   {
                    System.out.println(food);
                }
                
                if (clean.contains("*****"))   {
                    clean = clean.replace("*****", "");
                    JOptionPane.showMessageDialog(null, clean, "ALERT", JOptionPane.ERROR_MESSAGE);
                }
                else   {
                    System.out.println(clean);
                }
                System.out.println();
            }
        }
    }
    
}
