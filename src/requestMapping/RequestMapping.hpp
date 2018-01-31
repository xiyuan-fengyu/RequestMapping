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
void handler_##methodName##_callback(const std::vector<std::string> &pathParams, const std::shared_ptr<HttpServer::Request> &request, const std::shared_ptr<HttpServer::Response> &response);\
auto handler_##methodName = xiyuan::add(pathMatch, exactMatch, &(handler_##methodName##_callback)); /* NOLINT */\
void handler_##methodName##_callback(const std::vector<std::string> &pathParams, const std::shared_ptr<HttpServer::Request> &request, const std::shared_ptr<HttpServer::Response> &response)
#endif

}

#endif //REQUESTMAPPING_REQUESTMAPPING_HPP
