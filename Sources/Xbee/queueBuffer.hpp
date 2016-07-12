/*
 * queue.h
 *
 *  Created on: Jul 2, 2016
 *      Author: Prosper
 */

#ifndef SOURCES_QUEUEBUFFER_HPP_
#define SOURCES_QUEUEBUFFER_HPP_

#include <cstddef>

#define DEFAULT_MAX_QUEUE_LENGTH 12
//typedef 0x0 NULL;
template <class T>
class queue
{
public:

	queue();				// Queue constructor
    queue(int);
    ~queue();				// Queue destructor
    bool isEmpty();			// Check for an empty queue.
    void clear();			// Clears the entire queue.
    void add( T* );			// Push commandData into the queue.
    void add( T ); 			// Push commandData into the queue.
    T* peek();				// Look at the last item in the queue.
    T* popPtr();			// Pop the top item off the queue.
    T pop();				// Pop the top item off the queue.
    int queueLength();		// Return how many objects are in the queue.

private:
    int length;
    const int maxLength;

    struct queueNode                // Node object for the queue.
    {
        queueNode( T* array )
        {
            data = array;
            next = NULL;
        }
        ~queueNode()
        {}

        T* data;				// Pointer to the StructureItem object.
        queueNode * next;       // Next node in the queue.
    };
    queueNode * front;          // Root of the queue.
};


#endif /* SOURCES_QUEUEBUFFER_HPP_ */
