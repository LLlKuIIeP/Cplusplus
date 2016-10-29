#include "LOG.h"
#include <cstdio>
#include <cerrno>
#include <ctime>
//#include <io.h>

void Logger::check_file_size(const uint64_t size, std::string &name, std::ofstream &file, size_t &number) {
	file.seekp(0, file.end);

	if (size && size < static_cast<size_t>(file.tellp())) {
		file.close();
		auto pos = name.find("_" + std::to_string(number) + ".log");
		if (pos < name.size()) {
			name.erase(pos);
		}
		else {
			name.erase(name.find(".log"));
		}

		number++;
		name.append("_" + std::to_string(number) + ".log");
		file.open(name, std::ios_base::trunc);
	}
}

std::string Logger::get_log_file_name_default() {
	time_t t = time(NULL);
	struct tm *local_time = localtime(&t);
	auto buf_size = 30;
	//	Следующие три варианта эквивалентны
	//std::unique_ptr<char[]> u_ptr(new char[buf_size]);
	//std::unique_ptr<char[]> u_ptr(std::make_unique<char[]>(buf_size));
	auto u_ptr(std::make_unique<char[]>(buf_size));
	strftime(u_ptr.get(), buf_size, "%H%M%S_%d%m%Y", local_time);

	return u_ptr.get();
}



/*
		 _   _   _   _   _
	 	|_  |_| |_| | | |_|
	 	|_  |\  |\  |_| |\
 */	     
 
//public
	Logger::ERROR& Logger::ERROR::operator<<(std::ostream& (*os)(std::ostream &s)) {
		if (!this->file.is_open()) { this->file.open(this->name, std::ios_base::app); }
		if (console) { std::cout << os; }
		this->file << os;

		return *this;
	}

//protected
	Logger::ERROR::ERROR() {}
	Logger::ERROR& Logger::ERROR::get_this() { return *this; }

	int Logger::ERROR::set_file_name(const std::string &name, const bool flag = false) {
		mutex_file.lock();
		if (file.is_open()) {
			file.close();
		}
		if (!flag) { this->name = name; }
		else { this->name.append(name); }

		this->name.append(".log");

		//if (!_access(name.c_str(), 0)) {
			//std::cout << "File exist" << std::endl;
			//std::remove(name.c_str());
		//}

		mutex_file.unlock();
		return 0;
	}

	void Logger::ERROR::set_max_file_size(uint64_t size) { this->size = size; }

	int Logger::ERROR::write_log() {
		Logger::check_file_size(size, name, file, number);
		mutex_file.unlock();
		file.open(name, std::ios_base::app);
		return 0;
	}

	void Logger::ERROR::set_console(bool cons) { this->console = cons; }

	Logger::ERROR::~ERROR() { this->file.close(); }

//private
	std::string Logger::ERROR::get_date() {
		t = time(NULL);
		local_time = localtime(&t);
		auto buf_size = 30;
		auto u_ptr(std::make_unique<char[]>(buf_size));

		strftime(u_ptr.get(), buf_size, "%d.%m.%Y %H:%M:%S\t\t", local_time);
		std::string str(u_ptr.get());
		return str;
	}



/*
		      _   _       _ _       __
		|  | |_| |_| |\ |  |  |\ | | _
		|/\| | | |\  | \| _|_ | \| |__|
*/


//public
	Logger::WARNING::WARNING() {}
	Logger::WARNING& Logger::WARNING::get_this() { return *this; }

	int Logger::WARNING::set_file_name(const std::string &name, const bool flag = false) {
		mutex_file.lock();
		if (file.is_open()) {
			file.close();
		}
		if (!flag) { this->name = name; }
		else { this->name.append(name); }

		this->name.append(".log");
		mutex_file.unlock();

		return 0;
	}

	void Logger::WARNING::set_max_file_size(uint64_t size) { this->size = size; }
	
	int Logger::WARNING::write_log() {
		Logger::check_file_size(size, name, file, number);
		mutex_file.unlock();
		file.open(name, std::ios_base::app);
		return 0;
	}
	
	void Logger::WARNING::set_console(bool cons) { this->console = cons; }

	Logger::WARNING::~WARNING() {
		this->file.close();
	}

