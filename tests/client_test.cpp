// define alowing us to test private methods:
#define private public
#include "../07-GuessMyDrawing/Application/messageparser.h"
#include "../07-GuessMyDrawing/Application/client.h"

#include <QString>


// POKRETANJE:
// qmake test.pro
// make 
// dobija se izvrsni fajl test

TEST_CASE("client", "[class][function]"){

    SECTION("Clinet is not host after creating."){
        // Arrange 
        Client client = Client("milica");
        bool expectedOtput = false;
        
        // Act
        bool output = client.isHost(); 

        // Assert
        REQUIRE(output == expectedOtput);
    }
    
    
    SECTION("Clinet has messageSocket that is not nullptr adter creating."){
        // Arrange 
        Client client = Client("milica");
        QTcpSocket * notExpectedOtput = nullptr;
        
        // Act
        QTcpSocket *output = client.messageSocket; 

        // Assert
        REQUIRE(output != notExpectedOtput);
    }
    
    
    SECTION("Client's name sets after joining room."){
        // Arrange 
        Client client = Client("milica");
        QString name = "me";
        
        // Act
        client.joinRoom(name, "room");
        QString nameAfterJoin = client.mName;
        
        // Assert
        REQUIRE(name.compare(nameAfterJoin)==0);
    }
    
    
    SECTION("Client who was host won't be host anymore after leaving room."){
        // Arrange 
        Client client = Client("milica");
        client.imHost = true;
        
        // Act
        client.leaveRoom();
        bool afterLeaving = client.isHost();
        
        // Assert
        REQUIRE(afterLeaving == false);
    }

        
    SECTION("Client who was not host is not host after leaving room."){
        // Arrange 
        Client client = Client("milica");
        client.imHost = false;
        
        // Act
        client.leaveRoom();
        bool afterLeaving = client.isHost();
        
        // Assert
        REQUIRE(afterLeaving == false);
    }
}