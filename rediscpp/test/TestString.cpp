#include "rediscpp.h"

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "TestTool.h"

std::string ip = "127.0.0.1";
int port = 21015;

using namespace rediscpp;

Connection g_context;

bool test_SET_GET()
{
    try {
        String redis{g_context};
        redis.SET(Buffer("a"), Buffer(12));
        redis.SET(Buffer("b"), Buffer(120000));
        redis.SET(Buffer("c"), Buffer(123.23));
        redis.SET(Buffer("d"), Buffer("12345678901234567890"));

        std::vector<uint8_t> temp{};
        for (int i = 0; i != 1024; ++i) {
            temp.push_back(static_cast<uint8_t>(i));
        }
        redis.SET(Buffer("e"), Buffer(temp));

        TEST(redis.GET(Buffer("a")).asInt() == 12);
        TEST(redis.GET(Buffer("b")).asInt() == 120000);
        TEST(redis.GET(Buffer("c")).asDouble() == 123.23);
        TEST(redis.GET(Buffer("d")).asString() == "12345678901234567890");
        TEST(redis.GET(Buffer("e")).getDataVector() == temp);
        return true;
    } catch (const Exception& e) {
        std::cout << "RedisException:" << __LINE__ << ":" << __FUNCTION__ << ":" << e.what() << "\n";
        return false;
    }
}

bool test_INCR_INCRBY()
{
    try {
        String redis{g_context};
        Buffer key{"a"};
        redis.SET(key, Buffer(0));
        TEST(redis.INCRBY(key, 100000) == 100000);
        TEST(redis.INCR(key) == 100000 + 1);
        return true;
    } catch (const Exception& e) {
        std::cout << "RedisException:" << __LINE__ << ":" << __FUNCTION__ << ":" << e.what() << "\n";
        return false;
    }
}

bool test_PING()
{
    try {
        auto s = rediscpp::PING(g_context, "    ");
        std::cout << s << "\n";
        return true;
    } catch (const Exception& e) {
        std::cout << "RedisException:" << __LINE__ << ":" << __FUNCTION__ << ":" << e.what() << "\n";
        return false;
    }
}

int main()
{
    auto context = rediscpp::redisConnect(ip, port);
    if (!context) {
        std::cout << "error context error\n";
        return 0;
    }
    g_context = std::move(context);

    //test_SET_GET();
    //test_INCR_INCRBY();
    test_PING();
    return 0;
}
