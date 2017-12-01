#include <iostream>
using namespace std;

class node
{
  public:
	//constructor and destructor
	node();
	~node();
	//advanced constructor
	node(int xcyclenum, int xnumcycles, string xtype, string xletter, node* xnext);
	//get functions for nodes private data members
	int get_cyclenum();
	int get_numcycles();
	string get_type();
	node* get_next();
	string get_letter();
	//set next
	void set_next(node* xnext);

  private:
	node* next;
	int cyclenum;
	int numcycles;
	string type;
	string letter;

};




