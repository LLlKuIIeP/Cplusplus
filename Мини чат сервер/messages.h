#pragma once


bool send_message_all(int fd, std::unordered_map<int,std::string> &u_map_client, std::string &str_1);

//	Функция записывает исключения(exception) в файл exception_log
void error_log(const char *name_function, const int int_err, const char *string_err);
// Функция записывает сообщение сообщение, при отправке которого произошла ошибка в файл error_log
void error_msg(std::string &message);
//	Функция записывает ошибки системных вызовов в файл error_log
void exception_log(const char *exc);
//	Функция логирования
void log(const char *s);
