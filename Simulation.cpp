/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment#4: Registrar's Office Simulation
*/
#include "Simulation.h"

Simulation :: Simulation(){
  myQueue = new GenQueue<Student*>();
  finishedQueue = new GenQueue<Student*>();
  myFiles = new FileProcessor();
  CurrentTime = -1; //so time will start at 0 for the first number.
  TotalStudents = 0;
  TotalStudentsWaiting = 0;
}

Simulation :: ~Simulation(){
  delete myQueue;
  delete finishedQueue;
  delete myFiles;
  delete WindowArray;
}

//runs the entire simulation
void Simulation :: RunSimulation(string FileName){
  if(!OpenReader(FileName)){
    cout<<"File could not be openned.\nTry again with a different file name."<<endl;
  } else {
    SetUp();
    StartSim();
    //calculate the results
    MathCalc();
    //prints results
    PrintResults();
  }//end of reader ifelse
}//end of run sim

//calls the window and student set up methods
void Simulation :: SetUp(){
  WindowSetUp();
  StudentSetUp();
}
//opens the reader file given the right file name
bool Simulation :: OpenReader(string FileName){
  return myFiles->OpenReaderFile(FileName);
}

//sets up the windows in the window array given the first int of the file
void Simulation :: WindowSetUp(){
  //getting the windows open from the file
  string WindowsOpenString;
  getline(myFiles->Reader, WindowsOpenString);
  NumOfWindows = stoi(WindowsOpenString);
  //setting up the array with the right amount of windows
  WindowArray = new Window*[NumOfWindows];
  Window *tempWindow;
  for(int i=0; i<NumOfWindows; ++i){
    WindowArray[i] = new Window(i+1);
  }
}

//sets up the students in the queue given the rest of the file
void Simulation :: StudentSetUp(){
  string nextLine;
  int arrivalTime;
  string studentString;
  int numOfStudents;
  string timeNeededString;
  int timeNeededInt;
  Student *newStudent;
  int currentStudentKey = 0;
  //this should grab every arrival time of groups of students
  while(getline(myFiles->Reader, nextLine)){
    arrivalTime = stoi(nextLine);
    //grabbing the number of students that show up
    getline(myFiles->Reader, studentString);
    numOfStudents = stoi(studentString);
    TotalStudents += numOfStudents;
    //iterating to create the two students that show up at this arrival time
    for(int i=0; i<numOfStudents; ++i){
      currentStudentKey++;
      //grabbing the time needed for the student
      getline(myFiles->Reader, timeNeededString);
      timeNeededInt = stoi(timeNeededString);
      //creating the student
      newStudent = new Student(arrivalTime, timeNeededInt, currentStudentKey);
      //adding to the queue/line
      myQueue->Enqueue(newStudent);
    }//end of forloop
  }
}

//starts the actual simulation while keeping track of results
void Simulation :: StartSim(){
  //once the last student is helpped, the sim will be over
  Student *currentStudent;
  Window *currentWindow;
  bool simDone = false;
  int windowCount = 0;
  //should be over when studentebing helpped empty and queueu empty
  while(!simDone){
    CurrentTime++;
    //doing idle time first because the windows with a leaving student shouldn't add to to their idle time
    //need to make an ifstatement for if it's the first round....
    if(CurrentTime != 0){
      AddToIdleTime();
    }
    //first checking if there is a student leaving an occupied window
    CheckStudentLeaving();
    //checking if there is a student that has walked up and if there is a window open for them, then they can take it
    while(CheckArrivalTime() && CheckWindowOpen()){
      StudentOccupyWindow();
    }
    //checks if the queue is empty and the windows are all unoccupied
    simDone = CheckIfSimOver();
  }//end of sim while loop
}//end of start sim function

//given current time, check all windows to see if a student is supppose to be leaving
bool Simulation :: CheckStudentLeaving(){
  for(int i=0; i<NumOfWindows; ++i){
    //if they current time is the same as the time the student is suppose to leave the window...
    if(CurrentTime == WindowArray[i]->GetTimeStudentLeaves()){
      //window is openned and the student's waittime is calculated (if they had to wait)
      WindowArray[i]->isOccupied = false;
      WindowArray[i]->SetTimeStudentLeaves(-1);
      WindowArray[i]->GetCurrentStudent()->SetWaitTime();
      //adding to the total number of students waiting for the mean calculation
      if(WindowArray[i]->GetCurrentStudent()->WaitTime != 0){
        TotalStudentsWaiting++;
      }
      //want to save the student's info, so we requeue them into a different queue
      finishedQueue->Enqueue(WindowArray[i]->GetCurrentStudent());
    }//end of if
  }//end of for loop
}

//checks if the current time is a time a student arrives
bool Simulation :: CheckArrivalTime(){
  if(myQueue->isEmpty()){
    return false;
  }
  return (CurrentTime >= myQueue->Peek()->TimeArrived);
}

//checks if there are any unoccupied windows
bool Simulation :: CheckWindowOpen(){
  for(int i=0; i<NumOfWindows; ++i){
    if(!WindowArray[i]->isOccupied){
      return true;
    }
  }
  return false;
}

//retrieves open window for student to go into
Window* Simulation :: GetOpenWindow(){
  for(int i=0; i<NumOfWindows; ++i){
    if(!WindowArray[i]->isOccupied){
      return WindowArray[i];
    }
  }
}

