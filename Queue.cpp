/*
 * Queue.cpp
 *
 *  Created on: Oct 13, 2019
 *      Author: OS1
 */

#include "Queue.h"
#include "PCB.h"
#include <iostream.h>
#include "SQueue.h"

class PCB;
extern SQueue* globalSQ;
extern void locking();
extern void unlocking();

Queue::Queue(){

	locking();
	first = 0;
	last = 0;
	length = 0;
	unlocking();
}

void Queue::put(PCB* p) {
	locking();
	if (first == 0) {
		first = new ElemQ();
		first->pcb = p;
		first->next = 0;
		last = first;

	} else {
		ElemQ* cur;
		for (cur = first; cur->pcb != p && cur->next != 0; cur = cur->next);
		if (cur->next != 0) { //vec je u listi
			unlocking();
			return;
		} else {
			ElemQ* newElem = new ElemQ();
			newElem->pcb = p;
			last = last->next = newElem;
			last->next = 0;
		}
	}
	length++;

	unlocking();
}
PCB* Queue::get() {
	if (length == 0) {
		return 0;
	}
	PCB* temp;
	temp = first->pcb;
	if(first->next == 0){
		first = 0;
		length = 0;
		last = 0;
	} else{
		first = first->next;
		length--;
	}
	return temp;
}
PCB* Queue::getById(ID id) {
	if (length == 0) return 0;
	Queue::ElemQ* cur = first;
	Queue::ElemQ* prev = 0;
	while (cur != 0 && cur->pcb->myId != id) {
		prev = cur;
		cur = cur->next;
	}
	if (cur == 0){
		return 0;
	}
	PCB* temp = cur->pcb;
	if(prev != 0) {
		prev->next = cur->next;
	}
	else first = first->next;
	length--;
	return temp;

}
PCB* Queue::peekById(ID id){
	if (length == 0) return 0;
	ElemQ* cur = first;
	while(cur->pcb->myId != id && cur != 0){
		cur = cur->next;
	}
	if (cur == 0) {
		return 0;
	} else {
		return cur->pcb;
	}
}

int Queue::size() {
	return length;
}


Queue::~Queue(){

	ElemQ* old, *cur=first;
	while (cur!=0) {
		old = cur;
		cur = cur->next;
		delete old;
	}
	first = last = 0;
}
