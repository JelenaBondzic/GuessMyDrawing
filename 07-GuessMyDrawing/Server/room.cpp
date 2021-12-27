#include "room.h"
#include "../MessageType.h"
#include <unordered_map>
#include <QRandomGenerator>


Room::Room(QString username, QString room_name, int duration): name(room_name), duration(duration), host(username)
{
  gameIsStarted = false;
  parser = new MessageParser();
}

Room::~Room()
{
    delete parser;
}

void Room::setDuration(int newDuration)
{
    duration = newDuration;
}

void Room::leaveRoom(Thread* thread)
{

  QString name = "";

  for (auto i=players.begin(); i!=players.end(); i++){
    if (i.value() == thread){

        QJsonObject message = parser->userLeftMessage(i.key());
//        message[MessageType::TYPE] = MessageType::USER_LEFT;
//        message[MessageType::USERNAME] = i.key();

        //remove player from players map
        name = i.key();
        players.remove(i.key());
        broadcastMessage(message, thread);

        break;
      }
    }

    // if host left the game
    if (name.compare(host)==0){
      gameOver(thread);
      chooseRandomHost();
      return;
      }

    //if there are enough players left to continue the game
    if(players.size() < 2){
        gameOver(thread);

        // ako je host ostao sam onda mora da mu se kaze da je i dalje host, jer je izgubio "host" privilegije sa gameOver()
        QJsonObject message = parser->newHostMessage();
       // message[MessageType::TYPE] = MessageType::NEW_HOST;
        players[host]->send(message);
    }
}


bool Room::usernameIsTaken(QString username)
{
    if(players.contains(username)){
        return false;
    }

    return true;
}

void Room::setWordAndStartGame(const QString &newChosenWord)
{

  chosenWord = newChosenWord;
  if(players.size() >= 2)
      start();
}

void Room::checkChatWord(QString word, Thread* senderUser)
{
    if(word.compare(chosenWord)==0){
        QMapIterator<QString, Thread*> i(players);
        while (i.hasNext()) {
            i.next();
            if (i.value() == senderUser)
              host = i.key();
         }
        gameOver(senderUser);

        QJsonObject message = parser->newHostMessage();
       // message[MessageType::TYPE] = MessageType::NEW_HOST;
        senderUser->send(message);
    }

}


void Room::chooseRandomHost()
{

  int n = players.size();
  if (n == 0) {
      return ;
  }
  int index = QRandomGenerator::global()->bounded(0, n); // index random igraca
  for (auto it=players.begin(); it != players.end(); it++){
    if(index==0){
        QJsonObject message = parser->newHostMessage();
      //  message[MessageType::TYPE] = MessageType::NEW_HOST;
        it.value()->send(message);
        host = it.key();
      //  std::cout << " new random host " << host.toStdString() << std::endl;
        break;
      }
    index--;
    }
}

void Room::gameOver(Thread* t)
{
  QJsonObject message = parser->gameOverMessage();
//  message[MessageType::TYPE] = MessageType::GAME_OVER;
  broadcastMessage(message, t);
  gameIsStarted = false;
}


void Room::joinClient(QString username, Thread* thread){

    bool check = usernameIsTaken(username);

    QJsonObject message;

    if(!check){
        QString msg = "";
        message = parser->joinRoomMessage(msg);

       // message[MessageType::TYPE] = QString(MessageType::JOIN_ROOM);
        thread->send(message);
        return;
    }

    else{

        // javimo ostalima da se prikljucio
        QJsonObject m = parser->userJoinedMessage(username);
//        m[MessageType::TYPE] = MessageType::USER_JOINED;
//        m[MessageType::USERNAME] = username;
        broadcastMessage(m, thread);

      // javimo igracu da se prikljucio
        players.insert(username, thread);
        message = parser->joinRoomMessage(name);
//        message[MessageType::TYPE] = QString(MessageType::JOIN_ROOM);
//        message[MessageType::ROOM_NAME] = name;
        thread->send(message);
        // javimo igracu da je igra vec u toku
        if (gameIsStarted){
          QJsonObject gameIsOn = parser->startMessage();
        //  gameIsOn[MessageType::TYPE] = QString(MessageType::START);
          thread->send(gameIsOn);
      }

        if(players.size() == 1){
            std::cout << "jeste jedan" << std::endl;
            QJsonObject message = parser->newHostMessage();
            host = username;
            //message[MessageType::TYPE] = MessageType::NEW_HOST;
            thread->send(message);
        }

        //if there is 2 or more players, start game
        std::cout << "JOIN isGameStarted: " << this->gameIsStarted << std::endl;

        if(players.size() >= 2 and !gameIsStarted)
            start();

        return;
    }
}

void Room::start()
{
    QJsonObject message = parser->startMessage();
   //message[MessageType::TYPE] = MessageType::START;

    QMapIterator<QString, Thread*> i(players);
    while (i.hasNext()) {
         i.next();
         i.value()->send(message);
    }

    gameIsStarted = true;

}

void Room::broadcastMessage(const QJsonObject &message, Thread* t) {
    for (auto i=players.begin(); i!=players.end(); i++) {
          i.value()->send(message);
    }

    QString type = message.value(MessageType::TYPE).toString();
    QString word = message.value(MessageType::CONTENT).toString();

    if (gameIsStarted && type.compare(MessageType::TEXT_MESSAGE)==0)
      checkChatWord(word, t);

}

void Room::broadcastCanvas(const QJsonObject &message, Thread *t) {
    for (auto i=players.begin(); i!=players.end(); i++) {
        if (i.value() != t) {
          i.value()->send(message);
        }
    }
}
