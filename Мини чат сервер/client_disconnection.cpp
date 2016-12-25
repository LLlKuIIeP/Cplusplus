#include "client_disconnection.h"


bool shutdown_client_connection(int fd, std::unordered_map<int, std::string> &u_map_client) {
	try {
		std::string disconnect("DISCONNECT");
		if(send_message_all(fd, u_map_client, disconnect)) {
			u_map_client.erase(fd);
			return true;
		}
		return false;
	}
	catch(...) {
		return false;
	}
}

