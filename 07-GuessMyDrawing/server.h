#ifndef SERVER_H
#define SERVER_H

#include "QString"
#include <map>

class Server {
 public:
    Server() {}
    void broadcast(/*Message*/);
    void joinRoom(QString room_name);
    void /*Room**/ createRoom(QString room_name);
 private:
    std::map<QString, QString/*Room**/> rooms;
};

#endif // SERVER_H
