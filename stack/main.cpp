#include "stack.cpp"

int main(int argc, char *argv[])
{

	Stack<int> myStack;

	myStack.push(1);
	myStack.push(2);
	myStack.push(3);
	myStack.push(4);

	cout << "Is the stack empty? " << std::boolalpha << myStack.isEmpty() << endl;
	cout << "There are " << myStack.size() << " items in the stack." << endl;

	int length = myStack.size();

	for(int i = 0; i < length; i++)
	{
		cout << i << ". " << myStack.peek() << endl;
		myStack.pop();
	}

	cout << "There are " << myStack.size() << " items in the stack after deleting them." << endl;
	
	return 0;
}
