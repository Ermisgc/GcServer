#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
using namespace std;

class TcpServer{
	int m_sockfd;  //4bytes
	int m_clientfd;  //4bytes
	std::string m_clientip;  //32bytes
	unsigned short m_port;  //2bytes

public:
	TcpServer():m_sockfd(-1), m_clientfd(-1){}
	~TcpServer(){
		if(m_sockfd < 0) closelisten();
		if(m_clientfd < 0) closeclient();
	}

	bool initserver(const unsigned short in_port){  //receive only a port
		//Step 1. create socket
		m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if(m_sockfd == -1) return false;

		//Step 2. bind the ip and port to the socket:
		m_port = in_port;
		sockaddr_in servaddr;
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(m_port);
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //Every ip can be used
		if(bind(m_sockfd, (sockaddr*)&servaddr, sizeof(servaddr)) != 0) return false;

		//Step 3. set the socket connectable
		if(listen(m_sockfd, 5) != 0) return false;
		return true;
	}

	bool accept(){
		//Step 4. accept the request of client, blocking
		sockaddr_in caddr;
		socklen_t addrlen = sizeof(caddr);
		m_clientfd = ::accept(m_sockfd, (sockaddr*)&caddr, &addrlen);
		if(m_clientfd == -1) return false;
		m_clientip = inet_ntoa(caddr.sin_addr);
		return true;
	}

	const std::string & clientip() const{
		return m_clientip;
	} 

	bool recv(std::string & buffer, size_t max_len){
		buffer.clear();
		buffer.resize(max_len);

		int iret = 0;
		if((iret = ::recv(m_clientfd, &buffer[0], max_len, 0)) <= 0) return false;
		buffer.resize(iret);
		return true;
	} 

	bool send(std::string & s){
		int iret = 0;
		if((iret = ::send(m_clientfd, s.c_str(), s.length(), 0)) <= 0) return false;
		return true;
	}

	bool closeclient(){
		::close(m_clientfd);
		return true;
	}

	bool closelisten(){
		::close(m_sockfd);
		return true;
	}
};

void FathEXIT(int sig);
void ChldEXIT(int sig);

int main(int argc, char ** argv){
	// cout << sizeof(std::string) << endl;
	// cout << sizeof(unsigned short) << endl;
	if(argc != 2){
		cout << "Using: test 1214" << endl;
		exit(EXIT_FAILURE);
	}
	TcpServer ts;
	ts.initserver(atoi(argv[1]));
	
	while(ts.accept()){
		//blocking
		int pid = fork();
		if(pid == -1){
			cout << "resources are inadequate" << endl;
			exit(EXIT_FAILURE);
		}
		else if(pid > 0) continue;
		while(1){
			std::string buffer;
			if(ts.recv(buffer, 1024)){
				std::cout << buffer << std::endl;
				std::string back = "I have receive one";
				if(!ts.send(back)){
					std::cout << "Sending error" << std::endl;
					break;
				}
			}
		}
	}
	return 0;
}