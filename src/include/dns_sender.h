#pragma once
#include <string>
#include <deque>
#include <mutex>
#include <map>

#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")

#include "my_socket.h"
#include "dns_packet.h"
#include "host_list.h"
#include "my_map.h"

class MyQueue;
class JobQueue;
class DNSSender
{
public:
	DNSSender() = delete;
	explicit DNSSender(JobQueue *job_queue, HostList *host_list, MyMap *my_map, const std::string &address);
	DNSSender(const DNSSender *other) = delete;
	~DNSSender() = default;

	void Start();                               
	void set_packet();
	
	void set_queue(MyQueue *queue) noexcept;    

	void Responce();                            

private:
	JobQueue *job_queue_ = nullptr; // 从该队列中取出数据并处理发送
	MyQueue *data_queue_ = nullptr; // 将数据复制到该结构中
	HostList *host_list_ = nullptr; // 对照表

	MySocket sockSend_;             // 质询socket
	MySocket sockQuest_;            //

	std::string address_;           // 上级dns服务器地址
	MyMap *my_map_ = nullptr;
	DNSPacket dns_packet_;

	void set_reply(const std::string &ip);
	void send_to_client();
	void send_to_client(const sockaddr_in &addr);
};