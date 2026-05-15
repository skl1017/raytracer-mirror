#pragma once

#include <vector>
#include <thread>
#include <deque>
#include <mutex>
#include <functional>

class ParallelImageScheduler {
public:
    using Task = std::function<void(int)>;

    ParallelImageScheduler(int threads = std::thread::hardware_concurrency());

    void submit(int start, int end, int chunkSize, Task task);
    void run();
    void clear();

private:
    struct TaskChunk {
        int _start;
        int _end;
        Task _task;
    };
    int _numThreads;
    std::vector<std::deque<TaskChunk>> _queues;
    std::vector<std::mutex> _mutexes;
    std::vector<TaskChunk> _tasks;

    void distributeWork(int id);
    bool consumeWork(int id, TaskChunk &outChunk);
    bool stealWork(int id, TaskChunk &outChunk);
    TaskChunk getWorkerChunk(int id);
    bool executeTask(const TaskChunk &chunk);
    void worker(int id);
};
