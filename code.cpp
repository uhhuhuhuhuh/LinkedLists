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

    //adds an elemtn to the end of a list
    void push_back(T value){
        if(end != NULL){
            Node *tempPtr = new Node;
            tempPtr->value = value;
            tempPtr->link = NULL;
            end->link = tempPtr;
            end = tempPtr;
        }else{
            make_first(value);}
    }

    //if position is higher then the size of the LinkedList, the compiler will give a segmentation fault error
    void delete_place(unsigned int position){
        if(position+1 <= size()){
            Node *tempPtr = head;
            Node *otherTempPtr;
            bool isOnlyOne = tempPtr->link == NULL;

            if(!isOnlyOne && position > 0){
                for(int i = 0; i < position-1; ++i){
                    tempPtr = tempPtr->link;
                }
                otherTempPtr = tempPtr->link->link;
                delete tempPtr->link;
                tempPtr->link = otherTempPtr;
            } else{
                if(position == 0 && !isOnlyOne){
                    head = head->link;
                    delete tempPtr;
                }else{
                    head = NULL;
                    end = NULL;
                    delete tempPtr;
                }
            }
        }
    }

    //if position is higher then the size of the LinkedList, the compiler will give a segmentation fault error
    //Note add safe gaurds incase tries to get an element out of the list
    T get_value(T position){
        Node *tempPtr = head;

        if(head != NULL){
            for(int i = 0; i < position; ++i){
                tempPtr = tempPtr->link;
            }

            return tempPtr->value;
        }else{
            return 0;
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
            if(position+1 == size()){push_back(value)}
            else{
                if(position+2 !>= size()){
                    Node *tempPtr = head;
                    Node *otherTempPtr;
                    Node *newPtr = new Node;
                    newPtr->value = value;

                    for(int i = 0; i < position-1; ++i){
                        tempPtr = tempPtr->link;
                    }
                    otherTempPtr = tempPtr->link;
                    tempPtr->link = newPtr;
                    newPtr->link = otherTempPtr;
                }
            }
        }else{
            make_first(value);}
    }

private:
    struct Node{
        T value;
        Node *link;
    };

    //if push_back, push_front, ot insert is called and the size is 0 then call this function
    void make_first(int value){
        Node *tempPtr = new Node;
        tempPtr->value = value;
        tempPtr->link = head;
        head = tempPtr;
        head->link = NULL;
        end = head;
    }

    Node *head = NULL;
    Node *end = NULL;
};

int main(){
    LinkedList<int> linkedList;

    linkedList.push_front(1);
    linkedList.push_back(3);
    linkedList.insert(1, 2);
    linkedList.push_back(4);
    //remeber lists start at 0
    linkedList.delete_place(1);
    
    for(int i = 0; i < 3; ++i){
        std::cout << linkedList.get_value(i) << std::endl;
    }

    std::cin.get();
}
