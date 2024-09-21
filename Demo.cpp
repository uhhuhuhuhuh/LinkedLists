#include <iostream>
#include <string>
#include <functional>
#include "LinkedListCode.h"


//demo of all the functions for LinkedList
int main(){
    LL::LinkedList<int> linkedList;

    linkedList.push_front(1);
    linkedList.push_back(3);
    //remeber lists starts at 0 so this is inserting at the second element
    linkedList.insert(1, 2);
    linkedList.push_back(4);
    linkedList.delete_place(3);

    int element;
    
    linkedList.foreach(element, [&](){std::cout << element << std::endl;});
    std::cout << "Also the size of that list was " << linkedList.size() << " elements long!" << std::endl;

    std::cin.get();
}
