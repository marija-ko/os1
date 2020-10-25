/*
 * main.cpp
 *
 *  Created on: Oct 5, 2019
 *      Author: OS1
 */
#include "Thread.h"
#include "System.h"
#include "PCB.h"

extern int userMain(int argc, char* argv[]);
int main(int argc, char* argv[]){
	System::init();
	System::setMain();
	userMain(argc, argv);
	System::restore();
}


