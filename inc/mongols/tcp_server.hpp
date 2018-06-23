#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP


#include <netinet/in.h>   
#include <string>
#include <utility>


#include "thead_pool.hpp"
#include "epoll.hpp"

#define CLOSE_CONNECTION true
#define KEEPALIVE_CONNECTION false

namespace mongols {

    class tcp_server {
    public:
        tcp_server() = delete;
        tcp_server(const std::string& host, int port, int timeout = 5000, size_t buffer_size = 1024, size_t thread_size = 0, int max_event_size = 64);
        virtual~tcp_server();


    public:
        void run(const std::function<std::pair<std::string, bool>(const std::string&) >&);
    private:
        mongols::epoll epoll;
        std::string host;
        int port, listenfd, timeout;
        struct sockaddr_in serveraddr;
        size_t buffer_size;
    private:
        mongols::thread_pool th_pool;
        static bool done;
        static void signal_normal_cb(int sig);

    private:
        void setnonblocking(int fd);
    };
}


#endif /* TCP_SERVER_HPP */
