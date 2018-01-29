//
// Created by xiyuan_fengyu on 2018/1/29.
//

#ifndef REQUESTMAPPING_REQUESTMAPPING_HPP
#define REQUESTMAPPING_REQUESTMAPPING_HPP

#include <rapidjson/document.h>
#include "RequestDispatcher.hpp"

namespace xiyuan {

#ifndef RequestMapping
#define RequestMapping(pathMatch, exactMatch, methodName) \
static void methodName(const std::string &, const rapidjson::Document &, const rapidjson::Document &);\
xiyuan::RequestDispatcher dispatcher_##methodName(pathMatch, exactMatch, &(methodName));\
static void methodName(const std::string &path, const rapidjson::Document &request, const rapidjson::Document &response)
#endif

}

#endif //REQUESTMAPPING_REQUESTMAPPING_HPP
