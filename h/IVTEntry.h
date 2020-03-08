/*
 * IVTEntry.h
 *
 *  Created on: Jun 22, 2018
 *      Author: OS1
 */

#ifndef OSPRO_IVTENTRY_H_
#define OSPRO_IVTENTRY_H_

typedef unsigned char IVTNo;

class KernelEv;
class Event;

typedef void interrupt (*routine)(...);

class IVTEntry{
public:

	IVTEntry(IVTNo no, routine new_rout);
	static IVTEntry* getEntry(IVTNo no);
	routine old_rout;
	~IVTEntry();

	KernelEv* kernelEvent;

private:
	static IVTEntry* entries[256];
	IVTNo no;


};


#endif /* OSPRO_IVTENTRY_H_ */
