/***********************************************************************
* Header:
*    Deque
* Summary:
*    This class contains the notion of a Deque:
*
*    This will contain the class definition of:
*        Deque         : represents a circular line. You can add or 
*                        remove from either the back or the front of 
*                        the line. If the line is full the capacity
*                        will double
*       
* Author
*    edited by Mariah Ashley
************************************************************************/

#ifndef DEQUE_H
#define DEQUE_H

#include <cassert>
#include <iostream>
using namespace std;

/************************************************
 * Deque
 * A class that holds stuff
 ***********************************************/
template <class T>
class Deque
{
  public: 
   // default constructor : creates an empty Deque
   Deque() : numItems(0), cap(0), data(NULL), theFront(0), theBack(-1) {} 
   //when the first item is pushed, a Deque will be created with a cap of 1
   //front will be 0 and theBack will be -1. back will be changed to zero, the item will be pushed into
   //data[theBack], and numItems will be incremented to 1

   //if the deque is full, then cap will be doubled, what is in start will go to data[0]and the line subsequent 
   // items will follow in order from second to last items, theBack will become the location after the last item, and the new item will be pushed 
   // into the new theBack location

   // copy constructor : copy it
   Deque(const Deque & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Deque(int capacity) throw (const char *);
   
   ~Deque()             { if (!empty()) delete [] data;    }

   //overload = operator
   Deque & operator = (const Deque <T> & rhs);

   // is the Deque currently empty?
   bool empty() const   { return (numItems == 0);}

   // how many items are currently in the Deque?
   int size() const     { return numItems;              }

   //What is the Deque's capacity?
   int capacity()       { return cap;                   }

   // remove all the items from the Deque
   void clear()         { numItems = 0;                 }

   //if the Deque is empty, add 1 to capacity, if it's full, double the capacity
   void push_front(const T & t);
   //if the Deque is empty, add 1 to capacity, if it's full, double the capacity
   void push_back(const T & t);

   //pop from the front of the stack and increment front by 1
   void pop_front() throw (const char *);
   //pop from the  back of the stack and decrement back by 1
   void pop_back() throw (const char *);

   //Find the first item location that entered the Deque which will be the front of the Deque
   T front() throw (const char *);
   // find the last item in the stack
   T back() throw (const char *);

   private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Deque?
   int cap;           // how many items can I put on the Deque before full?
   int theFront;    // the front of the Deque/first item in the Deque
   int theBack;       // the back of the Deque/last item in the Deque

}; //close Deque class

/**********************************************
 * Deque : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Deque to "capacity"
 **********************************************/
template <class T>
Deque <T> :: Deque(int capacity) throw (const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->cap = this->numItems = 0;
      this->theFront = 0;
      this->theBack = -1;
      this->data = NULL;
      return;
   }
   
