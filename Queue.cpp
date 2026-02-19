// Description: Describes the templated class Queue

#ifndef QUEUE_CPP
#define QUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <type_traits>

using namespace std;

// Templated node class
template <class T>
class Node {
public:
  Node( const T& data ); // Constructor
  T GetData(); // Gets data from node
  void SetData( const T& data ); // Sets data in node
  Node<T>* GetNext(); // Gets next pointer
  void SetNext( Node<T>* next ); // Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};


// Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = nullptr;
}


// Gets the data from the Node
template <class T>
T Node<T>::GetData() {
  return m_data;
}


// Sets the data in a Node
template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}


// Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}


// Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}


// Templated queue class
template <class T>
class Queue {
 public:
  // Name: Queue() Queue from a linked list - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Pre-conditions: None
  // Post-conditions: Creates a new queue where m_head and m_tail point to nullptr and m_size = 0
  Queue();

  // Name: ~Queue() - Destructor
  // Desc: Used to destruct a Queue
  // Pre-conditions: There is a Queue
  // Post-conditions: Queue is deallocated (including dynamically allocated nodes)
 ~Queue();

  // Name: Queue (Copy Constructor)
  // Pre-conditions: Creates a copy of existing Queue in separate memory address (deep copy)
  //                 Requires one already existing Queue
  // Post-conditions: Copy of existing Queue
  Queue(const Queue&);

  // Name: operator= (Overloaded Assignment Operator)
  // Pre-conditions: When two Queue objects exist, sets one to equal another
  //                 Requires two Queue objects
  // Post-conditions: When completed, you have two Queues in separate memory addresses
  //                  with the same number of nodes with the same values in each node
  Queue<T>& operator= (Queue&);

  // Name: PushBack
  // Pre-conditions: Takes in data. Creates new node.
  //                 Requires a Queue
  // Post-conditions: Adds a new node to the end of the Queue.
  void PushBack(const T&);

  // Name: PopFront
  // Pre-conditions: Queue with at least one node.
  // Post-conditions: Removes first node in the queue and
  //                  returns the data in the first node
  T PopFront();


  // Name: Display
  // Pre-conditions: Outputs the queue.
  // Post-conditions: Displays the data in each node of queue
  void Display();

  // Name: Front
  // Pre-conditions: Requires a Queue with at least one node
  // Post-conditions: Returns whatever data is pointed at by m_head
  T Front();

  // Name: IsEmpty
  // Pre-conditions: Requires a queue
  // Post-conditions: Returns if the queue is empty.
  bool IsEmpty();

  // Name: GetSize
  // Pre-conditions: Requires a queue
  // Post-conditions: Returns m_size
  int GetSize();

  // Name: Find()
  // Pre-conditions: Requires a queue
  // Post-conditions: Iterates and if it finds the thing, returns index, else -1
  int Find(T);

  // Name: Clear
  // Pre-conditions: Requires a queue
  // Post-conditions: Deallocates and removes all nodes in a queue. No memory leaks
  void Clear();

  // Name: At
  // Pre-condition: Existing Queue
  // Post-condition: Returns object from Queue at a specific location
  // Desc: Iterates to node x and returns data from Queue
  T At (int x);

  // Name: Swap(int)
  // Pre-conditions: Requires a queue
  // Post-conditions: Swaps the nodes at the index with the node prior to it.
  // Desc: Swaps two nodes by updating the pointers (not just the value)
  void Swap(int);

  // Name: Sort()
  // Pre-conditions: Requires a queue with a minimum of 2 nodes (otherwise notifies user)
  // Post-conditions: Sorts the Queue (uses overloaded <).
  // Desc: This is used to sort anything in the Queue assuming the < is overloaded
  //       Uses bubble sort and Swap function above.
  //       Ensure working with queue_test before rest of project.
  void Sort();

private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};

