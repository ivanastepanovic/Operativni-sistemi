/*
 * Semaphore.cpp
 *
 *  Created on: Jun 21, 2018
 *      Author: OS1
 */


#include "semaphor.h"
#include "kersem.h"


Semaphore::Semaphore(int init){
	myImpl= new KernelSem(init);
}

int Semaphore::wait(int toBlock) {
	return myImpl->wait(toBlock);
}

void Semaphore::signal(){
	myImpl->signal();
}

Semaphore::~Semaphore(){
	delete myImpl;
}

int Semaphore::val() const {
	return myImpl->getVal();
}




