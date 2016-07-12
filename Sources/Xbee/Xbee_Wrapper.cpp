/*
 * Xbee_Wrapper.h
 *
 *  Created on: Jul 4, 2016
 *      Author: Prosper
 */

#ifndef SOURCES_XBEE_WRAPPER_H_
#define SOURCES_XBEE_WRAPPER_H_

#include "Xbee.hpp"
#include "MyGlobals.h"


xbeeCom * global_xbee;

extern "C"
{
	void * xbee_init()
	{
		xbeeCom *xbee = new xbeeCom();
		global_xbee = xbee;
		return (void*)xbee;
	}

	void xbee_callback(char data) { global_xbee->callback(data); }
	bool xbee_isData() { return global_xbee->isData(); }
	void xbee_getCMD() { global_xbee->getCMD(); }
	void xbee_deleteCMD(short * cmd) { delete[] cmd; }
}

#endif /* SOURCES_XBEE_WRAPPER_H_ */

