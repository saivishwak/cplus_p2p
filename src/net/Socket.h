/**
 * @file Socket.h
 * @author saivishwak
 * @brief 
 * @version 0.1
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include <sys/socket.h>
#include <iostream>
#include <sys/socket.h>
#include <spdlog/spdlog.h>
#include <netinet/in.h>

namespace net {

  /**
   * @brief Socket class to handle socket connection
   * 
   */
  class Socket {
  private:
    int sock;
    int connection;
    struct sockaddr_in address;
    bool toBind;

  public:
    /**
     * @brief Construct a new Socket object
     * 
     * @param domain 
     * @param service 
     * @param protocol 
     * @param port 
     * @param interface 
     * @param toBind 
     */
    Socket(int domain, int service, int protocol, int port, u_long interface, bool toBind);

    /**
     * @brief Method to bind or connect to network
     * 
     * @return int 
     */
    int connectToNetwork();
    //int sockBind(int sock, struct sockaddr_in address);

    /**
     * @brief Method to test sock connections
     * 
     * @param errorMessage 
     */
    void testConnection(int, const char* errorMessage);

    int getSock();
    int getConnection();
    struct sockaddr_in getAddress();
  };

}