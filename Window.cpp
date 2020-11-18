/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment#4: Registrar's Office Simulation
*/
#include "Window.h"

Window :: Window(int key){
  isOccupied = false;
  TimeStudentLeaves = -1;
  TotalIdleTime = 0;
  TimeStudentLeaves = -1;
  WindowKey = key;
}

Window :: ~Window(){
  //nothing to delete...
}

void Window :: IncrementIdleTime(){
  TotalIdleTime++;
}

int Window :: GetIdleTime(){
  return TotalIdleTime;
}

void Window :: SetCurrentStudent(Student* newStudent){
  currentStudent = newStudent;
}

Student* Window :: GetCurrentStudent(){
  return currentStudent;
}

void Window :: SetTimeStudentLeaves(int TimeLeaves){
  TimeStudentLeaves = TimeLeaves;
}

int Window :: GetTimeStudentLeaves(){
  return TimeStudentLeaves;
}

void Window :: ClearTimeStudentLeaves(){
  TimeStudentLeaves = -1;
}

void Window :: PrintWindow(){
  cout<<"isOccupied: "<<isOccupied<<endl;
  cout<<"TotalIdleTime: "<<TotalIdleTime<<endl;
  cout<<"window key: "<<WindowKey<<endl;
}

bool Window :: operator==(Window otherWindow){
  return (WindowKey == otherWindow.WindowKey);
}

bool Window :: operator!=(Window otherWindow){
  return (WindowKey != otherWindow.WindowKey);
}
