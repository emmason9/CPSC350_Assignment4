# CPSC350_Assignment4
Assignment 4 - Registrar's Office Simulation

1. IDENTIFYING INFORMATION
a. Full Name: Emilee Mason
b. Student ID: 2321064
c. Chapman Email: emmason@chapman.edu
d. Course Number and Section: CPSC 350-01
e. Assignment or Excercise Number: Assignment 4: Registrar Office Simulation 

2. A LIST OF ALL SOURCE FILED SUBMITTED FOR THIS ASSIGNMENT
CPSC350_Assignment4.zip
	DoubleLinkedList.h	//the double linked list template file
	FileProcessor.cpp	//reads, writes, and appends to files
	FileProcessor.h
	GenQueue.h		//the generic queue template file
	ListADT.h		//the double linked list interface file
	ListNode.h		//the list node template file for the double linked list objects
	main.cpp		//main method that runs the program
	MakeFile		//creates an executable file for the user to run
	README			//this :)
	Simulation.cpp		//the simulation file that puts all the objects together
	Simluation.h		
	Student.cpp		//the student object file that holds all the students information
	Student.h
	Window.cpp		//the window object file that holds all the windows information
	Window.h
	


3. A DESCRIPTION OF ANY KNOWN COMPILE OR RUNTIME ERRORS, CODE LIMITATIONS, OR DEVATIONS FROM ASSIGNMENT SPECIFICATIONS (IF APPLICABLE)
There shouldn't be any outstanding errors that I know of. If you don't have the right text file name, the program
immediately will tell you and not do anything, just as an FYI if you keep getting the "can't read your file, Try
again" message. 

4. A LIST OF ALL REFERENCES USED TO COMPLETE THE ASSIGNMENT, INCLUDING PEERS (IF APPLICABLE)
Natalie Ewing helpped me a lot with setting up the template classes, I was struggling a 
lot to get all the right things together for the template classes for some reason for 
this project. Also, the way the ListADT and the way I handle the Student operators ideas
came from her, the operators were giving me a SUPER hard time for whatever reason. 

I had to use some of the zybook to figure out what issues I was having with the double
linked lists insert and remove functions.


5. INSTRUCTIONS FOR RUNNING THE ASSIGNMENT
	1) Unzip the file you recieve from GitHub
	2) Make sure you place the file that you want to be read into the same folder
		ex. (TextFile.txt)
	3) Place the folder in a docker accessable location
	4) go to the folder through your computers terminal/powershell/etc.
		docker start [container]
		docker attach [container] etc...
	5) once you're in the folder, you can input
		"make all" (this creates the executable file)
	6) to run the file, you can input 
		"./Assignment4 [fileName.txt] (where fileName is the text folder you want the program to read)
		The program will inform you whether or not the file input is readable or not. 
		If it is readable, it will perform the calculations and display them in the terminal.
	7) to clean the folder again, you can input 
		"make realclean" (this will delete the excess files .exe, .o, etc, from the folder)
