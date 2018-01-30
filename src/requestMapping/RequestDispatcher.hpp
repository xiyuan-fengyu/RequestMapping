//
// Created by xiyuan_fengyu on 2018/1/29.
//

#ifndef REQUESTMAPPING_REQUESTDISPATCHER_HPP
#define REQUESTMAPPING_REQUESTDISPATCHER_HPP

#include <functional>
#include <vector>
#include <regex>
#include <json.hpp>

namespace xiyuan {

    class PathInfo {
    public:
        std::string path;
        std::vector<std::string> pathParams {};
        explicit PathInfo(const std::string &path) : path(std::move(path)) {}
    };

    typedef std::function<void(const xiyuan::PathInfo &pathInfo, nlohmann::json &request, nlohmann::json &response)> HandlerMethod;

    class Handler {
    public:
        std::string path;
        std::regex pathReg;
        bool exactMatch;
        HandlerMethod method;

        Handler(const std::string &path, bool exactMatch, const HandlerMethod &method) {
            this->path = path;
            this->exactMatch = exactMatch;
            if (!exactMatch) {
                pathReg = std::regex(path);
            }
            this->method = method;
        }
    };

    std::vector<Handler> handlers;

    Handler add(const char *path, bool exactMatch, const HandlerMethod &method) noexcept {
        Handler handler(path, exactMatch, method);
        handlers.push_back(handler);
        return handler;
    }

    void dispatch(const std::string &path, nlohmann::json &request, nlohmann::json &response) {
        try {
            auto it = handlers.begin();
            for (; it != handlers.end(); ++it) {
                std::string hPath = it->path;
                bool exactMatch = it->exactMatch;
                if (exactMatch) {
                    if (hPath == path) {
                        it->method(PathInfo(path), request, response);
                        return;
                    }
                } else {
                    std::smatch sm;
                    if (std::regex_match(path, sm, it->pathReg)) {
                        PathInfo pathInfo(path);
                        for (size_t i = 1, size = sm.size(); i <= size; ++i) {
                            pathInfo.pathParams.push_back(sm[i]);
                        }
                        it->method(pathInfo, request, response);
                        return;
                    }
                }
            }
        }
        catch (std::exception &e) {
            response["success"] = false;
            response["message"] = e.what()[0] == '\0' ? "inner exception" : e.what();
            return;
        }

        response["success"] = false;
        response["message"] = "not found";
    }

}
#endif //REQUESTMAPPING_REQUESTDISPATCHER_HPP
