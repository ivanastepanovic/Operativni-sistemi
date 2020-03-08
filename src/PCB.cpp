
#include "PCB.h"
#include <iostream.h>
#include "thread.h"
#include <dos.h>
#include "SCHEDULE.H"
#include "system.h"

int PCB::context_switch= 0;
volatile PCB* PCB::running= 0;


PCB::PCB(unsigned int size, unsigned int time, Thread* t){
	stack_size=size / sizeof(unsigned int);
	max_time=time;
	myThread=t;

	stack= new unsigned int[stack_size];

	System::lock;
	wait_to_comp_list= new List();
	System::unlock;

	System::lock;
	
	#ifndef BCC_BLOCK_IGNORE

		stack[stack_size - 1] = 0x0200;
		stack[stack_size - 2] = FP_SEG(wrapper);
		stack[stack_size - 3] = FP_OFF(wrapper);

		SP = FP_OFF(stack + stack_size - 12);
		BP = SP;
		SS = FP_SEG(stack + stack_size - 12);

		
	#endif

	System::unlock;
}

PCB* PCB::createInitRunning(){
	System::lock;
	Thread* idle= new Idle();
	System::unlock;
	idle->myPCB->state= idl;
	idle->myPCB->max_time=5;
	return idle->myPCB;
}

void PCB::wrapper(){
	running->myThread->run();
	//kada se zavrsi run vratim niti iz wait_to_comp_list u Scheduler
	LOCK;
	List::Elem* cur= running->wait_to_comp_list->head;
	while (cur!=0) {
		cur->pcb->state= ready;
		Scheduler::put(cur->pcb);
		List::Elem* pom= cur->next;
		running->wait_to_comp_list->delete_Elem(cur->pcb);
		cur= pom;
	}
	running->state= done;
	UNLOCK;
	dispatch();
}




const PCB* PCB::idlePCB= PCB::createInitRunning();


PCB::~PCB(){
	delete stack;
	if(wait_to_comp_list!=0) delete wait_to_comp_list;
}


