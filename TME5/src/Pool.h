#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>
#include <functional>
#include <iostream>

namespace pr {
void poolWorker(Queue<Job> &queue){
	while (true){
		Job* j = queue.pop();
		if (j==nullptr){ break;}
		j->run();
		delete j;
	}
}
class Pool {
	Queue<Job> queue;
	std::vector<std::thread> threads;
public:
	Pool(int qsize) : queue(qsize){}

	void start (int nbthread){
		for (int i=0;i<nbthread;i++){
			threads.emplace_back(poolWorker,std::ref(queue));
		}
	}
	void submit (Job * job){
		for (int i=0;i<queue.size();i++)
			queue.push(job);
	}
	void stop(){
		queue.setBlock(false);
		for (auto& t : threads){
			t.join();
		}
	}
	~Pool() ;
};

}
