#include "../include/move.h"
#include "../include/curling.h"
#include "../include/rapidjson/document.h"
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

std::vector<Move> Database::movesVector;

std::string Database::rcv() {
  std::cout << "Input a play string" << std::endl;
  std::getline(std::cin, playString);
  return playString;
}

std::vector<Move> Database::getFromDatabase() {
  movesVector.clear();
  std::string jsonRes = curl(playString);

  rapidjson::Document doc;
  doc.Parse(jsonRes.c_str());

  if (!doc.IsObject()) {
    std::cerr << "Invalid JSON format" << std::endl;
    return movesVector;
  }

  const rapidjson::Value &moves = doc["moves"];

  if (!moves.IsArray()) {
    std::cerr << "No 'moves' found in JSON" << std::endl;
    return movesVector;
  }

  for (rapidjson::SizeType i = 0; i < moves.Size(); ++i) {
    const rapidjson::Value &move = moves[i];
    if (!move.IsObject()) {
      std::cerr << "Invalid move object in JSON" << std::endl;
      return movesVector;
    }

    // extract the fields for the Move object
    std::string uci = move["uci"].GetString();
    std::string san = move["san"].GetString();
    int white = move["white"].GetInt();
    int draws = move["draws"].GetInt();
    int black = move["black"].GetInt();
    int averageRating = move["averageRating"].GetInt();

    Move moveObj(uci, san, white, draws, black, averageRating);
    movesVector.push_back(moveObj);
  }

  return movesVector;
}

int Database::sendMove() {

  // TODO: add the socket address instead path/to/socket
  char messageToSend[4];

  char *receivedData;
  int receivedDataSize = sizeof(receivedData);

  std::srand(std::time(nullptr));
  if (movesVector.empty()) {
    std::cerr << "No moves in vector" << std::endl;
    return -1;
  }
  int move = rand() % movesVector.size();
  std::string theMove = movesVector[move].getUci();

  std::cout << "The move to send: " << theMove << std::endl;

  strcpy(messageToSend, theMove.c_str());

  std::cout << "Message to send: " << messageToSend << std::endl;

  int sockfd;              // file descriptor
  struct sockaddr_un addr; // socket adress structure

  // Create a Unix domain socket
  if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) ==
      -1) { // check if socket creation fails
    std::cerr << "Error creating socket" << std::endl;
    return -1;
  }
  // TODO: Finish the send function to be able to send info to chess engine

  // set address family to AF_UNIX
  addr.sun_family = AF_UNIX;

  strncpy(addr.sun_path, socketPath,
          sizeof(addr.sun_path) - 1); // Copy socket path to address structure

  if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) ==
      -1) { // check if connection fails
    std::cerr << "Error connecting to server" << std::endl;
    close(sockfd);
    return -1;
  }
  // send data
  if (messageToSend != nullptr) { // if theres a message to send
    if (send(sockfd, messageToSend, std::strlen(messageToSend), 0) ==
        -1) { // check if seending data fails
      std::cerr << "Error sending data" << std::endl;
      close(sockfd);
      return -1;
    }
  }
  /*
    // Receive response (if needed)
    if (receivedData != nullptr) {
      int bytesReceived = recv(sockfd, receivedData, receivedDataSize, 0);
      if (bytesReceived == -1) {
        std::cerr << "Error receiving data" << std::endl;
        close(sockfd);
        return -1;
      }
      // Null-terminate received data
      receivedData[bytesReceived] = '\0';
    }
  */
  // Close the socket
  close(sockfd);

  return 0;
}
