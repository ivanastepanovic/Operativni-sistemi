/*
 * KerSem.cpp
 *
 *  Created on: Jun 21, 2018
 *      Author: OS1
 */

#include "kersem.h"
#include "SCHEDULE.H"
#include "PCB.h"
#include "thread.h"
#include "System.h"

KernelSem::KernelSem(int init){

	if (init<0)
		val=1;
	else
		val= init;


	System::lock;
	blocked_on_sem= new List();
	System::unlock;
}

void KernelSem::signal(){
	System::lock;
	val++;
	if (val<=0){
		blocked_on_sem->head->pcb->state=ready;
		Scheduler::put(blocked_on_sem->head->pcb);
		blocked_on_sem->delete_Elem(blocked_on_sem->head->pcb);
	}
	System::unlock;
}

int KernelSem::wait(int toBlock){
	LOCK;
	if (toBlock==0){
		if (val>0) {
			val--;
			UNLOCK;
			return 0;
		}
		else {
			UNLOCK;
			return -1;
		}
	}

	val--;
	if (val<0){
		blocked_on_sem->add_Elem((PCB*)PCB::running);
		PCB::running->state = blocked;
		dispatch();
		UNLOCK;
		return 1; //blokirala se
	}
	else {
		UNLOCK;
		return 0;
	}
}


int KernelSem::getVal(){
	return val;
}

KernelSem::~KernelSem(){
	System::lock;
	while (blocked_on_sem->head!=0){
		PCB* elem= blocked_on_sem->head->pcb;
		elem->state=ready;
		Scheduler::put(elem);
		blocked_on_sem->delete_Elem(elem);
	}
	System::unlock;
}

