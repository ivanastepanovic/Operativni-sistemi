#ifndef Usermain_H_
#define Usermain_H_


#include "Thread.h"


class UserMain:public Thread{
	private:
		int argc;
		char **argv;

	public:
		UserMain(int argc_, char** argv_);
		~UserMain();
		void run();
};

#endif;