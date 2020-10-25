/*
 * Idle.h
 *
 *  Created on: Oct 22, 2019
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_

#include "Thread.h"

class Idle: public Thread {
public:
	Idle();
	virtual ~Idle();
	void run();
	void start();
};

#endif /* IDLE_H_ */
