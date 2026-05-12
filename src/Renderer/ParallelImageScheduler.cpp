#include "ParallelImageScheduler.hpp"

#include <algorithm>
#include <thread>

ParallelImageScheduler::ParallelImageScheduler(int threads)
    : _numThreads(threads ? threads : 4),
      _queues(_numThreads),
      _mutexes(_numThreads) {}

void ParallelImageScheduler::submit(int start, int end, int chunkSize, Task task)
{
    for (int i = start; i < end; i += chunkSize) {
        int chunkEnd = std::min(i + chunkSize, end);
        _tasks.push_back({i, chunkEnd, task});
    }
}

void ParallelImageScheduler::run()
{
    std::vector<std::jthread> workers;
    workers.reserve(_numThreads);

    for (int i = 0; i < _numThreads; i++) {
        workers.emplace_back(&ParallelImageScheduler::worker, this, i);
    }
}

void ParallelImageScheduler::clear()
{
    _tasks.clear();

    for (int i = 0; i < _numThreads; i++) {
        std::lock_guard<std::mutex> lock(_mutexes[i]);
        _queues[i].clear();
    }
}

void ParallelImageScheduler::distributeWork(int id)
{
    for (size_t i = id; i < _tasks.size(); i += _numThreads) {
        std::lock_guard<std::mutex> lock(_mutexes[id]);
        _queues[id].push_back(_tasks[i]);
    }
}

bool ParallelImageScheduler::consumeWork(int id, TaskChunk &outChunk)
{
    std::lock_guard<std::mutex> lock(_mutexes[id]);
    if (!_queues[id].empty()) {
        outChunk = _queues[id].back();
        _queues[id].pop_back();
        return true;
    }
    return false;
}

bool ParallelImageScheduler::stealWork(int id, TaskChunk& outChunk)
{
    for (int i = 0; i < _numThreads; i++) {
        if (i == id)
            continue;
        std::lock_guard<std::mutex> lock(_mutexes[i]);
        if (!_queues[i].empty()) {
            outChunk = _queues[i].front();
            _queues[i].pop_front();
            return true;
        }
    }
    return false;
}

ParallelImageScheduler::TaskChunk ParallelImageScheduler::getWorkerChunk(int id)
{
    TaskChunk chunk;
    if (consumeWork(id, chunk) || stealWork(id, chunk))
        return chunk;
    return {};
}

bool ParallelImageScheduler::executeTask(const TaskChunk &chunk)
{
    if (chunk._start >= chunk._end || !chunk._task)
        return false;
    for (int i = chunk._start; i < chunk._end; i++) {
        chunk._task(i);
    }
    return true;
}

void ParallelImageScheduler::worker(int id)
{
    distributeWork(id);
    while (true) {
        if (executeTask(getWorkerChunk(id)))
            continue;
        return;
    }
}
