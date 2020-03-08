/*
 * system.h
 *
 *  Created on: Jun 3, 2018
 *      Author: OS1
 */

#ifndef OSPRO_SYSTEM_H_
#define OSPRO_SYSTEM_H_

#include "list.h"
#include <dos.h>
#include "thread.h"


#define LOCK asm pushf; asm cli;
#define UNLOCK asm popf;

#define lock ok_to_switch--;
#define unlock ok_to_switch++;


class System{
public:
	static int ok_to_switch;  //Samo ako je 1 onda se sme promeniti kontekst
	static List* sleeping_threads;
	volatile static int cnt;

	static void init();
	static void restore();
	static void interrupt timer(...);
};


class Idle: public Thread{
	void run();
};


#endif /* OSPRO_SYSTEM_H_ */

