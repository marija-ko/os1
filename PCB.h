/*
 * PCB.h
 *
 *  Created on: Oct 5, 2019
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

enum State{READY, BLOCKED, FINISHED};
class Queue;
class Idle;
class PCB{

public:
	PCB(Thread* myThread, StackSize stackSize, Time timeSlice);
	virtual ~PCB();

	void createStack();
	static void wrapper(Thread* myThread);
	void start();

	static Queue PCBQueue;
	static ID stId;

	unsigned* stack;
	unsigned ss, sp, bp;
	State status;

	Thread* myThread;
	StackSize myStackSize;
	Time myTimeSlice;
	Queue myQueue;
	ID myId;
	int timeOut;

	static PCB* running;
	static Idle* idle;
	static PCB* idlePCB;

};

#endif /* PCB_H_ */
