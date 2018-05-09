/********************************************************************
* Author        :       Herrera, Andres
* File          :       main.cpp
*
* Purpose :
*       This file contains the main function which creates an
*		instance of a binary search tree, and begins reading
*		user input.
*********************************************************************/
#include "queue.cpp"
#include <iomanip>
int main(int argc, char *argv[])
{
	queue<int> myQueue;

	myQueue.enque(1);
	myQueue.enque(2);
	myQueue.enque(3);
	myQueue.enque(4);

	cout << "Is the queue empty? " << std::boolalpha << myQueue.isEmpty() << endl;
	cout << "There are " << myQueue.size() << " items in the queue." << endl;

	int length = myQueue.size();

	for(int i = 0; i < length; i++)
	{
		cout << i << ". " << myQueue.peek() << endl;
		myQueue.deque();
	}

	cout << "There are " << myQueue.size() << " items in the queue after deleting them." << endl;
	
	return 0;
}
