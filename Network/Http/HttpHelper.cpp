//================
// HttpHelper.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "CharHelper.h"
#include "HttpHelper.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//========
// Common
//========

HttpMethod HttpHelper::MethodFromString(LPCTSTR method)
{
if(StringHelper::Compare(method, "NOTIFY", 0, false)==0)
	return HttpMethod::Notify;
if(StringHelper::Compare(method, "GET", 0, false)==0)
	return HttpMethod::Get;
if(StringHelper::Compare(method, "SET", 0, false)==0)
	return HttpMethod::Set;
if(StringHelper::Compare(method, "POST", 0, false)==0)
	return HttpMethod::Post;
return HttpMethod::Unknown;
}

LPCSTR HttpHelper::MethodToString(HttpMethod method)
{
switch(method)
	{
	case HttpMethod::Notify:
		return "NOTIFY";
	case HttpMethod::Get:
		return "GET";
	case HttpMethod::Set:
		return "SET";
	case HttpMethod::Post:
		return "POST";
	case HttpMethod::Unknown:
		return "Unknown";
	}
return nullptr;
}

UINT HttpHelper::PathLength(LPCTSTR str, UINT len)
{
if(len==0)
	len=UINT_MAX;
UINT ret=0;
for(UINT u=0; u<len; u++)
	{
	if(str[u]==0)
		break;
	if(str[u]=='%')
		u+=2;
	ret++;
	}
return ret;
}

Handle<String> HttpHelper::PathToString(LPCTSTR path, UINT len)
{
UINT path_len=PathLength(path, len);
auto str=String::Create(path_len+1, nullptr);
LPTSTR dst=(LPTSTR)str->Begin();
for(UINT u=0; u<len; u++)
	{
	TCHAR c=path[u];
	if(c=='%')
		{
		UINT hex1=0;
		CharHelper::ToDigit(path[u+1], &hex1, 16);
		UINT hex2=0;
		CharHelper::ToDigit(path[u+2], &hex2, 16);
		c=(BYTE)((hex1<<8)|hex2);
		u+=2;
		if(c=='\303')
			{
			TCHAR c1=path[u+1];
			if(c1=='%')
				{
				CharHelper::ToDigit(path[u+2], &hex1, 16);
				CharHelper::ToDigit(path[u+3], &hex2, 16);
				c1=(BYTE)((hex1<<8)|hex2);
				if(c1=='\204')
					{
					c='\304'; // Ä
					}
				else if(c1=='\226')
					{
					c='\326'; // Ö
					}
				else if(c1=='\234')
					{
					c='\334'; // Ü
					}
				else if(c1=='\237')
					{
					c='\337'; // ß
					}
				else if(c1=='\244')
					{
					c='\344'; // ä
					}
				else if(c1=='\266')
					{
					c='\366'; // ö
					}
				else if(c1=='\274')
					{
					c='\374'; // ü
					}
				else
					{
					c='_';
					}
				u+=3;
				}
			}
		}
	*dst++=c;
	}
*dst++=0;
return str;
}

HttpStatus HttpHelper::StatusFromString(LPCTSTR status)
{
if(StringHelper::Compare(status, "Ok", 0, false)==0)
	return HttpStatus::Ok;
if(StringHelper::Compare(status, "No Content", 0, false)==0)
	return HttpStatus::NoContent;
if(StringHelper::Compare(status, "Moved Permanently", 0, false)==0)
	return HttpStatus::MovedPermanently;
if(StringHelper::Compare(status, "Moved Temporary", 0, false)==0)
	return HttpStatus::MovedTemporary;
if(StringHelper::Compare(status, "Permanent Redirect", 0, false)==0)
	return HttpStatus::PermanentRedirect;
if(StringHelper::Compare(status, "Bad Request", 0, false)==0)
	return HttpStatus::BadRequest;
if(StringHelper::Compare(status, "Forbidden", 0, false)==0)
	return HttpStatus::Forbidden;
if(StringHelper::Compare(status, "Site Not Found", 0, false)==0)
	return HttpStatus::SiteNotFound;
if(StringHelper::Compare(status, "Request Timeout", 0, false)==0)
	return HttpStatus::RequestTimeout;
if(StringHelper::Compare(status, "Length Required", 0, false)==0)
	return HttpStatus::LengthRequired;
if(StringHelper::Compare(status, "Connection Closed", 0, false)==0)
	return HttpStatus::ConnectionClosed;
if(StringHelper::Compare(status, "Internal Server Error", 0, false)==0)
	return HttpStatus::InternalServerError;
return HttpStatus::None;
}

LPCSTR HttpHelper::StatusToString(HttpStatus status)
{
switch(status)
	{
	case HttpStatus::Ok:
		return "Ok";
	case HttpStatus::NoContent:
		return "No Content";
	case HttpStatus::MovedPermanently:
		return "Moved Permanently";
	case HttpStatus::MovedTemporary:
		return "Moved Temporary";
	case HttpStatus::PermanentRedirect:
		return "Permanent Redirect";
	case HttpStatus::BadRequest:
		return "Bad Request";
	case HttpStatus::Forbidden:
		return "Forbidden";
	case HttpStatus::SiteNotFound:
		return "Site Not Found";
	case HttpStatus::RequestTimeout:
		return "Request Timeout";
	case HttpStatus::LengthRequired:
		return "Length Required";
	case HttpStatus::ConnectionClosed:
		return "Connection Closed";
	case HttpStatus::InternalServerError:
		return "Internal Server Error";
	default:
		return nullptr;
	}
return nullptr;
}

}}