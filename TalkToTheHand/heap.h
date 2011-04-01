#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <time.h>

using namespace std;

/**
 * Heap class
 * This is a templatized heap class which takes any object as the
 * heap input(on which > and < operators are overloaded) and
 * organizes them in the heap to keep the maximum at the top of the
 * heap. Though a lot of functionalities are given in this class
 * but this application requires only max heap to be calculated
 * which will be used in the matching module to calculate maximum
 * number of occurences of the matched character.
 */
template <typename type> class Heap
{
public:

    /**
     * Constructor
     * Initializes the basic variables used in the heap class
     * @param IntArray[] an integer array of heaps
     * @param Count an integer saying number of items in the array
     */
    Heap(int IntArray[], int Count);

    /**
     * Contructor
     * Initializes the basic variable used in the heap class
     * @param MAXSIZE integer variable which defines the maximum
     * number of inputs which the heap can take.
     */
    Heap(int MAXSIZE);

    /**
     * A public function which returns <template type>
     * This function deletes an element from the heap and returns
     * that element. In max heap, the maximum element is deleted
     * and in min heap, the minimum element is deleted.
     */
    type Delete();

    /**
     * A public function.
     * This function is used to insert element into a heap.
     * @param Item a template type variable of the item to be inserted.
     */
    void Insert(type Item);

    /**
     * A public function
     * This function finds the maximum in the set of inputs and
     * returns it.
     */
    type FindMax();

    /**
     * A public function
     * This function finds the minimum in the heap and return
     * that minimum value or type.
     */
    type FindMin();

    /**
     * A public function.
     * This function checks if the Heap is empty or not.
     * Returns true if the heap is empty or else false.
     */
    bool IsEmpty()
    {
        //IS EMPTY FUNCTION
        return HeapSize == 0;
    }

    /**
     * A Public function.
     * This function sorts the heap and keeps in the array of template  type
     * @param IntArray a template type array which stores the sorted value
     * @param MAX, an integer type which stores the maximum size of the array
     */
    void SORT(type IntAarray[], int MAX);

    /**
     * A public function
     * This function removes the item from the heap as per specified by user.
     * @param item a template type variable denoting the item to be deleted
     */
    void  Remove(type item);

    /**
     * A public function.
     * This function overloads the operator [] so that the heap can be
     * addressed directly.
     * @param index an integer type which is to be retrieved.
     */
    type operator[](int index)
    {
        return HeapArrayPtr[index];
    }

private:

    /**
     * A private pointer of template type
     * This is the pointer to the heap array which stores the heap data
     */
    type * HeapArrayPtr;

    /**
     * A private integer.
     * This integer holds the maximum datas that can be stored in the heap.
     */
    int MaxHeapSize;

    /**
     * A private integer
     * This integer holds the present heap size
     */
    int HeapSize;

    /**
     * A private function
     * This function is used to heapify all the data stored in the array
     * from top of the heap tree to the bottom.
     * @param StartIndex an integer type denoting the node of the tree
     * to start hipification.
     */
    void FilterDown(int StartIndex);

    /**
     * A private function
     * This function is used to heapify all the data stored in the array
     * from bottom of the heap tree to the up.
     * @param StartIndex an integer type denoting the node of the tree
     * to start hipification.
     */
    void FilterUp(int StartIndex);

    /**
     * A private function
     * This function returns the index of the parent of the index provided
     * @param CurrentIndex an integer type denoting the index of the current data
     */
    int Parent(int CurrentIndex)
    {
        return (CurrentIndex - 1) / 2;
    }

    /**
     * A private function.
     * This function returns the index of the right child of current index.
     * @param CurrentIndex an integer type denoting the index of the current data
     */
    int RightChild(int CurrentIndex)
    {
        return 2 * (CurrentIndex + 1);
    }

    /**
     * A private function.
     * This function returns the index of the left child of current index.
     * @param CurrentIndex an integer type denoting the index of the current data
     */
    int LeftChild(int CurrentIndex)
    {
        return 2 * CurrentIndex + 1;
    }

};

/** Constructor declaration */
template <typename type> Heap<type>::Heap(int MAXSIZE)
{
    int *HeapArrayPtr = new int[MAXSIZE] ;
    MaxHeapSize = MAXSIZE;
    HeapSize=0;
}

template <typename type> Heap<type>::Heap(int IntArray[], int Count)
{
    int CurrentPosition;
    if (Count <= 0)
    {
        cerr << "Cannot construct a heap with size 0 or less." << endl;
        exit(1);
    }

    MaxHeapSize = Count;
    HeapSize = Count;
    HeapArrayPtr = IntArray; /** A pointer assignment statement */
    CurrentPosition = (HeapSize - 2) / 2; /** Set CurrentPosition to the last index of a parent node:*/

    while (CurrentPosition >= 0)
    {
        /** Get heap condition for subtree rooted at index CurrentPosition: */
        FilterDown(CurrentPosition);
        CurrentPosition--;
    }
}

