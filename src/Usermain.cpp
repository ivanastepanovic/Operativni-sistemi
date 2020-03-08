#include "usermain.h"
#include "schedule.h"
extern int userMain(int argc, char**argv);
extern PCB* mainPCB;

UserMain::UserMain(int argc_, char** argv_){
	argc=  argc_;
	argv = argv_;	
}

void UserMain::run(){
	userMain(argc, argv);
	Scheduler::put(mainPCB);
}

UserMain::~UserMain(){
	waitToComplete();
}
