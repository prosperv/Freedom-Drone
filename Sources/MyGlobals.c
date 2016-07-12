/*
 * myglobal.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: Prosper
 */

#include "MyGlobals.h"
#include "uartXbee.h"

void print(const char input[])
{
	uchar temp;
	int size = -1;
	do
	{
		size++;
		temp = input[size];
	} while (temp != 0);

	LPSCI_DRV_SendData(uartXbee_IDX, (const uint8_t *) input, size);
}

void printInt(const int input)
{
	char out[10];
	int temp = input;
	int mod = 1000000;
	int size = 0;
	char firstNum = true;
	while (mod > 0)
	{
		int digit = temp / mod;
		digit %= 10;
		if (digit == 0 && firstNum)
		{
			mod /= 10;
			continue;
		}
		else
		{
			mod /= 10;
			firstNum = false;
			out[size++] = digit + 48;
		}
	}
	out[size] = 0;
	LPSCI_DRV_SendData(uartXbee_IDX, (const uint8_t *) out, size);

}

