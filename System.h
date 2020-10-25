/*
 * System.h
 *
 *  Created on: Oct 5, 2019
 *      Author: OS1
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_
void interrupt timer();

class System {
public:
	System();
	static void init();
	static void restore();


	static void setMain();
	static void dispatch();

	virtual ~System();
};

#endif /* SYSTEM_H_ */
