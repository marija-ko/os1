/*
 * Event.cpp
 *
 *  Created on: Apr 2, 2020
 *      Author: OS1
 */

#include "Event.h"
#include "KernelEv.h"

extern void locking();
extern void unlocking();

Event::Event(IVTNo ivtNo) {
	locking();
	myImpl = new KernelEv(ivtNo);
	unlocking();

}

Event::~Event() {
	locking();
	delete myImpl;
	unlocking();
}

void Event::wait(){
	myImpl->wait();
}

void Event::signal(){
	myImpl->signal();
}

