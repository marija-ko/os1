/*
 * KernSem.cpp
 *
 *  Created on: Oct 18, 2019
 *      Author: OS1
 */

#include <iostream.h>
#include "KernSem.h"
#include "PCB.h"
#include "SQueue.h"
#include "schedule.h"

extern SQueue* globalSQ;
extern void deblock(PCB* p);
extern void locking();
extern void unlocking();

KernelSem::KernelSem(int init, Semaphore* s) {
	value=init;
	myQueue=new Queue();
	mySem=s;

}

KernelSem::~KernelSem() {
	Queue::ElemQ* cur = myQueue->first;
	for(int i = 0; i < myQueue->length; i++){
		PCB* temp = myQueue->get();
		deblock(temp);
		globalSQ->getById(temp->myId);
	}

	delete myQueue;
}

int KernelSem::wait(Time maxTimeToWait){

	int ret;
	if(--value<0){
		locking();
		int unlimited;
		if (maxTimeToWait == 0) unlimited=1; else unlimited=0;
		PCB::running->status = BLOCKED;
		PCB* temp = PCB::running;
		myQueue->put(PCB::running); //stavljam u moj red
		if (unlimited == 0) {
			ret = globalSQ->put(PCB::running, mySem, maxTimeToWait); //ako je ogranicena stavljam i u globalnu listu blokiranih
			if (ret == 0){
				unlocking();
				return -1;
			}
		}
		unlocking();

		dispatch();

		locking();
		if(temp->timeOut) {
			ret = 0;
			temp->timeOut = 0;
		} else {
			ret = 1;
		}
		unlocking();

		return ret;

	} else {
		return 1;
	}
}

int KernelSem::signal(int n){
	if(n<0) return n;

	if (n == 0){
		if(value++<0){
				locking();
				PCB* temp = myQueue->get();
				if (temp != 0){
					deblock(temp);
					globalSQ->getById(temp->myId);
					unlocking();
					return 0;
				}
		}
	} else {
		locking();
		int unblocked = 0;
		for (int i=0; i<n; i++){		//n puta povecavam value
			if (value<0){
				value++;
				PCB* temp = myQueue->get();
				if (temp != 0){
					deblock(temp);
					unblocked++;
					globalSQ->getById(temp->myId);
				}
			} else{
				value++;
			}
		}
		unlocking();
		return unblocked;
	}
}

int KernelSem::val(){
	return value;
}

