//
// Created by xiyuan_fengyu on 2018/1/29.
//

#ifndef REQUESTMAPPING_JSONUTIL_HPP
#define REQUESTMAPPING_JSONUTIL_HPP

#include <rapidjson/document.h>
#include <rapidjson/pointer.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include "StringUtil.hpp"

class JsonUtil {
public:
    template <typename Data>
    static void request(const rapidjson::Document &json, const Data &data = rapidjson::Value()) {
//        auto id = xiyuan::StringUtil::randomStrWithTime(4, "");
//        rapidjson::SetValueByPointer(json, "/id", id.c_str());
//        rapidjson::Value value;
//        value.Set(data);
//        if (!value.IsNull()) rapidjson::SetValueByPointer(json, "/data", value);
    }

    template <typename Data>
    static void response(const rapidjson::Document &json, const std::string &id, bool success, const std::string &message = "", const Data &data = rapidjson::Value()) {
//        rapidjson::SetValueByPointer(json, "/id", id.c_str());
//        rapidjson::SetValueByPointer(json, "/success", rapidjson::Value(success));
//        rapidjson::Value value;
//        value.Set(data);
//        if (!value.IsNull()) rapidjson::SetValueByPointer(json, "/data", value);
//        rapidjson::SetValueByPointer(json, "/message", message.c_str());
    }

    template <typename Data>
    static void response(const rapidjson::Document &json, const rapidjson::Document &req, bool success, const std::string &message = "", const Data &data = rapidjson::Value()) {
//        std::string id = rapidjson::GetValueByPointer(json, "/id")->GetString();
//        response(json, id, success, message, data);
    }

    static void print(const rapidjson::Document &json) {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        json.Accept(writer);
        std::cout << buffer.GetString() << std::endl;
    }

    static void prettyPrint(const rapidjson::Document &json) {
        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        json.Accept(writer);
        std::cout << buffer.GetString() << std::endl;
    }

};

#endif //REQUESTMAPPING_JSONUTIL_HPP
