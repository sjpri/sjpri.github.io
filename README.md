# **Overview**

This repository documents my procedures for developing my ePortfolio as the CS-499 Computer Science Capstone course final project to showcases my unique abilities and talents as one of the best visual communication tools to demonstrate my value to potential employers. The content of the ePortfolio is a solid starting point to clear ideas that showcase my skills across the key fields of Computer Science. The included artifact was previously developed in the Computer Science Program at Southern New Hampshire University and it represents my growth in the key categories of software design/engineering, algorithms and data structures, and databases.

## **Professional Self-Assessement**

I enrolled for my Computer Science degree in October of 2018, my goal was to be able to complete all the required courses in four years, so I have been working hard, only taking a single term off, and as a result, I am happy to say I will be done with my courses in October 2023. The program has been incredibly challenging for a wide number of reasons, including time management, learning, and understanding the different subjects every two months have kept me in my toes, and taught me to learn to be comfortable being uncomfortable. With every new course, a new challenge arises, it felt like I was missing something, as I was not following what a lot of the courses were referring to in the first few weeks, and that taught me how to research different topics and take charge of my own learning, by diversifying my resources and being open minded about problem solving. I decided to pursue my bachelor’s degree in computer science later in life when compared to the average person, and this is my second attempt in pursuing higher education. The first time was around fourteen years ago, I enrolled in a Community College looking to get an associate degree in software development. After my first semester in school, I found out I was pregnant and I could not afford school and a new baby, so I gave up going to school. 

Before I started school, I made a list of goals for myself, that included getting in the technology industry after my freshman year, where I could have the opportunity to grow more technical and after I graduated, I could transfer to the development team, or I could find a position within a different company that would allow me to work in the field. I am currently employed as a Technical Service Engineer at a security camera manufacturer, which is somewhat related to my computer science degree, but not very relevant with wit software development at all. Before I started school, I traced goals for the upcoming years that would lead me to eventually being able to pursue a career as a Software Engineer, I was working in the construction industry, that seemed very distant from my ultimate professional goals. Four years have gone by, and I am happy to say that I have been able to accomplish the steps I have set out to myself, with the approaching completion of my degree, a new opportunity presented itself at a different department at the company that currently employs me, a brand-new Junior development position with our in-house development team with a very diverse job description. I am glad to see that my hard work and dedication is paying off. I was able to enter the security industry as a Technical Support Representative, which is a non-technical position, I was given the ability to grow within the company and transition to a more technically inclined position before being promoted to an engineering position. Just six months prior to me finishing up all the courses required for my bachelor’s degree I was able to land a fantastic new opportunity with the solutions development team within the company I work, that will offer plenty of challenges and growth. As a testament to my successful progress, I was awarded the [2023 Excellence in Customer Service Award](https://www.axis.com/en-us/newsroom/news/2023-excellence-in-customer-service-award), I was nominated my superiors and feel like I have progressing well within my plans.


## **Code Review**
 
For the Software Engineering/Design category, I intend on using the Zoo Monitoring System project I completed in Foundation in Application Development (IT 145). The project will display the fundamentals of object-oriented programming for software development with the implementation of appropriate variables, operators, methods, classes, and appropriate syntax. My original program does not match the pseudocode below, that shows two classes, but the program shows three. I decided to add a class for the main menu, because it made testing the animal and habitat classes easier, without having to type a great deal of code. I plan on writing the code in C++, mainly because it is a language I have been experiencing most recently.

Class Monitoring System
  
Function main:

    CALL habitat
    
    CALL animal
    
    CALL exit
    
    
Function habitat:

    PROMPT user for habitat choice

    READ user input
    
    OPEN animal file
    
    WHILE not at end of file
    
        DISPLAY animal details
	
        IF abnormal detected
	
            DISPLAY warning dialog
	    
        ENDIF
	
    ENDWHILE
    
    WHILE user select return to original menu
    
        CONNECT to the original menu
        
	
Function animal:

    PROMPT user for animal choice
    
    READ user input
    
    OPEN animal file
    
    WHILE not at end of file
    
        DISPLAY animal detail
	
            IF abnormal detected

                DISPLAY warning dialog	

            ENDIF
    
    ENDWHILE
    
    WHILE user select return to original menu
        
	CONNECT to the original menu
        
Function exit:

I intend on continue improving the Zoo Monitoring System from the Foundation in Application Development by using data structure as a building tool to handle data efficiently. The program requires inserting, updating, deleting data, while keeping it organized, managing data by utilizing Vectors, Hash Tables, Tree Structures to later be used to search for specific items. 

Class Monitoring System

Function main:

    CALL habitat
    
    CALL animal
    
    CALL exit
    
Function habitat:
    
    PROMPT user for habitat choice
    
    PROMPT user to add habitat
    
    PROMPT user to delete existing habitat
    
    READ user input
    
    OPEN animal file
    
    WHILE not at end of file
        
	DISPLAY animal details
            
	    IF abnormal detected

                DISPLAY warning dialog
            
	    ENDIF
    
    ENDWHILE
    
    WHILE user select return to original menu
        
	CONNECT to the original menu
    
    WHILE user selects ADD or REMOVE habitat
	        
        IF add habitat
            
	    PROMPT user for habitat name
            
	    CREATE new habitat in database	

        ENDIF

        IF remove habitat

            PROMPT user for habitat name

            REMOVE habitat from database

        ENDIF
    
    ENDWHILE
    
Function animal:

    PROMPT user for animal choice, add or remove animal
    
    READ user input
    
    OPEN animal file
    
    WHILE not at end of file

        DISPLAY animal detail
            
	    IF abnormal detected

                DISPLAY warning dialog	

            ENDIF
    
    ENDWHILE
    
    WHILE user input is add or remove

        IF add animal

            PROMPT user for animal details

            CREATE new entry for animal

        ENDIF

        IF remove animal

            PROMPT user for animal name to be removed

            REMOVE entry for animal

        ENDIF

    ENDWHILE
    
    WHILE user select return to original menu

        CONNECT to the original menu

The Zoo Monitoring System from the Foundation in Application Development is the perfect opportunity to introduce the skills I developed in the Introduction to SQL course, by creating datasets triggered by the program to INSERT INTO, SHOW, and DELETE rows from the table. With the implementation of a proper database, the processing query is faster and more efficient, high portable, with multiple data views, that is scalable as the business grows. I am not expectin my program to be perfect, but if all of the enhancements are fulfilled the program will demonstrate my ability to problem solve while using the skills developed during the previous courses. The courses were a great introduction to the different subjects, the biggest challenge I can oversee is the fact that it has been a while since I have taken the couses, I am pretty confident I will need to revisit both my files and do additional research to accomplish the outcome I am looking for. My biggest concern at the moment includes questioning whether the proposed changes are enough to meet the crieterias set out for the final project. 

### **Enhancement One: Software Design and Engineering**
