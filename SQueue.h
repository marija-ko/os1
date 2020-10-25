/*
 * SQueue.h
 *
 *  Created on: Nov 9, 2019
 *      Author: OS1
 */

#ifndef SQUEUE_H_
#define SQUEUE_H_
#include "PCB.h"
#include "KernSem.h"

typedef unsigned int Time;



class SQueue
{
	struct Elem {
		PCB* pcb;
		Semaphore* sem;
		Time time;
		Elem* next;
		Elem(PCB* p, Semaphore* s, Time t): pcb(p), sem(s), time(t){ next=0; }

	};
public:
	SQueue();
	~SQueue();
	int put(PCB* pcb, Semaphore* s, Time t);
	PCB* get();
	PCB* getById(ID id);
	void deleteThreadById(ID id);
	int size();
	void timerTick();
	Elem* first;
	int length;



};

#endif /* SQUEUE_H_ */
