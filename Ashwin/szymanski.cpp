#include <iostream>
#include <thread>

void print_stuff(const std::thread::id & t)
{
    for(int i = 0; i < 10; ++i)
    {
        std::cout << "Hello ";
        std::cout.flush();
        std::cout << "from thread ";
        std::cout.flush();
        std::cout << t << std::endl;
    }
}

int main()
{
    std::thread t1(print_stuff, t1.get_id());
    std::thread t2(print_stuff, t2.get_id());
    t1.join();
    t2.join();
    // t1.join();
}