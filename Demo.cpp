#include <iostream>
#include <string>
#include "LinkedListCode.h"


//demo of all the functions for LinkedList
int main(){
    LL::LinkedList<int> linkedList;

    linkedList.push_front(1);
    linkedList.push_back(4);
    //remeber lists starts at 0 so this is inserting at the second element
    //also insert is placing the value 2 at the second position then moving the previous value bak to the third position
    linkedList.insert(1, 2);
    linkedList.push_back(4);
    linkedList.delete_place(3);
    linkedList.replace(3, 2);

    int element;
    
    //the second parameter is a lambda
    linkedList.foreach(element, [&](){std::cout << element << std::endl;});
    std::cout << "Also the size of that list was " << linkedList.size() << " elements long!" << std::endl;

    std::cin.get();
}
