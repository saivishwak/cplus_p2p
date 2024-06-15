// #include "Server.h"

// net::Server::Server(int port, unsigned int backlog) {
//     net::Server::port = port;
//     net::Server::backlog = backlog;
//     spdlog::info("Server Initiated with PORT {} And Bakclog {}", port, backlog);
// };

// std::thread net::Server::spawnStart() {
//     spdlog::info("Spawning serverThread ...");
//     return std::thread([=] { this->start(); });
// }

// void net::Server::broadcast(std::string res, int port) {
//     spdlog::info("Broadcasting : {}", res);
//     for (auto x : this->peers) {
//         if (x.getPort() != port) {
//             spdlog::info("Peer Port: {}", x.getPort());
//             int bytes_sent = send(x.getSocket(), res.data(), res.length(), 0);
//         }
//     }
//     return;
// }

// void net::Server::incomingRequestHandler(int socket) {
//     std::thread::id thread_id = std::this_thread::get_id();
//     spdlog::info("incomingRequestHandler thread spwaned");
//     char buffer[256];

//     while (true) {
//         memset(buffer, 0, sizeof(buffer));
//         int n = read(socket, buffer, sizeof(buffer));
//         if (n < 0) {
//             spdlog::error("Error in read");
//             break;
//         }
//         if (n == 0) {
//             spdlog::info("Client disconnected");
//             break;
//         }

//         spdlog::info("Message from client : {} - {}", socket, buffer);
//         // send call sends the data you specify as second param and it's length as 3rd p aram, also returns how many bytes were actually sent
//         // std::string res = "Message from server - " + std::string(buffer) + "\n";
//         // int bytes_sent = send(socket, res.data(), res.length(), 0);
//         msg::Block b = msg::Message::unmarshall(std::string(buffer));
//         switch (Utils::hashit(b.type)) {
//         case Utils::ePing: {
//             msg::Message m = msg::Message();
//             // std::string res = m.marshall(msg::Block("", "pong"));
//             std::string res = m.marshall("", "pong");
//             int bytes_sent = send(socket, res.data(), res.length(), 0);
//             continue;
//         }
//         case Utils::eRequestServerInfo: {
//             // std::string res = msg::Message::marshall(msg::Block(std::to_string(this->port), "serverInfo"));
//             std::string res = msg::Message::marshall(std::to_string(this->port), "serverInfo");
//             int bytes_sent = send(socket, res.data(), res.length(), 0);
//             continue;
//         }
//         case Utils::eServerInfo: {
//             spdlog::info("Server info recieved: {}", b.message);
//             int port = std::stoi(b.message);
//             std::vector<net::Peer>::iterator it;

//             std::unique_lock<std::mutex> lock(this->m);
//             for (auto it = this->peers.begin(); it != this->peers.end(); ++it) {
//                 if (it->socket == socket) {
//                     it->setPort(port);
//                 }
//             }
//             this->m.unlock();
//             // std::string res = msg::Message::marshall(msg::Block(std::to_string(port), "newPeer"));
//             std::string res = msg::Message::marshall(std::to_string(port), "newPeer");
//             this->broadcast(res, port);
//             continue;
//         }
//         case Utils::eNewPeer: {
//             int remotePort = std::stoi(b.message);
//             std::unique_lock<std::mutex> lock(this->m);
//             bool found = false;
//             for (auto x : this->peers) {
//                 if (x.getPort() == remotePort) {
//                     found = true;
//                 }
//             }
//             if (!found) {
//                 if (remotePort != this->port) {
//                     spdlog::info("Connecting to peer: {} - {}", b.message, this->port);
//                     std::thread clientThread([=] { connectToPeer(remotePort); });
//                     clientThread.detach();
//                 }
//             }
//             this->m.unlock();

//             continue;
//         }
//         default:
//         {
//             // Do nothing
//         }
//         }
//     }
//     std::vector<net::Peer>::iterator it;

//     std::unique_lock<std::mutex> lock(this->m);
//     for (auto it = peers.begin(); it != peers.end(); ++it) {
//         if (it->socket == socket) {
//             peers.erase(it);
//             break;
//         }
//     }
//     this->m.unlock();
//     close(socket);
//     return;
// }

