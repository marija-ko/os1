/*
 * SQueue.cpp
 *
 *  Created on: Nov 9, 2019
 *      Author: OS1
 */

#include "SQueue.h"
#include <iostream.h>
#include "schedule.h"

extern void locking();
extern void unlocking();
SQueue* globalSQ=new SQueue();

void deblock(PCB* p) {
	p->status=READY;
	Scheduler::put(p);
}


SQueue::SQueue(){
	first = 0;
	length = 0;
}

int SQueue::put(PCB* pcb, Semaphore* s, Time t) {
	locking();

	Elem* newElem = new Elem(pcb,s, t);

	if (first == 0) {
		first = newElem;
	}
	else {
		Elem* cur = first;
		for (; cur->pcb != pcb && cur->next != 0; cur = cur->next);
		if (cur->next != 0) {
			unlocking();
			return 0; //u listi je vec
		}
		if (first->time > newElem->time) { //ako ima najmanje vreme, prvi je
			newElem->next = first;
			first = newElem;
		}
		else {
			cur = first;
			while (cur->next != 0 && cur->next->time <= newElem->time) {
				cur = cur->next;
			}
			if(cur->next!=0) newElem->next = cur->next; else newElem->next = 0;
			cur->next = newElem;
		}
		cur = 0;
	}
	length++;

	unlocking();
	return 1;
}


int SQueue::size() {
	return length;
}

void SQueue::timerTick() {
	if (length == 0) {
		return;
	}
	Elem* cur = first;
	while(cur!=0){
		--cur->time;
		if (cur->time == 0) {
			PCB* p = cur->sem->myImpl->myQueue->getById(cur->pcb->myId);
			p = get();
			p->timeOut = 1;
			deblock(cur->pcb);
		}
		//prev = cur;
		cur = cur->next;
	}
	cur = 0;
}
PCB* SQueue::get() {

	if (length == 0) return 0;
	PCB* temp;
	Elem* tempE;
	temp = first->pcb;
	tempE = first;
	first = first->next;
	length--;
	return temp;
}

PCB* SQueue::getById(ID id) {
	if (length == 0) return 0;
	Elem* cur;
	Elem* prev = 0;

	cur = first;
	while (cur != 0 && cur->pcb->myId != id) {
		prev = cur;
		cur = cur->next;
	}

	if (cur == 0) {
		return 0;
	}
	PCB* temp = cur->pcb;
	if(prev != 0){
		prev->next = cur->next;
	}
	else first = first->next;
	length--;
	return temp;

}
void SQueue::deleteThreadById(ID id) {
	if (length == 0) return;
	Elem* cur;
	Elem* prev;
	Elem* temp;
	int ret;

	cur = first;
	while (cur != 0 && cur->pcb->myId != id) {
		prev = cur;
		cur = cur->next;
	}

	if (cur == 0) {
		return; //neuspelo
	}
	if(cur == first){
		temp = first;
		first = first->next;
		cur->next = 0;
		delete temp;
		length--;
		return;
	} else if(cur->next == 0 && cur != first){
		temp = cur;
		prev->next = 0;
		delete temp;
		length--;
		return;
	} else {
		temp = cur;
		prev->next = cur->next;
		cur->next = 0;
		delete temp;
		length--;
	}
}

SQueue::~SQueue()
{
	Elem* old, *cur = first;
	while (cur != 0) {
		deblock(cur->pcb);
		old = cur;
		cur = cur->next;
		delete old;
	}
	first=0;
}

