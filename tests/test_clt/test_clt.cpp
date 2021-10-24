#include <iostream>
#include <client.hpp>
#include <order_message.hpp>
#include <distribution_message.hpp>

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: chat_client <host> <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;

    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(argv[1], argv[2]);
    client<order_message, distribution_message> c(io_context, endpoints);

    std::thread t([&io_context](){ io_context.run(); });

    char line[order_message::max_body_length + 1];
    while (std::cin.getline(line, order_message::max_body_length + 1))
    {
      order_message msg;
      msg.body_length(std::strlen(line));
      std::memcpy(msg.body(), line, msg.body_length());
      msg.encode_header();
      msg.encode_tag();
      c.write(msg);
    }

    c.close();
    t.join();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}