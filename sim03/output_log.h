/**
   Output Log Class - Handles outputting all simulator data to console and file

 **/

#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>



class OutputLog {
 public:
  OutputLog();
  OutputLog(bool, bool, std::string);
  ~OutputLog();

  void load_config(bool, bool, std::string);
  void log(std::string);
  void time_stamp(long double);
  void flush_stream();


 private:
  bool print_to_file, print_to_console;
  std::string file_name;
  std::stringstream buffer;

};

#endif
