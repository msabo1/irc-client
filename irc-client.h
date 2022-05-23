#ifndef IRCCLIENT_H
#define IRCCLIENT_H

#include <deque>
#include <string>
#include <boost/asio.hpp>
#endif // IRCCLIENT_H
namespace asio = boost::asio;

namespace irc{

    struct Settings{
        std::string hostname;
        std::string port;
        std::string nick;
    };

    class Client{
    private:
        Settings settings_;
        asio::io_context& io_context_;
        asio::ip::tcp::socket* socket_;
        asio::streambuf buf_;
        std::deque<std::string>* send_queue_;
        std::function<void(std::string)> on_line_received_;
    public:
        explicit Client(asio::io_context& io_context, Settings settings);
        ~Client();
        void set_on_line_received_handler(std::function<void(std::string)> on_line_received);
        void send_line(std::string line);
        void join(std::string channel);
        void send_private_message(std:: string message, std::string receiver);

    private:
        void read_line();
        void send_next_line();
        void handle_ping(std::string line);
    };

}
