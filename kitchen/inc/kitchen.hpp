#pragma once 
#include <iostream>
#include <vector> 
#include <ctime>
#include <chrono>
#include <queue>

#include <server.hpp>
#include <distribution_message.hpp>

#include "order.hpp"

class kitchen 
{
public:
	kitchen(std::string &port, size_t num_of_cooks, size_t num_of_waiters, size_t stars, std::vector<dish> &&menu) : port(std::atoi(port.c_str())), num_of_cooks(num_of_cooks),
																													cooks(num_of_cooks), menu(menu)

	{
		start();
	}

private:

	struct cmp 
	{
        bool operator()(const order& a, const order& b) const {
            return a.priority > b.priority;
        }
    };

	struct cook
	{
		static size_t id;

		bool is_free;
		order* order_ = NULL;
	};
    
	void start();

	server *hall_pipeline;
	std::thread t;

	size_t port;
	size_t num_of_cooks;
	std::vector<cook> cooks;
	std::vector<dish> menu;
 	// std::priority_queue<order, std::vector<order>, cmp> orders;
	std::map<KITCHEN_MACHINES, bool> kitchen_machines;
};