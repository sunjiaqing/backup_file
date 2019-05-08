//
// Created by admin on 2019/5/6.
//

#include "Config.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/ostreamwrapper.h"
#include "include/rapidjson/writer.h"
#include "File.h"

using namespace rapidjson;
using namespace std;

Config::Config() {
    ifstream file(path);
    if (file) {
        configFile = json.reade(path);
        string backupPathsKey = "backupPaths";
        auto array = json.getArray(backupPathsKey, configFile);
        for (auto &v : array) {
            string name = json.getString("name", v);
            string path = json.getString("path", v);
            backup item(name, path);
            backupVector.push_back(item);
            std::cout << "加载--->" << "name:" << item.first << ",path:" << item.second << std::endl;
        }
    } else {
        initConfig();
    }
    file.close();
}

void Config::initConfig() {
    json.addArray("backupPaths", configFile);
    long long int nowTime = getLongTime();
    json.addAttrInt64("createTime", nowTime, configFile);
    json.addAttrInt64("updateTime", nowTime, configFile);
    json.write(path, configFile);
}


long long int Config::getCreateTime() {
    static string key = "createTime";
    return json.getInt64(key, configFile);
}

long long int Config::getUpdateTime() {
    static string key = "updateTime";
    return json.getInt64(key, configFile);
}

void Config::addBackupPath(std::string &name, std::string &path) {
    Value value(kObjectType);
    json.addObjectAttrString("name", name, configFile, value);
    json.addObjectAttrString("path", path, configFile, value);
    auto array = json.getArray("backupPaths", configFile);
    array.PushBack(value, configFile.GetAllocator());
    backup item(name, path);
    backupVector.push_back(item);
    json.write(this->path, configFile);
}

void Config::exeBackup() {
    for (auto &item:backupVector) {
        std::cout << "执行备份--->" << "name:" << item.first << ",path:" << item.second << std::endl;

        File file;
        /*     if (file.exist()){
                // file.copy("C:\\Users\\admin\\CLionProjects\\backup_file\\copy");
             } else{
                 std::cout<<":文件或文件夹不存在"<<std::endl;
             }*/
    }

}

long long int Config::getLongTime() {
    auto time_now = chrono::system_clock::now();
    auto duration_in_ms = chrono::duration_cast<chrono::milliseconds>(time_now.time_since_epoch());
    return duration_in_ms.count();
}



