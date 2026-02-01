#ifndef MY_LIST_H
#define MY_LIST_H


namespace my
{
    // Class: Node2
    // Definition of list's node
    template <typename T>
    class Node2
	{
	public:
        // Variable: m_next
        // Points to the next node
		Node2* m_next;
        // Variable: m_prev
        // Points to the previous node
		Node2* m_prev;
        // Variable: m_value
        // Value of current node
		T m_value;
        // Constructor
		Node2(T value);
	};


    // Class: list
    // Doubly linked list definition
	template <typename T>
	class list
	{
	public:
        // Default constructor
		list();
        // Destructor
		~list();

        // Method: push_front
        // Pushs node to the front of list
		void push_front(T value);
        // Method: pop_front
        // Pops node from the front of list
		void pop_front();
        // Method: push_back
        // Pushs node to the back of list
		void push_back(T value);
        // Method: pop_back
        // Pops node from the back of list
		void pop_back();
        // Method: print
        // Prints values of each node by order
		void print();

	private:
		class Node2;
		Node2* head;
		Node2* tail;
	};
}


template <typename T>
my::list<T>::list()
{
	head = nullptr;
	tail = nullptr;
}


template <typename T>
my::list<T>::~list()
{
	while (head != nullptr)
	{
		Node2* temp = head;
		head = head->m_next;
		delete[] temp;
	}
	head = nullptr;
	tail = nullptr;
}


template <typename T>
void my::list<T>::push_front(T value)
{
	if (head == nullptr)
	{
		head = new Node2(value);
		tail = head;
		return;
	}
	Node2* temp = new Node2(value);
	temp->m_next = head;
	temp->m_prev = nullptr;
	head->m_prev = temp;
	head = temp;
	return;
}


template <typename T>
void my::list<T>::pop_front()
{
	if (head == nullptr)
	{
		std::cout << "The double linked list is empty, there are nothing to pop" << std::endl;
		return;
	}
	Node2* temp = head;
	head = head->m_next;
	if (head == nullptr)
	{
		delete temp;
		return;
	}
	head->m_prev = nullptr;
	delete temp;
	return;
}


template <typename T>
void my::list<T>::push_back(T value)
{
	if (head == nullptr)
	{
		head = new Node2(value);
		tail = head;
		return;
	}
	tail->m_next = new Node2(value);
	(tail->m_next)->m_prev = tail;
	tail = tail->m_next;
	tail->m_next = nullptr;
	return;
}


template <typename T>
void my::list<T>::pop_back()
{
	if (tail == nullptr)
	{
		std::cout << "The double linked list is empty, there are nothing to pop" << std::endl;
		return;
	}
	Node2* temp = tail;
	tail = tail->m_prev;
	if (tail == nullptr)
	{
		head = nullptr;
		delete temp;
		return;
	}
	tail->m_next = nullptr;
	delete temp;
	return;
}


template <typename T>
void my::list<T>::print()
{
	if (head == nullptr)
	{
		std::cout << "The double linked list is empty" << std::endl;
		return;
	}
	Node2* temp = head;
	while (temp != nullptr)
	{
		std::cout << temp->m_value << ' ';
		temp = temp->m_next;
	}
	std::cout << std::endl;
	return;
}


template <typename T>
my::Node2<T>::Node2(T value)
	: m_value(value), m_next(nullptr), m_prev(nullptr)
{

}



#endif // !MY_LIST_H
