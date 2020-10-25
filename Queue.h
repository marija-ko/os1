/*
 * Queue.h
 *
 *  Created on: Oct 13, 2019
 *      Author: OS1
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include "Thread.h"
class PCB;

class Queue{

	struct ElemQ {
		PCB* pcb;
		ElemQ* next;
	};

public:
	Queue();
	virtual ~Queue();

	void put(PCB* pcb);
	PCB* get();
	PCB* getById(ID id);
	PCB* peekById(ID id);
	int size();
	ElemQ* first, *last;
	int length;

};

#endif /* QUEUE_H_ */
