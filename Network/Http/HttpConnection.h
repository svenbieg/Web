//==================
// HttpConnection.h
//==================

#pragma once


//=======
// Using
//=======

#include "Network/Tcp/TcpConnection.h"
#include "Network/Tls/TlsConnection.h"
#include "Storage/File.h"
#include "HttpResponse.h"
#include "HttpRequest.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//=======
// Flags
//=======

enum class HttpConnectionFlags: UINT
{
None=0,
Protected=1
};


//=================
// HTTP-Connection
//=================

class HttpConnection: public Storage::Streams::RandomAccessStream
{
public:
	// Using
	using File=Storage::File;
	using TcpConnection=Network::Tcp::TcpConnection;
	using TlsConnection=Network::Tls::TlsConnection;

	// Con-/Destructors
	static inline Handle<HttpConnection> Create(Handle<TcpConnection> Connection) { return new HttpConnection(Connection); }
	static inline Handle<HttpConnection> Create(Handle<TlsConnection> Connection) { return new HttpConnection(Connection); }

	// Common
	VOID Close();
	Handle<HttpRequest> GetRequest();
	Handle<HttpResponse> GetResponse();
	inline BOOL IsProtected()const { return FlagHelper::Get(m_Flags, HttpConnectionFlags::Protected); }
	VOID Send(Handle<HttpRequest> Request);
	VOID Send(Handle<HttpResponse> Response);
	BOOL SendFile(Handle<File> File, Handle<String> Path=nullptr);

	// Input-Stream
	SIZE_T Available()override;
	SIZE_T Read(VOID* Buffer, SIZE_T Size)override;

	// Output-Stream
	VOID Flush()override;
	SIZE_T Write(VOID const* Buffer, SIZE_T Size)override;

private:
	// Con-/Destructors
	HttpConnection(Handle<TcpConnection> Connection);
	HttpConnection(Handle<TlsConnection> Connection);

	// Common
	Handle<RandomAccessStream> m_Connection;
	HttpConnectionFlags m_Flags;
};

}}