template <class T>
Queue<T>::Queue(){
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

template <class T>
Queue<T>::~Queue() {
    Node<T>* curr = m_head;

    while (curr != nullptr) {
        Node <T>* next = curr->GetNext();
        delete curr;
        curr = next;
    }

    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

template <class T>
Queue<T>::Queue( const Queue& obj ) {
    // Begin as an empty queue.
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;

    // Make a deep copy of the object.
    Node<T>* curr = obj.m_head;
    while (curr != nullptr) {
        PushBack(curr->GetData());
        curr = curr->GetNext();
    }
}

template <class T>
Queue<T>& Queue<T>::operator= ( Queue& obj2 ) {
    if (this != &obj2) {
        // Remove any existing nodes in this queue.
        Clear();

        // Now, make a deep copy from obj2 to *this.
        Node<T>* curr = obj2.m_head;
        while (curr != nullptr) {
            PushBack(curr->GetData());
            curr = curr->GetNext();
        }
    }
    return *this;
}

template <class T>
void Queue<T>::PushBack( const T& data ) {
    Node<T>* newNode = new Node<T>(data);

    // Case in which the queue is empty.
    if (m_head == nullptr) {
        m_head = newNode;
        m_tail = newNode;
    }else {
        // Case in which the queue has at least one node.
        m_tail->SetNext(newNode);
        m_tail = newNode;
    }
    m_size++;
}

template <class T>
T Queue<T>::PopFront() {
    Node<T>* firstNode = m_head;
    T data = firstNode->GetData(); // ensure data is not lost in de-allocation.
    Node<T>* nextNode = firstNode->GetNext(); // ensure location of next node is not lost in de-allocation.

    // Executes if only one node exists in the queue.
    if (nextNode == nullptr) {
        delete firstNode;
        m_head = nextNode;
        m_tail = nextNode;
        m_size = 0;
        return data;
    }

    // Executes if more than one node exists in the queue.
    delete firstNode;
    m_head = nextNode;
    m_size--;
    return data;
}

template <class T>
void Queue<T>::Display() {
    Node<T>* curr = m_head;
    while (curr != nullptr) {
        if constexpr((is_pointer<T>::value) == true) {
            cout << (*(curr)->GetData()) << endl;
        } else {
            cout << curr->GetData() << endl;
        }
        curr = curr->GetNext();
    }
}

template <class T>
T Queue<T>::Front() {
    return m_head->GetData();
}

template <class T>
bool Queue<T>::IsEmpty() {
    if (m_head == nullptr)
        return true;
    else
        return false;
}

template <class T>
int Queue<T>::GetSize() {
    return m_size;
}

template<class T>
int Queue<T>::Find( T target ) {
    int index = -1;
    Node<T>* curr = m_head;

    while (curr != nullptr) {
        index ++; // track where we are in the queue.

        // Check if "thing" is found.
        if (curr->GetData() == target) {
            return index;
        }
        curr = curr->GetNext();
    }

    return -1; // executes if no match was found.
}

template <class T>
void Queue<T>::Clear() {
    Node<T>* curr = m_head;

    while (curr != nullptr) {
        Node<T>* next = curr->GetNext();
        delete curr;
        curr = next;
    }

    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

template <class T>
T Queue<T>::At( int x ) {
    Node<T>* curr = m_head;

    // Move forward "x" number of times.
    for (int i = 0; i < x; i++) {
        curr = curr->GetNext();
    }

    return curr->GetData();
}

template <class T>
void Queue<T>::Swap(int x) {
    // Executes when m_head needs to be changed. This is when the second node is swapped.
    if (x == 1) {

        // First, store location of target node, node before it, and node after it so we don't lose data in re-assignment.
        Node<T>* first = m_head;
        Node<T>* second = first->GetNext();
        Node<T>* third = second->GetNext();

        // Re-assign pointers to swap first and second.
        first->SetNext(third); // former first now points to third.
        m_head = second; // former second becomes new head.
        m_head->SetNext(first); // new head points to former first.

        // If there are only two nodes, update m_tail.
        if (third == nullptr) {
            m_tail = first;
        }

        return;
    }

    // Executes when m_tail needs to be changed, which is when last node is being swapped.
    if (x == (m_size - 1)) {

        // Find the third to last node (needed to swap last two nodes).
        Node<T>* curr = m_head;
        for (int i = 0; i < (m_size - 3); i++) {
            curr = curr->GetNext();
        }

        // Store locations of the three last nodes so we don't lose them.
        Node<T>* thirdToLast = curr;
        Node<T>* secondToLast = curr->GetNext();
        Node<T>* last = secondToLast->GetNext();

        // Swap the places of the second to last and last node.
        thirdToLast->SetNext(last);
        last->SetNext(secondToLast);
        secondToLast->SetNext(nullptr);
        m_tail = secondToLast;

        return;
    }

    // Executes when index corresponds to somewhere in the middle of the queue and neither m_head nor m_tail are changed.
    Node<T>* curr = m_head;
    for (int i = 1; i < (x - 1); i++) {
        curr = curr->GetNext();
    }

    // Organize the data needed for the swap.
    Node<T>* secondPrevious = curr; // node two before target.
    Node<T>* previous = secondPrevious->GetNext(); // node directly before target.
    Node<T>* target = previous->GetNext(); // node we are trying to swap.
    Node<T>* afterTarget = target->GetNext(); // node directly after target.

    // Swap the target node with node directly before it.
    secondPrevious->SetNext(target);
    target->SetNext(previous);
    previous->SetNext(afterTarget);
}

template <class T>
void Queue<T>::Sort() {
    // At least two nodes must exist to sort the Queue.
    if (m_head == nullptr || m_head->GetNext() == nullptr) {
        cout << "At least two nodes must exist." << endl;
        return;
    }

    bool isSorted = false; // flips to true if an entire traversal is made without any changes.

    // Loop terminates when entire queue has been sorted.
    while(isSorted == false) {

        int index = 0; // keeps track of node that needs to be swapped.
        bool swapped = false; // tracks whether the queue is sorted completely.

        Node<T>* curr = m_head;
        Node<T>* next = m_head->GetNext();

        long currData = m_head->GetData();
        T nextData = next->GetData();

        // Loop terminates when it reaches end of queue.
        while (next != nullptr) {
            index++;

            // We want the data that is "less than" to shift to the left. So, we must invoke the swap function on the index corresponding to it.
            if (nextData < currData) {
                Swap(index);
                swapped = true;

                // Update since the swap changes what it points to.
                next = curr->GetNext();

                // Guard against attempting to access data that does not exist.
                if (next != nullptr) {
                    nextData = next->GetData();
                }

            }else {
                // Should only shift to next node once the "thing" does not need to be swapped anymore for current iteration.
                curr = curr->GetNext();
                next = curr->GetNext();

                // Guard against attempting to access data that does not exist.
                if (curr != nullptr && next != nullptr) {
                    currData = curr->GetData();
                    nextData = next->GetData();
                }
            }
        }

        // If a full traversal through the queue is made and nothing is swapped, then the queue is fully sorted.
        if (swapped == false)
            isSorted = true;
    }
}


#endif


