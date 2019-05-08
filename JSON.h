//
// Created by admin on 2019/5/7.
//

#ifndef BACKUP_FILE_JSON_H
#define BACKUP_FILE_JSON_H

#include "include/rapidjson/document.h"
#include "include/rapidjson/ostreamwrapper.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/istreamwrapper.h"
#include <fstream>
#include <iostream>

using namespace rapidjson;

class JSON {
public:
    typedef GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> rapidJson;



/**
     * 根节点获取key的值
     * @param key
     * @param document
     * @return
     */
    std::string getString(std::string key, Document &document) {
        if (document.HasMember(key.data()) && document[key.data()].IsString()) {
            return document[key.data()].GetString();
        }
        return nullString;
    }

    /**
 * 根节点获取key的值
 * @param key
 * @param document
 * @return
 */
    long long int getInt64(std::string key, Document &document) {
        if (document.HasMember(key.data()) && document[key.data()].IsInt64()) {
            return document[key.data()].GetInt64();
        }
        return numberZero;
    }

    /**
      *获取object的key的值
      * @param key
      * @param document
      * @return
      */
    std::string getString(std::string key, Value &object) {
        if (object.HasMember(key.data()) && object.IsObject()
            && object[key.data()].IsString()) {
            return object[key.data()].GetString();
        }
        return nullString;
    }

    /**
     * 获取objec的int64
     * @param key
     * @param object
     * @return
     */
    long long int getInt64(std::string key, Value &object) {
        if (object.HasMember(key.data()) && object.IsObject()
            && object[key.data()].IsInt64()) {
            return object[key.data()].GetInt64();
        }
        return numberZero;
    }

    /**
     * 获取object
     * @param key
     * @param document
     * @return
     */
    rapidJson::Object getObject(std::string key, Document &document) {
        Value result(kObjectType);
        if (document.HasMember(key.data()) && document[key.data()].IsObject()) {
            return document[key.data()].GetObject();
        }
        return result.GetObject();
    }

    /**
     * 获取数组
     * @param key
     * @param document
     * @return
     */
    rapidJson::Array getArray(std::string key, Document &document) {

        if (document.HasMember(key.data()) && document[key.data()].IsArray()) {
            return document[key.data()].GetArray();
        }
        Value result(kArrayType);
        return result.GetArray();;
    }

    /**
     * 根节点添加属性
     * @param key
     * @param value
     * @param document
     * @return
     */
    Document &addAttrString(std::string key, std::string value, Document &document) {
        Value jsonValue(kStringType);
        jsonValue.SetString(StringRef(value.data()));
        auto &allocator = document.GetAllocator();
        document.AddMember(StringRef(key.data()), jsonValue, allocator);
        return document;
    }

    /**
     * 根节点添加属性
     * @param key
     * @param value
     * @param document
     * @return
     */
    Document &addAttrInt64(std::string key, long long int value, Document &document) {
        Value jsonValue(kNumberType);
        jsonValue.SetInt64(value);
        auto &allocator = document.GetAllocator();
        document.AddMember(StringRef(key.data()), jsonValue, allocator);
        return document;
    }

    Document &addArray(std::string key, Document &document) {
        if (document.IsNull()) {
            document.SetObject();
        }
        Value backupPaths(kArrayType);
        backupPaths.SetArray();
        auto &allocator = document.GetAllocator();
        document.AddMember("backupPaths", backupPaths, allocator);
        return document;
    }

    /**
     * 为对象添加属性 key值为value
     * @param key
     * @param value
     * @param document
     * @param object
     * @return
     */
    Value &addObjectAttrString(std::string key, std::string value, Document &document, Value &object) {
        if (object.IsObject()) {
            auto &allocator = document.GetAllocator();
            Value keyJson(StringRef(key.data()), allocator);
            Value valueJson(StringRef(value.data()));
            object.AddMember(keyJson, valueJson, allocator);
        }

        return object;
    }

    /**
     * 为对象添加属性 key值为value
     * @param key
     * @param value
     * @param document
     * @param object
     * @return
     */
    Value &addObjectAttrInt64(std::string key, long long int value, Document &document, Value &object) {
        if (object.IsObject()) {
            auto &allocator = document.GetAllocator();
            Value keyJson(StringRef(key.data()), allocator);
            Value valueJson(value);
            object.AddMember(keyJson, valueJson, allocator);
        }
        return object;
    }

    /**
     * 写
     * @param path
     * @param document
     */
    void write(std::string path, Document &document) {
        std::ofstream ofs(path);
        OStreamWrapper osw(ofs);
        Writer<OStreamWrapper> writer(osw);
        document.Accept(writer);
        osw.Flush();
        std::cout<<path<<"-->flush"<<std::endl;
        ofs.close();
    }

    /**
     * 读
     * @param path
     * @return
     */
    Document reade(std::string path) {
        Document document;
        std::ifstream file(path);
        if (file) {
            IStreamWrapper isw(file);
            document.ParseStream(isw);
        }
        return document;
    }

private:
    rapidJson json;
    const  std::string nullString = "";
    const  int numberZero=0;

};

#endif //BACKUP_FILE_JSON_H
