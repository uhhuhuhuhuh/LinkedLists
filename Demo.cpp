#include <iostream>
#include <string>
#include "LinkedListCode.h"


//demo of all the functions for LinkedList
int main(){
    LL::LinkedList<int> linkedList;
    LL::LinkedList<int> showOffCurlyBraces = {0, 1, 2};

    linkedList.push_front(1);
    linkedList.push_back(4);
    //remeber lists starts at 0 so this is inserting at the second element
    //also insert is placing the value 2 at the second position then moving the previous value bak to the third position
    linkedList.insert(1, 2);
    linkedList.push_back(4);
    linkedList.delete_place(3);
    linkedList[2] = 3;
    LL::LinkedList<int> copyList = linkedList;

    int element;
    
    //the second parameter is a lambda
    linkedList.foreach(element, [&](){std::cout << element << std::endl;});
    /* ouput:
        1
        2
        3
    */
    std::cout << "Also the size of that list was " << linkedList.size << " elements long!" << std::endl;
    std::cout << "However I replaced all the items in the list with the value 5!" << std::endl;
    linkedList.replace_all(5);
    linkedList.foreach(element, [&](){std::cout << element << std::endl;});
    /* ouput:
        5
        5
        5
    */
    linkedList.clear();
    std::cout << "Now the list is empty, the size of the list is " << linkedList.size << std::endl;
    std::cout << "Also here are the elements of another list" << std::endl;
    showOffCurlyBraces.foreach(element, [&](){std::cout << element << std::endl;});
    /* ouput:
        0
        1
        2
    */
    std::cout << "And another one" << std::endl;
    copyList.foreach(element, [&](){std::cout << element << std::endl;});
    /* ouput:
        1
        2
        3
    */

    copyList.repeat_push_front(5,2);
    std::cout << "But now there are 2 more items with a value of 5!" << std::endl;
    copyList.foreach(element, [&](){std::cout << element << std::endl;});
    /* ouput:
        5
        5
        1
        2
        3
    */

    std::cin.get();
}