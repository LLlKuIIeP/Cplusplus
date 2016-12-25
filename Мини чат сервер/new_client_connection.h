#include "chat_server.h"
#include "messages.h"

#pragma once

bool new_client_connection(int fd, struct sockaddr_in *Client_info, std::unordered_map<int,std::string> &u_map_client);

bool save_client_info(int fd, struct sockaddr_in *Client_info, std::unordered_map<int,std::string> &u_map_client);

