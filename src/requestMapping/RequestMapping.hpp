//
// Created by xiyuan_fengyu on 2018/1/29.
//

#ifndef REQUESTMAPPING_REQUESTMAPPING_HPP
#define REQUESTMAPPING_REQUESTMAPPING_HPP

#include "RequestDispatcher.hpp"

namespace xiyuan {

// 全局函数版本
#ifndef RequestMapping
#define RequestMapping(pathMatch, httpMethod, methodName) \
void handler_##methodName##_callback(const std::shared_ptr<HttpServer::Response> &response, const std::shared_ptr<HttpServer::Request> &request);\
auto handler_##methodName##_index = xiyuan::add(pathMatch, #httpMethod, &(handler_##methodName##_callback)); /* NOLINT */\
void handler_##methodName##_callback(const std::shared_ptr<HttpServer::Response> &response, const std::shared_ptr<HttpServer::Request> &request)
#endif

}

#endif //REQUESTMAPPING_REQUESTMAPPING_HPP
