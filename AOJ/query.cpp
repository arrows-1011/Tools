#include <iostream>
#include <string>
#include <stdlib.h>


#define BUF_SIZE 1024

std::string query(std::string url)
{
#ifdef _MSC_VER
    // Windows
    FILE *f = _popen(("C:\\bin\\curl.exe -s -k \"" + url + "\"").c_str(), "r");
#else
    // Linux, MacOS, Cygwin
    FILE *f = popen(("curl -s -k \"" + url + "\"").c_str(), "r");
#endif

    if (f == NULL || url.size() >= BUF_SIZE) {
        perror("error!");
    }

    char buf[BUF_SIZE];
    std::string xml;
    while (!feof(f)) {
        if (fgets(buf, 1024, f) == NULL) {
            break;
        }
        xml += (std::string)(buf);
    }

#ifdef _MSC_VER
    _pclose(f);
#else
    pclose(f);
#endif

    return xml;
}
