/*
 * queue.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: Prosper
 */

#include "queueBuffer.hpp"

template <class T>
queue<T>::queue() : maxLength(DEFAULT_MAX_QUEUE_LENGTH)
{
	length = 0;
    front = NULL;   // Set front to NULL at the start.
}

template <class T>
queue<T>::queue(int max) : maxLength(max)
{
	length = 0;
    front = NULL;   // Set front to NULL at the start.
}

template <class T>
queue<T>::~queue()
{
    clear();        // Clear the entire queue.
}


template <class T>
bool queue<T>::isEmpty()
{
    // Is the queue empty?
    if( front == NULL ) // Check the front pointer.
        return true;    // Queue is empty, return true.
    return false;       // There is atleast one item, not empty.
}


template <class T>
void queue<T>::clear()
{
    // Is the list already empty?
    if( isEmpty() )     // Check for an empty list.
        return;         // List is empty, don't need to do anything.

    queueNode * current = front;    // Create node to help step through list.
    queueNode * placeHold = front;  // Create node to keep place of delete.

    // As long as were not at the end, keep stepping to the next node.
    while( current != NULL)
    {
        placeHold = current->next;  // Hold where we have to go.
        delete current;             // Delete the node.
        current = placeHold;        // Set current to the next node.
    }

    front = NULL;   // Reset the front to NULL;
    length = 0;
}

template <class T>
void queue<T>::add( T item )
{
	T * temp = new T(item);
	add(temp);
}

template <class T>
void queue<T>::add( T * item )
{
    // Were we passed an invalid object somehow?
    if( item == NULL )  // Check for NULL
        return;         // If so, return.

    if( queueLength() > maxLength )
    {
    	pop();
    	return;
    }

    queueNode * newNode = new queueNode( item );    // Create the new node.

    if( isEmpty() )
        front = newNode;        // Set front to the new node.
    else
    {
        queueNode *temp = front;
        while( temp->next != NULL )
            temp = temp->next;

        temp->next = newNode;
    }
    length++;
}

template <class T>
T queue<T>::pop()
{
	T *temp = popPtr();
	T item = *temp;
	delete temp;
	return item;
}

template <class T>
T * queue<T>::popPtr()
{
    // Is the list already empty?
	T * dataout = NULL;
    if( isEmpty() )     			// Check for an empty list.
    {
        return dataout;    					// List is empty, don't need to do anything.
    }

    dataout = front->data;  	// Keep track of what were returning.
    queueNode * oldNode = front;    // Save the old node to be deleted
    front = front->next;            // Set front to next object.

    delete oldNode;                 // Delete the front node.
    length--;						// Remove one from the length.
    return dataout;					// return the stuctureItem.
}


template <class T>
T * queue<T>::peek()
{
    if( front != NULL )
        return front->data;

    return NULL;
}



template <class T>
int queue<T>::queueLength()
{
    return length;
}


template class queue<unsigned char>;
template class queue<short>;
