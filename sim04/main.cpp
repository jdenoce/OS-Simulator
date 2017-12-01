#include "config_data.h"
#include <iostream>
using namespace std;
#include <fstream>

int main(int argc, char* argv[])
{
  //welcomes user
  cout<<"======================="<<endl<<"Welcome to OS simulator"<<endl<<"by: Jordan DeNoce"<<endl<<"======================="<<endl;

  //takes in 1 cl arg, else exits program
  if (argc != 2)
  {
    cout<<"Error: incorrect input - expected 1 CL arg"<<endl;
    return EXIT_FAILURE;
  }
  else
  {
    std::string config_file = argv[1];
    
    //creates simulator
    config_data simulator(config_file);
    //parses config data
    simulator.parse_data();
    //parses meta data
    simulator.parse_meta_data();
    //sorts processes according to scheduling algorithm
    simulator.schedule();
    //always prints to screen, and logfile if !logtomonitor
    simulator.print_all();
  }


return 0;
}
