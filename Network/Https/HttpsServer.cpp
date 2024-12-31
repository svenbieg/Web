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


//========
// Common
//========

VOID HttpsServer::Close()
{
if(m_ListenTask)
	{
	m_ListenTask->Cancel();
	m_ListenTask=nullptr;
	}
m_Socket=nullptr;
}

VOID HttpsServer::Listen(WORD port)
{
m_ListenTask=Task::Create(this, [this, port]() { DoListen(port); });
}


//================
// Common Private
//================

VOID HttpsServer::DoListen(WORD port)
{
m_Socket=TlsSocket::Create();
m_Socket->Listen(port);
auto task=Task::Get();
while(!task->Cancelled)
	{
	auto tls_con=m_Socket->Accept();
	tls_con->Handshake(m_HostName);
	auto http_con=HttpConnection::Create(tls_con);
	ConnectionReceived(this, http_con);
	}
}

}}