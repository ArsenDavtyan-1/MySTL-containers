#include <iostream>
#include "my_vector.h"

int main()
{
    my::vector<int>  my_vect{11, -7, 6, -12, 4, 7, 23, -4};
    my_vect.push_back(77);
    my_vect.push_front(-555);
    my_vect.insert(33, 5);
    my_vect.print();

    return 0;
}