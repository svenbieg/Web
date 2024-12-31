//==============
// HttpServer.h
//==============

#pragma once


//=======
// Using
//=======

#include "Concurrency/Task.h"
#include "Network/Tcp/TcpSocket.h"
#include "HttpConnection.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//=============
// HTTP-Server
//=============

class HttpServer: public Object
{
private:
	// Using
	using Task=Concurrency::Task;
	using TcpSocket=Network::Tcp::TcpSocket;

public:
	// Con-/Destructors
	~HttpServer() { Close(); }
	static inline Handle<HttpServer> Create() { return new HttpServer(); }

	// Common
	VOID Close();
	Event<HttpServer, Handle<HttpConnection>> ConnectionReceived;
	VOID Listen(WORD Port=80);

private:
	// Con-/Destructors
	HttpServer() {}

	// Common
	VOID DoListen();
	Handle<Task> m_ListenTask;
	Handle<TcpSocket> m_Socket;
};

}}