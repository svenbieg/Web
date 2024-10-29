//=================
// HttpsServer.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "HttpsServer.h"

using namespace Network::Tls;


//===========
// Namespace
//===========

namespace Network {
	namespace Https {


//==================
// Con-/Destructors
//==================

HttpsServer::HttpsServer(Handle<String> host_name):
m_HostName(host_name)
{}


//========
// Common
//========

VOID HttpsServer::Listen(WORD port)
{
m_Socket=new TcpSocket();
m_Socket->Listen(port);
m_ListenTask=CreateTask(this, &HttpsServer::DoListen);
}


//================
// Common Private
//================

VOID HttpsServer::DoListen()
{
auto task=GetCurrentTask();
while(!task->Cancelled)
	{
	Handle<TcpSocket> tcp_sock=m_Socket->Accept();
	if(!tcp_sock)
		break;
	Handle<TlsSocket> tls_sock=new TlsSocket(tcp_sock);
	if(!tls_sock->Accept(m_HostName))
		break;
	Handle<HttpConnection> http_con=new HttpConnection(tls_sock);
	ConnectionReceived(this, http_con);
	}
}

}}