/*
 * IVTEntry.cpp
 *
 *  Created on: Apr 3, 2020
 *      Author: OS1
 */

#include "IVTEntry.h"
#include <dos.h>
#include "KernelEv.h"

IVTEntry* IVT[256];

IVTEntry::IVTEntry(IVTNo ivtNo, pInterrupt routine) {
	entry = ivtNo;
	newRoutine = routine;
	oldRoutine = getvect(entry);
	setvect(entry, routine);
	IVT[entry] = this;
	myEvent = 0;
}

IVTEntry::~IVTEntry() {
	setOld();
	newRoutine = oldRoutine = 0;
	IVT[entry]->myEvent=0;
}
void IVTEntry::callOld(){
	oldRoutine();
}

void IVTEntry::setOld(){
	setvect(entry, oldRoutine);
}

void IVTEntry::signal(){
	myEvent->signal();
}

IVTEntry* IVTEntry::get(IVTNo ivtNo){
	return IVT[ivtNo];
}
