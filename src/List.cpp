/*
 * List.cpp
 *
 *  Created on: May 13, 2018
 *      Author: OS1
 */

#include "list.h"
#include "system.h"

List::List(){
	head=0; tail=0;
}


//ubacuje element na kraj
void List::add_Elem(PCB* p){
	LOCK;
	Elem* new_elem= new Elem(p);
	UNLOCK;
	if (head==0) {
		head=tail=new_elem;
	}
	else {
		tail->next =new_elem;
		tail= tail->next;
	}
}


/*

//ubacuje element na pocetak
void List::add_Elem(PCB* p){
	LOCK;
	Elem* new_elem= new Elem(p);
	UNLOCK;
	if (head==0) head=tail=new_elem;
	else {
		new_elem->next= head;
		head= new_elem;
	}
}

*/

void List::delete_Elem(PCB* p){
	Elem* cur= head;
	Elem* prev=0;

	if (head==0) return;

	while(cur && cur->pcb!=p) {
		prev=cur; cur=cur->next;
	}

	if (cur==0) 
		return; //nisam nasla elem
	else {
		if (head==tail) {
			delete cur;
			tail=head=0;
		}
		else{
			if(cur==head) {
				head= head->next;
				delete cur;
			}
			else {
				prev->next= cur->next;
				if (tail==cur) tail= prev;
				delete cur;
			}
		}
	}
}


List::~List(){
	for (Elem* cur=head; cur!=0; ){
		head= cur;
		cur= cur->next;
		delete head;
	}
}





