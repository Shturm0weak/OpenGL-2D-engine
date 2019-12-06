#pragma once
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <future>
using Task = std::function<void()>;
class ThreadPool {
private:
	
	std::vector<std::thread> m_Threads;
	std::mutex m_mutex;
	std::condition_variable m_condition_var;
	bool m_stopping = false;
	std::queue <Task> m_Tasks;
public:
	static ThreadPool* thread_pool;
	int num_Threads = 0;
	ThreadPool(int n);
	~ThreadPool();
	void Infinite_loop_function();
	void shutdown()noexcept;

	void enqueue(Task task);
};
