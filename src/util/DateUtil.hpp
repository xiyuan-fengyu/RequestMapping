//
// Created by xiyuan_fengyu on 2018/1/29.
//

#ifndef REQUESTMAPPING_DATEUTIL_HPP
#define REQUESTMAPPING_DATEUTIL_HPP

#include <chrono>

namespace xiyuan {

    class DateUtil {

    public:
        static long now() {
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        }

    };

}

#endif //REQUESTMAPPING_DATEUTIL_HPP