/** DELETE()*/
template <typename type> type Heap<type>::Delete()
{

    int Temp;
    if (HeapSize == 0)
    {
        cerr << "Cannot remove from an empty heap" << endl;
        exit(1);
    }

    Temp = HeapArrayPtr[0];   /** Item at index 0 is the smallest */
    HeapArrayPtr[0] = HeapArrayPtr[HeapSize - 1]; /** Copy last one to root: */
    HeapSize--;
    FilterDown(0);   /** readjust to be a heap */
    return Temp;
}

/** FILTER DOWN() */
template <typename type> void Heap<type>::FilterDown(int StartIndex)
{
    int CurrentPosition, ChildPosition, RightChildPosition, Target;
    CurrentPosition = StartIndex;
    Target = HeapArrayPtr[StartIndex];
    ChildPosition = LeftChild(CurrentPosition);

    while (ChildPosition < HeapSize)
    {
        /**  Set ChildPosition to index of smaller of right, left children: */
        RightChildPosition = ChildPosition + 1;

        if ((RightChildPosition < HeapSize) && (HeapArrayPtr[RightChildPosition] <= HeapArrayPtr[ChildPosition]))
            ChildPosition = RightChildPosition;

        if (Target <= HeapArrayPtr[ChildPosition])
            break;  /** Get out of loop, heap OK with Target at CurrentPosition */

        /** Move value of the smaller child to the parent node: */
        HeapArrayPtr[CurrentPosition] = HeapArrayPtr[ChildPosition];
        /** Move down the tree: */
        CurrentPosition = ChildPosition;
        ChildPosition = LeftChild(CurrentPosition);
    }
    /** Put Target into the correct location: */
    HeapArrayPtr[CurrentPosition] = Target;
}

/** FILTER UP() */
template <typename type> void Heap<type>::FilterUp(int StartIndex)
{

    int CurrentPosition, ParentPosition;
    type Target;
    CurrentPosition = StartIndex;
    ParentPosition = Parent(CurrentPosition);
    Target = HeapArrayPtr[StartIndex];

    while (CurrentPosition != 0)
    {
        if (HeapArrayPtr[ParentPosition] <= Target)
            break; /** Get out of loop, heap OK with Target at CurrentPosition */

        /** Move parent value to child: */
        HeapArrayPtr[CurrentPosition] = HeapArrayPtr[ParentPosition];

        /** Move up in the tree: */
        CurrentPosition = ParentPosition;
        ParentPosition = Parent(CurrentPosition);
    }

    /** Place Target at the position located for it: */
    HeapArrayPtr[CurrentPosition] = Target;
}

/** INSERT() */
template <typename type> void Heap<type>::Insert(type Item)
{

    if (HeapSize == MaxHeapSize)
    {
        cerr << "Cannot insert into a full heap" << endl;
        exit(1);
    }

    /** At first, place item at the end of the heap: */
    HeapArrayPtr[HeapSize] = Item;

    /** restore heap property */
    FilterUp(HeapSize);
    HeapSize++;
}

/** SORT() */
template <typename type> void Heap<type>::SORT(type IntArray[], int MAX)
{

    type Smallest;
    int a;
    /** constructor makes IntArray a heap */
    Heap (IntArray, MAX);

    for (a = MAX - 1; a >= 1; a--)
    {
        /** Remove smallest item and place at index k */
        Smallest = Delete();
        /** At this point IntArray[0] contains the largest item by default */
        IntArray[a] = Smallest;
    }

    cout<<"print data in descending order"<<endl;

    for (int k = 0; k <MAX; k++){
        cout << setw(10) << IntArray[k];
    }

    cout << endl;
} 

/** FindMin() */
template <typename type> type Heap<type>::FindMin()
{
    type Temp;

    if (HeapSize == 0){
        cerr << "empty heap" << endl;
        exit(1);
    }

    /** Item at index 0 is the smallest */
    return  Temp = HeapArrayPtr[0];
}

/** FINDMax() */
template <typename type> type Heap<type>::FindMax()
{

    type temp1;
    temp1=HeapArrayPtr[0];

    if (HeapSize == 0)
    {
        cerr << "empty heap" << endl;
        exit(1);
    }

    for(int i=1; i<MaxHeapSize; i++){
	
        if(temp1<HeapArrayPtr[i])
            temp1=HeapArrayPtr[i];

    }
    return temp1;
}

/** Remove() */
template <typename type> void Heap<type>::Remove(type item)
{

    for(int i=0; i<MaxHeapSize; i++)
    {
        if(HeapArrayPtr[i]==item)
        {
            HeapArrayPtr[i] = HeapArrayPtr[HeapSize - 1];
            //      HeapSize--;
        }
    }

    Heap(HeapArrayPtr, MaxHeapSize-1);
}

#endif
