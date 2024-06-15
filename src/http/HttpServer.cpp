/**
 * @file HttpServer.cpp
 * @author saivishwak
 * @brief
 * @version 0.1
 * @date 2022-05-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "HttpServer.h"

http::HttpServer::HttpServer(int domain, int service, int protocol, int port, u_long interface, int backlog) {
  this->backlog = backlog;
  this->socket = new net::Socket(domain, service, protocol, port, interface, true);
  spdlog::info("Http server initialzed ...");
}

http::HttpServer::~HttpServer() {
  delete this->socket;
}

std::thread http::HttpServer::spawnStart() {
  spdlog::info("Spawning HTTP Server Thread ...");
  return std::thread([=] { this->start(); });
}

void http::HttpServer::start() {
  // Bind to the port
  int bindSocketConnection = this->socket->connectToNetwork();
  this->socket->testConnection(bindSocketConnection, "Error while binding the socket");

  // start listening for connections on our socket
  int listenR = listen(this->socket->getSock(), this->backlog);
  this->socket->testConnection(listenR, "Error while Listening on socket");

  spdlog::info("HTTP listening started");

  sockaddr_storage client_addr;
  socklen_t client_addr_size = sizeof(client_addr);

  while (true) {
    struct sockaddr_in clnt;
    socklen_t clnt_len = sizeof(clnt);
    int acceptFD = accept(this->socket->getSock(), (struct sockaddr*)&client_addr, &client_addr_size);

    if (acceptFD == -1) {
      spdlog::error("Error while Accepting on HTTP socket\n");
      continue;
    }
    else {
      spdlog::info("Accepted new connection {}", acceptFD);
      std::thread th1([=] { this->incomingRequestHandler(acceptFD); });
      th1.detach();
    }
  }

  close(this->socket->getSock());
  delete this->socket;
  return;
}


/**
 * @brief method to handle incoming request from thread
 * 
 * @param newSocket 
 */
void http::HttpServer::incomingRequestHandler(int newSocket) {
  std::thread::id thread_id = std::this_thread::get_id();
  spdlog::info("HTTP incomingRequestHandler thread spwaned");
  int buff_size = 4069;
  char buffer[buff_size];

  while (true) {
    memset(buffer, 0, buff_size);
    int n = recv(newSocket, buffer, buff_size, 0);
    if (n < 0) {
      spdlog::error("Error in reading HTTP Request from socket");
      break;
    }
    if (n == 0) {
      spdlog::info("HTTP Client disconnected");
      break;
    }

    atomizes::HTTPMessage request;
    atomizes::HTTPMessageParser parser;
    parser.Parse(&request, buffer);
    std::string headerPath = request.GetPath();
    std::string headerMethod = atomizes::MessageMethodToString(request.GetMethod());

    spdlog::info("New HTTP request on sock {} for : {} {}", newSocket, headerPath, headerMethod);

    if (this->handlers.count(headerPath + headerMethod)) {
      Json::Value parsedBody;
      if(request.GetHeader("Content-Type") == "application/json"){
        this->getJsonRequest(request, parsedBody, std::string(buffer));
      }
      this->handlers[headerPath + headerMethod](newSocket, request, parsedBody);
    }
    else {
      atomizes::HTTPMessage response;
      std::map<std::string, std::string> headers;
      headers.insert(std::make_pair("Content-Type" , "text/plain"));
      headers.insert(std::make_pair("Connection" , "close"));
      response.SetStatusCode(404);
      http::HttpServer::makeResponse(headers, "404, No Http handler found", response);
      int bytes_sent = send(newSocket, response.ToString().data(), response.ToString().length(), 0);
      spdlog::error("No HTTP handler for {} {}", atomizes::MessageMethodToString(request.GetMethod()), headerPath);
    }
    //close(newSocket); //Not closing to keep the connection alive for longer buffers
  }
  close(newSocket);
  return;
}

/**
 * @brief parse the incoming JSON request
 * 
 * @param request 
 * @param json 
 * @param buffer 
 */
void http::HttpServer::getJsonRequest(atomizes::HTTPMessage& request, Json::Value& json, const std::string& buffer) {
  std::string str;
  std::vector<u_int8_t> v = request.GetMessageBody();
  str.assign(v.begin(), v.end());
  json = msg::Message::unmarshall(str, 0);
  return;
}

void http::HttpServer::makeResponse(std::map<std::string, std::string> headers, std::string body, atomizes::HTTPMessage& response) {
  for (auto x : headers) {
    response.SetHeader(x.first, x.second);
  }
  response.SetMessageBody(body);
  return;
}

void http::HttpServer::addHandler(std::string method, std::string path, http::Handler callback) {
  this->handlers.insert(std::make_pair(path + method, callback));
  return;
}