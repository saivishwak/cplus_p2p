/**
 * @file P2PServer.h
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
#include <cstring> // sizeof()
#include <string>
#include <thread>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // close()
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mutex>
#include "Peer.h"
#include "Socket.h"
#include "../message/Message.hpp"
#include "../utils/Utils.h"
#include <spdlog/spdlog.h>

namespace net {

    /**
     * @brief P2P server class
     * 
     */
    class P2PServer
    {
    public:
        int port;
        unsigned int backlog;
        std::vector<net::Peer> peers;

        /**
         * @brief Construct a new P2PServer object
         * 
         * @param port 
         * @param backlog 
         */
        P2PServer(int port, unsigned int backlog = 10);
        /**
         * @brief use this method to start P2P server with thread
         * 
         * @return std::thread 
         */
        std::thread spawnStart();
        /**
         * @brief ConnetToPeer method to connect an external peer
         * 
         * @param port 
         */
        void connectToPeer(int port);
        /**
         * @brief Broadcast method to send data to all peers
         * 
         * @param res 
         * @param port 
         */
        void broadcast(std::string res, int port);

    private:
        std::mutex m;
        /**
         * @brief Start method is called from spawnStart for thread purpose
         * 
         */
        void start();
        /**
         * @brief Handle incoming requests function
         * 
         * @param socket 
         */
        void incomingRequestHandler(int socket);
    };
}
