//================
// HttpClient.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "Network/Tcp/TcpClient.h"
#include "HttpClient.h"

using namespace Network::Tcp;


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//========
// Common
//========

Handle<HttpConnection> HttpClient::Connect(Handle<String> url, WORD port)
{
auto tcp_con=TcpClient::Connect(url, port);
return HttpConnection::Create(tcp_con);
}

}}