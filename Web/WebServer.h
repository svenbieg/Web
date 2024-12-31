//=============
// WebServer.h
//=============

#pragma once


//=======
// Using
//=======

#include "Collections/map.hpp"
#include "Network/Http/HttpServer.h"
#include "Network/Https/HttpsServer.h"
#include "Timing/Clock.h"
#include "WebContext.h"
#include "WebSession.h"


//===========
// Namespace
//===========

namespace Web {


//======================
// Forward-Declarations
//======================

class WebSite;


//============
// Web-Server
//============

class WebServer: public Object
{
public:
	// Using
	using Clock=Timing::Clock;
	using HttpConnection=Network::Http::HttpConnection;
	using HttpServer=Network::Http::HttpServer;
	using HttpsServer=Network::Https::HttpsServer;
	using WebSessionMap=Collections::map<Handle<String>, Handle<WebSession>>;

	// Con-/Destructors
	~WebServer() { Close(); }
	static inline Handle<WebServer> Create(WebSite* WebSite, Handle<String> HostName=nullptr)
		{
		return new WebServer(WebSite, HostName);
		}

	// Common
	VOID Close();
	VOID Listen();

private:
	// Con-/Destructors
	WebServer(WebSite* WebSite, Handle<String> HostName);

	// Common
	VOID DoAccept(Handle<HttpConnection> Connection);
	VOID DoGet(Handle<WebContext> Context);
	VOID DoNotify(Handle<WebContext> Context);
	VOID DoPost(Handle<WebContext> Context);
	VOID OnClockHour();
	VOID OnConnectionReceived(Handle<HttpConnection> Connection);
	Handle<Clock> m_Clock;
	Handle<HttpServer> m_HttpServer;
	Handle<HttpsServer> m_HttpsServer;
	Concurrency::Mutex m_Mutex;
	WebSessionMap m_Sessions;
	WebSite* m_WebSite;
};

}