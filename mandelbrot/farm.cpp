#include "farm.h"
#include <vector>
#include <thread>
// FIXME - You may need to add #includes here (e.g. <thread>)

void Farm::add_task(Task* task)
{
	task_queue.push(task);
}

void Farm::run()
{
	const int threadCount = std::thread::hardware_concurrency();
	/*std::cout << "Threads to be ran = " << threadCount << std::endl;
	std::cout << "Jobs to be completed = " << task_queue.size() << std::endl;*/
	std::vector<std::thread*> threads;

	for (int i = 0; i < threadCount; i++)
	{
		threads.push_back(new std::thread([&] {
			while (true) {		
				queue_mutex.lock();
				if (task_queue.empty()) {
					queue_mutex.unlock();
					return 0;
				}			
				Task* task = task_queue.front();
				task_queue.pop();
				queue_mutex.unlock();
				task->run();
				delete task;
			}
		}));
	}
	
	
	for (std::thread* t : threads)
	{
		t->join();
		delete t;
	}
}