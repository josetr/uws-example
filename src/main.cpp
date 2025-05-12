#include <chrono>
#include <uwebsockets/App.h>
#include <iostream>
#include <vector>

int main()
{
    const auto port = 9000;

    std::vector<std::thread> threads;

    uWS::App()
        .get("/*", [](uWS::HttpResponse<false> *res, uWS::HttpRequest *req)
             {
            res->writeHeader("Content-Type", "text/plain");
            res->end("Hello from HTTP server"); })
        .get("/async", [&](uWS::HttpResponse<false> *res, uWS::HttpRequest *req)
             {
            bool aborted = false;

            res->onAborted([&]() {
                aborted = true;
                std::cout << "Request aborted by client!" << std::endl;
            });

            threads.emplace_back([res, &aborted]()
            {
                std::this_thread::sleep_for(std::chrono::seconds(5));
                if (aborted) {
                    std::cout << "Cancelling async response" << std::endl;
                    return;
                }

                res->writeHeader("Content-Type", "text/plain");
                res->end("Hello from HTTP server (async)");
            }); })
        .listen(port, [port](auto *socket)
                {
            if (socket)
            {
                std::cout << "Listening on port " << port << std::endl;
            }
            else
            {
                std::cerr << "Failed to listen on port " << port << std::endl;
            } })
        .run();

    for (auto &thread : threads)
    {
        if (thread.joinable())
            thread.join();
    }
}
