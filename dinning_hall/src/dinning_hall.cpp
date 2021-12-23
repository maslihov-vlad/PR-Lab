#include "dinning_hall.hpp"

void hall::start()
{
	boost::asio::io_context io_context;
	tcp::resolver resolver(io_context);
	auto endpoints = resolver.resolve("127.0.0.1", port.c_str());
	
	kitchen_pipeline = new client<order_message>(io_context, endpoints); // костыль 
	std::thread t([&io_context](){ io_context.run(); });

	try {
		while(1) {
			for (auto waiter : waiters) {
				if (!waiter.is_free)
					continue;

				for (auto table : tables) {
					waiter.get_order(table.request_order());
				}

			}

		}
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	kitchen_pipeline->close();
	t.join();
	delete kitchen_pipeline;

}

hall::table::table() 
{
	id = id? id++ : 1;
}

hall::waiter::waiter() 
{
	id = id? id++ : 1;
	order_id = order_id? order_id++ : 1;
}


order* hall::table::request_order()
{
	if (is_free && !have_order && rand()%100 == 0) { 
		return gen_order();
	}
}

order* hall::table::gen_order()
{
	size_t items[MAX_DISH_IN_ORDER] = {0};
	size_t items_count = rand()%MAX_DISH_IN_ORDER;
	size_t max_wait = 0;
	
	for (int i = 0; i < items_count; ++i) {
		items[i] = rand()%ctx->menu_size;	
		max_wait = ctx->menu[items[i]].preparation_time > max_wait  ? ctx->menu[items[i]].preparation_time : max_wait;
		++items[i]; 
	}

	std::time_t t = std::time(0);

	order_.table_id = id;
	order_.priority = rand()%5+1;
	order_.max_wait = max_wait * 1.3;
	order_.pick_up_time = (uint64_t)t;
	order_.items_count = items_count;
	memcpy(order_.items, items, items_count*sizeof(size_t));

	return &order_;
}

void hall::waiter::get_order(order* new_order) 
{
	if (new_order == NULL) 
		return;
	new_order->order_id = order_id++;
	new_order->waiter_id = id;
	order_ = new_order;
}

void hall::waiter::POST() 
{
	order_message msg;
	msg.body_length(SIZEOF_ORDER(order_));
	std::memcpy(msg.body(), order_, msg.body_length());
	msg.encode_header();
	ctx->kitchen_pipeline->write(msg);
}
