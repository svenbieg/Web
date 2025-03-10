//==============
// HttpClient.h
//==============

#pragma once


//=======
// Using
//=======

#include "HttpConnection.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//=============
// Http-Client
//=============

class HttpClient
{
public:
	// Common
	static Handle<HttpConnection> Connect(Handle<String> Url, WORD Port=80);
};

}}