#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {
    template <typename T>
    class SortedList {
    private:
        struct Node{
            T data;
            Node* next;
            explicit Node(const T& d,Node* n= nullptr): data(d),next(n){};
        };
        int size;
        Node* head;

    public:
        class ConstIterator;
        SortedList() {
            this-> size = 0;
            this->head = nullptr;
        }

        SortedList(const SortedList& n) : size(0), head(nullptr){
            if (n.head == nullptr) {
                return;
            }
            try{
            Node* copy = n.head->next; // their list
            this->head = new Node(n.head->data);
            Node* temp = this->head; // my list starts from head
            this->size = 1;
            while (copy){
                temp->next = new Node(copy->data);
                temp = temp->next;
                copy = copy->next;
               ++this->size;
            }
            }catch(...){
              clear();
              throw;
            }
        }

        ~SortedList()  {
           clear();
        }

        SortedList& operator=(const SortedList& list) {
            if (this == &list) {
                return *this;
            }

            Node* currPtr = this->head;
            while (currPtr != nullptr) {
                Node* next = currPtr->next; // point to the first chain
                delete currPtr;// delete first chain
                currPtr = next;
            }
            this->head = nullptr;
            this->size = 0;

            if (list.head == nullptr) {
                return *this;
            }

            	this->size = list.size;
            	Node* copy = list.head->next; // their list
            	Node* temp = new Node(list.head->data); // my list starts from head
            	this->head = temp;
            try{
                while (copy){
                temp->next = new Node(copy->data);
                temp = temp->next;
                copy = copy->next;
            	}
			}catch(...){
  				while (copy){
                Node* next = copy->next;
                delete copy;
                copy = next;
            	}
            throw;
			}
            return *this;
    }




        Node* GetHead() const {
            return this->head;
        }
        int length() const
        {
            return this->size;
        }


        template <typename Predicate>
            SortedList filter(Predicate predicate) const {
            SortedList<T> newS;
            for (ConstIterator it = begin(); it != end(); ++it) {
                if (predicate(*it)) {
                    newS.insert(*it);
                }
            }
            return newS;
        }

        template <typename Predicate>
        SortedList apply(Predicate predicate) const {
            SortedList<T> newS;
            for (ConstIterator it = begin(); it != end(); ++it) {
                newS.insert(predicate(*it));
            }
            return newS;
        }

        void insert(const T& element) {
            Node* curr = new Node(element);
            // in case the node >
            if (this->head == nullptr || curr->data > this->head->data) {
                curr->next = this->head;
                this->head = curr;
                ++this->size;
                return;
            }

            // in case <= / if =: keep searching for > num
            Node* prev = head;
            while ((prev->next) && (prev->next->data > curr->data))
            {
                prev = prev->next;
            }

            curr->next = prev->next;
            prev->next = curr;

            ++this->size;
        }


    void clear()
    {
        Node* p = head;
        while (p) {
            Node* next = p->next;
            delete p;
            p = next;
        }
        head = nullptr;
        size = 0;
    }


/*
        void remove(const ConstIterator& it) {
            Node* del = it.GetNode();;

            if (del == nullptr) {
            return;            }
            if (head == nullptr) {
                throw std::runtime_error("Iterator not in this list");
            }
            if (head == del) {
                head = head->next;
            } else {
                Node* prev = head;
                while (prev->next && prev->next != del) {
                    prev = prev->next;
                }

                if (prev->next == nullptr) {
                    throw std::runtime_error("iterator not in this list");
                }

                prev->next = del->next;
            }

            delete del;
            --this->size;
        }


*/
        void remove(const ConstIterator& it) {
            Node* del = it.GetNode();;

            if (del == nullptr) {
                return;            }
            if (head == nullptr) {
                throw std::runtime_error("Iterator not in this list");
            }
            if (head == del) {
                head = head->next;
            } else {
                Node* prev = head;
                while (prev->next && prev->next != del) {
                    prev = prev->next;
                }

                if (prev->next == nullptr) {
                    throw std::runtime_error("iterator not in this list");
                }

                prev->next = del->next;
            }

            delete del;
            --this->size;
        }

        ConstIterator begin() const {
              return ConstIterator(this->head);        }

        ConstIterator end()   const {
             return ConstIterator(nullptr);
        }


        /**
         *
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. SortedList() - creates an empty list.
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~SortedList() - destructor
         *
         * iterator:
         * 5. class ConstIterator;
         * 6. begin method
         * 7. end method
         *
         * functions:
         * 8. insert - inserts a new element to the list
         * 9. remove - removes an element from the list
         * 10. length - returns the number of elements in the list
         * 11. filter - returns a new list with elements that satisfy a given condition
         * 12. apply - returns a new list with elements that were modified by an operation
         */

    };

    template <class T>
    class SortedList<T>::ConstIterator {
        Node* current;
    public:
        ConstIterator() = default;
        explicit ConstIterator(Node* current) : current(current) {}
        ConstIterator(const ConstIterator&) = default;
        ~ConstIterator() = default;
        ConstIterator& operator=(const ConstIterator& it) = default;
        const T& operator*() const {
            if (!current) {
                throw std::out_of_range("dereference of end() iterator");
            }
            return current->data;
        }


            ConstIterator& operator++(){
                if (!current)
                    throw std::out_of_range("increment past end() iterator");
                current = current->next;
                return *this;
            }

            bool operator!=(const ConstIterator& other) const{
                return current != other.current;
            }
            Node* GetNode() const {
            return current;
             }

            /**
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. a ctor(or ctors) your implementation needs
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~ConstIterator() - destructor
         *
         * operators:
         * 5. operator* - returns the element the iterator points to
         * 6. operator++ - advances the iterator to the next element
         * 7. operator!= - returns true if the iterator points to a different element
         *
         */


        };



}

