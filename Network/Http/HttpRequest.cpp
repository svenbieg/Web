//=================
// HttpRequest.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StreamHelper.h"
#include "Storage/Streams/StreamReader.h"
#include "Storage/Streams/StreamWriter.h"
#include "HttpRequest.h"

using namespace Culture;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//========
// Common
//========

VOID HttpRequest::Clear()
{
HttpMessage::Clear();
Cookies->Clear();
Method=HttpMethod::Unknown;
Parameters->Clear();
Path=nullptr;
}

LanguageCode HttpRequest::GetLanguage()
{
auto lng=Parameters->Get("lng");
if(lng)
	return Language::FromString(lng->Begin());
lng=Properties->Get("Accept-Language");
if(!lng)
	return LanguageCode::None;
return Language::FromString(lng->Begin());
}

Handle<HttpRequest> HttpRequest::FromUrl(Handle<String> url)
{
Handle<HttpRequest> request=new HttpRequest();
if(!url)
	return request;
LPCTSTR url_ptr=url->Begin();
UINT host_pos=0;
if(StringHelper::Compare(url_ptr, "http://", 7, false)==0)
	host_pos+=7;
if(StringHelper::Compare(url_ptr, "https://", 8, false)==0)
	host_pos+=8;
Handle<String> host;
LPCTSTR host_ptr=&url_ptr[host_pos];
UINT path_pos=0;
if(StringHelper::Find(host_ptr, "/", &path_pos))
	{
	host=String::Create(path_pos, host_ptr);
	LPCTSTR path_ptr=&host_ptr[path_pos+1];
	UINT params_pos=0;
	if(StringHelper::Find(path_ptr, "?", &params_pos))
		{
		LPCTSTR params_ptr=&path_ptr[params_pos+1];
		request->Path=String::Create(params_pos, path_ptr);
		request->Parameters->Set(params_ptr);
		}
	else
		{
		request->Path=path_ptr;
		}
	}
else
	{
	host=host_ptr;
	}
request->Properties->Add("Host", host);
return request;
}

SIZE_T HttpRequest::ReadFromStream(InputStream* stream)
{
Clear();
Status=HttpStatus::InternalServerError;
StreamReader reader(stream);
SIZE_T size=0;
TCHAR buf[256];
size+=reader.ReadString(buf, 256, " ");
Method=HttpHelper::MethodFromString(buf);
if(Method==HttpMethod::Unknown)
	return size;
UINT path_len=reader.ReadString(buf, 256, " ");
size+=path_len;
UINT params_pos=0;
if(StringHelper::Find(buf, "?", &params_pos))
	{
	Path=HttpHelper::PathToString(buf, params_pos);
	Parameters->Set(&buf[params_pos+1]);
	}
else
	{
	Path=HttpHelper::PathToString(buf, path_len);
	}
size+=reader.FindChar("\n");
while(1)
	{
	size+=reader.ReadString(buf, 256, "\r");
	size+=reader.Skip();
	if(buf[0]==0)
		break;
	UINT value_pos=0;
	if(!StringHelper::Find(buf, ":", &value_pos))
		{
		Properties->Add(buf, nullptr);
		continue;
		}
	buf[value_pos]=0;
	value_pos++;
	if(buf[value_pos]==' ')
		value_pos++;
	Handle<String> key=buf;
	Handle<String> value=&buf[value_pos];
	Properties->Add(key, value);
	}
auto cookie=Properties->Get("Cookie");
if(cookie)
	Cookies->Set(cookie->Begin());
Status=HttpStatus::Ok;
return size;
}

SIZE_T HttpRequest::WriteHeaderToStream(OutputStream* stream)
{
SIZE_T size=0;
StreamWriter writer(stream);
size+=writer.Print(HttpHelper::MethodToString(Method));
size+=writer.Print(" ");
size+=writer.Print(Path);
if(Parameters->GetCount()>0)
	{
	size+=writer.Print("?");
	size+=Parameters->WriteToStream(stream);
	}
size+=writer.Print(" HTTP/1.1\r\n");
for(auto it=Properties->Begin(); it->HasCurrent(); it->MoveNext())
	{
	auto key=it->GetKey();
	auto value=it->GetValue();
	size+=writer.Print(key);
	size+=writer.Print(": ");
	size+=writer.Print(value);
	size+=writer.Print("\r\n");
	}
size+=writer.Print("\r\n");
return size;
}

SIZE_T HttpRequest::WriteToStream(OutputStream* stream)
{
SIZE_T size=0;
StreamWriter writer(stream);
size+=writer.Print(HttpHelper::MethodToString(Method));
size+=writer.Print(" ");
size+=writer.Print(Path);
if(Parameters->GetCount()>0)
	{
	size+=writer.Print("?");
	size+=Parameters->WriteToStream(stream);
	}
size+=writer.Print(" HTTP/1.1\r\n");
UINT64 content_size=0;
Handle<String> content_len;
if(Content)
	{
	content_len=Properties->Get("Content-Length");
	if(content_len)
		{
		StringHelper::Scan(content_len->Begin(), "%u", &content_size);
		}
	else
		{
		content_size=Content->Available();
		}
	if(content_size>SIZE_MAX)
		content_size=0;
	}
if(content_size>0)
	{
	if(!content_len)
		Properties->Add("Content-Length", String::Create("%u", content_size));
	Properties->Add("Content-Type", "text/html; charset=UTF-8");
	}
else
	{
	Properties->Remove("Content-Length");
	Properties->Remove("Content-Type");
	}
for(auto it=Properties->Begin(); it->HasCurrent(); it->MoveNext())
	{
	auto key=it->GetKey();
	auto value=it->GetValue();
	size+=writer.Print(key);
	size+=writer.Print(": ");
	size+=writer.Print(value);
	size+=writer.Print("\r\n");
	}
size+=writer.Print("\r\n");
if(Content)
	size+=StreamHelper::Copy(stream, Content, (SIZE_T)content_size);
return size;
}


//==========================
// Con-/Destructors Private
//==========================

HttpRequest::HttpRequest():
Method(HttpMethod::Get)
{
Cookies=HttpParameters::Create();
Parameters=HttpParameters::Create();
}

}}