/*
 * File:   Socket.h
 * Author: RAJIB AHMED            - raae10
 * Author: MOHAMMAD ABDUR RAZZAK  - morc10
 * influenced by Rob Tougher Article on Linux Gazette
 * Created on December 10, 2011, 2:38 AM
 */

#ifndef SOCKET_H
#define SOCKET_H


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>


const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 600;

class Socket
{
 public:
  Socket();
  virtual ~Socket();

  bool create();
  bool bind ( const int port );
  bool listen() const;
  bool accept ( Socket& ) const;


  bool connect ( const std::string host, const int port );

  bool send ( const std::string ) const;
  int recv ( std::string& ) const;
  void close();


  bool is_valid() const { return m_sock != -1; }


 private:

  int m_sock;
  sockaddr_in m_addr;

};
#endif
