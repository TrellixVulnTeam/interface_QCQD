//
//  network.h
//  interface
//
//  Created by Philip Rosedale on 8/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef interface_network_h
#define interface_network_h

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/time.h>
#include "util.h"

//  Port to use for communicating UDP with other nearby agents 
const int MAX_PACKET_SIZE = 1500;
const int UDP_PORT = 30001; 
const char DESTINATION_IP[] = "127.0.0.1";

//  Address and port of spaceserver process to advertise other agents 
const char SPACESERVER_IP[] = "127.0.0.1";
const int SPACESERVER_PORT = 40000;

//  Randomly send a ping packet every N packets sent
const int PING_PACKET_COUNT = 20;      

int network_init();
int network_send(int handle, char * packet_data, int packet_size);
int network_receive(int handle, char * packet_data, int delay /*msecs*/);
timeval network_send_ping(int handle);
int notify_spaceserver(int handle, float x, float y, float z);

#endif
