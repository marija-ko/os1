/*
 * IVTEntry.h
 *
 *  Created on: Apr 3, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "event.h"
class KernelEv;


typedef void interrupt (*pInterrupt)(...);


class IVTEntry {
public:
	IVTEntry(IVTNo ivtNo, pInterrupt routine);
	virtual ~IVTEntry();
	void callOld();
	void setOld();
	void signal();
	static IVTEntry* get(IVTNo ivtNo);


	IVTNo entry;
	KernelEv* myEvent;
	pInterrupt oldRoutine, newRoutine;

};




#endif /* IVTENTRY_H_ */
