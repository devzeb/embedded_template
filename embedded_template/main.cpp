#include <chrono>


int main()
{
    auto now_steady = std::chrono::steady_clock::now();

    volatile auto counts = now_steady.time_since_epoch().count();

    return 0;
}


