#pragma once
#include<iostream>
#include<thread>
namespace pr {

class Job {
public:
	virtual void run () = 0;
	virtual ~Job() {};
};

}
