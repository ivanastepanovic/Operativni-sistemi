
#ifndef _PCB_H_
#define _PCB_H_

#include "list.h"

class Thread;
class List;


const int ready=1, blocked=2, done=3, idl=4;  //pitanje je da li mi treba ovo done jer cim je done ja je izbacim

class PCB{
public:
	unsigned int* stack;
	unsigned int stack_size;
	unsigned SS, SP, BP;
	int state;
	unsigned max_time;
	unsigned sleep_time;
	volatile static PCB* running;
	List* wait_to_comp_list;
	Thread* myThread;

	static int context_switch;

	PCB(unsigned size, unsigned time, Thread* t);
	~PCB();
	static void wrapper();
	static PCB* createInitRunning();


	const static PCB* idlePCB;

};


#endif

