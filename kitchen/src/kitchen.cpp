#include "kitchen.hpp"

void kitchen::start()
{
	
	boost::asio::io_context io_context;
    hall_pipeline = new server(io_context, port);
    io_context.run();
    try {
		while(1) {
			server.do_read();
			server.get_data(orders);

			for (auto cook : cooks) {
				if (!cook.is_cooking) {
					if (!orders.empty()){
						cook.start(orders.front());
						orders.pop_front();
					}
				} else {
					cook.process();
				}
			}

		}
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	delete hall_pipeline;

}

void kitchen::cook::process();
{
	if (is_cooking) {
		std::chrono::steady_clock::time_point now;
		if (std::chrono::duration_cast<std::chrono::microseconds>(now - start).count() > get_cur_dish().preparation_time) {
			free_cooking_apparatus();

			if (dish_in_process == order_.items_count) {
				is_cooking = false;
				POST();
			} else {
				dish_in_process += 1;
			}
		}
	} else {
		if (cook.check_cooking_apparatus()) {
			start = std::chrono::steady_clock::now();
		}
	}
}

const dish& kitchen::cook::get_cur_dish() 
{
	return ctx->menu[order_.items[dish_in_process]];
}

void kitchen::cook::free_cooking_apparatus() 
{
	auto dish = get_cur_dish(); 
	for (int i = 0; i < dish.complexity; ++i) {
		ctx->kitchen_machines[dish.cooking_apparatus[i]] = false; 
	}
} 

bool kitchen::cook::check_cooking_apparatus() 
{
	auto dish = get_cur_dish(); 
	for (int i = 0; i < dish.complexity; ++i) {
		if (ctx->kitchen_machines[dish.cooking_apparatus[i]] == false)  
			return false;
	}

	for (int i = 0; i < dish.complexity; ++i) {
		ctx->kitchen_machines[dish.cooking_apparatus[i]] = false; 
	}
	
	return true;
}

void kitchen::cook::start(order &new_order) 
{	
	order_ = new_order;
	dish_in_process = 0;
}

distribution kitchen::cook::create_distribution()
{
	std::chrono::steady_clock::time_point now;
	
	distribution d;
	
	d.order_id = order_.order_id;
	d.table_id = order_.table_id;
	d.waiter_id = order_.waiter_id;
	d.priority = order_.priority;
	d.max_wait = order_.priority;
	d.pick_up_time = order_.priority;
	d.cooking_time = std::chrono::duration_cast<std::chrono::microseconds>(now - start).count();
	d.items_count = order_.items_count;
	memcpy(d.items, order_.items, sizeif(size_t) * d.items_count);

	return distribution;
}

void kitchen::cook::POST() 
{
	auto dist = create_distribution();
	distribution_message msg;
	msg.body_length(SIZEOF_DISTRIBUTION(dist));
	std::memcpy(msg.body(), dist, msg.body_length());
	msg.encode_header();
	ctx->server->do_write(msg);
}