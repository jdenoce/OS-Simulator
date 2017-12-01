#include "config_data.h"
#include <iostream>
using namespace std;
#include <fstream>

int main(int argc, char* argv[])
{

  cout<<"======================="<<endl<<"Welcome to OS simulator"<<endl<<"by: Jordan DeNoce"<<endl<<"======================="<<endl;

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
    if(simulator.parse_data())
    {//parses meta data
	if(simulator.parse_meta_data())
	{
	  simulator.print_all();
	  //simulator.meta_data_ptr->print_meta_data(simulator.logtomonitor, simulator.log_file_path);
	}
    }
  }


return 0;
}
