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

    struct Response{
        std::string sender;
        std::string command;
        std::string params;
    };

    class Client{
    private:
        Settings settings_;
        asio::io_context& io_context_;
        asio::ip::tcp::socket* socket_;
        asio::ip::tcp::resolver* resolver_;
        asio::streambuf buf_;
        std::deque<std::string>* send_queue_;
        std::function<void(irc::Response)> on_message_received_;
        std::function<void(irc::Response)> on_names_received_;
        std::function<void()> on_connection_failed_;
        std::function<void()> on_connection_success_;
    public:
        explicit Client(asio::io_context& io_context, Settings settings);
        ~Client();
        void set_on_message_received_handler(std::function<void(irc::Response)> on_message_received);
        void set_on_names_received_handler(std::function<void(irc::Response)> on_names_received);
        void set_on_connection_failed_handler(std::function<void()> on_connection_failed);
        void set_on_connection_success_handler(std::function<void()> on_connection_success);
        void set_settings(irc::Settings settings);
        void connect();
        void send_line(std::string line);
        void join(std::string channel);
        void send_private_message(std:: string message, std::string receiver);
        void send_names_command(std::string channel);
        void identify();

    private:
        void read_line();
        void send_next_line();
        void handle_ping(std::string line);
        void handle_new_line(std::string line);
        irc::Response parse_response(std::string line);
    };

}
