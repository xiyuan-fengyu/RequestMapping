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

RequestMapping("/test", true, root) {
    stringstream ss;
    ss << "Test ok !";
    response->write(ss);
}

RequestMapping("/test/(\\d+)", false, testId) {
    json resJ;
    resJ["success"] = true;
    resJ["message"] = "ok";
    resJ["data"] = pathParams[0];
    response->write(resJ.dump());
}

RequestMapping("/test/echo", true, testEcho) {
    json resJ;
    resJ["query"] = request->query_string;
    resJ["content"] = request->content.string();
    response->write(resJ.dump());
}

#endif //REQUESTMAPPING_MYCONTROLLER_HPP
