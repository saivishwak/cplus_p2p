/**
 * @file HttpServer.h
 * @author saivishwak
 * @brief
 * @version 0.1
 * @date 2022-05-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <iostream>
#include <sys/socket.h>
#include <spdlog/spdlog.h>
#include <json/json.h>
#include <netinet/in.h>
#include <map>
#include <optional>
#include <sstream>
#include "../net/Socket.h"
#include "../message/Message.hpp"
#include "../utils/Utils.h"
#include "atomizes.hpp"

namespace http {
  /**
   * @brief Class for HTTP Server
   *
   */
  using Handler = std::function<void(int socket, const atomizes::HTTPMessage &request, Json::Value &json)>;

  class HttpServer {
  private:
    net::Socket* socket;
    int backlog;
    std::map<std::string, Handler> handlers;

    /**
     * @brief Private method called internnaly when spawnStart
     *
     */
    void start();

  public:
    HttpServer(int domain, int service, int protocol, int port, u_long interface, int backlog);
    ~HttpServer();

    /**
     * @brief Method to handle incoming requests
     *
     * @param socket
     */
    void incomingRequestHandler(int socket);
    /**
     * @brief Method to start server from thread
     *
     * @return std::thread
     */
    std::thread spawnStart();

    /**
     * @brief make a HTTP response
     * 
     * @param headers 
     * @param body 
     * @param response 
     */
    void static makeResponse(std::map<std::string, std::string> headers, std::string body, atomizes::HTTPMessage &response);

    /**
     * @brief Get the Json Request object
     * 
     * @param request 
     * @param json 
     * @param buffer 
     */
    void getJsonRequest(atomizes::HTTPMessage &request, Json::Value &json, const std::string &buffer);

    /**
     * @brief Add HTTP handler
     * 
     * @param method 
     * @param path 
     * @param callback 
     */
    void addHandler(std::string method, std::string path, Handler callback);
  };
}