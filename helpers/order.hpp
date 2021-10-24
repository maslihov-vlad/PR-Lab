#pragma once 
#include <map>
#include <string>

#define MAX_MENU_SIZE 20
#define MAX_DISH_IN_ORDER 10
#define MAX_DISH_NAME_SIZE 30
#define MAX_COOKING_APPARATUS_NAME_SIZE 30

#define SIZEOF_ORDER(order) sizeof(size_t) * 5 + sizeof(float) + sizeof(uint64_t) + sizeof(size_t)*order->items_count
#define MIN_SIZEOF_ORDER  sizeof(size_t)   * 5 + sizeof(float) + sizeof(uint64_t) + sizeof(size_t)*1
#define MAX_SIZEOF_ORDER  sizeof(size_t)   * 5 + sizeof(float) + sizeof(uint64_t) + sizeof(size_t)*MAX_DISH_IN_ORDER

#define SIZEOF_DISTRIBUTION(distribution) sizeof(size_t) * 6 + sizeof(float) + sizeof(uint64_t) + sizeof(size_t)*distribution->items_count + sizeof(details)*distribution->items_count
#define MIN_SIZEOF_DISTRIBUTION  		  sizeof(size_t) * 6 + sizeof(float) + sizeof(uint64_t) + sizeof(size_t)*1 + sizeof(details)*1
#define MAX_SIZEOF_DISTRIBUTION  		  sizeof(size_t) * 6 + sizeof(float) + sizeof(uint64_t) + sizeof(size_t)*MAX_DISH_IN_ORDER + sizeof(details)*MAX_DISH_IN_ORDER

struct order
{
	size_t   order_id;
	size_t   table_id;
	size_t   waiter_id;
	size_t   priority;
	float    max_wait;
	uint64_t pick_up_time;
	size_t   items_count;
	size_t   items[MAX_DISH_IN_ORDER]; // для того, чтобы не отправлять хвост
};

struct dish
{
	size_t id;
	char name[MAX_DISH_NAME_SIZE];
	size_t preparation_time;
	size_t complexity;
	char cooking_apparatus[MAX_COOKING_APPARATUS_NAME_SIZE];
};

struct details
{
	size_t food_id;
	size_t cook_id;
};

struct distribution
{
	size_t   order_id;
	size_t   table_id;
	size_t   waiter_id;
	size_t   priority;
	float    max_wait;
	uint64_t pick_up_time;
	size_t 	 cooking_time;
	size_t   items_count;
	size_t   items[MAX_DISH_IN_ORDER];
	details	 cooking_details[MAX_DISH_IN_ORDER];
};

enum KITCHEN_MACHINES
{
	stove,
	oven
};

std::map<std::string, KITCHEN_MACHINES> map {{"oven", oven}, {"stove", stove}};