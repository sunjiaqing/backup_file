#include <iostream>
#include <synchapi.h>
#include <thread>
#include "include/rapidjson/document.h"
#include "Config.h"
#include "include/rapidjson/filereadstream.h"

using namespace rapidjson;
using namespace std;
void xxx();
int main() {
    Config config;

    config.exeBackup();
/*    while (1){
        Sleep(1000);

    }*/
    return 0;
}
void xxx(){
    std::cout<<"ce"<<std::endl;
}