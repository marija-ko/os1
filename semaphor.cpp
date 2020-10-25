/*
 * semaphor.cpp
 *
 *  Created on: Oct 18, 2019
 *      Author: OS1
 */

#include "semaphor.h"
#include "KernSem.h"

extern void locking();
extern void unlocking();

Semaphore::Semaphore(int init){
	locking();
	myImpl= new KernelSem(init, this);
	unlocking();
}

Semaphore::~Semaphore() {
	locking();
	delete myImpl;
	unlocking();
}
int Semaphore::wait (Time maxTimeToWait){
	if (myImpl->wait(maxTimeToWait)){
		return 1;
	}
	return 0;
}
int Semaphore::signal(int n){
	if(myImpl->signal(n)) {
		return 1;
	}
	return 0;
}
int Semaphore::val () const{
	return myImpl->val();
}

