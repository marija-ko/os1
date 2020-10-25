/*
 * Thread.cpp
 *
 *  Created on: Oct 5, 2019
 *      Author: OS1
 */

#include <iostream.h>
#include "System.h"
#include "Thread.h"
#include "PCB.h"
#include "schedule.h"
#include "Queue.h"

extern void locking();
extern void unlocking();

void Thread::start(){
	myPCB->start();
}
void Thread::waitToComplete(){
	locking();
	if((this->myPCB)==PCB::running||(this->myPCB->status)==FINISHED) {
		unlocking();
		return;
	}
	(PCB::running->status)=BLOCKED;
	myPCB->myQueue.put(PCB::running);
	unlocking();
	dispatch();
}
Thread::~Thread(){
	locking();
	waitToComplete();
	if(myPCB!=0) delete myPCB;
	unlocking();
}
ID Thread::getId(){
	return myPCB->myId;
}
ID Thread::getRunningId(){
	if (PCB::running!=0){
		return PCB::running->myId;
	}
}
Thread * Thread::getThreadById(ID id){
	locking();
	PCB* temp = 0;
	temp = PCB::PCBQueue.peekById(id);

	if (temp == 0 ){
		unlocking();
		return 0;
	}
	else {
		unlocking();
		return temp->myThread;
	}
}
Thread::Thread (StackSize stackSize, Time timeSlice){
	locking();
	myPCB= new PCB(this, stackSize, timeSlice);
	unlocking();
}



void dispatch(){
	System::dispatch();
}
