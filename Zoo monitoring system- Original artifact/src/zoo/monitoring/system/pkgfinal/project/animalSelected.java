
package zoo.monitoring.system.pkgfinal.project;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;
import javax.swing.JOptionPane;

/**
 *
 * @author Priscilla
 */
public class animalSelected {
    public static void animalSelected() throws FileNotFoundException   {
        Scanner scnr = new Scanner(System.in);
        Scanner animalOfChoice = new Scanner(new FileInputStream("animalfile.txt"));
        String currentLine = null;
        
        //Initialize user input for animal selection
        String animalSelection = scnr.nextLine();

        //Read file till the end
        while (animalOfChoice.hasNextLine())   {
            currentLine = animalOfChoice.nextLine();
            //If file matcches user input
            if(currentLine.contains(animalSelection))   {
                System.out.println(currentLine);
                
                //Call out strings for name, age, health and feeding
                String name = animalOfChoice.nextLine();
                String age = animalOfChoice.nextLine();
                String health = animalOfChoice.nextLine();
                String feeding = animalOfChoice.nextLine();
                
                System.out.println(name);
                System.out.println(age);               
                
                //Remove "*" from string and add alert to dialog box
                if (health.contains("*****"))  {
                    health = health.replace("*****", "");
                    JOptionPane.showMessageDialog(null, health, "ALERT", JOptionPane.ERROR_MESSAGE);
                }
                else   {
                    System.out.println(health);
                }
                
                if (feeding.contains("*****"))   {
                    feeding = feeding.replace("*****", "");
                    JOptionPane.showMessageDialog(null, feeding, "ALERT", JOptionPane.ERROR_MESSAGE);
                }
                else   {
                    System.out.println(feeding);
                }
                
                System.out.println();
                
            }
            
        }
        
    }
    
}
