#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <time.h>
#include <pthread.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "output_log.h"
#include "meta_data.h"

struct PCB{
int process_state;
/*
1-start
2-ready
3-running
4-waiting
5-exit
*/
};

struct Thread {
  int num_cycles;
  int cycle_time;
  
Thread(int n, int t) : num_cycles(n), cycle_time(t) {};
};


class config_data
{


  public:
	//constructors and destructor
	config_data(string xconfig_file);
	config_data(int* table, float xversion, string xlog_file_path, string xmeta_data_file);
	~config_data();

	//accesses array storing the cycle time of each component. Takes in component code 0-7 and returns ms/cycle
	int cycle_time(int selection);

	//prints config data, then meta data. Prints to monitor and log as specified
	void print_all();

	//data parsing functions for config and meta data
	bool parse_data();
	bool parse_meta_data();
	//meta data ptr
	meta_data* meta_data_ptr;
	//set functions
	bool set_log_file_path(string s);
	bool set_meta_data_file(string s);
	bool set_cycle_time(int selection, int time);
	bool set_version(float selection);
	//helper functions
	bool is_digit(char);
	void remove_spaces(string &);
	int data_size();
	void lowercase(string &);
	void timestamp(long double);
	void execute(long double, int);
	int allocate_memory();
	string int_to_hex(int);
	//log checks
	bool logtomonitor;
	bool logtofile;
	//log file name
	string log_file_path;
	//threading function, has mutex lock
	static void* execute_thread(void*);

  private:
	int *cycle_time_array;
	float version;
	string meta_data_file;
	string config_file;
	int system_memory, block_size;
	int current;
	int printer_quantity, hd_quantity;
	int printer_number, hd_number;
	PCB program;
	OutputLog global_log;

};
