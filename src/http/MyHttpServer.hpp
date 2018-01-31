//
// Created by xiyuan_fengyu on 2018/1/31.
//

#ifndef REQUESTMAPPING_MYHTTPSERVER_HPP
#define REQUESTMAPPING_MYHTTPSERVER_HPP

#include <server_http.hpp>
#include "requestMapping/RequestDispatcher.hpp"
#include <thread>
#include <fstream>
#include <boost/filesystem.hpp>

#ifndef READ_FILE_BUFFER_SIZE
#define READ_FILE_BUFFER_SIZE 204800
#endif

namespace xiyuan {
    class MyHttpServer {
        HttpServer httpServer{};
        std::thread httpServerThread;

    public:
        explicit MyHttpServer(const std::string &address = "0.0.0.0", unsigned short port = 8080, size_t threadPoolSize = 10) {
            httpServer.config.address = address;
            httpServer.config.port = port;
            httpServer.config.thread_pool_size = threadPoolSize;

            for (auto &handler : xiyuan::handlers) {
                httpServer.resource[handler.path][handler.httpMethod] = [handler](const std::shared_ptr<HttpServer::Response> &response, const std::shared_ptr<HttpServer::Request> &request) {
                    handler.method(response, request);
                };
            }
            httpServer.default_resource["GET"] = [](const std::shared_ptr<HttpServer::Response> &response, const std::shared_ptr<HttpServer::Request> &request) {
                try {
                    auto web_root_path = boost::filesystem::canonical("web");
                    auto path = boost::filesystem::canonical(web_root_path / request->path);
                    // Check if path is within web_root_path
                    if(std::distance(web_root_path.begin(), web_root_path.end()) > std::distance(path.begin(), path.end()) ||
                       !std::equal(web_root_path.begin(), web_root_path.end(), path.begin()))
                        throw std::runtime_error("path must be within root path");
                    if(boost::filesystem::is_directory(path))
                        path /= "index.html";

                    SimpleWeb::CaseInsensitiveMultimap header;

                    // Uncomment the following line to enable Cache-Control
                    header.emplace("Cache-Control", "max-age=86400");

                    auto ifs = std::make_shared<std::ifstream>();
                    ifs->open(path.string(), std::ifstream::in | std::ios::binary | std::ios::ate);

                    if(*ifs) {
                        auto length = ifs->tellg();
                        ifs->seekg(0, std::ios::beg);

                        header.emplace("Content-Length", to_string(length));
                        response->write(header);

                        sendStaticFile(response, ifs);
                    }
                    else
                        throw std::runtime_error("could not read file");
                }
                catch(const std::exception &e) {
                    response->write(SimpleWeb::StatusCode::client_error_bad_request, "not found: " + request->path);
                }
            };

            httpServer.on_error = [](std::shared_ptr<HttpServer::Request> equest, const SimpleWeb::error_code & /*ec*/) {
                // Handle errors here
                // Note that connection timeouts will also call this handle with ec set to SimpleWeb::errc::operation_canceled
            };

            httpServerThread = std::thread([this]{
                httpServer.start();
            });
        }

        static void sendStaticFile(const std::shared_ptr<HttpServer::Response> &response, const std::shared_ptr<std::ifstream> &ifs) {
            thread_local char buffer[READ_FILE_BUFFER_SIZE];
            std::streamsize bufferSize(READ_FILE_BUFFER_SIZE);
            std::streamsize readLen;
            if ((readLen = ifs->read(&buffer[0], bufferSize).gcount()) > 0) {
                response->write(&buffer[0], readLen);
                response->send([response, ifs](const SimpleWeb::error_code &ec) {
                    if (ec) {
                        std::cerr << "connection interrupted" << std::endl;
                    }
                    else {
                        sendStaticFile(response, ifs);
                    }
                });
            }
        }

        virtual ~MyHttpServer() {
            if (httpServerThread.joinable()) httpServerThread.join();
            httpServer.stop();
        }

    };
}

#endif //REQUESTMAPPING_MYHTTPSERVER_HPP
