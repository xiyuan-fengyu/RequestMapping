//
// Created by xiyuan_fengyu on 2018/1/29.
//

#ifndef REQUESTMAPPING_STRINGUTIL_HPP
#define REQUESTMAPPING_STRINGUTIL_HPP

#include <random>
#include "DateUtil.hpp"

namespace xiyuan {

    class StringUtil {
        static std::string chars;

    public:
        static std::string randomStr(int len) {
            if (len <= 0) return "";
            static auto charsLen = int(chars.length());

            std::random_device rd;
            std::default_random_engine gen = std::default_random_engine(rd());
            std::uniform_int_distribution<int> dis(0, int(chars.length() - 1));

            std::string res;
            for (int i = 0; i < len; ++i) {
                res.push_back(chars[dis(gen)]);
            }
            return res;
        }

        static std::string randomStrWithTime(int len, const std::string &divider) {
            auto res = randomStr(len);
            res += divider;

            long now = DateUtil::now();
            while (now > 0) {
                res.push_back(chars[int(now % chars.length())]);
                now /= chars.length();
            }
            return res;
        }
    };
    std::string StringUtil::chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

}

#endif //REQUESTMAPPING_STRINGUTIL_HPP
