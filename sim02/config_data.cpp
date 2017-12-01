#include "config_data.h"
//constructor
config_data::config_data(string xconfig_file)
{
  config_file = xconfig_file;
  version = 0.0;
  cycle_time_array = new int[8];
  for(int x=0;x<8;x++)
  {
    cycle_time_array[x]=0;
  }
  log_file_path = "\n";
  meta_data_file = "\n";
  meta_data_ptr = NULL;
  logtomonitor=true;
  logtofile=false;
  meta_data_ptr = new meta_data;
  system_memory = 0;
  program.process_state = 0;
}
//destructor
config_data::~config_data()
{
  version = 0.0;
  log_file_path = "\n";
  delete[] cycle_time_array;
  cycle_time_array = NULL;
  meta_data_file = "\n";
}
//advanced contructor //not used
config_data::config_data(int* table, float xversion, string xlog_file_path, string xmeta_data_file)
{
  cycle_time_array = new int[8];
  for(int x=0;x<8;x++)
  {
    cycle_time_array[x]=table[x];
  }
  version = xversion;
  log_file_path = xlog_file_path;
  meta_data_file = xmeta_data_file;
}

/*
0 - processor
1 - monitor
2 - hard drive
3 - printer
4 - keyboard
5 - memory
6 - mouse
7 - speaker
component cycle codes for valid input
returns ms/cycle
*/
int config_data::cycle_time(int selection)
{
  if(selection > 7 || selection < 0)
  {
    cout<<"Invalid location to retrieve data"<<endl;
    return 0;
  }
  return cycle_time_array[selection];
}

//sets cycle_time array values (code, time ms/cycle)
bool config_data::set_cycle_time(int selection, int time)
{
  if(selection < 0 || selection > 7)
  {
    cout<<"Invalid location to store data"<<endl;
    return false;
  }
  cycle_time_array[selection]=time;
  return true;
}
//Begin get/set functions
bool config_data::set_version(float selection)
{
  if(selection < 1 || selection > 4)
  {
    cout<<"Invalid version"<<endl;
    return false;
  }
  version = selection;
  return true;
}
//-
bool config_data::set_log_file_path(string s)
{
  log_file_path = s;
  return true;
}
//-
bool config_data::set_meta_data_file(string s)
{
  meta_data_file = s;
  return true;
}
//end get/set functions

