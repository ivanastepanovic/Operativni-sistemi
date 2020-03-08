//pretpostavljeni memorijski model: huge

#include <iostream.h>
#include <dos.h>
#include "PCB.h"
#include "thread.h"
#include "system.h"
#include "SCHEDULE.h"
#include "usermain.h"

PCB* mainPCB;
extern int userMain(int argc, char**argv);


int main(int argc, char* argv[]){
  mainPCB= new PCB(defaultStackSize, defaultTimeSlice, 0);
  

  mainPCB->state= ready; //ali treba ready, ovo je samo pokusaj
  PCB::running= mainPCB;

  UserMain *user = new UserMain(argc, argv);

  user->start();


  System::init();

  dispatch();

  System::restore();


  return 0;
}

