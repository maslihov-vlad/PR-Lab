#pragma once 
#include <iostream>
#include <vector> 
#include <ctime>
#include <chrono>

#include <client.hpp>
#include <order_message.hpp>

#include "order.hpp"

#define MAX_WAIT 1.4

class hall
{
public:
	hall(std::string port, size_t num_of_tables, size_t num_of_waiters, size_t stars, std::vector<dish> &&menu) : port(port), num_of_waiters(num_of_waiters),
																	  stars(stars), num_of_tables(num_of_tables),
																	  tables(num_of_tables), waiters(num_of_waiters), menu(menu)
	{
		for (auto table  : tables) table.ctx = this;
		for (auto waiter : waiters) waiter.ctx = this;

		start();
	}

	~hall();

private:
	struct table
	{
		static size_t id;
		table();

		const hall *ctx;

		bool is_free = true;
		bool have_order = false;
		order order_;

		order* request_order();
		order* gen_order();
	};

	struct waiter
	{
		static size_t id;
		static size_t order_id;

		waiter();

		const hall *ctx;

		std::time_t order_start;
		bool is_free = true;
		const order* order_ = NULL;

		void get_order(order* new_order);
		void POST();
	};

	void start();

	client<order_message> *kitchen_pipeline;
	std::thread t;
	size_t stars;
	size_t num_of_tables;
	size_t num_of_waiters;
	size_t menu_size;
	std::string port;
	std::vector<table> tables; 
	std::vector<waiter> waiters;
	std::vector<dish> menu;
};