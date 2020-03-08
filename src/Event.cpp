/*
 * Event.cpp
 *
 *  Created on: Jun 22, 2018
 *      Author: OS1
 */


#include "event.h"
#include "system.h"
#include "kernelEv.h"


Event::Event(IVTNo ivtNo){
LOCK;
	myImpl= new KernelEv(ivtNo);
UNLOCK;
}

Event::~Event(){
	delete myImpl;
}

void Event::wait(){
	myImpl->wait();
}

void Event::signal(){
	myImpl->signal();
}
