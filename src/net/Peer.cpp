/**
 * @file Peer.cpp
 * @author saivishwak
 * @brief 
 * @version 0.1
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Peer.h"

net::Peer::Peer(int socket, int direction) {
    this->socket = socket;
    this->direction = direction;
}

void net::Peer::setSocket(int socket) {
    this->socket = socket;
    return;
}

void net::Peer::setPort(int port) {
    this->port = port;
    return;
}

void net::Peer::setDirection(int direction) {
    // 0 for incoming and 1 for outgoing
    this->direction = direction;
}

int net::Peer::getSocket() {
    return this->socket;
}

int net::Peer::getPort() {
    return this->port;
}

int net::Peer::getDirection() {
    return this->direction;
}
