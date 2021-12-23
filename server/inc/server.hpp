#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <string>

using boost::asio::ip::tcp;

class session
  : public std::enable_shared_from_this<session>
{
public:
  ~session()
  {
    std::cout << "session dead " << "\n";
  }

  session(tcp::socket socket)
    : socket_(std::move(socket))
  {
  }

  void start()
  {
    do_read();
  }

private:
  void do_read();

  void do_write(std::size_t length);
  
  tcp::socket socket_;
  enum { max_length = 255 };
  uint8_t data_[max_length];
};

class server
{
public:
  server(boost::asio::io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
  {
    do_accept();
  }

private:
  void do_accept();

  tcp::acceptor acceptor_;
};