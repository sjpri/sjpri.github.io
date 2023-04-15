
package zoo.monitoring.system.pkgfinal.project;
import java.io.FileNotFoundException;
import java.util.Scanner;
import static zoo.monitoring.system.pkgfinal.project.animalSelected.animalSelected;

/**
 *
 * @author Priscilla
 */
import static zoo.monitoring.system.pkgfinal.project.animals.animals;
import static zoo.monitoring.system.pkgfinal.project.habitat.habitat;
import static zoo.monitoring.system.pkgfinal.project.habitatSelected.habitatSelected;
public class MainMenu {
    
    
    public static void MainMenu() throws FileNotFoundException   {
        
        //Display main menu
        System.out.println("WELCOME TO NATIONAL ZOO");
        System.out.println("Please enter your selection: ");
        System.out.println();
        System.out.println("0- To exit the program.");
        System.out.println("1- To monitor animals");
        System.out.println("2- To monitor habitats");
        
       
        
        //Initialize scanner and variable for user input
        Scanner scnr = new Scanner(System.in);
        int userIn = 0;
        
        //request user input
         userIn = scnr.nextInt();
        
         
        switch (userIn)   {
            //If user selects "0", program will exit
            case 0:
                System.out.println("Shutting down monitoring program.");
                break;
                
            //If user selects "1" program will access available animals    
            case 1:
                System.out.println("Initializing animals monitor...");
                animals();
                animalSelected();
                MainMenu();
                break;
                
            //If user selects "2" program will access avaialble habitats    
            case 2:
                System.out.println("Initializing habitat monitor...");
                habitat();
                habitatSelected();
                MainMenu();
                break;
                
            //If selection does not match available options, user will receive an error message    
            default:
                System.out.println("ERROR: Please make a valid selection");
                System.out.println();
                MainMenu();
        }
        
    }
}
