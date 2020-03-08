/*
 * IVTEndtry.cpp
 *
 *  Created on: Jun 22, 2018
 *      Author: OS1
 */
#include "IVTEntry.h"
#include "dos.h"


IVTEntry* IVTEntry::entries[256];

IVTEntry* IVTEntry::getEntry(IVTNo no){
	return entries[no];
}

IVTEntry::IVTEntry(IVTNo no, routine new_rout){
	this->no= no;
	entries[no]= this;
#ifndef	BCC_BLOCK_IGNORE
	old_rout= getvect(no);
	setvect(no, new_rout);
#endif
}


IVTEntry::~IVTEntry(){
		#ifndef BCC_BLOCK_IGNORE
		setvect(no, old_rout);
		entries[no] = 0;
		#endif
		//delete entries[no]; // ovo ok, ne?s
}




