/**
 * @file Peer.h
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

namespace net {
    /**
     * @brief Peer class to maintain incoming and outgoing peer data
     * 
     */
    class Peer {
    public:
        int socket;

        void setSocket(int socket);
        void setPort(int port);
        /* 0 for incoming and 1 for outgoing */
        void setDirection(int direction);
        int getSocket();
        int getPort();
        int getDirection();
        Peer(int socket, int direction);

    private:
        int port;
        int direction;
    };
}
