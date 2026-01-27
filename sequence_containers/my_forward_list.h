#ifndef MY_FORWARD_LIST_H
#define MY_FORWARD_LIST_H
#include <cstddef>


namespace my
{
	template <typename T>
	struct Node
	{
	public:
		T m_value;
		Node* m_next;
		Node()
		{
			m_next = nullptr;
		}
		Node(T value) : m_value(value), m_next(nullptr)
		{}
		~Node()
		{
			m_next = nullptr;
		}
	};


	template <typename T>
	class forward_list
	{
	private:
        // head of single linked list
		Node<T>* head;

	public:
		// Default Constructor
		forward_list();
		// Constructor with one node
		forward_list(T value);
		// Copy Constructor
		forward_list(const forward_list&);
		// Assignment Operator
		forward_list& operator=(const forward_list&);
		// Method: front
		// Access to first element
		// Node<T>* front()
		
		// Method: push_front
		// Push node to the front 
		void push_front(T value);
		// Method: pop_front
		// Pop element from front
		void pop_front();
		// Method: print
		// Prints all elements of list by order
		void print();
		// Method: insert
		// Inserts element after the given position
		// TODO: make like insert_after, should return iterator
		void insert(T value, int position);
		// Method: remove
		// Removes element from the given position
		// TODO: need to be like remove of std::forward_list, should remove by value
		void remove(const size_t position);
		// Method: reverse
		// Reverses list
		void reverse();
		// Method: last_Nth
		// Don't even remember what is this 
		void last_Nth(int position);
		// Destructor
		~forward_list();
	};

}


template <typename T>
my::forward_list<T>::forward_list()
{
	head = nullptr;
}

template <typename T>
my::forward_list<T>::forward_list(T value)
{
	head = new Node<T>(value);
}


template <typename T>
my::forward_list<T>::forward_list(const forward_list& obj)
{
	if (obj.head == nullptr)
	{
		head = nullptr;
		return;
	}

	head = new Node<T>(obj.head->m_value);
	head->m_next = nullptr;
	Node<T>* ptr = head;
	Node<T>* obj_ptr = obj.head->m_next;


	while (obj_ptr != nullptr)
	{
		ptr->m_next = new Node<T>(obj_ptr->m_value);
		ptr = ptr->m_next;	
		
		obj_ptr = obj_ptr->m_next;
	}
	ptr->m_next = nullptr;
}


template <typename T>
my::forward_list<T>& my::forward_list<T>::operator=(const forward_list<T>& obj)
{
	if (this == &obj)
		return *this;

	Node<T>* temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->m_next;
		delete temp;
	}
	head = nullptr;

	if (obj.head == nullptr)
		return *this;

	head = new Node<T>(obj.head->m_value);
	head->m_next = nullptr;
	Node<T>* ptr = head;
	Node<T>* obj_ptr = obj.head->m_next;


	while (obj_ptr != nullptr)
	{
		ptr->m_next = new Node<T>(obj_ptr->m_value);
		ptr = ptr->m_next;

		obj_ptr = obj_ptr->m_next;
	}
	ptr->m_next = nullptr;
	
	return *this;
}


template <typename T>
void my::forward_list<T>::push_front(T value)
{
	Node<T>* temp = new Node<T>(value);
	temp->m_next = head;
	head = temp;
}

template <typename T>
void my::forward_list<T>::pop_front()
{
	if (head == nullptr)
	{
		std::cout << "The list are empty, there are nothing to pop" << std::endl;
		return;
	}
	Node<T>* temp = head;
	head = head->m_next;
	delete temp;
}

template <typename T>
void my::forward_list<T>::print()
{
	if (head == nullptr)
	{
		std::cout << "The forward_list are empty" << std::endl;
		return;
	}
	Node<T>* temp = head;
	while (temp != nullptr)
	{
		std::cout << temp->m_value << ' ';
		temp = temp->m_next;
	}
	std::cout << std::endl;
}

template <typename T>
void my::forward_list<T>::insert(T value, int position)
{
	if (position < 0)
	{
		std::cout << "Invalid position" << std::endl;
		return;
	}
	Node<T>* temp = head;
	for (int i = 0; i < position - 1; ++i)
	{
		temp = temp->m_next;
		if (temp == nullptr )
		{
			std::cout << "Invalid position" << std::endl;
			return;
		}
	}
	Node<T>* obj = new Node<T>(value);
	obj->m_next = temp->m_next;
	temp->m_next = obj;
	return;
}


template <typename T>
void my::forward_list<T>::remove(const size_t position)
{
	if (head == nullptr)
	{
		std::cout << "The single linked list are empty, there are nothing to remove"
				  << std::endl;
		return;
	}
	if (position == 0)
	{
		Node<T>* temp = head;
		head = head->m_next;
		delete temp;
		return;
	}

	int count = 0;
	Node<T>* temp = head;

	while (count + 1 != position)
	{
		if (temp->m_next == nullptr)
		{
			std::cout << position << " is Invalid position" << std::endl;
			return;
		}
		temp = temp->m_next;
		++count;
	}
	if (temp->m_next == nullptr)
	{
		std::cout << position << " is Invalid position" << std::endl;
		return;
	}
	
	Node<T>* rem = temp->m_next;
	temp->m_next = (temp->m_next)->m_next;
	delete rem;
	
	return;
}


template <typename T>
my::forward_list<T>::~forward_list()
{
	Node<T>* temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->m_next;
		delete temp;
	}
}


template <typename T>
void my::forward_list<T>::last_Nth(int position)
{
	if (position < 0)
	{
		std::cout << "invalid position" << std::endl;
		return;
	}
	int i = 0;
	Node<T>* temp1 = head;
	Node<T>* temp2 = head;
	while (i < position && temp1 != nullptr)
	{
		temp1 = temp1->m_next;
		++i;
	}
	if (i < (position - 1) || temp1 == nullptr)
	{
		std::cout << "There are not n-th element counted from the last" << std::endl;
		return;
	}

	while (temp1->m_next != nullptr)
	{
		temp1 = temp1->m_next;
		temp2 = temp2->m_next;
	}
	std::cout << "The " << position <<"-th element from the last is - " << temp2->m_value << std::endl;
}


template <typename T>
void my::forward_list<T>::reverse()
{
	if (head == nullptr || head->m_next == nullptr)
		return;
	Node<T>* temp1 = head->m_next->m_next;
	Node<T>* temp2 = head->m_next;
	head->m_next = nullptr;
	temp2->m_next = head;
	while (temp1 != nullptr)
	{
		head = temp2;
		temp2 = temp1;
		temp1 = temp1->m_next;
		temp2->m_next = head;
	}
	temp2->m_next = head;
	head = temp2;

}


#endif // !MY_FORWARD_LIST_H
