#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

class TcpClient {
	int m_socketfd;

public:
	TcpClient() :m_socketfd(-1) {
	
	}
	~TcpClient() {
		if (m_socketfd >= 0) close();
	}

	bool connect(char** argv) {
		m_socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_socketfd == -1) return false;

		hostent* h = gethostbyname(argv[1]);
		sockaddr_in servaddr;
		//servaddr.sin_addr = h->h_addr_list[0];
		memcpy(&servaddr.sin_addr, h->h_addr, h->h_length);
		servaddr.sin_port = htons(atoi(argv[2]));
		servaddr.sin_family = AF_INET;

		if (::connect(m_socketfd, (sockaddr*)&servaddr, sizeof(servaddr)) != 0)  //向服务器发起连接请求
		{
			std::cout << "连接建立失败" << std::endl;
			return false;
		}
		return true;
	}


	bool send(const std::string& s) {
		int iret = 0;
		if ((iret = ::send(m_socketfd, s.c_str(), s.size(), 0)) <= 0) {
			return false;
		}
		return true;
	}

	bool recv(std::string & buffer, size_t max_len) {
		int iret = 0;
		buffer.clear();
		buffer.resize(max_len);
		if ((iret = ::recv(m_socketfd, &buffer[0], max_len, 0)) <= 0) return false;
		buffer.resize(iret);
		return true;
	}

	bool close() {
		::close(m_socketfd);
		return true;
	}
};

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cout << "error when inputting" << std::endl;
		exit(EXIT_FAILURE);
	}
	TcpClient tc;
	if (!tc.connect(argv)) {
		std::cout << "Connection Failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < 10; ++i) {
		std::string str = "This is the " + std::to_string(i) + "st/nd/rd/th request";
		if (!tc.send(str)) {
			std::cout << "Sending Failed" << std::endl;
			exit(EXIT_FAILURE);
		}
		std::string buffer;
		if (tc.recv(buffer, 1024)) {
			std::cout << "Recv: " << buffer << std::endl;
		}
	}

	tc.close();
	return 0;
}