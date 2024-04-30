#include "curling.h" //include the libcurl library for curling
#include "openings.h"
#include <iostream>
#include <string>

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

  std::string res = curl(fenString);

  curl_global_cleanup(); // cleanup curl after using

  Openings test[2];
  test[0].update("g8f6", "Nf6", 180066, 240676, 130039, 2414);
  test[1].update("d7d5", "d5", 75185, 108855, 45846, 2405);

  std::cout << test[0] << std::endl;
  std::cout << test[1] << std::endl;

  std::string tester = test[0].getUci();
  std::cout << "Get uci test: " << tester << std::endl;

  return 0;
}
