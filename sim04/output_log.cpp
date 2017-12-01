#include "output_log.h"

//Constructor
OutputLog :: OutputLog()
{

}

//Parameterized constructor
OutputLog :: OutputLog(bool file, bool console, std::string name)
{
  print_to_file = file;
  print_to_console = console;

  if(print_to_file) {
    file_name = name;
  }
  else {
    file_name = " ";
  }
}

//Destructor
OutputLog :: ~OutputLog()
{
  if(print_to_file) {
    flush_stream();
  }
}

//Loads in configuration data into the object
void OutputLog::load_config(bool file, bool console, std::string name)
{
 print_to_file = file;
 print_to_console = console;

  if(print_to_file) {
    file_name = name;
  }
  else {
    file_name = " ";
  }
}

//Logs a string to the specified paths
void OutputLog :: log(std::string output)
{
  if(print_to_file) {
    buffer << output << std::endl;
  }

  if(print_to_console) {
    std::cout << output << std::endl;
  }
}

//Logs a timestamp precise to 6 digits
void OutputLog :: time_stamp(long double time)
{
 if(print_to_file) {
   buffer << std::fixed;
   buffer << std::setprecision(6);
   buffer << time << " - ";
  }

  if(print_to_console) {
    std::cout << std::fixed;
    std::cout << std::setprecision(6);
    std::cout << time << " - ";
  }
}

//Flushes string stream to file path
void OutputLog :: flush_stream()
{
  if(print_to_file)
    {
      std::ofstream output;
      output.open(file_name.c_str(), std::ofstream::out);

      output << buffer.rdbuf();
      output.close();
    }
}