//prints to screen and log accoring to specifications
void config_data::print_all()//UPDATE --- need to beable to print to only logfile
{
  //make PCB
  PCB process1;

  if(!logtomonitor && logtofile){
    cout<<"logging to file..."<<endl;
  }

  Timer clock;
  clock.start();
    //dequeues meta data nodes as they are printed, stops when there are no mode nodes
    while(meta_data_ptr->front != NULL)
    {
	//loop variable setup
	int num, cycle;
	std::string letter, type; 
	type = (meta_data_ptr->front->get_type());
	letter = (meta_data_ptr->front->get_letter());
	cycle = meta_data_ptr->front->get_cyclenum();
	num = meta_data_ptr->front->get_numcycles();
	//timstamps operation start time
	global_log.time_stamp(clock.elapsed_time());
	

	if(letter == "S"){//change PCB program as needed
	  if(type == "start"){
	    global_log.log("Simulator program starting");
	  }
	  else{
	    global_log.log("Simulator program ending");
	  }
	}
	if(letter == "A"){
	  if(type == "start"){
	    global_log.log("OS: preparing process 1");
	    process1.process_state = 1;//start
	    global_log.time_stamp(clock.elapsed_time());
	    global_log.log("OS: starting process 1");
	    process1.process_state = 2;//ready
	  }
	  else{
	    global_log.log("OS: removing process 1");
	    process1.process_state = 5;//exit
	  }
	}
	if(letter == "P"){
      	  global_log.log("Process 1: start processing action");
	  process1.process_state = 3;//running
	  execute(cycle, num);
	  global_log.time_stamp(clock.elapsed_time());
      	  global_log.log("Process 1: end processing action");
	  process1.process_state = 2;//ready
	}
	if(letter == "M"){
	  if(type == "allocate"){
  	    global_log.log("Process 1: allocating memory");
	    unsigned int mem_loc = allocate_memory(system_memory);
	    process1.process_state = 4;//waiting
	    execute(cycle, num);
	    global_log.time_stamp(clock.elapsed_time());
	    int mem = mem_loc;
	    global_log.log("Process 1: memory allocated at 0x" + std::to_string(mem));
	    process1.process_state = 2;//ready
	  }
	  if(type == "block"){
	   global_log.log("Process 1: start memory blocking");
	   process1.process_state = 3;//running
	   execute(cycle, num);
	   global_log.time_stamp(clock.elapsed_time());
	   global_log.log("Process 1: end memory blocking");
	   process1.process_state = 2;//ready
	  }
	}
	if(letter == "I"){//uses threads
	  if(type == "harddrive"){
	   global_log.log("Process 1: start hard drive input");
	   process1.process_state = 4;//waiting

	   //threading
	   Thread data(num, cycle);
	   pthread_t t1;
           num = pthread_create(&t1, NULL, &execute_thread, &data);
           pthread_join(t1, NULL);

	   global_log.time_stamp(clock.elapsed_time());
	   global_log.log("Process 1: end hard drive input");
	   process1.process_state = 2;//ready
	  }
	if(type == "keyboard"){
	   global_log.log("Process 1: start keyboard input");
	   process1.process_state = 4;//waiting
	   //threading
	   Thread data(num, cycle);
	   pthread_t t1;
           pthread_create(&t1, NULL, &execute_thread, &data);
           pthread_join(t1, NULL);

	   global_log.time_stamp(clock.elapsed_time());
	   global_log.log("Process 1: end keyboard input");
	   process1.process_state = 2;//ready
	  }
	if(type == "mouse"){
	   global_log.log("Process 1: start mouse input");
	   process1.process_state = 4;//waiting
	   //threading
	   Thread data(num, cycle);
	   pthread_t t1;
           pthread_create(&t1, NULL, &execute_thread, &data);
           pthread_join(t1, NULL);

	   global_log.time_stamp(clock.elapsed_time());
	   global_log.log("Process 1: end mouse input");
	   process1.process_state = 2;//ready
	  }
	}
	if(letter == "O"){//uses threads
	 if(type == "harddrive"){
	   global_log.log("Process 1: start hard drive output");
	   process1.process_state = 4;//waiting
	   //threading
	   Thread data(num, cycle);
	   pthread_t t1;
           pthread_create(&t1, NULL, &execute_thread, &data);
           pthread_join(t1, NULL);

	   global_log.time_stamp(clock.elapsed_time());
	   global_log.log("Process 1: end hard drive output");
	   process1.process_state = 2;//ready
	 }
	 if(type == "monitor"){
	   global_log.log("Process 1: start monitor output");
	   process1.process_state = 4;//waiting
	   //threading
	   Thread data(num, cycle);
	   pthread_t t1;
           pthread_create(&t1, NULL, &execute_thread, &data);
           pthread_join(t1, NULL);

	   global_log.time_stamp(clock.elapsed_time());
	   global_log.log("Process 1: end monitor output");
	   process1.process_state = 2;//ready
	 }
	 if(type == "printer"){
	   global_log.log("Process 1: start printer output");
	   process1.process_state = 4;//waiting
	   //threading
	   Thread data(num, cycle);
	   pthread_t t1;
           pthread_create(&t1, NULL, &execute_thread, &data);
           pthread_join(t1, NULL);

	   global_log.time_stamp(clock.elapsed_time());
	   global_log.log("Process 1: end printer output");
	   process1.process_state = 2;//ready
	 }
	 if(type == "speaker"){
	   global_log.log("Process 1: start speaker output");
	   process1.process_state = 4;//waiting
	   //threading
	   Thread data(num, cycle);
	   pthread_t t1;
           pthread_create(&t1, NULL, &execute_thread, &data);
           pthread_join(t1, NULL);

	   global_log.time_stamp(clock.elapsed_time());
	   global_log.log("Process 1: end speaker output");
	   process1.process_state = 2;//ready
	 }
	}
	meta_data_ptr->dequeue();
    }//end while
  if(!logtomonitor && logtofile){
    cout<<"log complete!"<<endl;
  }
}

//returns how many items are in the cycle_time array, to check if all the data is present
int config_data::data_size()
{
  int size=0;
  for(int x=0;x<8;x++)
  {
    if(cycle_time_array[x] != 0)
    {
      size++;
    }
  }
  return size;
}

