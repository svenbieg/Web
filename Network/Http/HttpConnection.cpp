//====================
// HttpConnection.cpp
//====================

#include "pch.h"


//=======
// Using
//=======

#include "HttpConnection.h"

using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//========
// Common
//========

VOID HttpConnection::Close()
{
m_Connection=nullptr;
m_Flags=HttpConnectionFlags::None;
}

Handle<HttpRequest> HttpConnection::GetRequest()
{
auto request=HttpRequest::Create();
request->ReadFromStream(this);
return request;
}

Handle<HttpResponse> HttpConnection::GetResponse()
{
auto response=HttpResponse::Create();
response->ReadFromStream(this);
return response;
}

VOID HttpConnection::Send(Handle<HttpRequest> request)
{
request->WriteToStream(this);
m_Connection->Flush();
}

VOID HttpConnection::Send(Handle<HttpResponse> response)
{
response->WriteToStream(this);
m_Connection->Flush();
}

BOOL HttpConnection::SendFile(Handle<File> file, Handle<String> path)
{
if(!file)
	return false;
auto request=HttpRequest::Create();
request->Content=file;
request->Method=HttpMethod::Post;
request->Parameters->Set("name", file->GetName());
request->Path=path;
request->Properties->Set("Content-Type", "application/octet-stream");
UINT64 pos=0;
UINT64 size=file->GetSize();
constexpr UINT64 chunk_size=1024*1024;
while(pos<size)
	{
	UINT64 copy=TypeHelper::Min(size-pos, chunk_size);
	UINT64 end=pos+copy;
	request->Properties->Set("Content-Length", String::Create("%u", copy));
	request->Properties->Set("Content-Range", String::Create("%u-%u/%u", pos, end, size));
	request->Properties->Set("Connection", end<size? "Keep-Alive": "Close");
	Send(request);
	auto response=GetResponse();
	if(response->Status!=HttpStatus::Ok)
		return false;
	pos+=copy;
	}
return true;
}


//==============
// Input-Stream
//==============

SIZE_T HttpConnection::Available()
{
return m_Connection->Available();
}

SIZE_T HttpConnection::Read(VOID* buf, SIZE_T size)
{
return m_Connection->Read(buf, size);
}


//===============
// Output-Stream
//===============

VOID HttpConnection::Flush()
{
m_Connection->Flush();
}

SIZE_T HttpConnection::Write(VOID const* buf, SIZE_T size)
{
return m_Connection->Write(buf, size);
}


//==========================
// Con-/Destructors Private
//==========================

HttpConnection::HttpConnection(Handle<TcpConnection> con):
m_Connection(con),
m_Flags(HttpConnectionFlags::None)
{
m_Format=StreamFormat::Ansi;
}

HttpConnection::HttpConnection(Handle<TlsConnection> con):
m_Connection(con),
m_Flags(HttpConnectionFlags::None)
{
m_Format=StreamFormat::Ansi;
}

}}