#include "curl_handler.h"
#include "curl/curl.h"
#include <iostream>

using namespace net;

namespace {
    bool verbose = false;
    size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* out) { 
        size_t totalSize = size * nmemb;
        out->append((char*)contents, totalSize);
        return totalSize;
    }

    bool performCurlRequest(const std::string& url) {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            
            // If you want to follow redirects
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

            // Define our callback to get called when there's data to be written
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

            // This points to our 'readBuffer' which will store the raw HTML data
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            curl_easy_setopt(curl, CURLOPT_VERBOSE, verbose);

            // Perform the request, res will get the return code
            res = curl_easy_perform(curl);
            
            // Check for errors
            if(res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            }
            else {
                // Now, our readBuffer contains the HTML data of the site
                std::cout << readBuffer << std::endl;
            }

            // Always cleanup
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();

        return (res == CURLE_OK);
    }
}

void handler::request_GET(const std::string& url) {
    performCurlRequest(url);
}
