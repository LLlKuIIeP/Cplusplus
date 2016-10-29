#include "LOG.h"
#include <cstdio>
#include <cerrno>
#include <ctime>
#include <memory>
//#include <io.h>

bool Logger::check_file_size(const uint64_t size, std::string &name, std::ofstream &file, size_t &number) {
	file.seekp(0, file.end);
	//std::cout << "check_file_size\n";
	if (size && size < static_cast<size_t>(file.tellp())) {
		//std::cout << "if\n";
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
		return true;
	}
	return false;
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
		     _   __
		|   | | | _
		|__ |_| |__|
*/

//public
	Logger::LOG::LOG() {
		std::string name = Logger::get_log_file_name_default();

		this->name.append(name);
		this->name.append(".log");
	}


	Logger::LOG& Logger::LOG::operator<<(std::ostream& (*os)(std::ostream &s)) {
		std::lock_guard<std::mutex> lock(mutex_file);
		if (!this->file.is_open()) {
			this->file.open(this->name, std::ios_base::app);
		}
		
		//std::cout << os;
		this->file << os;
		return *this;
	}

	int Logger::LOG::set_file_name(const std::string &name) {

		std::lock_guard<std::mutex> lock(mutex_file);
		this->file.close();
		this->name = name + ".log";
		this->file.open(this->name, std::ios_base::trunc);

		return 0;
	}

	void Logger::LOG::set_max_file_size(uint64_t size) {
		this->size = size;
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
		//mutex_file.unlock();
		//file.open(name, std::ios_base::app);

		return 0;
	}



Logger::LOG::~LOG() {

	this->file.close();
}