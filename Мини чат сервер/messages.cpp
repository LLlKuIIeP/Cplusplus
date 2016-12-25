#include <fstream>

#include "chat_server.h"
#include "messages.h"


bool send_message_all(int fd, std::unordered_map<int, std::string> &u_map_client, std::string &str_1) {
	try {

		for(auto it = u_map_client.begin(); it != u_map_client.end(); it++) {
			if(it->first != fd) {
				std::string s(it->second);
				s += ": ";
				s += str_1;
				if(send(it->first, &(s.front()), s.size(), MSG_NOSIGNAL) == -1) {
					error_log("send_message_all -> send", errno, strerror(errno));
					error_msg(s);
					return false;
				}
			}
		}
		return true;
	}
	catch(...) {

	}
}


//	Функция записывает ошибки системных вызовов в файл error_log
void error_log(const char *name_function, const int int_err, const char *string_err) {
	std::ofstream file_error("error.log", std::ios_base::app);


	file_error << "Name function: " << name_function << std::endl
					<< "Error (errno): "<< string_err 
					<< "("<< int_err << ")" << std::endl;


	file_error.close();
}


// Функция записывает сообщение сообщение, при отправке которого произошла ошибка в файл error_log
void error_msg(std::string &message) {
	std::ofstream file_error("error.log", std::ios_base::app);

	file_error << message << std::endl;

	file_error.close();
}


//	Функция записывает исключения(exception) в файл exception_log
void exception_log(const char *exc) {
	std::ofstream file_exception("exception.log", std::ios_base::app);

	file_exception << exc << std::endl;

	file_exception.close();
}


//	Функция логирования
void log(const char *s) {
	std::ofstream log("log", std::ios_base::app);

	log << s << std::endl;

	log.close();
}
