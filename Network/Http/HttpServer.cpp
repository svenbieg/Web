//================
// HttpServer.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "HttpServer.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//==================
// Con-/Destructors
//==================

HttpServer::HttpServer()
{}


//========
// Common
//========

VOID HttpServer::Listen(WORD port)
{
m_Socket=new TcpSocket();
m_Socket->Listen(port);
m_ListenTask=CreateTask(this, &HttpServer::DoListen);
}


//================
// Common Private
//================

VOID HttpServer::DoListen()
{
auto task=GetCurrentTask();
while(!task->Cancelled)
	{
	Handle<TcpSocket> tcp_sock=m_Socket->Accept();
	if(!tcp_sock)
		break;
	Handle<HttpConnection> http_con=new HttpConnection(tcp_sock);
	ConnectionReceived(this, http_con);
	}
}

}}