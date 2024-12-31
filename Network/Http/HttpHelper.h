//==============
// HttpHelper.h
//==============

#pragma once


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//=============
// HTTP-Status
//=============

enum class HttpStatus: UINT
{
None=0,
Ok=200,
NoContent=204,
MovedPermanently=301,
MovedTemporary=302,
PermanentRedirect=308,
BadRequest=400,
Forbidden=403,
SiteNotFound=404,
RequestTimeout=408,
LengthRequired=411,
ConnectionClosed=444,
InternalServerError=500
};


//=============
// HTTP-Method
//=============

enum class HttpMethod: UINT
{
Get,
Notify,
Set,
Post,
Unknown
};


//=============
// HTTP-Helper
//=============

class HttpHelper
{
public:
	// Common
	static LPCSTR MethodToString(HttpMethod Method);
	static HttpMethod MethodFromString(LPCTSTR Method);
	static UINT PathLength(LPCTSTR Buffer, UINT Length=0);
	static Handle<String> PathToString(LPCTSTR Buffer, UINT Length=0);
	static LPCSTR StatusToString(HttpStatus Status);
	static HttpStatus StatusFromString(LPCTSTR Status);
};

}}