#include "meta_data.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdexcept>

class config_data
{
  public:
	//constructors and destructor
	config_data(string xconfig_file);
	config_data(int* table, float xversion, string xlog_file_path, string xmeta_data_file);
	~config_data();

	//accesses array storing the cycle time of each component. Takes in component code 0-7 and returns ms/cycle
	int cycle_time(int selection);

	//prints config data, then meta data. Also logs to file if !logtomonitor
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
	//logs only to monitor, if !logtomonitor then logs to both
	bool logtomonitor;
	//log file name
	string log_file_path;


  private:
	int *cycle_time_array;
	float version;
	string meta_data_file;
	string config_file;

};