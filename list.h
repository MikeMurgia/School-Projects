//Michael Murgia
//Section 8
//Due date: 4/26/24



// Fig. 21.4: list.h
// Template List class definition.
#ifndef LIST_H
#define LIST_H

#include <iostream>

using std::cout;

#include <new>
#include "listnode.h"  // ListNode class definition

template< class NODETYPE >
class List {

public:
   List();      // constructor
   ~List();     // destructor
   void insertAtFront( const NODETYPE & );
   void insertAtBack( const NODETYPE & );
   bool removeFromFront( NODETYPE & );
   bool removeFromBack( NODETYPE & );
   bool isEmpty() const;
   void print() const;

	bool insertMiddle( const NODETYPE &, int pos);
	bool removeMiddle( NODETYPE &, int pos);
	List(const List& val);
	List& operator=(const List& val);


private:
   ListNode< NODETYPE > *firstPtr;  // pointer to first node
   ListNode< NODETYPE > *lastPtr;   // pointer to last node

   // utility function to allocate new node
   ListNode< NODETYPE > *getNewNode( const NODETYPE & );

}; // end class List

//new functions

template< class NODETYPE >
bool List< NODETYPE >::insertMiddle(const NODETYPE & val, int pos)
{
	if (pos <= 1 || isEmpty())
	{
		insertAtFront(val);
		return true;
	}
	
	ListNode<NODETYPE>* newNode = new ListNode<NODETYPE>(val);
	ListNode<NODETYPE>* current = firstPtr;
	ListNode<NODETYPE>* prev = nullptr;
	int index = 0;

	while(current != nullptr && index < pos)
	{
		prev = current;
		current = current->nextPtr;
		index++;
	}
	if (current == nullptr)
	{
		insertAtBack(val);
		return true;
	}

	prev->nextPtr = newNode;
	newNode->nextPtr = current;

	return true;
}


template< class NODETYPE >
bool List< NODETYPE >::removeMiddle(NODETYPE& val, int pos)
{
	if (pos <= 0 || isEmpty())
		return false;

	ListNode<NODETYPE>* current = firstPtr;
	ListNode<NODETYPE>* prev = nullptr;
	int index = 0;
	
	while(current != nullptr && index < (pos-1))
	{
		prev = current;
		current = current->nextPtr;
		index++;
	}
	if (current == nullptr)
		return false;	

	if (prev == nullptr)
		firstPtr = current->nextPtr;
	else
		prev->nextPtr = current->nextPtr;

	val = current->data;
	delete current;

	return true;
}

template< class NODETYPE >
List<NODETYPE>::List(const List& val) : firstPtr(nullptr), lastPtr(nullptr)
{
	ListNode<NODETYPE>* current = val.firstPtr;
	while (current != nullptr)
	{
		insertAtBack(current->data);
		current = current->nextPtr;
	}
}

template<class NODETYPE>
List<NODETYPE>& List<NODETYPE>::operator=(const List& val)
{
	if (this == &val)
		return *this;

	while (firstPtr != nullptr)
	{
		NODETYPE node;
		removeFromFront(node);
	}

	ListNode<NODETYPE>* current = val.firstPtr;
	while(current != nullptr)
	{
		insertAtBack(current->data);
		current = current->nextPtr;
	}
	return *this;
}




// default constructor
template< class NODETYPE >
List< NODETYPE >::List() 
   : firstPtr( 0 ), 
     lastPtr( 0 ) 
{ 
   // empty body

} // end List constructor

// destructor
template< class NODETYPE >
List< NODETYPE >::~List()
{
   if ( !isEmpty() ) {    // List is not empty
//      cout << "Destroying nodes ...\n";

      ListNode< NODETYPE > *currentPtr = firstPtr;
      ListNode< NODETYPE > *tempPtr;

      while ( currentPtr != 0 )         // delete remaining nodes
      {  
         tempPtr = currentPtr;

// commented out the output -- no need to print what we are deallocating
//         cout << tempPtr->data << '\n';  

         currentPtr = currentPtr->nextPtr;
         delete tempPtr;

      }

   }

//   cout << "All nodes destroyed\n\n";

} // end List destructor

// insert node at front of list
template< class NODETYPE >
void List< NODETYPE >::insertAtFront( const NODETYPE &value )
{
   ListNode< NODETYPE > *newPtr = getNewNode( value );

   if ( isEmpty() )  // List is empty
      firstPtr = lastPtr = newPtr;

   else {  // List is not empty
      newPtr->nextPtr = firstPtr;
      firstPtr = newPtr;

   } // end else

} // end function insertAtFront

// insert node at back of list
template< class NODETYPE >
void List< NODETYPE >::insertAtBack( const NODETYPE &value )
{
   ListNode< NODETYPE > *newPtr = getNewNode( value );

   if ( isEmpty() )  // List is empty
      firstPtr = lastPtr = newPtr;

   else {  // List is not empty
      lastPtr->nextPtr = newPtr;
      lastPtr = newPtr;

   } // end else

} // end function insertAtBack

// delete node from front of list
template< class NODETYPE >
bool List< NODETYPE >::removeFromFront( NODETYPE &value )
{
   if ( isEmpty() )  // List is empty
      return false;  // delete unsuccessful

   else {  
      ListNode< NODETYPE > *tempPtr = firstPtr;

      if ( firstPtr == lastPtr )
         firstPtr = lastPtr = 0;
      else
         firstPtr = firstPtr->nextPtr;

      value = tempPtr->data;  // data being removed
      delete tempPtr;

      return true;  // delete successful

   } // end else

} // end function removeFromFront

// delete node from back of list
template< class NODETYPE >
bool List< NODETYPE >::removeFromBack( NODETYPE &value )
{
   if ( isEmpty() )
      return false;  // delete unsuccessful

   else {
      ListNode< NODETYPE > *tempPtr = lastPtr;

      if ( firstPtr == lastPtr )
         firstPtr = lastPtr = 0;
      else {
         ListNode< NODETYPE > *currentPtr = firstPtr;

         // locate second-to-last element
         while ( currentPtr->nextPtr != lastPtr )
            currentPtr = currentPtr->nextPtr;

         lastPtr = currentPtr;
         currentPtr->nextPtr = 0;

      } // end else

      value = tempPtr->data;
      delete tempPtr;

      return true;  // delete successful

   } // end else

} // end function removeFromBack

// is List empty?
template< class NODETYPE > 
bool List< NODETYPE >::isEmpty() const 
{ 
   return firstPtr == 0; 
   
} // end function isEmpty

// return pointer to newly allocated node
template< class NODETYPE >
ListNode< NODETYPE > *List< NODETYPE >::getNewNode( 
   const NODETYPE &value )
{
   return new ListNode< NODETYPE >( value );

} // end function getNewNode

// display contents of List
template< class NODETYPE >
void List< NODETYPE >::print() const
{
   if ( isEmpty() ) {
      cout << "The list is empty\n\n";
      return;

   } // end if

   ListNode< NODETYPE > *currentPtr = firstPtr;

   cout << "The list is: ";

   while ( currentPtr != 0 ) {
      cout << currentPtr->data << ' ';
      currentPtr = currentPtr->nextPtr;

   } // end while

   cout << "\n\n";

} // end function print

#endif

/**************************************************************************
 * (C) Copyright 1992-2003 by Deitel & Associates, Inc. and Prentice      *
 * Hall. All Rights Reserved.                                             *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
