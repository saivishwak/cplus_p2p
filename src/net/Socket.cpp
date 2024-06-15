/**
 * @file Socket.cpp
 * @author saivishwak
 * @brief 
 * @version 0.1
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Socket.h"

net::Socket::Socket(int domain, int service, int protocol, int port, u_long interface, bool toBind) {
  //params
  this->toBind = toBind;

  // Define address params for socket
  this->address.sin_family = domain;
  this->address.sin_port = htons(port);
  this->address.sin_addr.s_addr = htonl(interface);

  //Created socket connection
  this->sock = socket(domain, service, protocol);
  this->testConnection(sock, "Error While Creating the Socket");
  
  spdlog::info("New Socket Created");
}

int net::Socket::connectToNetwork() {
  if (this->toBind)
    return bind(this->sock, (struct sockaddr*)&this->address, sizeof(this->address));
  else
    return connect(this->sock, (struct sockaddr*)&this->address, sizeof(this->address));
}

void net::Socket::testConnection(int item_to_test, const char* errorMessage) {
  if (item_to_test < 0) {
    perror(errorMessage);
    exit(EXIT_FAILURE);
  }
}

int net::Socket::getSock() {
  return this->sock;
}

int net::Socket::getConnection() {
  return this->connection;
}

struct sockaddr_in net::Socket::getAddress() {
  return this->address;
}