#include <iostream>
#include <thread>
#include <unistd.h>
#include <cstdlib>

void print_stuff(const std::thread::id & t)
{
    for(int i = 0; i < 10; ++i)
    {
        std::cout << "Hello ";
        std::cout.flush();
        usleep((rand() % 1000));
        std::cout << "from thread ";
        usleep(rand() % 1000);
        std::cout.flush();
        usleep(rand() % 1000);
        std::cout << t << std::endl;
        usleep(rand() % 1000);
    }
}

int main()
{
    std::thread t1(print_stuff, t1.get_id());
    std::thread t2(print_stuff, t2.get_id());
    t1.join();
    t2.join();
}