//student occupies an open window
void Simulation :: StudentOccupyWindow(){
  Window *currentWindow = GetOpenWindow();
  Student *currStud = myQueue->Dequeue();
  currStud->TimeHelpped = CurrentTime;
  currentWindow->isOccupied = true;
  currentWindow->SetCurrentStudent(currStud);
  currentWindow->SetTimeStudentLeaves(CurrentTime + currStud->TimeRequired);
}

void Simulation :: AddToIdleTime(){
  for(int i=0; i<NumOfWindows; ++i){
    if(!WindowArray[i]->isOccupied){
      WindowArray[i]->IncrementIdleTime();
    }
  }
}

bool Simulation :: CheckIfSimOver(){
  if(myQueue->isEmpty()){
    for(int i=0; i<NumOfWindows; ++i){
      if(WindowArray[i]->isOccupied){
        return false;
      } //end of window if
    }//end of for loop
  } else { //end of is empty
    return false;
  }
  return true;
}

void Simulation :: MathCalc(){
  int *waitTimes = SetUpWaitTimes();
  int *idleTimes = SetUpIdleTimes();
  //the wait time array requires total students, but will only account for the ones that waited
  WaitTimeMean = GetMean(waitTimes, TotalStudents);
  IdleTimeMean = GetMean(idleTimes, TotalWindowsIdling);
  //median will need all the students, not just the waiting students
  WaitTimeMedian = GetMedian(waitTimes, TotalStudentsWaiting);
  LongestWaitTime = GetLongest(waitTimes, TotalStudents);
  LongestIdleTime = GetLongest(idleTimes, TotalWindowsIdling);
  GetStudentsWaitingOver10(waitTimes);
  GetWindowsIdleOver5();
}

//sets up an array that will hold the wait times of all the students, including the ones who didn't wait
int* Simulation :: SetUpWaitTimes(){
  int *waitTimes = new int[TotalStudents];
  Student *currStudent;
  int count = 0;
  bool isEmptyBool = false;
  while(!isEmptyBool){
    currStudent = finishedQueue->Dequeue();
    isEmptyBool = finishedQueue->isEmpty();
    waitTimes[count] = currStudent->WaitTime;
    count++;
  }
  return waitTimes;
}

//sets up an array for all the idle times of the windows
int* Simulation :: SetUpIdleTimes(){
  //getting total number of windows idling first.
  for(int i=0; i<NumOfWindows; ++i){
    if(WindowArray[i]->GetIdleTime() != 0){
      TotalWindowsIdling++;
    }
  }
  //setting up array
  int *idleTimes = new int[NumOfWindows];
  for(int j=0; j<NumOfWindows; ++j){
    idleTimes[j] = WindowArray[j]->GetIdleTime();
  }
  return idleTimes;
}

//returns the mean given an array of ints and the length of the array
double Simulation :: GetMean(int* array, int length){
  if(length == 0){
    //this means there was no idle windows, so there would be no idle mean...
    return 0;
  }
  int totalSum = 0;
  int newLength = 0;
  for(int i=0; i<length; ++i){
    if(array[i] != 0){
      totalSum += array[i];
      newLength++;
    }
    if(newLength == 0){
      //this is a double check just in case there is still a length, but the new one shows that there wasn't
      return 0;
    }
  }
  return ((double)totalSum/(double)newLength);
}

//returns the median given an array and the length of the array
double Simulation :: GetMedian(int* array, int length){
  double medianDouble;
  int midPoint = length/2;
  if(length%2 == 0){ //even length
    medianDouble = ((array[midPoint] + array[midPoint+1]) / 2.0);
  } else {//odd length
    medianDouble = array[midPoint+1];
  }
  return medianDouble;
}

//find the longest given time within an array and returns it
int Simulation :: GetLongest(int* array, int length){
  int currentLongest = 0;
  for(int i=0; i<length; ++i){
    if(array[i] > currentLongest){
      currentLongest = array[i];
    }
  }
  return currentLongest;
}

//looks through the students and find how many waited 10 or more minutes long
void Simulation :: GetStudentsWaitingOver10(int* array){
  for(int i=0; i<TotalStudents; ++i){
    if(array[i] >= 10){
      StudentsWaitingOver10Minutes++;
    }
  }
}
//looks through the windows and find how many were idle for 5 minutes or longer
void Simulation :: GetWindowsIdleOver5(){
  for(int i=0; i<NumOfWindows; i++){
    if(WindowArray[i]->GetIdleTime() >= 5){
      WindowsIdleOver5Minutes++;
    }
  }

}
//prints out all the results of the calculations
void Simulation :: PrintResults(){
  cout<<"Mean Student Wait Time: "<<WaitTimeMean<<endl;
  cout<<"Median Student Wait Time: "<<WaitTimeMedian<<endl;
  cout<<"Longest Student Wait Time: "<<LongestWaitTime<<endl;
  cout<<"Number of Students Waiting Over 10 Minutes: "<<StudentsWaitingOver10Minutes<<endl;
  cout<<"Mean Window Idle Time: "<<IdleTimeMean<<endl;
  cout<<"Longest Window Idle Time: "<<LongestIdleTime<<endl;
  cout<<"Number of Windows Idle For Over 5 Minutes: "<<WindowsIdleOver5Minutes<<endl;
}
