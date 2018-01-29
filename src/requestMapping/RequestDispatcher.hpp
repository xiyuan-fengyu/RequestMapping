//
// Created by xiyuan_fengyu on 2018/1/29.
//

#ifndef REQUESTMAPPING_REQUESTDISPATCHER_HPP
#define REQUESTMAPPING_REQUESTDISPATCHER_HPP

#include <rapidjson/document.h>
#include <unordered_map>
#include "util/JsonUtil.hpp"

namespace xiyuan {

    typedef void(*HandlerMethod)(const std::string &path, const rapidjson::Document &request, const rapidjson::Document &response);

    struct Handler {
        bool exactMatch;
        HandlerMethod method;
    };

    class RequestDispatcher {

        typedef std::unordered_map<std::string, Handler> HandlerMap;

        HandlerMap handlers;

        explicit RequestDispatcher() = default;

    public:
        static RequestDispatcher instance;

        RequestDispatcher(const std::string &path, bool exactMatch, HandlerMethod method) noexcept {
            Handler handler { exactMatch, method };
            instance.handlers[path] = handler;
        }

        void dispatch(const std::string &path, const rapidjson::Document &request, const rapidjson::Document &response) {
            try {
                auto it = handlers.begin();
                for (; it != handlers.end(); ++it) {
                    std::string hPath = it->first;
                    HandlerMethod hMethod = it->second.method;
                    bool exactMatch = it->second.exactMatch;
                    if (exactMatch) {
                        if (hPath == path) {
                            hMethod(path, request, response);
                            return;
                        }
                    } else if (path.find(hPath) == 0) {
                        hMethod(path, request, response);
                        return;
                    }
                }
            }
            catch (std::exception &e) {
                auto exceptionH = handlers.find("/exception");
                if (exceptionH != handlers.cend()) {
                    exceptionH->second.method(path, request, response);
                } else JsonUtil::response(response, request, false, "inner exception", nullptr);
                return;
            }

            auto notFoundH = handlers.find("/notFound");
            if (notFoundH != handlers.cend()) {
                notFoundH->second.method(path, request, response);
            } else JsonUtil::response(response, request, false, "not found", nullptr);
        }

    };

    RequestDispatcher RequestDispatcher::instance{};

}
#endif //REQUESTMAPPING_REQUESTDISPATCHER_HPP
