/*
 * System.cpp
 *
 *  Created on: Oct 5, 2019
 *      Author: OS1
 */

#include "System.h"
#include "schedule.h"
#include "PCB.h"
#include "SQueue.h"
#include <dos.h>
#include <stdlib.h>
#include <iostream.h>

unsigned oldTimerOFF, oldTimerSEG;
unsigned newTimerOFF, newTimerSEG;
volatile int contextOnDemand;
volatile int counter=20;
int lockValue;

unsigned tsp, tss, tbp;
extern void tick();
extern int activeThreads;


PCB* mainPCB;
extern SQueue* globalSQ;

void System::init(){

	asm{
			cli
			push es
			push ax

			mov ax,0   //  ; inicijalizuje rutinu za tajmer
			mov es,ax

			mov ax, word ptr es:0022h //; pamti staru rutinu
			mov word ptr oldTimerSEG, ax
			mov ax, word ptr es:0020h
			mov word ptr oldTimerOFF, ax

			mov word ptr es:0022h, seg timer	 //postavlja
			mov word ptr es:0020h, offset timer //novu rutinu

			mov ax, oldTimerSEG	 //	postavlja staru rutinu
			mov word ptr es:0182h, ax //; na int 60h
			mov ax, oldTimerOFF
			mov word ptr es:0180h, ax

			pop ax
			pop es
			sti
		}
	}


// vraca staru prekidnu rutinu
void System::restore(){
	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax


		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
		sti
	}
}

void interrupt timer(){
	if (!contextOnDemand) {
		counter--;
		asm int 60h;
		globalSQ->timerTick();
		tick();
	}
	if (counter == 0 || contextOnDemand || (PCB::running->status) == FINISHED) {
		if(lockValue == 0){
			contextOnDemand = 0;
			asm {
				// cuva sp
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			}

			PCB::running->sp = tsp;
			PCB::running->ss = tss;
			PCB::running->bp= tbp;
			if ((PCB::running->status)==READY) Scheduler::put((PCB *) PCB::running);
			PCB::running=Scheduler::get();
			if (PCB::running==0 && activeThreads>0) PCB::running=PCB::idlePCB; // proverim da li je 0, ako jeste, onda stavi idle nit

			tsp = PCB::running->sp;
			tss = PCB::running->ss;
			tbp = PCB::running->bp;

			//ako je timeslice 0  onda neograniceno da se stavi myTimeSlice
			if(PCB::running->myTimeSlice==0){
				counter=-1;
			}else
				counter = PCB::running->myTimeSlice;

			asm {
				mov sp, tsp   // restore sp
				mov ss, tss
				mov bp, tbp
			}
		} else {
				contextOnDemand =1;

			}
		}


	}


System::System() {
	lockValue = 0;
}

System::~System() {
}
void System::dispatch(){
	asm cli;
	contextOnDemand = 1;
	timer();
	asm sti;
}

void System::setMain(){
	Thread* mainT=new Thread();
	PCB::running=mainT->myPCB;
	PCB::running->status=READY;
	PCB::idle=new Idle();
	PCB::idlePCB=PCB::idle->myPCB;
	PCB::idle->start();


}

void locking(){
	lockValue++;
}
void unlocking(){
	if(--lockValue == 0 && contextOnDemand){
		dispatch();
	}
}

