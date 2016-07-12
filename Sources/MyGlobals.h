/*
 * myglobal.h
 *
 *  Created on: Jul 2, 2016
 *      Author: Prosper
 *
 *      Global function for Drone project
 */

#ifndef SOURCES_MYGLOBALS_H_
#define SOURCES_MYGLOBALS_H_

#ifndef DEBUG
	#define LOG(x)	print(x)
#else
	#define LOG(x)
#endif

typedef unsigned char uchar;

void print(const char input[]);
void printInt(const int input);



#endif /* SOURCES_MYGLOBALS_H_ */
