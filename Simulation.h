/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment#4: Registrar's Office Simulation
*/
#include "GenQueue.h"
#include "Window.h"
#include "FileProcessor.h"
#include <string> //helps converting string to ints with stoi()

class Simulation{
  public:
    Simulation();
    ~Simulation();
    void RunSimulation(string FileName);

  private:
    //setup Simulation
    void SetUp();
    //open reader
    bool OpenReader(string FileName);
    //assign variables
    void WindowSetUp();
    void StudentSetUp();
    //running simulation and collecting info
    //SIMULATION LOOP CONTAINS ALL LOOPS
    void StartSim();

    //loop 1: check if any students are suppose to leave window and reopen the window
    bool CheckStudentLeaving();

    //loop 2: until windows are occupied or no more students
    bool CheckArrivalTime(); //check is next student arrives at current time
    bool CheckWindowOpen(); //check if there are any windows available
    Window* GetOpenWindow(); //looks for an open window the student can take
    void StudentOccupyWindow(); //student will occupy open window and have their waittime recorded

    //loop 3: incrementing all the idle times and last boolean check
    void AddToIdleTime(); //if there are idle windows
    bool CheckIfSimOver(); //check if the student queue is empty and the windows are unoccupied

    //math calculations
    void ResultsCheck();
    void MathCalc();
    int* SetUpWaitTimes();
    int* SetUpIdleTimes();
    double GetMean(int* array, int length);
    double GetMedian(int* array, int length);
    int GetLongest(int* array, int length);
    void GetStudentsWaitingOver10(int*array);
    void GetWindowsIdleOver5();
    //print out all calculations
    void PrintResults();


    string FileName;
    int CurrentTime;
    int NumOfWindows;
    int TotalStudents;
    int TotalStudentsWaiting;
    int TotalWindowsIdling;

    double WaitTimeMean;
    double WaitTimeMedian;
    int LongestWaitTime;
    int StudentsWaitingOver10Minutes;
    double IdleTimeMean;
    int LongestIdleTime;
    int WindowsIdleOver5Minutes;

    FileProcessor *myFiles;
    //queue the students will wait in
    GenQueue<Student*> *myQueue;
    //keeps track of all the students that leave and their wait times
    GenQueue<Student*> *finishedQueue;
    //array with all the windows
    Window **WindowArray;

};
