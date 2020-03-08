/*
 * KernelEv.cpp
 *
 *  Created on: Jun 22, 2018
 *      Author: OS1
 */

#include "kernelEv.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "thread.h"
#include "system.h"
#include "IVTEntry.h"

KernelEv::KernelEv(IVTNo ivtNo){
	pcb= (PCB*) PCB::running;
	val = 0;
	IVTEntry::getEntry(ivtNo)->kernelEvent= this;
}

KernelEv::~KernelEv(){
	IVTEntry::getEntry(no)->kernelEvent= 0;
	pcb = 0;
	val=0;
	waiting=0; // da li moze da se desi da neka nit ceka ovde, a onda se pozove destruktor
		 	 	 // onda treba da na ovom mestu tu nit vratim u scheduler jel tako? illi se to nece desiti
}

void KernelEv::wait(){ //samo nit koja je vlasnik dogadjaja, ako je neka druga onda bez dejstva
	LOCK;
	if (PCB::running == pcb) {
		if (val == 0) { // nit moze da se blokira
			val = 1;
			pcb->state= blocked;
			dispatch();
		}
	}
	UNLOCK;
}

void KernelEv::signal(){
	System::lock;
	if (val == 1) {
		val = 0;
		pcb->state=ready;
		Scheduler::put(pcb);
	}
	System::unlock;
}

