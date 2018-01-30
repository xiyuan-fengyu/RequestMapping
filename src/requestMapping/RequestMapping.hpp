//
// Created by xiyuan_fengyu on 2018/1/29.
//

#ifndef REQUESTMAPPING_REQUESTMAPPING_HPP
#define REQUESTMAPPING_REQUESTMAPPING_HPP

#include <functional>
#include <rapidjson/document.h>
#include "RequestDispatcher.hpp"

namespace xiyuan {

// 全局函数版本
#ifndef RequestMapping
#define RequestMapping(pathMatch, exactMatch, methodName) \
void handler_##methodName##_callback(const xiyuan::PathInfo &, const rapidjson::Document &, const rapidjson::Document &);\
auto handler_##methodName = xiyuan::add(pathMatch, exactMatch, &(handler_##methodName##_callback)); /* NOLINT */\
void handler_##methodName##_callback(const xiyuan::PathInfo &pathInfo, const rapidjson::Document &request, const rapidjson::Document &response)
#endif

}

#endif //REQUESTMAPPING_REQUESTMAPPING_HPP

// 废弃版本 Controller + Method
// 版本原型
//class MyController {
//
//public: static MyController instance;
//
//public: xiyuan::HandlerMethod handler_root = RequestDispatcher::instance.add("/", true, std::bind(&root, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
//public: void root(const std::string &path, const rapidjson::Document &request, const rapidjson::Document &response) {
//        cout << "just test" << endl;
//    }
//
//};
//MyController MyController::instance;

// Controller + Method 的版本
//#ifndef Controller_Start
//#define Controller_Start(controllerName)\
//class controllerName {\
//public: static controllerName instance;
//#endif
//
//#ifndef Controller_End
//#define Controller_End(controllerName)\
//};\
//controllerName controllerName::instance;
//#endif
//
//#ifndef RequestMapping
//#define RequestMapping(pathMatch, exactMatch, methodName)\
//public: xiyuan::HandlerMethod handler_##methodName = RequestDispatcher::instance.add(pathMatch, exactMatch, std::bind(&methodName, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));\
//public: void methodName(const std::string &path, const rapidjson::Document &request, const rapidjson::Document &response)
//#endif

// 示例
//Controller_Start(Main)
//    RequestMapping("/", true, test) {
//    JsonUtil::prettyPrint(request);
//}
//Controller_End(Main)