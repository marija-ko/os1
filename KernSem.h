/*
 * KernSem.h
 *
 *  Created on: Oct 18, 2019
 *      Author: OS1
 */

#ifndef KERNSEM_H_
#define KERNSEM_H_

#include "semaphor.h"
class Queue;
class SQueue;

class KernelSem {
public:
	KernelSem(int init, Semaphore* s);
	virtual ~KernelSem();
	int wait(Time maxTimeToWait);
	int signal(int n);
	int val();

	int value;
	Semaphore* mySem;
	Queue* myQueue;



};

#endif /* KERNSEM_H_ */
