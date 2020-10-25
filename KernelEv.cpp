/*
 * KernelEv.cpp
 *
 *  Created on: Apr 2, 2020
 *      Author: OS1
 */

#include <iostream.h>
#include "KernelEv.h"
#include "PCB.h"
#include "Schedule.h"
#include "IVTEntry.h"

extern void locking();
extern void unlocking();


KernelEv::KernelEv(IVTNo ivtNo) {
	val = 0;
	this->ivtNo = ivtNo;
	owner = PCB::running;
	IVTEntry::get(ivtNo)->myEvent = this;
}

KernelEv::~KernelEv() {
	locking();
	if (IVTEntry::get(ivtNo)!=0)
		IVTEntry::get(ivtNo)->myEvent = 0;
	owner = 0;
	unlocking();
}

void KernelEv::signal(){
	locking();
	if(val==0 && owner->status == BLOCKED){
		owner->status = READY;
		Scheduler::put(owner);
	}
	else{
		val = 1;
	}
	unlocking();
}

void KernelEv::wait(){
	if (PCB::running != owner) return;
	if (val == 0){
		owner->status = BLOCKED;
		dispatch();
	} else {
		val = 0;
	}

}

