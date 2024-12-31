//=================
// HttpsClient.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Network/Dns/DnsClient.h"
#include "Network/Tls/TlsSocket.h"
#include "HttpsClient.h"

using namespace Network::Dns;
using namespace Network::Http;
using namespace Network::Tls;


//===========
// Namespace
//===========

namespace Network {
	namespace Https {


//========
// Common
//========

Handle<HttpConnection> HttpsClient::Connect(Handle<String> url, WORD port)
{
auto dns_client=DnsClient::Create();
auto host_ip=dns_client->Lookup(url);
auto host_name=PathHelper::GetHostName(url);
auto tls_socket=TlsSocket::Create();
auto tls_con=tls_socket->Connect(host_ip, port);
tls_con->Handshake(host_name);
return HttpConnection::Create(tls_con);
}

}}