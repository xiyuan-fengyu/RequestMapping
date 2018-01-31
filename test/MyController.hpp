//
// Created by xiyuan_fengyu on 2018/1/31.
//

#ifndef REQUESTMAPPING_MYCONTROLLER_HPP
#define REQUESTMAPPING_MYCONTROLLER_HPP

#include <iostream>
#include "requestMapping/RequestMapping.hpp"
#include <json.hpp>  // https://github.com/nlohmann/json/blob/develop/src/json.hpp

using namespace std;
using namespace xiyuan;
using namespace nlohmann;

RequestMapping("/test", GET, root) {
    stringstream ss;
    ss << "Test ok !";
    response->write(ss);
}

RequestMapping("/test/(\\d+)", GET|POST, testId) {
    json res;
    res["success"] = true;
    res["message"] = "ok";
    res["data"] = request->path_match[1];
    response->write(res.dump());
}

RequestMapping("/test/get", GET, testGet) {
    json res;
    res["query"] = request->query_string;
    response->write(res.dump());
}

RequestMapping("/test/post", POST, testPost) {
    json res;
    res["query"] = request->query_string;
    res["content"] = request->content.string();
    response->write(res.dump());
}

#endif //REQUESTMAPPING_MYCONTROLLER_HPP
