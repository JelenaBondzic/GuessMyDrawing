#include "../07-GuessMyDrawing/Server/servermessageparser.h"
#include "../07-GuessMyDrawing/MessageType.h"

#include <QString>

TEST_CASE("Construction of a message to start the game", "[toStartMessage][function]"){

    SECTION("The function constructs a message with a START value for TYPE"){

        //Arrange
        ServerMessageParser parser = ServerMessageParser();
    
        //Act
        QJsonObject message = parser.toStartMessage();

        CHECK(message.length() == 1);

        //Assert
        REQUIRE(message[MessageType::TYPE].toString().compare(MessageType::START)==0);


    
    }



}

TEST_CASE("Construction of a message for game over", "[toGameOverMessage][function]"){

    SECTION("The function constructs a message with a GAME_OVER value for TYPE"){

        //Arrange
        ServerMessageParser parser = ServerMessageParser();
    
        //Act
        QJsonObject message = parser.toGameOverMessage();

        CHECK(message.length() == 1);

        //Assert
        REQUIRE(message[MessageType::TYPE].toString().compare(MessageType::GAME_OVER)==0);

    }



}

TEST_CASE("Construction of a message for new host", "[toNewHostMessage][function]"){

    SECTION("The function constructs a message with a NEW_HOST value for TYPE"){

        //Arrange
        ServerMessageParser parser = ServerMessageParser();
    
        //Act
        QJsonObject message = parser.toNewHostMessage();

        CHECK(message.length() == 1);

        //Assert
        REQUIRE(message[MessageType::TYPE].toString().compare(MessageType::NEW_HOST)==0);

    }


}

TEST_CASE("Construction of a message for user joined", "[toUserJoinedMessage][function]"){
    
    SECTION("The function constructs a message with a USER_JOINED value for TYPE and username value for USERNAME"){
        // Arrange 
        ServerMessageParser parser = ServerMessageParser();
        QString username = "Jason";
        
        // Act
        QJsonObject message = parser.toUserJoinedMessage(username);
        
        CHECK(message.length() == 2);
        
        // Assert
        REQUIRE(message[MessageType::TYPE].toString().compare(MessageType::USER_JOINED)==0);
        REQUIRE(message[MessageType::USERNAME].toString().compare(username)==0);
    }
}

TEST_CASE("Construction of a message for joining room", "[toJoinRoomMessage][function]"){
    
    SECTION("The function constructs a message with a JOIN_ROOM value for TYPE and roomName value for ROOM_NAME"){
        // Arrange 
        ServerMessageParser parser = ServerMessageParser();
        QString roomName = "Room1";
        
        // Act
        QJsonObject message = parser.toJoinRoomMessage(roomName);
        
        CHECK(message.length() == 2);
        
        // Assert
        REQUIRE(message[MessageType::TYPE].toString().compare(MessageType::JOIN_ROOM)==0);
        REQUIRE(message[MessageType::ROOM_NAME].toString().compare(roomName)==0);
    }
}

TEST_CASE("Construction of a message for user left", "[toUserLeftMessage][function]"){
    
    SECTION("The function constructs a message with a USER_LEFT value for TYPE and username value for USERNAME"){
        // Arrange 
        ServerMessageParser parser = ServerMessageParser();
        QString username = "Jason";
        
        // Act
        QJsonObject message = parser.toUserLeftMessage(username);
        
        CHECK(message.length() == 2);
        
        // Assert
        REQUIRE(message[MessageType::TYPE].toString().compare(MessageType::USER_LEFT)==0);
        REQUIRE(message[MessageType::USERNAME].toString().compare(username)==0);
    }
}