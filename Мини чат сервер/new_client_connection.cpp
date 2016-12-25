#include "new_client_connection.h"

//	Функция оповещает всех участников чата о новом подключении к чату
bool new_client_connection(int fd, struct sockaddr_in *Client_info ,std::unordered_map<int, std::string> &u_map_client) {
	
	if(save_client_info(fd, Client_info, u_map_client)) {

		try {
			std::string connect("CONNECT");
			if(send_message_all(fd, u_map_client, connect)) {

				std::string new_client("Connect successful");
				if(send(fd, &(new_client.front()), new_client.size(), MSG_NOSIGNAL) == -1) {
					error_log("new_client_connection -> send", errno, strerror(errno));
					error_msg(new_client);

					return false;
				}
				else {
					return true;
				}
			}
		}
		catch(...) {
			return false;
		}
	}
}


bool save_client_info(int fd, struct sockaddr_in *Client_info, std::unordered_map<int, std::string> &u_map_client) {
	try {
		if(Client_info->sin_family == AF_INET) {
			std::string client_ip(INET_ADDRSTRLEN, '\0');

			if(inet_ntop(AF_INET, &Client_info->sin_addr.s_addr, &(client_ip.front()), client_ip.length()) == NULL) {
				error_log("save_client_info -> inet_ntop", errno, strerror(errno));
				return false;
			}
			u_map_client[fd] = client_ip;
		}
		else if(Client_info->sin_family == AF_INET6) {

		}


		return true;
	}
	catch(...) {
		return false;
	}
}

