//===============
// HttpsServer.h
//===============

#pragma once


//=======
// Using
//=======

#include "Concurrency/Task.h"
#include "Network/Http/HttpConnection.h"
#include "Network/Tls/TlsSocket.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Https {


//==============
// HTTPS-Server
//==============

class HttpsServer: public Object
{
private:
	// Using
	using HttpConnection=Network::Http::HttpConnection;
	using Task=Concurrency::Task;
	using TlsSocket=Network::Tls::TlsSocket;

public:
	// Con-/Destructors
	~HttpsServer() { Close(); }
	static inline Handle<HttpsServer> Create(Handle<String> HostName)
		{
		return new HttpsServer(HostName);
		}

	// Common
	VOID Close();
	Event<HttpsServer, Handle<HttpConnection>> ConnectionReceived;
	VOID Listen(WORD Port=443);

private:
	// Con-/Destructors
	HttpsServer(Handle<String> HostName): m_HostName(HostName) {}

	// Common
	VOID DoListen(WORD Port);
	Handle<String> m_HostName;
	Handle<Task> m_ListenTask;
	Handle<TlsSocket> m_Socket;
};

}}
