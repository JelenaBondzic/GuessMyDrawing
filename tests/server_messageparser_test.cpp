#include "../07-GuessMyDrawing/Server/servermessageparser.h"
#include "../07-GuessMyDrawing/MessageType.h"

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