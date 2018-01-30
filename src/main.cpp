#include <iostream>
#include <memory>
#include "requestMapping/RequestMapping.hpp"

using namespace std;
using namespace xiyuan;

RequestMapping("/", true, root) {
    cout << "just test" << endl;
}

RequestMapping("/user/(\\d+)", false, userInfo) {
    cout << "user id: " << pathInfo.pathParams[0] << endl;
}

int main() {
    rapidjson::Document doc;
    doc.Parse("{}");
    xiyuan::dispatch("/", doc, doc);
    xiyuan::dispatch("/user/123", doc, doc);
    xiyuan::dispatch("/user/456", doc, doc);
    return 0;
}