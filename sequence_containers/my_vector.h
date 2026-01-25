#ifndef MY_VECTOR_H
#define MY_VECTOR_H
#include <exception>
#include <initializer_list>
#include <variant>

namespace my
{
	template <typename T>
	class vector
	{
	private:

        // Variable: m_size
        // stores the actual size of vector
		int m_size;
        // Variable: m_cap
        // stores the allocated size of vector
		int m_cap;
        // Variable: m_ptr
        // Stores start address of the vector in memory
		T* m_ptr;

	public:

        // Default Constructor
		vector();
        // Initializer List Constructor
		vector(std::initializer_list<T> init);
        // Copy Constructor
		vector(const vector& other);
        // Assignment Operator
		vector& operator=(const vector& other);
        // Move Constructor(not yet overridden)
		vector(vector&&) = delete;
        // Move Assignment Operator(not yet overriden)
		vector& operator=(vector&& ) = delete;
        // Method: get_size
        // Returns the value of size variable
		int get_size();
        // Method: get_capacity
        // Returns the value of cap variable
		int get_capacity();
        // Method: push_back
        // Adds element to the back of vector
		void push_back(T);
        // Method: pop_back
        // Removes element from the back of vector
		void pop_back();
        // Method: push_front
        // Adds element at the start of vector
		void push_front(T);
        // Method: pop_front
        // Removes first element of the vector
		void pop_front();
        // Method: insert
        // Adds element at the given position
		void insert(T value, int position);
        // Method: remove
        // Removes element from the given position
		void remove(size_t position);
        // Method: is_empty
        // Returns true if vector is empty
		bool is_empty();
        // Method: print
        // Prints elements of vector
		void print();
        // Destructor
		~vector();
        // Random Access Operator
		T operator[](int);
        // Method: at
        // Returns reference of a element from the given position
		T& at(int);

	};
}


template <typename T>
my::vector<T>::vector() : m_ptr(nullptr), m_size(0), m_cap(15)
{
	m_ptr = new T[m_cap];
}

template<typename T>
my::vector<T>::vector(std::initializer_list<T> init)
{
	m_size = init.size();
	m_cap = 15;
	while (m_cap < m_size) // Can cause a problem if m_size > INT_MAX / 2
		m_cap *= 2;
	m_ptr = new T[m_cap];
	int i = 0;
	for (const T& elem : init)
		m_ptr[i++] = elem;
}

template <typename T>
my::vector<T>::vector(const vector<T>& other)
{
	m_size = other.m_size;
	m_cap = other.m_cap;
	m_ptr = new T[other.m_cap];
	for (int i = 0; i < m_size; ++i)
		m_ptr[i] = other.m_ptr[i];
}

template <typename T>
my::vector<T>& my::vector<T>::operator=(const my::vector<T>& other)
{
	if (this != &other)
	{
		delete[] m_ptr;
		m_size = other.m_size;
		m_cap = other.m_cap;
		m_ptr = new T[m_cap];
		for (int i = 0; i < m_size; ++i)
			m_ptr[i] = other.m_ptr[i];
	}
	return* this;
}

template <typename T>
void my::vector<T>::push_back(T a)
{
	if (m_size < m_cap) {
		m_ptr[m_size++] = a;
	}
	else { 
		m_cap *= 2;
		T* temp_ptr = new T[m_cap];
		for (int i = 0; i < m_size; ++i)
		{
			temp_ptr[i] = m_ptr[i];
		}
		temp_ptr[m_size++] = a;
		delete[] m_ptr;
		m_ptr = temp_ptr;
		temp_ptr = nullptr;
	}
	return;
}

template <typename T>
void my::vector<T>::pop_back()
{
	if (is_empty())
		return;
	--m_size;
	if (m_size < (m_cap / 2) && m_cap > 15)
	{
		m_cap /= 2;
		T* new_ptr = new T[m_cap];
		for (int i = 0; i < m_size; ++i){
			new_ptr[i] = m_ptr[i];
		}
		delete[] m_ptr;
		m_ptr = new_ptr;
		new_ptr = nullptr;
	}
	return;
}

