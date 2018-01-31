//
// Created by xiyuan_fengyu on 2018/1/29.
//

#ifndef REQUESTMAPPING_REQUESTDISPATCHER_HPP
#define REQUESTMAPPING_REQUESTDISPATCHER_HPP

#include <server_http.hpp>
#include <functional>
#include <utility>
#include <boost/algorithm/string.hpp>

namespace xiyuan {

    using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

    typedef
    std::function<void(const std::shared_ptr<HttpServer::Response> &response, const std::shared_ptr<HttpServer::Request> &request)>
    HandlerMethod;

    class Handler {
    public:
        const std::string path;
        const std::string httpMethod;
        const HandlerMethod method;
        Handler(const std::string &path, const std::string &httpMethod, const HandlerMethod &method) :
                path(path),
                httpMethod(httpMethod),
                method(method) {}
    };

    std::vector<Handler> handlers;

    size_t add(const std::string &path, const std::string &httpMethod, const HandlerMethod &method) noexcept {
        std::vector<std::string> splits;
        boost::split(splits, httpMethod, boost::is_any_of("|"));
        for (auto &item : splits) {
            handlers.emplace_back(path, item, method);
        }
        return handlers.size() - 1;
    }

}
#endif //REQUESTMAPPING_REQUESTDISPATCHER_HPP
