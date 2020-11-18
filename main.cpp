/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment#4: Registrar's Office Simulation
*/
#include "Simulation.h"

int main (int argc, char** argv){
  Simulation *RegistrarSim = new Simulation();

  RegistrarSim->RunSimulation(argv[1]);

  delete RegistrarSim;
  return 0;
}
