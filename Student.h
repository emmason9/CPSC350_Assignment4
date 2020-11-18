/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment#4: Registrar's Office Simulation
*/
class Student{
  public:
    int TimeArrived;
    int TimeRequired;
    int WaitTime;
    int TimeHelpped;

    int StudentKey; //help with comparing students to each other

    Student();
    Student(int timeArrived, int timeRequired, int key);
    ~Student();

    void SetTimeHelpped();
    void SetWaitTime();
    void PrintStudent();

    bool operator==(Student otherStud);
    bool operator!=(Student otherStud);
};
