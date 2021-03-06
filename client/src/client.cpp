#include "client.hpp"

// template <typename MESSAGE>
// void client<MESSAGE>::write(const MESSAGE& msg)
// {
//   boost::asio::post(io_context_,
//     [this, msg]()
//     {
//       bool write_in_progress = !write_msgs_.empty();
//       write_msgs_.push_back(msg);
//       if (!write_in_progress)
//       {
//         do_write();
//       }
//     });
// }


// template <typename MESSAGE>
// void client<MESSAGE>::close()
// {
//   boost::asio::post(io_context_, [this]() { socket_.close(); });
// }

// template <typename MESSAGE>
// void client<MESSAGE>::do_connect(const tcp::resolver::results_type& endpoints)
// {
//   boost::asio::async_connect(socket_, endpoints,
//     [this](boost::system::error_code ec, tcp::endpoint)
//     {
//       if (!ec) {
//         do_read_header();
//       }
//     });
// }

// template <typename MESSAGE>
// void client<MESSAGE>::do_read_header()
// {
//   boost::asio::async_read(socket_,
//     boost::asio::buffer(read_msg_.data(), MESSAGE::header_length),
//     [this](boost::system::error_code ec, std::size_t /*length*/)
//     {
//       if (!ec) {
//         std::cout << "tag : " << std::string(read_msg_.data(), MESSAGE::header_length) << "\n";
//         do_read_body();
//       } else {
//         socket_.close();
//       }
//     });
// }

// template <typename MESSAGE>
// void client<MESSAGE>::do_read_body()
// {
//   boost::asio::async_read(socket_,
//     boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
//     [this](boost::system::error_code ec, std::size_t /*length*/)
//     {
//       if (!ec) {
//         std::cout.write(read_msg_.body(), read_msg_.body_length());
//         std::cout << "\n";
//         do_read_header();
//       } else {
//         socket_.close();
//       }
//     });
// }

// template <typename MESSAGE>
// void client<MESSAGE>::do_write()
// {
//   boost::asio::async_write(socket_,
//     boost::asio::buffer(write_msgs_.front().data(),
//       write_msgs_.front().length()),
//     [this](boost::system::error_code ec, std::size_t /*length*/)
//     {
//       if (!ec) {
//         write_msgs_.pop_front();
//         if (!write_msgs_.empty()) {
//           do_write();
//         }
//       } else {
//         socket_.close();
//       }
//     });
// }