   // attempt to allocate
   try
   {
      data = new T[capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   this-> cap = capacity;
   this-> numItems = 0;
   this->theFront = 0;
   this->theBack = -1;

   for (int i = 0; i < capacity; i++)
   {
      data[i] = T();
   }
   
}

/*******************************************
 * Stack :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Deque <T> :: Deque(const Deque <T> & rhs) throw (const char *)
{
  data = NULL;
  numItems = 0;
  cap = 0;
  theFront = 0;
  theBack = -1;
  *this = rhs;
}

/**********************************************
 * Deque : OVERLOAD ASSIGNMENT OPERATOR
 * 
 **********************************************/
template <class T>
Deque <T> & Deque <T> :: operator = (const Deque <T> & rhs)
{      
   assert(rhs.cap >= 0);
   // do nothing if there is nothing to do

   if (rhs.cap == 0)
   {
      theFront = 0;
      theBack = -1;
      cap = 0;
      numItems = 0;
      delete [] data;
      data = NULL;
      return *this;
   }
   // attempt to allocate
   try
   {
      data = new T[rhs.cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.cap;
   numItems = rhs.numItems;
   theFront = rhs.theFront;
   theBack = rhs.theBack;
   
   // copy the items over one at a time using the assignment operator
     for (int i = 0; i < cap; i++)
     {
      data[i] = rhs.data[i];
     }
     return *this;
   }

/**********************************************
 * Deque : FRONT()
 * Finds the front of the Deque
 **********************************************/
template <class T>
T Deque <T> :: front() throw (const char *)
{
   if(!empty())
   {
      return data[theFront];
   }
   else
   {
      throw "ERROR: unable to access data from an empty deque";
   }
}
/**********************************************
 * Deque : BACK()
 * Finds the back of the Deque
 **********************************************/
template <class T>
T Deque <T> :: back() throw (const char *)
{
   if(!empty())
   {
      if (theBack < 0 && cap > 0)
      {
        theBack = ((theFront - 1) + numItems) % cap;
      }
      return data[theBack];
   }
   else
   {
     throw "ERROR: unable to access data from an empty deque";
   }
}

/**********************************************
*Deque : PUSH_FRONT()
* Pushes a new item to the front of the stack,
* and decrement front by one
********************************************/
template <class T>
void Deque <T> :: push_front(const T & t)
{
    //if the array is empty
   if (numItems == 0 && data == NULL)
   {
      //create the new array with capacity of 1
      cap++; //cap should be 1 now
      data = new T[cap];  
      theBack++; //move back from -1 to 0
      data[theFront] = t; // front starts at location 0
      numItems++; //numItems should be 1 now
   }
   else if (numItems == cap)      
   {
       //if it's full:
       //we will copy the Deque into a new array with double capacity, then insert the new item
       //to the front and decrement front by 1

       int oldCap = cap;
       T * temp; //create a temporary array
       cap *= 2; //double the capacity
       temp = new T[cap]; //allocate the temporary array
       
       //set the temporary array equal to the current data array
       int j = theFront;
       for (int i = 0; i < numItems; i++, j = (j + 1 ) % oldCap)
       {
         temp[i] = data[j];

       }
          //delete the old array
       delete [] data;
        
       //a new data array is created and the temporary array is copied into it
       data = temp;
       theBack = numItems - 1; //the default for back is -1, it should now be 0
       numItems++;
       theFront = cap - 1; //what was in front is now in location 0 so front needs to 
                      //decrement by 1 to push the new item
       data[theFront] = t; 
   }
   else//if the array isn't full, and numItems > 0 add to back and increment back
   {  
       theFront = (theFront - 1) % cap;
       if (theFront < 0)
       {
          theFront = cap - 1;
       }
       data[theFront] = t;
       numItems++;
   }    
}

/**********************************************
*Deque : PUSH_BACK()
* Pushes a new item to the back of the stack,
* and adds 1 to back
********************************************/
template <class T>
void Deque <T> :: push_back(const T & t)
{
    //if the array is empty
   if (numItems == 0 && data == NULL)
   {
      //create the new array with capacity of 1
      cap++;
      data = new T[cap];  
      theBack++; 
      data[theBack] = t;
      numItems++;
   }
   else if (numItems == cap)      
   {
       //the array is full when theBack is equal to cap and front is 0 
       //or if front is one more than back (front is the next location after back)

       //if it's full:
       //we will copy the Deque into a new array with double capacity, then insert the new item
       //and increment back by 1
       int oldCap = cap;
       T * temp; //create a temporary array
       cap *= 2; //double the capacity
       temp = new T[cap]; //allocate the temporary array
       
       //set the temporary array equal to the current data array
       int j = theFront;
       for (int i = 0; i < numItems; i++, j = (j + 1 ) % oldCap)
       {
         temp[i] = data[j];
       }
          //delete the old array
       delete [] data;
        
       //a new data array is created and the temporary array is copied into it
       data = temp;
       numItems++;
       theFront = 0;
       theBack = numItems -1; //numItems starts at 0 and theBack starts at -1, so subtract 1
       data[theBack] = t; 
   }
   else//if the array isn't full, add to back and increment back
   {  
      theBack = (theBack + 1) % cap;
      data[theBack] = t;
      numItems++;
   }    
}

/**********************************************
 * Deque : POP_FRONT()
 * Pops the front item off the the Deque and 
 * increment front by 1
 **********************************************/
template <class T>
void Deque <T> :: pop_front() throw (const char *)
{
   if(!empty())
   {
       theFront = (theFront + 1) % cap;
       numItems--; 
   }
   else
   {
       throw "ERROR: unable to pop from the front of empty deque";
   }
}

/**********************************************
 * Deque : POP_BACK()
 * Pops the front item off the back of the Deque 
 * and decrement back by 1
 **********************************************/
template <class T>
void Deque <T> :: pop_back() throw (const char *)
{
   if(!empty())
   {
       theBack = (theBack - 1) % cap;
       if (theBack < 0)
       {
          theBack = cap - 1;
       }
       numItems--; 
   }
   else
   {
       throw "ERROR: unable to pop from the back of empty deque";
   }
}
#endif //Deque