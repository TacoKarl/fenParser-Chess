#include "../include/curling.h" //include the libcurl library for curling
#include "../include/move.h"
#include "../include/rapidjson/document.h" // json parser from  https://github.com/Tencent/rapidjson
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

int main(/*int argc, char *argv[]*/) {
  std::string playString;

  std::srand(std::time(nullptr)); // random number seed
                                  /*if (argc != 2) {
                                    std::cerr << "Usage: " << argv[0] << " \"playString\"" << std::endl;
                                    std::cout << "Type play string using the uci format followed by comma and "
                                                 "next uci move (example d2d4,d7d5)"
                                              << std::endl;
                                
                                    std::getline(std::cin, playString);
                                  } else {
                                    playString = argv[1];
                                    }*/
  Database DB;
  int chosenMove;

  bool running = true;

  curl_global_init(
      CURL_GLOBAL_ALL); // initialize the libcurl libray (only once)
  while (running) {

    DB.rcv();

    DB.getFromDatabase();
    /*  for (int i = 0; i < playString.size(); i++) {
       if (playString[i] == ' ') {
         playString[i] = '%';            // Replace space with '%'
         playString.insert(i + 1, "20"); // Insert '20' after '%'
         i += 2;                         // Move to the character after '20'}
       }
     }*/
    std::cout << "Parsen play string\n"
              << playString
              << "\nto https://explorer.lichess.ovh/masters?play=" << playString
              << std::endl;

    std::cout << DB;
    /*
        std::string jsonRes = curl(playString);

        rapidjson::Document doc;
        doc.Parse(jsonRes.c_str());

        if (!doc.IsObject()) {
          std::cerr << "Invalid JSON format" << std::endl;
          std::cerr << "No move found in the database using this position"
                    << std::endl;
          return 1;
        }
        // if doc has member "moves" and moves.IsArray()
        // Extract the "moves" array from the JSON
        const rapidjson::Value &moves = doc["moves"];

        if (!moves.IsArray()) {
          std::cerr << "No 'moves' array found in JSON" << std::endl;
          std::cerr << "No move found in the database using this position"
                    << std::endl;
          return 1;
        }

        std::vector<Move> moveVector; // Move vector

        for (rapidjson::SizeType i = 0; i < moves.Size(); ++i) {
          const rapidjson::Value &move = moves[i];
          if (!move.IsObject()) {
            std::cerr << "Invalid move object in JSON" << std::endl;
            return 1;
          }

          // Extract relevant fields for the Move object
          std::string uci = move["uci"].GetString();
          std::string san = move["san"].GetString();
          int white = move["white"].GetInt();
          int draws = move["draws"].GetInt();
          int black = move["black"].GetInt();
          int averageRating = move["averageRating"].GetInt();

          // make moveObj
          Move moveObj(uci, san, white, draws, black, averageRating);
          moveVector.push_back(moveObj);
        }
    */
    /*    // print out moves
        int moveCounter = 1;
        for (const auto &move : moveVector) {
          std::cout << "Move " << moveCounter << "\n" << move << std::endl;
          moveCounter++;
        }
        moveCounter = 1;
    */
 /*   std::cout << "Choose a move (returns the uci of the chosen movenumber)"
              << std::endl;
    std::cout << "Choose between 1 and " << moveVector.size() << std::endl;

    chosenMove = rand() % moveVector.size();

    std::cout << "Chosen move: " << chosenMove + 1 << std::endl;

    moveVector[chosenMove].getUci();
 */ }

 curl_global_cleanup(); // cleanup curl after using

 /*Move test[2];
 test[0].update("g8f6", "Nf6", 180066, 240676, 130039, 2414);
 test[1].update("d7d5", "d5", 75185, 108855, 45846, 2405);

 std::cout << test[0] << std::endl;
 std::cout << test[1] << std::endl;

 std::string tester = test[0].getUci();
 std::cout << "Get uci test: " << tester << std::endl;*/

 return 0;
}
