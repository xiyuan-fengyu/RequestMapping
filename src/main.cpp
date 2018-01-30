#include <iostream>
#include <memory>
#include <boost/lexical_cast.hpp>
#include "requestMapping/RequestMapping.hpp"

using namespace std;
using namespace xiyuan;

RequestMapping("/", true, root) {
    response["data"] = "root test";
    response["success"] = true;
}

RequestMapping("/user/(\\d+)", false, userInfo) {
    response["userId"] = pathInfo.pathParams[0];
}

RequestMapping("/(\\d+)/divide/by/(\\d+)", false, divideByNum) {
    auto num1 = boost::lexical_cast<int>(pathInfo.pathParams[1]);
    if (num1 == 0) throw runtime_error("divide by zero");
    auto num0 = boost::lexical_cast<int>(pathInfo.pathParams[0]);
    response["data"] = num0 / num1;
    response["success"] = true;
}

int main() {
    {
        nlohmann::json req;
        nlohmann::json res;
        xiyuan::dispatch("/", req, res);
        cout << res << endl;
    }

    {
        nlohmann::json req;
        nlohmann::json res;
        xiyuan::dispatch("/user/123", req, res);
        cout << res << endl;
    }

    {
        nlohmann::json req;
        nlohmann::json res;
        xiyuan::dispatch("/1/divide/by/0", req, res);
        cout << res << endl;
    }

    {
        nlohmann::json req;
        nlohmann::json res;
        xiyuan::dispatch("/404", req, res);
        cout << res << endl;
    }

    return 0;
}