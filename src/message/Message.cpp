/**
 * @file Message.cpp
 * @author saivishwak
 * @brief 
 * @version 0.1
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include "Message.hpp"
#include <json/json.h>
#include "Block.pb.h"
#include "Block.hpp"
#include "Transactions.pb.h"

void myMethod(Json::Value& jsonValue_ref, std::vector<int> ports) {
    for (int x : ports) {
        jsonValue_ref.append(x);
    }
}

msg::Message::Message() {}


std::string msg::Message::marshall(std::string message, std::string type) {
    PROTO::Block block;
    block.set_message(message);
    block.set_type(type);
    return block.SerializeAsString();
}

std::string msg::Message::marshall(std::string message, std::string type, std::vector<int> peers) {
    PROTO::Block block;
    block.set_message(message);
    block.set_type(type);
    for (int i = 0; i < peers.size(); i++) {
        block.set_peers(i, peers[i]);
    }
    return block.SerializeAsString();
}


std::string msg::Message::marshall(msg::Block body) {
    Json::Value root;
    if (body.type != "handshake")
        root["message"] = body.message;
    else {
        Json::Value jsonValue;
        myMethod(jsonValue, body.ports);
        root["message"] = jsonValue;
    }
    root["type"] = body.type;

    //Json::StyledWriter styledWriter;
    Json::FastWriter fastWriter;

    //std::cout << styledWriter.write(root) << "\n";
    //std::cout << fastWriter.write(root) << "\n";
    return fastWriter.write(root);
}

Json::Value msg::Message::unmarshall(std::string buffer, int type) {
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(buffer, root);
    if ( !parsingSuccessful )
    {
        std::cout << "Error parsing the input" << std::endl;
        return root;
    }
    // if (root["type"].asString() == "handshake"){
    //     std::vector<int> arr;
    //     for (auto x: root["message"]){
    //         arr.push_back(x.asInt());
    //     }
    //     return msg::Body(arr, root["type"].asString());
    // }
    return root;
}

msg::Block msg::Message::unmarshall(std::string buffer) {
    PROTO::Block block;
    block.ParseFromString(buffer);
    msg::Block body;
    body.message = block.message();
    body.type = block.type();
    return body;
}
