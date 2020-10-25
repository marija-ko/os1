/*
 * PCB.cpp
 *
 *  Created on: Oct 5, 2019
 *      Author: OS1
 */

#include <dos.h>
#include "iostream.h"
#include "PCB.h"
#include "Queue.h"
#include "Idle.h"
#include "schedule.h"

PCB* PCB::running=0;
Idle* PCB::idle=0;
PCB* PCB::idlePCB=0;
ID PCB::stId=1;
Queue PCB::PCBQueue;
volatile int activeThreads=0;
extern void locking();
extern void unlocking();

PCB::PCB(Thread* myT, StackSize stackS, Time timeS) {
	myThread = myT;
	myTimeSlice = timeS;
	myStackSize = stackS;
	myId = stId++;
	timeOut = 0;
	PCBQueue.put(this);

}

void PCB::wrapper(Thread* myThread){
	myThread->run();
	myThread->myPCB->status=FINISHED;
	activeThreads--;
	while(myThread->myPCB->myQueue.size()>0){
		PCB* temp=myThread->myPCB->myQueue.get();
		temp->status=READY;
		Scheduler::put(temp);
	}
	dispatch();
}

void PCB::createStack(){
	StackSize stackSize=myStackSize;
	stackSize /= sizeof(unsigned);
	stack=new unsigned[stackSize];
	stack[stackSize-1] = FP_SEG(myThread);//argument moje funkcije wrappera
	stack[stackSize-2] = FP_OFF(myThread);
	//-3 i -4 idu delovi za callback funkciju
	stack[stackSize-5] = 0x200;//PSW I bit
	stack[stackSize-6] = FP_SEG(wrapper); //moram da obezbedim da poslednja linija bude dispatch zbog callback fje koji nemam
	stack[stackSize-7] = FP_OFF(wrapper);
	ss=FP_SEG(stack+stackSize-16); //bilo bi -12 ako nemam argument wrappera
	sp=FP_OFF(stack+stackSize-16);
	bp=sp;
}

void PCB::start(){
	locking();
	createStack();
	status=READY;
	Scheduler::put(this);
	activeThreads++;
	unlocking();

}

PCB::~PCB() {
	PCB* temp= PCBQueue.get();
	for(int i=0; i<PCBQueue.size();i++){
		if(temp->myId!=myId){
			PCBQueue.put(temp);
		}
	}
}

