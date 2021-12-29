#include "../07-GuessMyDrawing/Server/servermessageparser.h"
#include "../07-GuessMyDrawing/MessageType.h"
#include "../07-GuessMyDrawing/Server/ServerMessageEnum.h"

#include <QString>

TEST_CASE("Construction of a message to start the game", "[startMessage][function]"){

    SECTION("The function constructs a message with a START value for TYPE"){

        //Arrange
        ServerMessageParser parser = ServerMessageParser();
    
        //Act
        QJsonObject message = parser.startMessage();

        CHECK(message.length() == 1);

        //Assert
        REQUIRE(message[MessageType::TYPE].toString().compare(MessageType::START)==0);


    
    }



}

TEST_CASE("Construction of a message for game over", "[gameOverMessage][function]"){

    SECTION("The function constructs a message with a GAME_OVER value for TYPE"){

        //Arrange
        ServerMessageParser parser = ServerMessageParser();
    
        //Act
        QJsonObject message = parser.gameOverMessage();

        CHECK(message.length() == 1);

        //Assert
        REQUIRE(message[MessageType::TYPE].toString().compare(MessageType::GAME_OVER)==0);

    }



}

TEST_CASE("Construction of a message for new host", "[newHostMessage][function]"){

    SECTION("The function constructs a message with a NEW_HOST value for TYPE"){

        //Arrange
        ServerMessageParser parser = ServerMessageParser();
    
        //Act
        QJsonObject message = parser.newHostMessage();

        CHECK(message.length() == 1);

        //Assert
        REQUIRE(message[MessageType::TYPE].toString().compare(MessageType::NEW_HOST)==0);

    }


}

TEST_CASE("Construction of a message for user joined", "[userJoinedMessage][function]"){
    
    SECTION("The function constructs a message with a USER_JOINED value for TYPE and username value for USERNAME"){
        // Arrange 
        ServerMessageParser parser = ServerMessageParser();
        QString username = "Jason";
        
        // Act
        QJsonObject message = parser.userJoinedMessage(username);
        
        CHECK(message.length() == 2);
        
        // Assert
        REQUIRE(message[MessageType::TYPE].toString().compare(MessageType::USER_JOINED)==0);
        REQUIRE(message[MessageType::USERNAME].toString().compare(username)==0);
    }
}


TEST_CASE("ServerMessageParser", "[class]") {
    
    SECTION("The function getTypeFromMessage returns correct message type for a given message.") {
        // Arrange
        ServerMessageParser parser;
        QJsonObject message;
        message[MessageType::TYPE] = MessageType::TEXT_MESSAGE;
        ServerMessageType expected_type = ServerMessageType::TEXT_MESSAGE;
        // Act
        ServerMessageType received_type = parser.getTypeFromMessage(message);
        // Assert
        REQUIRE(expected_type == received_type);
    }

    SECTION("When a message with invalid message type is passed the function getTypeFromMessage returns an error message type.") {
        // Arrange
        ServerMessageParser parser;
        QJsonObject message;
        message[MessageType::TYPE] = MessageType::UNKNOW;
        ServerMessageType expected_type = ServerMessageType::ERROR;
        // Act
        ServerMessageType received_type = parser.getTypeFromMessage(message);
        // Assert
        REQUIRE(expected_type == received_type);
    }

    SECTION("The function toGetRoomsMessage converts given string of rooms to message correctly.") {
        // Arrange
        ServerMessageParser parser;
        const QString input_rooms = QString("test1, test2, test3");
        // Act
        QJsonObject received_message = parser.toGetRoomsMessage(input_rooms);
        // Assert
        CHECK(received_message.length() == 2);
        REQUIRE(received_message[MessageType::TYPE].toString().compare(MessageType::GET_ROOMS) == 0);
        REQUIRE(received_message[MessageType::CONTENT].toString().compare(input_rooms) == 0);
    }

    SECTION("When an empty string of rooms is given the function toGetRoomsMessage returns correct message.") {
        // Arrange
        ServerMessageParser parser;
        const QString input_rooms = QString("");
        // Act
        QJsonObject received_message = parser.toGetRoomsMessage(input_rooms);
        // Assert
        CHECK(received_message.length() == 2);
        REQUIRE(received_message[MessageType::TYPE].toString().compare(MessageType::GET_ROOMS) == 0);
        REQUIRE(received_message[MessageType::CONTENT].toString().compare(input_rooms) == 0);
    }

    SECTION("Function fromJoinRoomMessage converts a join room message to QVector<QString> correctly.") {
        // Arrange
        ServerMessageParser parser;
        QJsonObject input_message;
        input_message[MessageType::TYPE] = MessageType::JOIN_ROOM;
        input_message[MessageType::USERNAME] = QString("user_name");
        input_message[MessageType::ROOM_NAME] = QString("room_name");
        QVector<QString> expected_result;
        expected_result.append(QString("user_name"));
        expected_result.append(QString("room_name"));
        // Act
        QVector<QString> received_result = parser.fromJoinRoomMessage(input_message);
        // Assert
        CHECK(received_result.length() == 2);
        REQUIRE(expected_result == received_result);
    }

    SECTION("Function fromChooseWordMessage converts a choose word message to QVector<QString> correctly.") {
        // Arrange
        ServerMessageParser parser;
        QJsonObject input_message;
        input_message[MessageType::TYPE] = MessageType::CHOOSE_WORD;
        input_message[MessageType::CONTENT] = QString("test_word");
        QVector<QString> expected_result;
        expected_result.append(QString("test_word"));
        // Act
        QVector<QString> received_result = parser.fromChooseWordMessage(input_message);
        // Assert
        CHECK(received_result.length() == 1);
        REQUIRE(expected_result == received_result);
    }

    SECTION("Function fromCreateRoomMessage converts a create room message to QVector<QString> correctly.") {
        // Arrange
        ServerMessageParser parser;
        QJsonObject input_message;
        input_message[MessageType::TYPE] = MessageType::CREATE_ROOM;
        input_message[MessageType::USERNAME] = QString("user_name");
        input_message[MessageType::ROOM_NAME] = QString("room_name");
        input_message[MessageType::DURATION] = QString(60);
        QVector<QString> expected_result;
        expected_result.append(QString("user_name"));
        expected_result.append(QString("room_name"));
        expected_result.append(QString(60));
        // Act
        QVector<QString> received_result = parser.fromCreateRoomMessage(input_message);
        // Assert
        CHECK(received_result.length() == 3);
        REQUIRE(expected_result == received_result);
    }

}

