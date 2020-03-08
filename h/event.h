/*
 * event.h
 *
 *  Created on: Jun 22, 2018
 *      Author: OS1
 */

#ifndef OSPRO_EVENT_H_
#define OSPRO_EVENT_H_

typedef unsigned char IVTNo;
class KernelEv;

#include "IVTEntry.h"
#include "KernelEv.h"

class Event{
public:
	Event(IVTNo ivtNo);
	~Event();
	void wait();

protected:
	friend class KernelEv;
	void signal(); //can call KernelEv

private:
	KernelEv* myImpl;
};

//ovde imam nepoznato kernelEvent kao polje koje mi fali u IVTEntry, i lockFlag klase System;
#define PREPAREENTRY(number,old)\
	void interrupt rout##number(...);\
	IVTEntry newEntry##number(number, rout##number);\
	void interrupt rout##number(...){\
		if(newEntry##number.kernelEvent!=0) \
			newEntry##number.kernelEvent->signal();\
		if (old==1 && newEntry##number.old_rout!=0) \
			newEntry##number.old_rout();\
		dispatch();\
	}

#endif /* OSPRO_EVENT_H_ */
