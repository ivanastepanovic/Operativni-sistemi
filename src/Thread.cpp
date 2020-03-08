/*
 * Thread.cpp
 *
 *  Created on: May 7, 2018
 *      Author: OS1
 */

#include "thread.h"
#include "dos.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "system.h"
#include <iostream.h>


Thread::Thread (StackSize stackSize, Time timeSlice){
	System::lock;
	PCB* newPCB= new PCB(stackSize, timeSlice, this);
	System::unlock;
	myPCB= newPCB;
}

void Thread::start(){
	this->myPCB->state= ready;
	Scheduler::put(this->myPCB);
}

void dispatch (){
	LOCK;
	PCB::context_switch=1; //zahtevala sam promenu konteksta
	System::timer();
	UNLOCK;
}

void Thread::sleep(Time timeToSleep){
	System::lock;
	if (timeToSleep > 0){
		PCB::running->sleep_time= timeToSleep;
		PCB::running->state=blocked;
		System::sleeping_threads->add_Elem((PCB*)PCB::running);
	}
	System::unlock;
	dispatch();
}

void Thread:: waitToComplete(){
	if (PCB::running == this->myPCB)
		return;
	if (this->myPCB->state == done)
		return;

	System::lock;
	PCB::running->state=blocked;
	this->myPCB->wait_to_comp_list->add_Elem((PCB*)PCB::running);
	System::unlock;
	dispatch();
}

Thread::~Thread(){
	waitToComplete();
	LOCK;
	delete myPCB;
	UNLOCK;
}



