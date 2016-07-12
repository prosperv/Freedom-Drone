/*
 * Xbee.hpp
 *
 *  Created on: Jul 4, 2016
 *      Author: Prosper
 */

#ifndef SOURCES_XBEE_XBEE_HPP_
#define SOURCES_XBEE_XBEE_HPP_


//#include "Cpu.h"
#include "MyGlobals.h"
#include "queueBuffer.hpp"
#include "uartXbee.h"

#define RX_DATATYPE		uchar
#define TX_DATATYPE		uchar
#define CMD_DATATYPE	short

static const int cmdBuffer_LENGTH = 6;
static const int txBuffer_LENGTH = 6;

typedef unsigned char uchar;



class xbeeCom
{
public:
	xbeeCom(uint32_t * instance);
	xbeeCom();
    ~xbeeCom();
    short * getCMD();
    bool isData();
    bool rdy2ack();
    void sendACK();
    void write(short,short);
//    void print(char*);
    void callback(char);

private:
    uint32_t * instance;
    queue<CMD_DATATYPE> cmdBuffer;
    queue<TX_DATATYPE> txBuffer;
    queue<RX_DATATYPE> rxBuffer;

};

//extern xbeeCom * Xbee;


#endif /* SOURCES_XBEE_XBEE_HPP_ */
