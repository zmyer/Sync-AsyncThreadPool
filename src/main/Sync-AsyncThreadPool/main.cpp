//
// Created by StevensChew on 17/1/15.
//
#include <thread>
#include "ThreadPool.h"

namespace syncasyncthreadpool {
    int main() {
        ThreadPool pool;
        pool.Start(2);

        this_thread::sleep_for(std::chrono::seconds(2));
        getchar();
        pool.Stop();
        return 0;
    }
}