// void net::Server::start() {
//     struct sockaddr_in address;
//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons(this->port);

//     net::Socket bindSock = net::Socket(AF_INET, SOCK_STREAM, 0 , this->port, INADDR_ANY, true);

//     // these calls usually return -1 as result of some error
//     int sockFD = socket(AF_INET, SOCK_STREAM, 0);
//     if (sockFD == -1) {
//         spdlog::error("Error while creating socket\n");
//         exit(0);
//         return;
//     }

//     // Let's bind address to our socket we've just created
//     int bindR = bind(sockFD, (struct sockaddr*)&address, sizeof(address));
//     if (bindR == -1) {
//         spdlog::error("Error while binding socket\n");
//         // if some error occurs, make sure to close socket and free resources
//         close(sockFD);
//         exit(0);
//         return;
//     }

//     // finally start listening for connections on our socket
//     int listenR = listen(sockFD, this->backlog);
//     if (listenR == -1) {
//         spdlog::error("Error while Listening on socket\n");

//         // if some error occurs, make sure to close socket and free resources
//         exit(0);
//         close(sockFD);
//         return;
//     }

//     spdlog::info("Listening started");

//     sockaddr_storage client_addr;
//     socklen_t client_addr_size = sizeof(client_addr);

//     // a fresh infinite loop to communicate with incoming connections
//     // this will take client connections one at a time
//     // in further examples, we're going to use fork() call for each client connection
//     while (true) {

//         // accept call will give us a new socket descriptor
//         struct sockaddr_in clnt;
//         socklen_t clnt_len = sizeof(clnt);
//         net::Peer incomingPeer = net::Peer(accept(sockFD, (struct sockaddr*)&client_addr, &client_addr_size), 0);
//         incomingPeer.setPort(0);

//         if (incomingPeer.getSocket() == -1) {
//             spdlog::error("Error while Accepting on socket\n");
//             continue;
//         }
//         else {
//             /*if(getpeername(incomingPeer.getSocket(), (struct sockaddr*)&clnt, &clnt_len) < 0) {
//               std::cerr << " Error in getting remote addr" << std::endl;
//               continue;
//               }

//               std::cout << "Remote Peer Addr: " << clnt.sin_port << std::endl;*/
//             std::unique_lock<std::mutex> lock(this->m);
//             this->peers.push_back(incomingPeer);
//             spdlog::info("Got new connnection {} Total Perrs: {}", incomingPeer.getSocket(), this->peers.size());
//             this->m.unlock();

//             std::thread th1([=] { this->incomingRequestHandler(incomingPeer.socket); });
//             th1.detach();

//             msg::Message m = msg::Message();
//             // std::string res = m.marshall(msg::Block("", "requestServerInfo"));
//             std::string res = m.marshall("", "requestServerInfo");
//             int bytes_sent = send(incomingPeer.getSocket(), res.data(), res.length(), 0);
//         }
//     }

//     close(sockFD);
//     return;
// }

// void net::Server::connectToPeer(int port) {
//     struct sockaddr_in connect_address;
//     connect_address.sin_family = AF_INET;
//     connect_address.sin_addr.s_addr = inet_addr("127.0.0.1");
//     connect_address.sin_port = htons(port);

//     int client_sockFD = socket(AF_INET, SOCK_STREAM, 0);

//     net::Peer outBoundPeer = net::Peer(client_sockFD, 1);
//     outBoundPeer.setPort(port);

//     if (connect(client_sockFD, (struct sockaddr*)&connect_address, sizeof(connect_address)) != 0) {
//         spdlog::error("connection with the server failed...");
//         close(client_sockFD);
//         return;
//     }
//     else {
//         spdlog::info("Connected to server at {}", port);
//         std::unique_lock<std::mutex> lock(this->m);
//         peers.push_back(outBoundPeer);
//         this->m.unlock();
//         std::thread th1([=] { this->incomingRequestHandler(outBoundPeer.socket); });
//         th1.detach();
//     }
// }