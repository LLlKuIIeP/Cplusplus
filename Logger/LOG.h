#include <string>
#include <fstream>
#include <mutex>
#include <sstream>
#include <iostream>
#include <cstdint>




#pragma once


namespace Logger {
	std::string get_log_file_name_default();
	enum class LEVEL : unsigned int { ZERO, ONE, TWO };
	enum class TYPE_LOG : unsigned int { LOG, ERROR, INFO, WARNING };

	bool check_file_size(uint64_t, std::string&, std::ofstream&, size_t&);


	class LOG {
	public:
		LOG();
		LOG(LOG&) = delete;
		LOG(LOG&&) = delete;
		LOG& operator=(const LOG&) = delete;
		LOG& operator=(const LOG&&) = delete;


		template<class T>
		LOG& operator<<(const T &arg) {
			std::lock_guard<std::mutex> lock(mutex_file);
			if (!this->file.is_open()) {
				//std::cout << "if\n";
				this->file.open(this->name, std::ios_base::app);
			}
			//mutex_file.lock();

			file << arg;
			//std::cout << arg;
			write_log();
			return *this;
		}

		LOG& operator<<(std::ostream& (*os)(std::ostream &s));

		int set_file_name(const std::string &name);
		void set_max_file_size(uint64_t size);

		template<class... Types>
		int write(const Types&... param) {
			std::lock_guard<std::mutex> lock(mutex_file);

					//mutex_file.lock();
			date = get_date();

			file << date;
			write_log(param...);

			return 0;
		}



		~LOG();
	private:
		std::ofstream file;
		uint64_t size{ 0 };
		time_t t{ 0 };
		size_t number{ 0 };
		struct tm *local_time{ nullptr };

		std::string date{ "" };
		std::mutex mutex_file;

		std::string name{ "log_" };


		std::string get_date();
		

		template<class T, class... Types>
		int write_log(const T &par, const Types&... param) {
			//std::cout << par;
			file << par;
			write_log(param...);
			return 0;
		}
		int write_log();
	};
}