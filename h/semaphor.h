/*
 * semaphor.h
 *
 *  Created on: Jun 21, 2018
 *      Author: OS1
 */

#ifndef OSPRO_SEMAPHOR_H_
#define OSPRO_SEMAPHOR_H_


class KernelSem;

class Semaphore {
public:
	Semaphore(int init=1);
	virtual ~Semaphore();

	virtual int wait (int toBlock);
	virtual void signal();

	int val () const;

private:
	KernelSem* myImpl;
};


#endif /* OSPRO_SEMAPHOR_H_ */
