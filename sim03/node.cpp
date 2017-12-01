#include "node.h"

//constructor
node::node()
{
  next = NULL;
  cyclenum = -1;
  numcycles = -1;
  type = "\n";
  letter = "\n";
}
//destructor
node::~node()
{
  next = NULL;
  cyclenum = -1;
  numcycles = -1;
  type = "\n";
  letter = "\n";
}
//advanced constructor
node::node(int xcyclenum, int xnumcycles, string xtype, string xletter, node* xnext)
{
  cyclenum = xcyclenum;
  numcycles = xnumcycles;
  type = xtype;
  letter = xletter;
  next = xnext;
}
//set next
void node::set_next(node* xnext)
{
  next = xnext;
}
//start get functions
int node::get_cyclenum()
{
  return cyclenum;
}

int node::get_numcycles()
{
  return numcycles;
}

string node::get_type()
{
  return type;
}

node* node::get_next()
{
  return next;
}

string node::get_letter()
{
  return letter;
}
//end get functions





