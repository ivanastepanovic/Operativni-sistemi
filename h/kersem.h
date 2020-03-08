/*
 * kernsem.h
 *
 *  Created on: Jun 21, 2018
 *      Author: OS1
 */

#ifndef OSPRO_KERSEM_H_
#define OSPRO_KERSEM_H_

#include "semaphor.h"
#include "list.h"

class KernelSem{
public:
	int getVal();
	int wait(int toBlock);
	void signal();

	KernelSem(int init);
	~KernelSem();

private:
	int val;
	List* blocked_on_sem;

};



#endif /* OSPRO_KERSEM_H_ */
