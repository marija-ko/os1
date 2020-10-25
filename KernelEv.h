/*
 * KernelEv.h
 *
 *  Created on: Apr 2, 2020
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_


class PCB;
class Event;
typedef unsigned char IVTNo;


class KernelEv {
public:
	KernelEv(IVTNo ivtNo);
	virtual ~KernelEv();
	void wait();
	void signal();

	int val;
	PCB* owner;
	IVTNo ivtNo;

};

#endif /* KERNELEV_H_ */
