/*
 * Idle.cpp
 *
 *  Created on: Oct 22, 2019
 *      Author: OS1
 */

#include "Idle.h"
#include "PCB.h"
#include <iostream.h>


extern volatile int activeThreads;
extern void locking();
extern void unlocking();

Idle::Idle(): Thread(256,1) {

}

Idle::~Idle() {

}
void Idle::run(){
	while(activeThreads>0){
	}
}
void Idle::start(){
	locking();
	myPCB->createStack();
	myPCB->status=READY;
	unlocking();
}

