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


//========
// Common
//========

VOID HttpServer::Close()
{
if(m_ListenTask)
	{
	m_ListenTask->Cancel();
	m_ListenTask=nullptr;
	}
if(m_Socket)
	{
	m_Socket->Close();
	m_Socket=nullptr;
	}
}

VOID HttpServer::Listen(WORD port)
{
m_Socket=TcpSocket::Create();
m_Socket->Listen(port);
m_ListenTask=Task::Create(this, &HttpServer::DoListen);
}


//================
// Common Private
//================

VOID HttpServer::DoListen()
{
auto task=Task::Get();
while(!task->Cancelled)
	{
	auto tcp_con=m_Socket->Accept();
	auto http_con=HttpConnection::Create(tcp_con);
	ConnectionReceived(this, http_con);
	}
}

}}