//reads config data. Extracts and stores information
bool config_data::parse_data()
{
  //opening file
  std::ifstream file(config_file.c_str());

  //check if file is empty
  if(file.peek() == ifstream::traits_type::eof())
  {
    throw invalid_argument("Error: Configuration data file empty");
  }

  string line;
  //goes through file line by line
  while(getline(file, line)) 
  {
    //finds the : in each line and seperates string into pre and post : strings
    string colon = ":";
    string pre_colon = line.substr(0, line.find(colon));
    string post_colon = line.substr(line.find(colon) + 1);
    //removes whitespace
    remove_spaces(pre_colon);
    remove_spaces(post_colon);
    //converts to lowercase, except when taking in a file name
    lowercase(pre_colon);
    if(pre_colon != "filepath" && pre_colon != "logfilepath")
    {
      lowercase(post_colon);
    }
    //if colon is end of string do nothing
    if(line.find(colon) == std::string::npos){
    }
  else
  {
    //new memory input
    if(pre_colon.find("systemmemory") != std::string::npos){
	int start, finish;
	//finds type of memory needed
	for(int x=0;x<pre_colon.length();x++){
	  if(pre_colon[x]=='('){
	    start=x+1;
	  }
	  if(pre_colon[x]==')'){
	    finish=x;
	  }
	}
	string type = pre_colon.substr(start, finish-start);
	int mem = atoi(post_colon.c_str());//kbytes, Mbytes, or Gbytes)
	if(type=="kbytes"){
	  system_memory = mem;
	}
	if(type=="mbytes"){
	  system_memory = (mem * 1000);
	}
	if(type=="gbytes"){
	  system_memory = (mem * 1000 * 1000);
	}
    }
    if(pre_colon == "version/phase")
    {
	version = atoi(post_colon.c_str());
    }
    if(pre_colon == "filepath")
    {
	meta_data_file = post_colon;
    }
    if(pre_colon.find("processor") != std::string::npos)
    {
	int time = atoi(post_colon.c_str());
	set_cycle_time(0, time);
    }
    if(pre_colon.find("monitor") != std::string::npos)
    {
	int time = atoi(post_colon.c_str());
	set_cycle_time(1, time);
    }
    if(pre_colon.find("harddrive") != std::string::npos)
    {
	int time = atoi(post_colon.c_str());
	set_cycle_time(2, time);
    }
    if(pre_colon.find("printer") != std::string::npos)
    {
	int time = atoi(post_colon.c_str());
	set_cycle_time(3, time);
    }
    if(pre_colon.find("keyboard") != std::string::npos)
    {
	int time = atoi(post_colon.c_str());
	set_cycle_time(4, time);
    }
    if(pre_colon.find("memorycycletime") != std::string::npos)
    {
	int time = atoi(post_colon.c_str());
	set_cycle_time(5, time);
    }
    if(pre_colon.find("mouse") != std::string::npos)
    {
	int time = atoi(post_colon.c_str());
	set_cycle_time(6, time);
    }
    if(pre_colon.find("speaker") != std::string::npos)
    {
	int time = atoi(post_colon.c_str());
	set_cycle_time(7, time);
    }
    if(pre_colon == "log"){
	bool log=false;
	if(post_colon == "logtoboth"){
	  logtomonitor=true;
	  logtofile=true;
	  log=true;
	}
	if(post_colon == "logtofile"){
	  logtomonitor=false;
	  logtofile=true;
	  log=true;
	}
	if(post_colon == "logtomonitor"){
	  logtomonitor=true;
	  logtofile=false;
	  log=true;
	}
	if(!log){
	  throw invalid_argument("Error: After Log: specify Log to Monitor, Log to File, Log to Both");
	}
    }
    if(pre_colon == "logfilepath")
    {
	log_file_path = post_colon;
    }
  }

  }
  //end of while getline loop
global_log.load_config(logtofile, logtomonitor, log_file_path);
return true;
}

