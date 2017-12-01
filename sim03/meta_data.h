#include "node.h"
#include <fstream>
class meta_data//structured as a queue
{
  public:
	//constructor and destructor
	meta_data();
	~meta_data();
	//queue and dequeue
	bool enqueue(int, int, string, string);
	bool dequeue();
	//pointers to front and back of queue. Current used for queue and dequeue methods
	node* current;
	node* front;
	node* back;
};
