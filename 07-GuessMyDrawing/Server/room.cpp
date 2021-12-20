#include "room.h"
#include "../Application/MessageType.h"
#include<unordered_map>


void Room::setDuration(int newDuration)
{
    duration = newDuration;
}

void Room::leaveRoom(Thread* thread)
{
//    QMap<QString, Thread*>::iterator i = players.find(player);
//    players.erase(i);


    //broadcast others that player has left the game??

  QString name = "";
  for (auto i=players.begin(); i!=players.end(); i++){
    if (i.value() == thread){

        QJsonObject message;
        message[MessageType::TYPE] = MessageType::USER_LEFT;
        message[MessageType::USERNAME] = i.key();

        broadcast(message, thread);

        players.remove(i.key());

        break;
      }
    }



    if(players.size() < 2){
        QJsonObject message;
        message[MessageType::TYPE] = MessageType::GAME_OVER;
    }
}

bool Room::usernameIsValid(QString username)
{
    if(players.contains(username))
        return false;

    return true;
}

void Room::setWordAndStartGame(const QString &newChosenWord)
{
  std::cout << "Room word: " << chosenWord.toStdString() << std::endl;
    chosenWord = newChosenWord;
    //if there is 2 or more players, start game
    if(players.size() >= 2)
        start();

    std::cout << "2 Room word: " << chosenWord.toStdString() << std::endl;
}

void Room::checkChatWord(QString word, Thread* senderUser)
{
    std::cout << "Correct;" << word.toStdString() << std::endl;
    if(word.compare(chosenWord)==0){



        std::cout << "Correct;" << std::endl;
        QJsonObject message1;
        message1[MessageType::TYPE] = MessageType::GAME_OVER;
        QMapIterator<QString, Thread*> i(players);
        while (i.hasNext()) {
            i.next();
            i.value()->send(message1);
         }

        QJsonObject message;
        message[MessageType::TYPE] = MessageType::NEW_HOST;
        senderUser->send(message);



    }

}

Room::Room(QString name, QString host, int duration): name(name), duration(duration), host(host)
{
  gameIsStarted = false;
}

void Room::joinClient(QString username, Thread* thread){
    QJsonObject message;


    //ckech if username is taken
    bool check = usernameIsValid(username);

    //if username is taken
    if(!check){
        message[MessageType::TYPE] = QString(MessageType::JOIN_ROOM);
        message[MessageType::ROOM_NAME] = "";
        thread->send(message);

        std::cout << "USER NOT JOINED " << std::endl;
        return;
    }

    else{
    //if username is not taken

        QJsonObject m;
        m[MessageType::TYPE] = MessageType::USER_JOINED;
        m[MessageType::USERNAME] = username;
        broadcast(m, thread);


        std::cout << "USER JOINED " << std::endl;
        players.insert(username, thread);
        message[MessageType::TYPE] = QString(MessageType::JOIN_ROOM);
        message[MessageType::ROOM_NAME] = name;
        thread->send(message);


        if(players.size() == 1){
            std::cout << "jeste jedan" << std::endl;
            QJsonObject message;
            message[MessageType::TYPE] = MessageType::NEW_HOST;
            thread->send(message);
        }

        //if there is 2 or more players, start game
        if(players.size() >= 2 and !gameIsStarted)
            start();

        return;
    }
}

void Room::start()
{
  std::cout << "START " <<std::endl;

    QJsonObject message;
    message[MessageType::TYPE] = MessageType::START;

    QMapIterator<QString, Thread*> i(players);
    while (i.hasNext()) {
         i.next();
         i.value()->send(message);
    }

    gameIsStarted = true;

}

void Room::broadcast(const QJsonObject &message, Thread* t) {
    for (auto i=players.begin(); i!=players.end(); i++) {
//        if (i.value() != t)
          i.value()->send(message);
    }
    QString word = message.value(MessageType::CONTENT).toString();
    std::cout << "STRIGLO U BROADCAST REC: " << word.toStdString() << std::endl;
    std::cout << "Word: " << chosenWord.toStdString() << std::endl;
    checkChatWord(word, t);
}
