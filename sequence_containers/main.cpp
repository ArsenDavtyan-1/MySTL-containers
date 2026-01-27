#include <iostream>
#include "my_vector.h"
#include <forward_list>
#include <algorithm>
#include <vector>
#include "my_forward_list.h"

int main()
{
    my::vector<int>  my_vect{11, -7, 6, -12, 4, 7, 23, -4};
    my_vect.push_back(77);
    my_vect.push_front(-555);
    my_vect.insert(33, 5);
    my_vect.print();

    my::forward_list<int> my_list;
    for(int i = 0; i < 6; ++i)
        my_list.push_front(i);
    my_list.push_front(11);
    my_list.print();
    my_list.reverse();
    my_list.pop_front();
    my_list.print();

    return 0;
}