
/*
 * System.cpp
 *
 *  Created on: Jun 3, 2018
 *      Author: OS1
 */

#include "system.h"
#include "list.h"
#include "thread.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include <iostream.h>
#include <dos.h>

extern PCB* mainPCB;

int System::ok_to_switch=1;

LOCK;
List* System::sleeping_threads= new List();
UNLOCK;

static int oldTimerOFF, oldTimerSEG;        // stara prekidna rutina

volatile int System::cnt=5; // inicijalizacija
unsigned temp_sp, temp_ss, temp_bp;
void Idle::run(){

	for ( ; ; ) ;
}
void tick();
void interrupt System::timer(...){


	if (PCB::context_switch == 0) {
			if(cnt>0) cnt--;
			tick();
			List::Elem* cur= System::sleeping_threads->head;  //smanjiti sleep_time u listi uspavanih niti i staviti ako treba neke u Scheduler
			while( cur!=0) {
				List::Elem* next= cur->next;

				cur->pcb->sleep_time--;
				if (cur->pcb->sleep_time==0) {
					cur->pcb->state=ready;
					Scheduler::put(cur->pcb);
					System::sleeping_threads->delete_Elem(cur->pcb);
				}
				cur=next;
			}

			#ifndef BCC_BLOCK_IGNORE
			asm int 60;
			#endif
	}

	if ((cnt == 0 && PCB::running->max_time!=0 )|| PCB::context_switch ) {

			if (ok_to_switch != 1) {
				PCB::context_switch=1;
				return;
			}

			PCB::context_switch=0;
			#ifndef BCC_BLOCK_IGNORE
			asm {
			// cuva sp
				mov temp_sp, sp
				mov temp_ss, ss
				mov temp_bp, bp
			}
			#endif
			PCB::running->SP = temp_sp;
			PCB::running->SS = temp_ss;
			PCB::running->BP = temp_bp;

			if (PCB::running->state == ready && PCB::running!=mainPCB) 
				Scheduler::put((PCB*)PCB::running);
			PCB::running= Scheduler::get();
			if (PCB::running==0) 
				PCB::running= (volatile PCB*)PCB::idlePCB;
			cnt= PCB::running->max_time;

			temp_sp = PCB::running->SP;
			temp_ss = PCB::running->SS;
			temp_bp = PCB::running->BP;

			#ifndef BCC_BLOCK_IGNORE
			asm {
				mov sp, temp_sp   // restore sp and bp
				mov bp, temp_bp
				mov ss, temp_ss
				
			}
			#endif

	}

}


void System::init(){
	#ifndef BCC_BLOCK_IGNORE

	setvect(60, getvect(8));
	setvect (8, timer);


	#endif
}


// vraca staru prekidnu rutinu
void System:: restore(){
#ifndef BCC_BLOCK_IGNORE

	setvect(8, getvect(60));

#endif
}
