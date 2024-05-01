#include "../include/curling.h"
#include <iostream>

size_t writeCallback(char *ptr, size_t size, size_t nmemb,
                     std::string *userdata) {
  size_t totalsize = size * nmemb;
  userdata->append(ptr, totalsize);
  return totalsize;
}

std::string curl(std::string playString) {
  CURL *handle = curl_easy_init();
  if (handle) {

    std::string url = "https://explorer.lichess.ovh/masters?play=" +
                      playString; // curling url

    std::string response; // for curl response

    // set url for request
    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());

    // handle received date
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(handle);
    if (res != CURLE_OK) {
      std::cerr << "curl_easy_perform() error " << curl_easy_strerror(res)
                << std::endl;
    } else {
      std::cout << "Response:\n" << response << std::endl;
    }
    curl_easy_cleanup(handle);

    return response;
  } else {
    return "Error in curl_easy_setopt()";
  }
}
