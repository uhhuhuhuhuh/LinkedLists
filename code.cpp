#include <iostream>
#include <string>

template<typename T>
class LinkedList{
public:
    //adds an element to the front of a list
    void push_front(T value){
        if(head != NULL){
            Node *tempPtr = head;
            tempPtr->value = value;
            tempPtr->link = head;
            head = tempPtr;
        }else{
            make_first(value);}
    }

    //adds an element to the last of a list
    void push_back(T value){
        if(last != NULL){
            Node *tempPtr = new Node;
            tempPtr->value = value;
            tempPtr->link = NULL;
            last->link = tempPtr;
            last = tempPtr;
        }else{
            make_first(value);}
    }

    //if position is higher then the size of the LinkedList, the compiler will give a segmentation fault error
    void delete_place(unsigned int position){
        if(position+1 <= size()){
            //ptr before the element you want to delete
            Node *prevPtr = head;
            //ptr after the element you want to delete
            Node *afterPtr;
            bool isOnlyOne = prevPtr->link == NULL;

            if(!isOnlyOne && position > 0){
                //gets "prevPtr" up to position
                for(int i = 0; i < position-1; ++i){
                    prevPtr = prevPtr->link;
                }
                afterPtr = prevPtr->link->link;
                delete prevPtr->link;
                prevPtr->link = afterPtr;
            } else{
                if(position == 0 && !isOnlyOne){
                    //does this is if is the user is deleteing the first element
                    head = head->link;
                    delete prevPtr;
                }else{
                    //does this is if is the user is deleteing the first and only element
                    head = NULL;
                    last = NULL;
                    delete prevPtr;
                }
            }
        }
    }

    //if position is higher then the size of the LinkedList, the compiler will give a segmentation fault error
    //Note add safe gaurds incase tries to get an element out of the list
    T get_value(int position){
        if(position+1 <= size()){
            Node *tempPtr = head;

            if(head != NULL){
                for(int i = 0; i < position; ++i){
                    tempPtr = tempPtr->link;
                }

                return tempPtr->value;
            }else{
                return NULL;
            }
        }else{
            return NULL;
        }
    }

    //returns size of list
    int size(){
        Node *tempPtr = head;

        if(head != NULL){
            int i = 1;
            while(tempPtr->link != NULL){
                tempPtr = tempPtr->link;
                ++i;
            }
            return i;
        }else{
            return 0;
        }
    }

    //inserts at a given position
    void insert(unsigned int position, T value){
        if(head != NULL){
            //deos a check to see if user is trying to add an eleent to the last of the list
            if(position == size()+2){push_back(value);}
            else{
                //does a check if user is inserting completely out of list
                if(position < size()-3){
                    Node *prevPtr = head;
                    Node *afterPtr;
                    Node *tempPtr = new Node;
                    tempPtr->value = value;

                    for(int i = 0; i < position-1; ++i){
                        prevPtr = prevPtr->link;
                    }
                    afterPtr = prevPtr->link;
                    prevPtr->link = tempPtr;
                    tempPtr->link = afterPtr;
                }
            }
        }else{
            make_first(value);}
    }

    T *begin(){
        return &head->value;
    }

    T *end(){
        return &last->value;
    }

private:
    struct Node{
        T value;
        Node *link;
    };

    //if push_back, push_front, or insert is called and the size is 0 then this funtion is called
    void make_first(int value){
        Node *tempPtr = new Node;
        tempPtr->value = value;
        tempPtr->link = head;
        head = tempPtr;
        head->link = NULL;
        last = head;
    }

    Node *head = NULL;
    Node *last = NULL;
};


//demo of all the functions for LinkedList
int main(){
    LinkedList<int> linkedList;

    linkedList.push_front(1);
    linkedList.push_back(3);
    //remeber lists starts at 0 so this is inserting at the second element
    linkedList.insert(1, 2);
    linkedList.push_back(4);
    linkedList.delete_place(3);
    
    for(int i = 0; i < linkedList.size(); ++i){
        std::cout << linkedList.get_value(i) << std::endl;
    }

    std::cin.get();
}