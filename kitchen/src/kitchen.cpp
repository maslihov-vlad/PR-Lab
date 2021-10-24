#include "kitchen.hpp"

void kitchen::start()
{
	
	boost::asio::io_context io_context;
    hall_pipeline = new server<distribution_message, order_message>(io_context, port);
    io_context.run();
    try {
		while(1) {
			for (auto cook : cooks) {
				if (cook.is_free) {
					auto order = hall_pipeline->get_msg();
					memcpy(&(cook.order_), order.body(), sizeof(cook.order_));
					cook.is_free = false;
					cook.start();
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

void kitchen::cook::start() 
{
	
}

void kitchen::cook::process() 
{

}