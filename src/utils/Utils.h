/**
 * @file Utils.h
 * @author saivishwak
 * @brief 
 * @version 0.1
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include <string>

namespace Utils {
  enum string_code
  {
    ePing,
    eHandshake,
    eRequestHandShake,
    eRequestServerInfo,
    eServerInfo,
    eNewPeer,
    eDefault
  };

  enum header_methods
  {
    eGet,
    ePost,
    eNULL
  };

  inline string_code hashit(std::string inString) {
    if (inString == "ping")
      return Utils::ePing;
    if (inString == "handshake")
      return Utils::eHandshake;
    if (inString == "requestHandShake")
      return Utils::eRequestHandShake;
    if (inString == "requestServerInfo")
      return Utils::eRequestServerInfo;
    if (inString == "serverInfo")
      return Utils::eServerInfo;
    if (inString == "newPeer")
      return Utils::eNewPeer;
    return Utils::eDefault;
  }

  inline header_methods getHeaderValue(std::string inString) {
    if (inString == "GET")
      return Utils::eGet;
    if (inString == "POST")
      return Utils::ePost;
    return Utils::eNULL;
  }
}