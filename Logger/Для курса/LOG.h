#include <string>
#include <fstream>
#include <mutex>
#include <sstream>
#include <iostream>
#include <cstdint>

#include <io.h>


#pragma once


namespace Logger {
	std::string get_log_file_name_default();
	enum class LEVEL : unsigned int { ZERO, ONE, TWO };
	enum class TYPE_LOG : unsigned int { LOG, ERROR, INFO, WARNING };

	void check_file_size(uint64_t, std::string&, std::ofstream&, size_t&);


	class ERROR {
	public:
		ERROR(ERROR&&) = delete;
		ERROR& operator=(const ERROR&) = delete;
		ERROR& operator=(const ERROR&&) = delete;

		template<class T>
		ERROR& operator<<(const T &arg) {
			if (!this->file.is_open()) {
				this->file.open(this->name, std::ios_base::trunc);
			}
			mutex_file.lock();
			if (console) {
				std::cout << arg;
			}
			file << arg;
			write_log();
			return *this;
		}
		ERROR& operator<<(std::ostream& (*os)(std::ostream &s));

	protected:
		ERROR();
		ERROR& get_this();
		int set_file_name(const std::string&, const bool);
		void set_max_file_size(uint64_t);
		

		template<class... Types>
		int write(const Types&... param) {
			mutex_file.lock();
			date = get_date();
			if (console) {
				std::cout << date;
			}
			//if (!_access(name.c_str(), 0)) {
			//	std::cout << "File exist" << std::endl;
			//}

			if (!file.is_open()) { 
				this->file.open(this->name, std::ios_base::trunc);
			}
			file << date;
			write_log(param...);

			return 0;
		}
		template<class T, class... Types>
		int write_log(const T &par, const Types&... param) {
			if (console) {
				std::cout << par;
			}
			file << par;
			write_log(param...);
			return 0;
		}
		int write_log();

		void set_console(bool);

		~ERROR();

	private:
		std::ofstream file;
		uint64_t size{ 0 };
		time_t t{ 0 };
		size_t number{ 0 };
		struct tm *local_time{ nullptr };

		std::string date{ "" };
		std::mutex mutex_file;

		std::string name{ "err_" };
		bool console{ false };

		std::string get_date();
		
	};

	class WARNING {
	public:
		WARNING(WARNING&&) = delete;
		WARNING& operator=(const WARNING&) = delete;
		WARNING& operator=(const WARNING&&) = delete;
		
		template<class T>
		WARNING& operator<<(const T &arg) {
			if (!this->file.is_open()) {
				this->file.open(this->name, std::ios_base::trunc);
			}
			mutex_file.lock();
			if (console) {
				std::cout << arg;
			}
			file << arg;
			write_log();
			return *this;
		}

		
	protected:
		WARNING();
		WARNING& get_this();
		void set_max_file_size(uint64_t);
		int set_file_name(const std::string&, const bool);
		
		template<class... Types>
		int write(const Types&... param) {
			mutex_file.lock();
			date = get_date();
			if (console) {
				std::cout << date;
			}
			if (!file.is_open()) {
				this->file.open(this->name, std::ios_base::trunc);
			}
			file << date;
			write_log(param...);

			return 0;
		}
		template<class T, class... Types>
		int write_log(const T &par, const Types&... param) {
			if (console) {
				std::cout << par;
			}
			file << par;
			write_log(param...);
			return 0;
		}
		int write_log();

		void set_console(bool);
		~WARNING();

	private:
		std::ofstream file;
		uint64_t size{ 0 };
		time_t t{ 0 };
		size_t number{ 0 };
		struct tm *local_time{ nullptr };

		std::string date{ "" };
		std::mutex mutex_file;

		std::string name{ "" };
		bool console{ false };

		std::string get_date();
	};

	class INFO {
		//INFO() = delete;
		//INFO(const INFO&) = delete;
		INFO& operator=(const INFO&) = delete;
	protected:
		int set_level(unsigned int);
		int print(std::string&);
	private:
		std::string name;
		unsigned int lvl_;
		bool screen_;
	};




	//class LOG : protected ERROR, protected INFO, protected WARNING {
	class LOG : protected ERROR, protected WARNING {
	public:
		LOG();
		LOG(LOG&) = delete;
		LOG(LOG&&) = delete;
		LOG& operator=(const LOG&) = delete;
		LOG& operator=(const LOG&&) = delete;
		ERROR& err();
		WARNING& warn();

		template<class T>
		LOG& operator<<(const T &arg) {
			if (!this->file.is_open()) {
				this->file.open(this->name, std::ios_base::app);
			}
			mutex_file.lock();
			if (console) {
				std::cout << arg;
			}
			file << arg;
			write_log();
			return *this;
		}
		LOG& operator<<(std::ostream& (*os)(std::ostream &s));

		int set_file_name(const std::string &name, TYPE_LOG type = TYPE_LOG::LOG);
		void set_max_file_size(uint64_t size, TYPE_LOG type = TYPE_LOG::LOG);

		template<class... Types>
		int write(const TYPE_LOG &type, const Types&... param) {

			switch (type) {
				case TYPE_LOG::LOG : {
					mutex_file.lock();
					date = get_date();
					if (console) {
						std::cout << date;
					}
					file << date;
					write_log(param...);
					break;
				}
				case TYPE_LOG::ERROR : {
					ERROR::write(param...);
					break;
				}
			default:
				break;
			}

			return 0;
		}

		void set_console(bool cons, TYPE_LOG type = TYPE_LOG::LOG);


		~LOG();
	private:
		std::ofstream file;
		uint64_t size{ 0 };
		time_t t{ 0 };
		size_t number{ 0 };
		struct tm *local_time{ nullptr };

		std::string date{ "" };
		std::mutex mutex_file;

		std::string name{ "" };
		bool console{ false };


		std::string get_date();
		

		template<class T, class... Types>
		int write_log(const T &par, const Types&... param) {
			if (console) {
				std::cout << par;
			}
			file << par;
			write_log(param...);
			return 0;
		}
		int write_log();
	};
}



