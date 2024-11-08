```cpp
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

std::queue<int> produced_nums;
std::mutex m;
std::condition_variable cond_var;

void producer(int id) {
    for (int i = 0; ; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(900));
        std::unique_lock<std::mutex> lock(m);
        std::cout << "producer " << id << " pushing " << i << std::endl;
        produced_nums.push(i);
        cond_var.notify_all();
    }
}

void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(m);
        while (produced_nums.empty()) {
            cond_var.wait(lock);
        }
        std::cout << "consumer " << id << " popped " << produced_nums.front() << std::endl;
        produced_nums.pop();
    }
}

int main() {
    std::thread p1(producer, 0);
    std::thread p2(producer, 1);
    std::thread c1(consumer, 0);
    std::thread c2(consumer, 1);
    p1.join();
    p2.join();
    c1.join();
    c2.join();
    return 0;
}
```