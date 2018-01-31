//
// Created by xiyuan_fengyu on 2018/1/29.
//

#ifndef REQUESTMAPPING_REQUESTDISPATCHER_HPP
#define REQUESTMAPPING_REQUESTDISPATCHER_HPP

#include <server_http.hpp>
#include <functional>
#include <vector>
#include <regex>
#include <unordered_map>

namespace xiyuan {

    using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

    typedef
    std::function<void(const std::vector<std::string> &pathParams, const std::shared_ptr<HttpServer::Request> &request, const std::shared_ptr<HttpServer::Response> &response)>
    HandlerMethod;

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

    Handler add(const std::string &path, bool exactMatch, const HandlerMethod &method) noexcept {
        Handler handler(path[path.size() - 1] == '/' ? path.substr(0, path.size() - 1) : path, exactMatch, method);
        handlers.push_back(handler);
        return handler;
    }

    bool dispatch(const std::shared_ptr<HttpServer::Request> &request, const std::shared_ptr<HttpServer::Response> &response) {
        auto path = request->path;
        if (path[path.size() - 1] == '/') path.pop_back();
        auto it = handlers.begin();
        std::vector<std::string> pathParams;
        for (; it != handlers.end(); ++it) {
            std::string hPath = it->path;
            bool exactMatch = it->exactMatch;
            if (exactMatch) {
                if (hPath == path) {
                    it->method(pathParams, request, response);
                    return true;
                }
            } else {
                std::smatch sm;
                if (std::regex_match(path, sm, it->pathReg)) {
                    for (size_t i = 1, size = sm.size(); i <= size; ++i) {
                        pathParams.push_back(sm[i]);
                    }
                    it->method(pathParams, request, response);
                    return true;
                }
            }
        }

        return false;
    }

}
#endif //REQUESTMAPPING_REQUESTDISPATCHER_HPP
