//
// Created by admin on 2019/5/6.
//

#ifndef BACKUP_FILE_CONFIG_H
#define BACKUP_FILE_CONFIG_H

#include "include/rapidjson/document.h"
#include "JSON.h"
#include <vector>
typedef rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::Array jsonArray;
typedef std::pair<std::string,std::string> backup;

class Config {

public:

    Config();

    long long int getCreateTime();

    long long int getUpdateTime();

    void addBackupPath(std::string &, std::string &);

    void exeBackup();

private:
    JSON json;
    const std::string path = "C:\\Users\\admin\\CLionProjects\\backup_file\\test1.json";
    long long int getLongTime();
    rapidjson::Document configFile;
    std::vector<backup> backupVector;
    void initConfig();
};


#endif //BACKUP_FILE_CONFIG_H
