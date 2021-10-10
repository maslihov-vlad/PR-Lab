#include "kitchen.hpp"

void kitchen::start()
{
	
	boost::asio::io_context io_context;
    hall_pipeline = new server(io_context, port);
    io_context.run();
    try {
		while(1) {
			for (auto cook : cooks) {

			}

		}
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	delete hall_pipeline;

}