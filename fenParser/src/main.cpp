#include "../include/curling.h" //include the libcurl library for curling
#include "../include/move.h"
#include "../include/rapidjson/document.h" // json parser from  https://github.com/Tencent/rapidjson
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " \"fenstring\"" << std::endl;
    return 1;
  }

  curl_global_init(
      CURL_GLOBAL_ALL); // initialize the libcurl libray (only once)

  std::string fenString = argv[1];

  // std::cout << "Input a fen string" << std::endl;

  // std::getline(std::cin, fenString);

  for (int i = 0; i < fenString.size(); i++) {
    if (fenString[i] == ' ') {
      fenString[i] = '%';            // Replace space with '%'
      fenString.insert(i + 1, "20"); // Insert '20' after '%'
      i += 2;                        // Move to the character after '20'}
    }
  }
  std::cout << "Parsen fen string\n"
            << fenString
            << "\nto https://explorer.lichess.ovh/masters?fen=" << fenString
            << std::endl;

  std::string jsonRes = curl(fenString);

  rapidjson::Document doc;
  doc.Parse(jsonRes.c_str());

  if (!doc.IsObject()) {
    std::cerr << "Invalid JSON format" << std::endl;
    return 1;
  }
  // if doc has member "moves" and moves.IsArray()
  // Extract the "moves" array from the JSON
  const rapidjson::Value &moves = doc["moves"];
  if (!moves.IsArray()) {
    std::cerr << "No 'moves' array found in JSON" << std::endl;
    return 1;
  }

  curl_global_cleanup(); // cleanup curl after using

  Move test[2];
  test[0].update("g8f6", "Nf6", 180066, 240676, 130039, 2414);
  test[1].update("d7d5", "d5", 75185, 108855, 45846, 2405);

  std::cout << test[0] << std::endl;
  std::cout << test[1] << std::endl;

  std::string tester = test[0].getUci();
  std::cout << "Get uci test: " << tester << std::endl;

  return 0;
}
