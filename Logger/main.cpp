#include <iostream>
#include "LOG.h"



int main(int argc, char *argv[]) {
	Logger::LOG log;


	//log << "Hello, " << "world!" << std::endl;

	log.set_file_name("MyLogFile");
	log << "Hello, " << "world!" << std::endl;
	log.write("Test", " 2", "\n");



	//system("color 0C");
	//system("pause");
	return 0;
}
