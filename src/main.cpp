// ============================================================
// main.cpp —— 第 1 周：最小 HTTP 服务
// ============================================================

#include "httplib.h"   // HTTP 服务器
#include "json.hpp"    // JSON 序列化

#include <cstdio>      // std::printf
#include <cstdlib>     // std::getenv, std::atoi
#include <ctime>       // std::time
#include <string>

int main() {
    httplib::Server svr;

    // ---------- 路由 1：首页 ----------
    svr.Get("/", [](const httplib::Request &, httplib::Response &res) {
        const std::string html =
            "<!doctype html><html lang=\"zh-CN\"><head><meta charset=\"utf-8\">"
            "<title>shop</title></head><body>"
            "<h1>shop 服务已启动</h1>"
            "<p>/api/ping 可以看到 JSON。</p>"
            "</body></html>";
        res.set_content(html, "text/html; charset=utf-8");
    });

    // ---------- 路由 2：健康检查 ----------
    svr.Get("/api/ping", [](const httplib::Request &, httplib::Response &res) {
        nlohmann::json body;
        body["ok"] = true;
        body["ts"] = static_cast<long long>(std::time(nullptr));
        res.set_content(body.dump(), "application/json");
    });

    // ---------- 端口：优先读环境变量 ----------
    int port = 8080;
    if (const char *env = std::getenv("APP_PORT")) {
        port = std::atoi(env);
    }

    std::printf("listening on http://0.0.0.0:%d\n", port);
    svr.listen("0.0.0.0", port);
    return 0;
}
