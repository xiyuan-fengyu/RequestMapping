//
// Created by xiyuan_fengyu on 2018/1/29.
//

#ifndef REQUESTMAPPING_REQUESTMAPPING_HPP
#define REQUESTMAPPING_REQUESTMAPPING_HPP

#include "RequestDispatcher.hpp"

namespace xiyuan {

// 全局函数版本
#ifndef RequestMapping
#define RequestMapping(pathMatch, exactMatch, methodName) \
void handler_##methodName##_callback(const xiyuan::PathInfo &, nlohmann::json &, nlohmann::json &);\
auto handler_##methodName = xiyuan::add(pathMatch, exactMatch, &(handler_##methodName##_callback)); /* NOLINT */\
void handler_##methodName##_callback(const xiyuan::PathInfo &pathInfo, nlohmann::json &request, nlohmann::json &response)
#endif

}

#endif //REQUESTMAPPING_REQUESTMAPPING_HPP
