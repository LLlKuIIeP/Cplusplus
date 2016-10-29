#include <iostream>
#include "LOG.h"



int main(int argc, char *argv[]) {
	Logger::LOG log;

	/*	Если не указывать имя лог файла, то по умолчанию
	*	имя файла имеет вид
	*	log_[время в фармате HHMMSS]_[дата в формате ddmmyyyy].log
	*
	*	Например log_125532_07112016.log
	*/

	/*
	*	Перегруженный оператор << - не записывает время и дату
	*/
	log << "Hello, " << "world!" << std::endl;
	
	//	Можно явно указать имя лог файла
	log.set_file_name("MyLogFile");
	log << "Hello, " << "world!" << std::endl;

	/*	Можно указать максимальный размер файла лога в байтах
	*	После превышения размера файла, создается второй файл
	*	с именем [старое имя]_[номер].log
	*
	*	Например MyLogFile_1.log
	*/
	log.set_max_file_size(20);
	//	Если не указан размер, то пишет в один файл

	log << "0123456789-9876543210\n";
	log << "9876543210-0123456789\n";


	/*
	*	Функция write(...) - имеет обязательный первый параметр, остальные не ограницены и
	*	заптсывает время и дату во время каждого вызова
	*/
	log.set_max_file_size(1024);
	log.write(Logger::TYPE_LOG::LOG, "Hello\n");
	log.write(Logger::TYPE_LOG::LOG, "world\n");


	/*
	 *	Можно разбить логирование по трем файлам: 
	 *	1 - обычное логирование(один файл)
	 *	2 - лог для ошибок
	 *	3 - лог для предупреждений
	 */

	/*
	 *	Соответсвенно для каждого из файлов есть имя по умолчанию,
	 *	но можно указать свое имя размер
	*/

	//	Для файла ошибок
	log.set_file_name("Err_MyLogFile", Logger::TYPE_LOG::ERROR);
	//	Устанавливать размер не обязательно
	log.set_max_file_size(1024, Logger::TYPE_LOG::ERROR);

	//	Для файла предупреждений
	log.set_file_name("Warn_MyLogFile", Logger::TYPE_LOG::WARNING);
	log.set_max_file_size(1024, Logger::TYPE_LOG::WARNING);

	//	Записывать в файлы
	log.err() << "Start logging: version " << 1.1 << std::endl;
	log.write(Logger::TYPE_LOG::ERROR, "[ERROR] ", "Hello, world!");


	log.warn() << "Start logging: version " << 1.1 << std::endl;
	log.write(Logger::TYPE_LOG::WARNING, "[WARNING] ", "Hello, world!");



	system("color 0C");
	system("pause");
	return 0;
}
