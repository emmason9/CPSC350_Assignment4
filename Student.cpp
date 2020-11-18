/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment#4: Registrar's Office Simulation
*/
#include "Student.h"
#include <cstddef>
#include <iostream>
using namespace std;

//default constructor
Student :: Student(){
  TimeArrived = -1;
  TimeRequired = -1;
  WaitTime = -1;
  TimeHelpped = -1;
  StudentKey = -1;
}

//overloaded constructor
Student :: Student(int arrival, int required, int key){
  TimeArrived = arrival;
  TimeRequired = required;
  WaitTime = 0;
  TimeHelpped = -1;
  StudentKey = key;
}

Student :: ~Student(){
  //nothing to delete...
}

void Student :: SetTimeHelpped(){
  TimeHelpped = TimeArrived + WaitTime;
}

void Student :: SetWaitTime(){
  WaitTime = TimeHelpped - TimeArrived;
}

void Student :: PrintStudent(){
  cout<<"Time Arrived: " << TimeArrived <<endl;
  cout<<"Time Required: " << TimeRequired <<endl;
  cout<<"Student Key: " << StudentKey <<endl;
  cout<<"Wait Time: "<<WaitTime<< endl;
}

//these are for comparing students amongst each other
bool Student :: operator==(Student otherStud){
  return(StudentKey == otherStud.StudentKey);
}

bool Student :: operator!=(Student otherStud){
  return(StudentKey != otherStud.StudentKey);
}
