#include <iostream>
#include <irc-client.h>
#include <regex>

irc::Client::Client(asio::io_context& io_context, Settings settings) : io_context_(io_context), settings_(settings){
    socket_ = new asio::ip::tcp::socket(io_context);
    resolver_ = new asio::ip::tcp::resolver(io_context_);
    send_queue_ = new std::deque<std::string>();

}

irc::Client::~Client(){
    delete socket_;
    delete send_queue_;
    delete resolver_;
}

void irc::Client::set_on_message_received_handler(std::function<void(irc::Response)> on_message_received){
    on_message_received_ = on_message_received;
}

void irc::Client::set_on_names_received_handler(std::function<void(irc::Response)> on_names_received){
    on_names_received_ = on_names_received;
}

void irc::Client::set_on_connection_failed_handler(std::function<void()> on_connection_failed){
    on_connection_failed_ = on_connection_failed;
}

void irc::Client::set_on_connection_success_handler(std::function<void()> on_connection_success){
    on_connection_success_ = on_connection_success;
}

void irc::Client::set_settings(irc::Settings settings){
    settings_ = settings;
}

void irc::Client::connect(){
    socket_->close();
    resolver_->async_resolve(settings_.hostname, settings_.port, [this](auto const& error, auto results){
        if(error){
            on_connection_failed_();
            return;
        }
        socket_->async_connect(*results, [this](auto const& error){
            if(error){
                on_connection_failed_();
                return;
            }
            on_connection_success_();
            identify();
            read_line();
        });
    });
}

void irc::Client::identify(){
    send_line("USER " + settings_.nick + " 0 . " + settings_.nick);
    send_line("NICK " + settings_.nick);
}

void irc::Client::send_line(std::string line){
    line += "\r\n";
    if(line.find("PONG") == 0){
        send_queue_->push_front(line);
    }else{
        send_queue_->push_back(line);
    }
    send_next_line();
}

void irc::Client::join(std::string channel){
    send_line("JOIN " + channel);
}

void irc::Client::send_private_message(std::string message, std::string receiver){
    auto line = "PRIVMSG " + receiver + " :" + message;
    send_line(line);
}

void irc::Client::send_names_command(std::string channel){
    auto line = "NAMES " + channel;
    send_line(line);
}

void irc::Client::read_line(){
    asio::async_read_until(*socket_, buf_, "\r\n", [this](auto const& error, std::size_t s){
        std::istream i{&buf_};
        std::string line;
        std::getline(i, line);
        handle_new_line(line);
        read_line();
    });
}

void irc::Client::handle_new_line(std::string line){
    irc::Response response = parse_response(line);
    if(response.command == "353"){
        on_names_received_(response);
    }
    if(response.command == "PING"){
        handle_ping(response.params);
    }
    if(response.command == "PRIVMSG" || response.command == "NOTICE"){
        on_message_received_(response);
    }
}

void irc::Client::send_next_line(){
    if(send_queue_->size() == 0){
        return;
    }
    auto line = send_queue_->front();
    send_queue_->pop_front();
    socket_->async_send(asio::buffer(line), [this](auto const& error, std::size_t size){
        send_next_line();
    });
}

void irc::Client::handle_ping(std::string ping){
    std::string message = "PONG " + ping;
    send_line(message);
}

irc::Response irc::Client::parse_response(std::string line) {
    std::regex rgx("(?::(.*?)(?:!(?:.*?))?(?:@(?:.*?))? )?(.*?) (.*)");
    std::smatch matches;
    irc::Response response;
    if(std::regex_search(line, matches, rgx)){
        response.sender = matches[1].str();
        response.command = matches[2].str();
        response.params = matches[3].str();
    }
    return response;
}
