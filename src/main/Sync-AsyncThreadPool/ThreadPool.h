//
// Created by StevensChew on 17/1/15.
//

#ifndef SYNC_ASYNCTHREADPOOL_THREADPOOL_H
#define SYNC_ASYNCTHREADPOOL_THREADPOOL_H

#include <iostream>
#include <list>
#include <thread>
#include "SyncQueue.h"

using namespace std;

namespace syncasyncthreadpool {
    const int MAX_TASK_COUNT = 100;

    class ThreadPool {
    public:
        using Task = std::function<void()>;

        ThreadPool(int numThreds = std::thread::hardware_concurrency()) : m_queue(MAX_TASK_COUNT) {
            Start(numThreds);
        }

        ~ThreadPool() {
            Stop();
        }

        void Stop() {
            std::call_once(m_flag, [this] { StopThreadGroup(); });
        }

        void AddTask(Task &&task) {
            m_queue.Put(std::forward<Task>(task));
        }

        void AddTask(const Task &task) {
            m_queue.Put(task);
        }

        void Start(int numThreads) {
            m_running = true;
            for (int index = 0; index < numThreads; index++) {
                m_threadgroup.push_back(std::make_shared<std::thread>(&ThreadPool::RunInThread, this));
            }
        }

        void RunInThread() {
            while (m_running) {
                std::list<Task> list;
                m_queue.Task(list);
                for (auto &task : list) {
                    if (!m_running)
                        return;
                    task();
                }
            }
        }

        void StopThreadGroup() {
            m_queue.stop();
            m_running = false;
            for (auto thread : m_threadgroup) {
                if (thread)
                    thread->join();
            }
            m_threadgroup.clear();
        }

    private:
        std::list<std::shared_ptr<std::thread>> m_threadgroup;
        SyncQueue<Task> m_queue;
        atomic_bool m_running;
        std::once_flag m_flag;
    };
}

#endif //SYNC_ASYNCTHREADPOOL_THREADPOOL_H
