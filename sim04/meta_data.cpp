#include "meta_data.h"
//constructor
meta_data::meta_data()
{
  current = NULL;
  front = NULL;
  back = NULL;
  processes = 0;
  totalTime = 0;
}

//destructor
meta_data::~meta_data()
{
  while(front != NULL)
  {
    current = back;
    back = back->get_next();
    delete current;
  }
  
}
//queues a node at the back of the line
bool meta_data::enqueue(int xcyclenum, int xnumcycles, string xtype, string xletter)
{
  if(front == NULL)
  {
    front = new node(xcyclenum, xnumcycles, xtype, xletter, NULL);
    back = front;
  }
  else
  {
    current = new node(xcyclenum, xnumcycles, xtype, xletter, NULL);
    back->set_next(current);
    back = current;
  }
  
}
//dequeues the front node and deletes it
bool meta_data::dequeue()
{
  current = front;
  front = current->get_next();
  delete current;
}


