/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment#4: Registrar's Office Simulation
*/
#include "Student.h"
#include <iostream>
using namespace std;

class Window{
  public:
    bool isOccupied;
    int WindowKey;
    Student *currentStudent;

    Window(int key);
    ~Window();

    void IncrementIdleTime();
    int GetIdleTime();
    void SetCurrentStudent(Student* newStudent);
    Student* GetCurrentStudent();
    void SetTimeStudentLeaves(int TimeLeaves);
    int GetTimeStudentLeaves();
    void ClearTimeStudentLeaves();
    void PrintWindow();

    bool operator==(Window otherWindow);
    bool operator!=(Window otherWindow);

  private:
    int TotalIdleTime;
    int TimeStudentLeaves;

};
