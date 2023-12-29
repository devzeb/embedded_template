#include <chrono>


int main()
{
    auto now_steady = std::chrono::steady_clock::now();

    auto new_system = std::chrono::system_clock::now();

    return 0;
}


