/*
 * Xbee.cpp
 *
 *  Created on: Jul 4, 2016
 *      Author: Prosper
 */

#include "Xbee.hpp"

//xbeeCom * Xbee;

xbeeCom::xbeeCom()	: cmdBuffer(cmdBuffer_LENGTH)
					, txBuffer(txBuffer_LENGTH)
{
	this->instance = NULL;
}

xbeeCom::xbeeCom(uint32_t * instance ) //:	cmdBuffer(cmdBuffer_LENGTH),
										//txBuffer(txBuffer_LENGTH)
{
	this->instance = instance;
}

xbeeCom::~xbeeCom()
{
	cmdBuffer.~queue();
}


void xbeeCom::callback(char data)
{
//	LOG("Callback\r\n");
	rxBuffer.add(data);
}

bool xbeeCom::isData()
{
    static char packetIndex = 0;
    static char pack_cmd = 0;
    static char pack_value[2] = {0,0};
    static char pack_seq = 0;
    static char pack_checksum = 0;

//    __disable_irq();
    while ( !rxBuffer.isEmpty() )
    {
    	uchar data = rxBuffer.pop();
//        __enable_irq();
//        PRINTF("d: %d \n\r", data);
//        LOG(&data);
        switch (packetIndex)
        {
            case 0:
            {
            	if (data == 255)
            	{
            		packetIndex++;
            	}
                break;
            }
            case 1:
            {
                if ( data < 13 )
                {
                    pack_cmd = data;
                    packetIndex++;
                }
                else
                    packetIndex = 0;
                break;
            }
            case 2:
            {
            	if (data < 128)
            	{
                    pack_value[1] = data;
                    packetIndex++;
            	}
                else
                    packetIndex = 0;
                break;
            }
            case 3:
            {
                if ( data < 128 )
                {
                    pack_value[0] = data;
                    packetIndex++;
                }
                else
                    packetIndex = 0;
                break;
            }
            case 4:
            {
                if ( data < 128 )
                {
					pack_seq = data;
					packetIndex++;
                }
				else
					packetIndex = 0;
                break;
            }
            case 5:
            {
            	CMD_DATATYPE added_checksum = pack_value[0] + pack_cmd;
                pack_checksum = data;
                if ( added_checksum == pack_checksum )
                {
                	TX_DATATYPE * ackPacket = new TX_DATATYPE[2];
                    ackPacket[0] = pack_cmd;
                    ackPacket[1] = pack_seq;
                    txBuffer.add( ackPacket ); // Ack the packet with sequence nuber.

                    CMD_DATATYPE * array = new CMD_DATATYPE[2];
                    array[0] = pack_cmd;
                    array[1] = pack_value[1] * 128 + pack_value[0];
                    cmdBuffer.add( array );
                }

                packetIndex = 0;
                break;
            }
            default:
            packetIndex = 0;
            break;
        }


    }
//    __enable_irq();
    return !cmdBuffer.isEmpty();
    return 0;
}

short * xbeeCom::getCMD()
{
	short * temp = 0;
    if ( !cmdBuffer.isEmpty() )
    {
    	sendACK();
    	temp = cmdBuffer.popPtr();
        return temp;
    }
    else
        return NULL;
}


bool xbeeCom::rdy2ack()
{
    return !txBuffer.isEmpty();
//	return true;
}

void xbeeCom::sendACK()
{
//    __disable_irq();

    if( !txBuffer.isEmpty() )
    {
    	TX_DATATYPE * pkt = 0;
        pkt = txBuffer.popPtr();
        write(pkt[0],pkt[1]); //may need to disable interrupt
        delete[] pkt;

    }
//    __enable_irq();
}

void xbeeCom::write( short xbeeCommand, short seq  )
{
//    xbee.putc( 255 );                     // End of message.
//    xbee.putc( (char)xbeeCommand );           // xbeeCommand
//    xbee.putc( (char) seq);            // Second 8 bits in array.
//    xbee.putc( (char) xbeeCommand + seq );        // Checksum array[0] + array[1].
	TX_DATATYPE packet[4];
	packet[0] = 255;
	packet[1] = xbeeCommand;
	packet[2] = seq;
	packet[3] = xbeeCommand + seq;
	LPSCI_DRV_SendDataBlocking(uartXbee_IDX,packet,4,5);
}

//void xbeeCom::print(char* str)
//{
////    __disable_irq();
////    xbee.printf(str);
////    __enable_irq();
//}


