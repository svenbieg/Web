//===============
// HttpMessage.h
//===============

#pragma once


//=======
// Using
//=======

#include "Collections/Map.h"
#include "Storage/Streams/InputStream.h"
#include "Storage/Streams/OutputStream.h"
#include "HttpHelper.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//==============
// Http-Message
//==============

class HttpMessage: public Object
{
public:
	// Using
	using InputStream=Storage::Streams::InputStream;
	using OutputStream=Storage::Streams::OutputStream;
	using PropertyMap=Collections::Map<Handle<String>, Handle<String>>;

	// Common
	virtual VOID Clear();
	Handle<InputStream> Content;
	BOOL KeepAlive();
	VOID KeepAlive(BOOL KeepAlive);
	Handle<PropertyMap> Properties;
	virtual SIZE_T ReadFromStream(InputStream* Stream)=0;
	HttpStatus Status;
	virtual SIZE_T WriteToStream(OutputStream* Stream)=0;

protected:
	// Con-/Destructors
	HttpMessage(HttpStatus Status=HttpStatus::Ok);
};

}}
