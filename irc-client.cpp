#include <irc-client.h>

irc::Client::Client(asio::io_context& io_context, Settings settings) : io_context_(io_context), settings_(settings){
    socket_ = new asio::ip::tcp::socket(io_context);
    send_queue_ = new std::deque<std::string>();
    asio::ip::tcp::resolver resolver(io_context);
    auto endpoint = resolver.resolve("irc.freenode.org", "6667");
    auto hostname = asio::ip::host_name();
    asio::connect(*socket_, endpoint);
    std::stringstream message;
    message << "USER marac2 " << hostname << " . :marac2";
    send_line(message.str());
    send_line("NICK marac2");
    read_line();
}

irc::Client::~Client(){
    delete socket_;
    delete send_queue_;
}

void irc::Client::set_on_line_received_handler(std::function<void(std::string)> on_line_received){
    on_line_received_ = on_line_received;
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

void irc::Client::read_line(){
    asio::async_read_until(*socket_, buf_, "\r\n", [this](auto const& error, std::size_t s){
        std::istream i{&buf_};
        std::string line;
        std::getline(i, line);
        on_line_received_(line);
        if(line.find("PING") == 0){
            handle_ping(line);
        }
        read_line();
    });
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

void irc::Client::handle_ping(std::string line){
    std::stringstream message;
    message << "PONG" << line.substr(4);
    send_line(message.str());
}
