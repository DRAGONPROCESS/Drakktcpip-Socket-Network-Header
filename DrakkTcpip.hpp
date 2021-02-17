/*
* 
* Developed by Drakk
* DrakkTcpip.hpp (Open the TCP/IP socket library)
* Version<1.0>
* 
* Define the "CLIENT",If you just want to use client Before including this header.
* Also, Define the "SERVER",If you just want to use server Before including this header.
* ## This library can only be running with C++17 or higher versions. ##
* 
*/

/*
* 
* [ Defined Methods ]
* Socket(int);
* Socket(const char*, int, int);
* Conn_Debug(int);
* 
* [ Defined Macros ]
* CONN_NO : 0
* CONN_YES : 1
* CONN_SUCCESS : 100
* 
*/

#pragma once
#pragma comment(lib, "ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define CONN_NO (0)
#define CONN_YES (1)
#define CONN_SUCCESS (100)

#include <tuple>
#include <winsock2.h>
#include <windows.h>

namespace taboo {
	int drakk_len(const char* __STR) {
		__int32 size = 0;
		while (__STR[size] != '\0') size++;
		return size;
	}
}

#ifdef SERVER
/// <summary>
/// The function that Open the TCP/IP server socket.
/// </summary>
/// <param name="__PORT">Input your port number.</param>
/// <returns>It returns the socket structure and integer data type.</returns>
std::tuple<SOCKET, SOCKADDR_IN, int> Socket(int __PORT) {
	SOCKET server = NULL;
	SOCKADDR_IN addr = { 0 };
	try {
		WSADATA wsa;
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) throw 1;

		server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (server == INVALID_SOCKET) throw 2;

		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		addr.sin_port = htons(__PORT);
		addr.sin_family = AF_INET;

		if (bind(server, (SOCKADDR*)&addr, sizeof addr) == SOCKET_ERROR) throw 3;
		if (listen(server, SOMAXCONN) == SOCKET_ERROR) throw 4;

		SOCKADDR_IN clientaddr = { 0 };
		int clientsize = sizeof clientaddr;
		server = accept(server, (SOCKADDR*)&clientaddr, &clientsize);
		if (server == INVALID_SOCKET) throw 5;
		throw 6;
	}
	catch (int returns) {
		switch (returns) {
		case 1: return std::make_tuple(NULL, (SOCKADDR_IN)NULL, 1);
		case 2: return std::make_tuple(NULL, (SOCKADDR_IN)NULL, 2);
		case 3: return std::make_tuple(NULL, (SOCKADDR_IN)NULL, 3);
		case 4: return std::make_tuple(NULL, (SOCKADDR_IN)NULL, 4);
		case 5: return std::make_tuple(NULL, (SOCKADDR_IN)NULL, 5);
		case 6: return std::make_tuple(server, addr, 100);
		}
	}
	return std::make_tuple(NULL, (SOCKADDR_IN)NULL, 7);
}

/// <summary>
/// Debugging based on "Socket" Function returns and print debug message.
/// </summary>
/// <param name="__RETURN">Value that retuned from "Socket" Function.</param>
void Conn_Debug(int __RETURN) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushFileBuffers(hStdOut);

	if (__RETURN == 1) WriteFile(hStdOut, "WSA ERROR.", taboo::drakk_len("WSA ERROR."), 0, 0);
	else if (__RETURN == 2) WriteFile(hStdOut, "INVALID SERVER SOCKET.", taboo::drakk_len("INVALID SERVER SOCKET."), 0, 0);
	else if (__RETURN == 3) WriteFile(hStdOut, "BIND ERROR.", taboo::drakk_len("BIND ERROR."), 0, 0);
	else if (__RETURN == 4) WriteFile(hStdOut, "LISTEN ERROR.", taboo::drakk_len("LISTEN ERROR."), 0, 0);
	else if (__RETURN == 5) WriteFile(hStdOut, "INVALID SERVER SOCKET.", taboo::drakk_len("INVALID SERVER SOCKET."), 0, 0);
	else if (__RETURN == 100) WriteFile(hStdOut, "SUCCESS.", taboo::drakk_len("SUCCESS."), 0, 0);
	else if (__RETURN == 7) WriteFile(hStdOut, "FUNCTION NOT RETURNED.", taboo::drakk_len("FUNCTION NOT RETURNED."), 0, 0);
	
	FlushFileBuffers(hStdOut);
}
#endif

#ifdef CLIENT
/// <summary>
/// The function that Open the TCP/IP client socket.
/// </summary>
/// <param name="__IP">Input your ip address.</param>
/// <param name="__PORT">Input your port number.</param>
/// <param name="__FLAGS">CONN_NO : Connecting to server</param>
/// <param name="__FLAGS">CONN_YES: Connecting to server until connected to server</param>
/// <returns>It returns the socket structure and integer data type.</returns>
std::tuple<SOCKET, SOCKADDR_IN, int> Socket(const char* __IP, int __PORT, int __FLAGS) {
	SOCKET server = NULL;
	SOCKADDR_IN addr = { 0 };
	try {
		WSADATA wsa;
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) throw 1;

		server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (server == INVALID_SOCKET) throw 2;

		addr.sin_addr.s_addr = inet_addr(__IP);
		addr.sin_port = htons(__PORT);
		addr.sin_family = AF_INET;

		if (__FLAGS == 0) {
			if (connect(server, (SOCKADDR*)&addr, sizeof addr) == INVALID_SOCKET)
				throw 3;
		}
		else if (__FLAGS == 1) while (connect(server, (SOCKADDR*)&addr, sizeof addr));
		if (server == INVALID_SOCKET) throw 4;
		throw 5;
	}
	catch (int returns) {
		switch (returns) {
		case 1: return std::make_tuple(NULL, (SOCKADDR_IN)NULL, 1);
		case 2: return std::make_tuple(NULL, (SOCKADDR_IN)NULL, 2);
		case 3: return std::make_tuple(NULL, (SOCKADDR_IN)NULL, 3);
		case 4: return std::make_tuple(NULL, (SOCKADDR_IN)NULL, 4);
		case 5: return std::make_tuple(server, addr, 100);
		}
	}
	return std::make_tuple(NULL, (SOCKADDR_IN)NULL, 6);
}

/// <summary>
/// Debugging based on "Socket" Function returns and print debug message.
/// </summary>
/// <param name="__RETURN">Value that retuned from "Socket" Function.</param>
void Conn_Debug(int __RETURN) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushFileBuffers(hStdOut);

	if (__RETURN == 1) WriteFile(hStdOut, "WSA ERROR.", taboo::drakk_len("WSA ERROR."), 0, 0);
	else if (__RETURN == 2) WriteFile(hStdOut, "INVALID SERVER SOCKET.", taboo::drakk_len("INVALID SERVER SOCKET."), 0, 0);
	else if (__RETURN == 3) WriteFile(hStdOut, "SERVER CONNECTION ERROR(#1).", taboo::drakk_len("SERVER CONNECTION ERROR(#1)."), 0, 0);
	else if (__RETURN == 4) WriteFile(hStdOut, "SERVER CONNECTION ERROR(#2).", taboo::drakk_len("SERVER CONNECTION ERROR(#2)."), 0, 0);
	else if (__RETURN == 100) WriteFile(hStdOut, "SUCCESS.", taboo::drakk_len("SUCCESS."), 0, 0);
	else if (__RETURN == 6) WriteFile(hStdOut, "FUNCTION NOT RETURNED.", taboo::drakk_len("FUNCTION NOT RETURNED."), 0, 0);

	FlushFileBuffers(hStdOut);
}
#endif