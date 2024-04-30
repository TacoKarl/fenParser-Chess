#include <curl/curl.h> //include the libcurl for curling
#include <string>
//

std::string curl(std::string); // curls th fenstring to lichess ONLY USE IF CURL
                               // IS INITIALIZED
//
size_t writeCallback(char *ptr, size_t size, size_t nmemb,
                     std::string *userdata);
