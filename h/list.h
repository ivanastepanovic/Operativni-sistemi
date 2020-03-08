/*
 * list.h
 *
 *  Created on: May 13, 2018
 *      Author: OS1
 */


#ifndef OSPRO_LIST_H_
#define OSPRO_LIST_H_

#include "PCB.h"
class PCB;

class List{
public:
	struct Elem{
		PCB* pcb;
		Elem* next;

		Elem(PCB* p){
			pcb=p;
			next=0;
		}
	};

	Elem* head, *tail;

	List();
	~List();

	//PCB* get_Elem();
	void add_Elem(PCB* p);
	void delete_Elem(PCB* p);
};




#endif /* OSPRO_LIST_H_ */
