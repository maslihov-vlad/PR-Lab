#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <string>
#include <message.hpp>
#include <variant>
#include <deque>

using boost::asio::ip::tcp;

template <typename MESSAGE_POST, typename MESSAGE_GET>
class session
  : public std::enable_shared_from_this<session<MESSAGE_POST, MESSAGE_GET>>
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

  std::variant<bool, MESSAGE_GET> get_msg()
  {
    if (!accepted_msg.empty()) {
      auto m = accepted_msg.front();
      accepted_msg.pop_front();
      return m;
    }
    return false;
  }

  void start()
  {
    do_read_header();
  }

private:
  void do_read_header()
  {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(msg.data(), MESSAGE_GET::header_length + MESSAGE_GET::tag_length),
      [this, self](boost::system::error_code ec, std::size_t length)
      {
        if (!ec)
        {
          printf("\n");
          msg.decode_header();
          msg.decode_tag();

          printf("len %d\ntag %d\n", msg.data()[0], msg.data()[1]);
          
          do_read_body();
        }
      });
  }


  void do_read_body()
  {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(msg.body(), msg.body_length()),
      [this, self](boost::system::error_code ec, std::size_t length)
      {
        if (!ec)
        {
          accepted_msg.push_back(msg);
          std::cout << std::string((char*)msg.body(), msg.body_length()) << "\n";
          do_write();
        }
      });
  }

  void do_write()
  {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(msg.data(), msg.length()),
      [this, self](boost::system::error_code ec, std::size_t /*length*/)
      {
        if (!ec) {
          do_read_header();
        }
      });
  } 

  std::deque<MESSAGE_GET> accepted_msg;
  MESSAGE_GET msg;
  tcp::socket socket_;
};

template <typename MESSAGE_POST, typename MESSAGE_GET>
class server
{
public:
  server(boost::asio::io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
  {
    do_accept();
  }


  MESSAGE_GET&& get_msg()
  {
  }


private:
  void do_accept()
  {
    acceptor_.async_accept(
      [this](boost::system::error_code ec, tcp::socket socket)
      {
        if (!ec) {
          std::make_shared<session<MESSAGE_POST, MESSAGE_GET>>(std::move(socket))->start();
        }

        do_accept();
      });
  }

  tcp::acceptor acceptor_;
};