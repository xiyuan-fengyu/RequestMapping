#include <iostream>
#include "requestMapping/RequestMapping.hpp"

using namespace std;
using namespace xiyuan;

//class Handler {
//
//    RequestMapping("/", true, root) {
//        cout << "just test" << endl;
//    }
//
//};

RequestMapping("/", true, root) {
    cout << "just test" << endl;
}

void test(const std::string &path, const rapidjson::Document &request, const rapidjson::Document &response){
    cout << "test" << endl;
}

int main() {

    rapidjson::Document doc;
    doc.Parse("{}");

    xiyuan::RequestDispatcher::instance.dispatch("/", doc, doc);

    JsonUtil::prettyPrint(doc);
    return 0;
}