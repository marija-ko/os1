/*
 * Prepare.h
 *
 *  Created on: Apr 4, 2020
 *      Author: OS1
 */

#ifndef PREPARE_H_
#define PREPARE_H_

#include "KernelEv.h"
#include "IVTEntry.h"


#define PREPAREENTRY(ivtNo, callOldR) \
void interrupt inter##ivtNo(...); \
IVTEntry ivtEntry##ivtNo(ivtNo,inter##ivtNo); \
void interrupt inter##ivtNo(...) { \
	ivtEntry##ivtNo.signal(); \
	if(callOldR == 1) \
		ivtEntry##ivtNo.callOld();} \


#endif /* PREPARE_H_ */