template <typename T>
void my::vector<T>::push_front(T value)
{
	if (m_size + 1 >= m_cap){
		T* new_ptr = new T[m_cap * 2];
		new_ptr[0] = value;
		for (int i = 0; i < m_size; ++i)
			new_ptr[i + 1] = m_ptr[i];
		delete[] m_ptr;
		m_ptr = new_ptr;
		new_ptr = nullptr;
	}
	else {
		for (int i = m_size - 1; i >= 0; --i)
			m_ptr[i + 1] = m_ptr[i];
		m_ptr[0] = value;
	}
	++m_size;
	return;
}

template <typename T>
void my::vector<T>::pop_front()
{
	if (m_size - 1 <= m_cap / 2 && m_cap > 15){
		T* new_ptr = new T[m_cap / 2];
		for (int i = 0; i < m_size - 1; ++i)
			new_ptr[i] = m_ptr[i + 1];
		m_cap /= 2;
		delete[] m_ptr;
		m_ptr = new_ptr;
		new_ptr = nullptr;
	}
	else {
		for (int i = 0; i < m_size - 1; i++)
			m_ptr[i] = m_ptr[i + 1];
	}
	--m_size;
	return;
}

template <typename T>
void my::vector<T>::insert(T value, int position)
{
	if (position < 0 || position > m_size){
		std::cout << "invalid position for insert" << std::endl;
		return;
	}
	if (m_size + 1 > m_cap)
	{
		m_cap *= 2;
		T* new_ptr = new T[m_cap];
		for (int i = 0; i < position; ++i)
			new_ptr[i] = m_ptr[i];
		new_ptr[position] = value;
		for(int i = position + 1;i < m_size + 1; ++i)
			new_ptr[i] = m_ptr[i - 1];
		delete[] m_ptr;
		m_ptr = new_ptr;
		new_ptr = nullptr;
	}
	else {
		for (int i = m_size; i > position; --i)
			m_ptr[i] = m_ptr[i - 1];
		m_ptr[position] = value;
	}

	++m_size;
	return;
}


template <typename T>
void my::vector<T>::remove(size_t position)
{
	if (position < 0 || position >= m_size)
	{
		std::cout << "invalid position for remove" << std::endl;
		return;
	}
	if (m_size - 1 < m_cap / 2)
	{
		m_cap /= 2;
		T* new_ptr = new T[m_cap];
		for (int i = 0; i < position; ++i)
			new_ptr[i] = m_ptr[i];
		for (int i = position + 1; i < m_size; ++i)
			new_ptr[i - 1] = m_ptr[i];
		delete[] m_ptr;
		m_ptr = new_ptr;
		new_ptr = nullptr;
	}
	else
	{
		for (int i = position; i < m_size - 1; ++i)
			m_ptr[i] = m_ptr[i + 1];
	}
	
	--m_size;
	return;
}


template <typename T>
int my::vector<T>::get_size()
{
	return m_size;
}

template <typename T>
int my::vector<T>::get_capacity()
{
	return m_cap;
}

template <typename T>
my::vector<T>::~vector()
{
	delete[] m_ptr;
}

template<typename T>
T my::vector<T>::operator[](int i)
{
	return m_ptr[i];
}

template<typename T>
inline bool my::vector<T>::is_empty()
{
	return !m_size;
}

template<typename T>
void my::vector<T>::print()
{
	if (m_size) {
		for (int i = 0; i < m_size; ++i)
		{
			std::cout << m_ptr[i] << ' ';
		}
		std::cout << '\n';
	}
	else {
		std::cout << "The container is empty" << std::endl;
	}
}


template <typename T>
T& my::vector<T>::at(int n)
{
	try {
		if (n < 0 || n >= m_size)
		{
			throw std::bad_variant_access();
		}
		return *(m_ptr + n);
	}
	catch (std::bad_variant_access& expt){
		std::cout << expt.what() << std::endl;
	}
}



#endif // !MY_VECTOR_H