//reads meta data. Extracts and stores information and queues the meta data nodes
bool config_data::parse_meta_data()
{
  //checks for valid extension
  int period = meta_data_file.find_last_of(".");
  string extension = meta_data_file.substr(period);
  if(extension != ".mdf")
  {
    throw invalid_argument("Error: Invalid meta data file extension");
    return false;
  }
  //Opening file   
  ifstream meta_file (meta_data_file.c_str());
  string line;
  //Checking if file is empty
  if(meta_file.peek() == ifstream::traits_type::eof()) 
  {
    throw std::invalid_argument("Error: Empty meta data file");
    return false;
  }
  //flags for start and end of node info
  bool start_found  = false;
  bool end_found = false;
  //location in current string where type info starts and ends
  int xtype_start;
  int xtype_end;
  //location in current string where cycle info starts and ends
  int xnumcycle_start;
  int xnumcycle_end;
  //letter code at beginning of meta data
  string letter;
  

  //Loops through each line
  while(getline(meta_file, line))
  {
    //removes whitespace
    remove_spaces(line);
    //Loop through each character of the line
    for(int x=0;x<line.length();x++) 
    {
	if(line[x] == '(')
	{
	  //Current char is (, then +1 is meta data type, -1 is letter
	  xtype_start = x + 1;
	  letter = line[x - 1];
	  //Set flag to true
	  start_found = true;
	}
	else if(line[x] == ')') 
	{
	  //Current is ), then +1 is # of cycles
	  xtype_end = x;
	  xnumcycle_start = x + 1;
	  xnumcycle_end = xnumcycle_start;
	  //iterate until character is not a digit
	  while(is_digit(line[xnumcycle_end])) 
	  {
	    xnumcycle_end++;
	  }
	  //Set flag to true
	  end_found = true;
	}
	//if data start and end are found
	if(start_found && end_found) 
	{
	  bool queue = true;
	  int code;
	  //Extract info and push onto meta_data stack
	  string type = line.substr(xtype_start, xtype_end - xtype_start);
	  string numcyclesstr = line.substr(xnumcycle_start, xnumcycle_end - xnumcycle_start);
	  int numcycles = atoi(numcyclesstr.c_str());
	  if(letter == "S"){
	  }
	  if(letter == "A"){
	  }
	  if(letter == "P"){
	    code = cycle_time(0);
	  }
	  if(letter == "I"){
	    if(type=="harddrive"){
		code=2;
	    }
	    if(type=="keyboard"){
		code=cycle_time(4);
	    }
	    if(type=="mouse"){
		code=cycle_time(6);
	    } 
	  }
	  if(letter == "O"){
	    if(type=="harddrive"){
		code=cycle_time(2);
	    }
	    if(type=="monitor"){
		code=cycle_time(1);
	    }
	    if(type=="speaker"){
		code=cycle_time(7);
	    }
	    if(type=="printer"){
		code=cycle_time(3);
	    }
	  }
	  if(letter == "M"){
	    if(type=="block"){
		code=cycle_time(5);
	    }
	    if(type=="allocate"){
		code=cycle_time(5);
	    }
	  }
	  
	  //queues data
	  if(queue)
	  {
	    meta_data_ptr->enqueue(code, numcycles, type, letter);
	  }

	  //reset flags
	  start_found = false;
	  end_found = false;
	}
    }
  }
  return true;
}



//removes whitespace from strings
void config_data::remove_spaces(string &str)
{
  std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
  str.erase(end_pos, str.end());
}
//converts string to lowercase
void config_data::lowercase(string& str)
{
  std::transform(str.begin(), str.end(), str.begin(), :: tolower);
}
//checks if char is a digit
bool config_data::is_digit(char x)
{
  if((x=='0') || (x=='1') || (x=='2') || (x=='3') || (x=='4') || (x=='5')  || (x=='6')  || (x=='7') || (x=='8') || (x=='9') )
  {
    return true;
  }
  return false;
}

void config_data::timestamp(long double time)
{
  cout<<std::fixed;
  cout<<std::setprecision(6);
  cout<<time<< " - ";
}

//simulates the time the OS would need to complete task given cycle time and # of cycles
void config_data::execute(long double cycle, int num)
{
Timer clock; 
  
for(int i = 0; i < num; i++) {
  clock.start();
  while(clock.elapsed_milli() < cycle);
}
}

//given memory allocation function
unsigned int config_data::allocate_memory(int totMem)
{
	unsigned int address;
	
	srand(time(NULL));
	
	if( totMem > 0 )
	{
		address = rand() % totMem;
	}
	return address;
}

//Executes an operation using threads
void* config_data::execute_thread(void* p) 
{
  Thread* op = (Thread*) p;
  Timer clock; 
  for(int i = 0; i < op->num_cycles; i++) {
    clock.start();
    while(clock.elapsed_milli() < op->cycle_time);
  }
}