//private
	std::string Logger::WARNING::get_date() {
		t = time(NULL);
		local_time = localtime(&t);
		auto buf_size = 30;
		auto u_ptr(std::make_unique<char[]>(buf_size));

		strftime(u_ptr.get(), buf_size, "%d.%m.%Y %H:%M:%S\t\t", local_time);
		std::string str(u_ptr.get());
		return str;
	}





/*
		     _   __
		|   | | | _
		|__ |_| |__|
*/

//public
	Logger::LOG::LOG() : ERROR(), WARNING() {
		std::string name = Logger::get_log_file_name_default();
		Logger::ERROR::set_file_name(name, true);
		Logger::WARNING::set_file_name(name, true);
		this->name.append("log_");
		this->name.append(name);
	}
	Logger::ERROR& Logger::LOG::err() { return Logger::ERROR::get_this(); }
	Logger::WARNING& Logger::LOG::warn() { return Logger::WARNING::get_this(); }

	Logger::LOG& Logger::LOG::operator<<(std::ostream& (*os)(std::ostream &s)) {
		if (!this->file.is_open()) {
			this->file.open(this->name, std::ios_base::app);
		}

		if (console) { std::cout << os; }
		this->file << os;
		return *this;
	}

	int Logger::LOG::set_file_name(const std::string &name, TYPE_LOG type) {
		switch (type) {
			case Logger::TYPE_LOG::LOG : {
				mutex_file.lock();
				this->file.close();
				this->name = name + ".log";
				this->file.open(this->name, std::ios_base::trunc);
				mutex_file.unlock();
				break;
			}
			case Logger::TYPE_LOG::ERROR : {
				Logger::ERROR::set_file_name(name, false);
				break;
			}
		default:
			break;
		}

		return 0;
	}

	void Logger::LOG::set_max_file_size(uint64_t size, Logger::TYPE_LOG type) {
		switch (type)
		{
		case Logger::TYPE_LOG::LOG:
			this->size = size;
			break;
		case Logger::TYPE_LOG::ERROR:
			Logger::ERROR::set_max_file_size(size);
			break;
		case Logger::TYPE_LOG::WARNING:
			Logger::WARNING::set_max_file_size(size);
			break;
		case Logger::TYPE_LOG::INFO:
			break;
		default:
			break;
		}
	}

	void Logger::LOG::set_console(bool cons, Logger::TYPE_LOG type) {
		switch (type)
		{
		case Logger::TYPE_LOG::LOG:
			this->console = cons;
			break;
		case Logger::TYPE_LOG::ERROR:
			Logger::ERROR::set_console(cons);
			break;
		case Logger::TYPE_LOG::WARNING:
			Logger::WARNING::set_console(cons);
			break;
		case Logger::TYPE_LOG::INFO:
			break;
		default:
			break;
		}
	}

//private
	std::string Logger::LOG::get_date() {
		t = time(NULL);
		local_time = localtime(&t);
		auto buf_size = 30;
		auto u_ptr(std::make_unique<char[]>(buf_size));

		strftime(u_ptr.get(), buf_size, "%d.%m.%Y %H:%M:%S\t\t", local_time);
		std::string str(u_ptr.get());
		return str;
	}

	int Logger::LOG::write_log() {
		Logger::check_file_size(size, name, file, number);
		mutex_file.unlock();
		file.open(name, std::ios_base::app);

		return 0;
	}



Logger::LOG::~LOG() {
	//Logger::ERROR::~ERROR();
	//Logger::WARNING::~WARNING();
	//Logger::ERROR::~ERROR();
	this->file.close();
}
