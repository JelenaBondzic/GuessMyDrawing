#ifndef MESSAGETYPE_H
#define MESSAGETYPE_H

#include <QString>

class MessageType {
public:
  inline static const QString TYPE = "type";
  inline static const QString MESSAGE_SENDER = "sender";

  inline static const QString CANVAS_MESSAGE = "canvas_message";
  inline static const QString TEXT_MESSAGE = "text_message";

  inline static const QString USER_JOINED = "user_joined";
  inline static const QString USER_LEFT = "user_left";

  inline static const QString USERNAME = "username";

  inline static const QString UNKNOW = "unknown";

  inline static const QString CONTENT = "content";


  inline static const QString JOIN_ROOM = "join_room";
  inline static const QString LEAVE_ROOM = "join_room";
  inline static const QString ROOM_NAME = "room_name";

  inline static const QString CHOOSE_WORD = "choose_word";
  inline static const QString GET_ROOMS = "get_rooms";

  inline static const QString CANVAS_SOCKET = "canvas_socket";
  inline static const QString MESSAGE_SOCKET = "message_socket";

};

//enum class MessageType {
//  MESSAGE_TYPE,
//  MESSAGE_SENDER,

//  TEXT_MESSAGE,
//  CANVAS_MESSAGE,
//  USER_JOINED,

//  UKNOWN
//};

//QString EnumToString(MessageType e){
//  switch (e) {
//    case MessageType::MESSAGE_TYPE: return "type";
//    case MessageType::MESSAGE_SENDER: return "sender";

//    case MessageType::TEXT_MESSAGE: return "text_mesage";
//    case MessageType::CANVAS_MESSAGE: return "canvas_message";
//    case MessageType::USER_JOINED: return "user_joined";
//    default: return "unknown";
//    }
//}


#endif // MESSAGETYPE_H
