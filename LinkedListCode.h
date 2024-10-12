#pragma once
#include <functional>

namespace LL{
    //    i|i
    //    n|s
    //    k|t
    //    e
    //    d
    template<typename T>
    class LinkedList{
    public:
        //Constructors
        LinkedList() = default;
        LinkedList(std::initializer_list<T> init){
            for(T element : init){
                push_back(element);
            }
        }
        LinkedList(const LL::LinkedList<T> &other){
            clear();
            for(int i = 0; i < other.size; ++i){
                Node *tempPtr = other.head;

                for(int j = 0; j < i; ++j){
                    tempPtr = tempPtr->link;
                }

                push_back(tempPtr->value);
            }
        }

        int size = 0;

        //adds an element to the front of a list
        void push_front(const T &value){
            if(head != NULL){
                Node *tempPtr = new Node;
                tempPtr->value = value;
                tempPtr->link = head;
                head = tempPtr;
                ++size;
            }else{
                make_first(value);}
        }

        //adds an element to the last of a list
        void push_back(const T &value){
            if(last != NULL){
                Node *tempPtr = new Node;
                tempPtr->value = value;
                tempPtr->link = NULL;
                last->link = tempPtr;
                last = tempPtr;
                ++size;
            }else{
            make_first(value);}
        }

        void repeat_push_front(const T &value, unsigned int repeat){
            for(unsigned int i = 0;i < repeat; ++i){
                push_front(value);
            }
        }
        
        void repeat_push_back(const T &value, unsigned int repeat){
            for(unsigned int i = 0;i < repeat; ++i){
                push_back(value);
            }
        }

        //if position is higher then the size of the LinkedList, the compiler will give a segmentation fault error
        void delete_place(unsigned int position){
            if(position+1 <= size){
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

                    --size;
                } else{
                    if(position == 0 && !isOnlyOne){
                        //does this is if is the user is deleteing the first element
                        head = head->link;
                        delete prevPtr;
                        --size;
                    }else{
                        //does this is if is the user is deleteing the first and only element
                        head = NULL;
                        last = NULL;
                        delete prevPtr;
                        --size;
                    }
                }
            }
        }

        //returns size of list
        int recount_size(){
            Node *tempPtr = head;

            if(head != NULL){
                int i = 1;
                while(tempPtr->link != NULL){
                    tempPtr = tempPtr->link;
                    ++i;
                }
                size = i;
                return i;
            }else{
                size = 0;
                return 0;
            }
        }

        //inserts at a given position
        void insert(unsigned int position, const T &value){
            if(head != NULL){
                //deos a check to see if user is trying to add an eleent to the last of the list
                if(position == size+2){push_back(value);}
                else{
                    //does a check if user is inserting completely out of list
                    if(position < size-3){
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
                        ++size;
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

        /*You have to #include <functional> and do this if you want compatibilty with lambdas, but if you
        want to do it without #include <functional> or don't care about lambdas then do: void(*func)()  
        for the second parameter*/
        void foreach(T &element, const std::function<void()>& func){
            int i = 0;
            for(i = 0; i < size; ++i){
                element = get_value(i);
                func();
            }
        }

        //if you read the comments for the first foreach and also want to replace the second parameter then do this: void(*func)(T)
        void foreach(T &element, const std::function<void(T)>& func){
            int i = 0;
            for(i = 0; i < size; ++i){
                element = get_value(i);
                func(element);
            }
        }

        void clear(){
            int listsize = size;

            for(int i = 0; i < listsize; ++i){
                delete_place(0);
            }
        }

        void replace_all(const T &value){
            int listsize = size;

            int i = 0;
            for(i = 0; i < listsize; ++i){
                get_value_ref(i) = value;
            }
        }

        bool is_contain(const T &value){
            for(int i = 0; i < size; ++i){
                if(get_value(i) == value){
                    return true;
                }
            }
            return false;
        }

        //Operators:
        
        T& operator[](const unsigned int &position){
            Node *tempPtr = head;

            for(int i = 0; i < position; ++i){
                tempPtr = tempPtr->link;
            }

            return tempPtr->value;
        }

        bool operator==(const LL::LinkedList<T> &other){
            if(other.size != size)
                return false;

            for(int i = 0; i < other.size; ++i){
                if(get_value(i) != get_value_of_other(i, other.head))
                    return false;
            }

            return true;
        }

        bool operator!=(const LL::LinkedList<T> &other){
            if(other.size != size)
                return true;

            for(int i = 0; i < other.size; ++i){
                if(get_value(i) != get_value_of_other(i, other.head))
                    return true;
            }

            return false;
        }

        //satic stuff

        static void CopyOver(LinkedList<T> &copyTo, LinkedList<T> &copyFrom){
            int size = copyFrom.size;
            copyTo.clear();
            for(int i = 0; i < size; ++i){
                copyTo.push_back(get_value_of_other(i, copyFrom.head));
            }
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
            ++size;
        }

        T get_value(const unsigned int position){
            Node *tempPtr = head;

            for(int i = 0; i < position; ++i){
                tempPtr = tempPtr->link;
            }

            return tempPtr->value;
        }

        T get_value_of_other(const unsigned int position, Node* otherHead){
            Node *tempPtr = otherHead;

            for(int i = 0; i < position; ++i){
                tempPtr = tempPtr->link;
            }

            return tempPtr->value;
        }

        T& get_value_ref(const unsigned int position){
            Node *tempPtr = head;

            for(int i = 0; i < position; ++i){
                tempPtr = tempPtr->link;
            }

            return tempPtr->value;
        }

        Node *head = NULL;
        Node *last = NULL;
    };
}