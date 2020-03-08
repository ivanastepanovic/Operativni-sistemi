/*
 * kernelEv.h
 *
 *  Created on: Jun 22, 2018
 *      Author: OS1
 */

#ifndef OSPRO_KERNELEV_H_
#define OSPRO_KERNELEV_H_

class Event;
#include "PCB.h"

typedef unsigned char IVTNo;

class KernelEv{
public:
	KernelEv(IVTNo ivtNo);
	~KernelEv();
	void wait();
	void signal();

private:
	int val;
	PCB* pcb;
	int waiting;
	IVTNo no;
};

#endif /* OSPRO_KERNELEV_H_ */
