//=============
// WebPage.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Intermediate.h"
#include "WebEventSource.h"
#include "WebPage.h"

using namespace Concurrency;
using namespace Network::Http;
using namespace Storage;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Web {


//==================
// Con-/Destructors
//==================

WebPage::WebPage()
{
Controls=new WebControlMap();
}


//========
// Common
//========

VOID WebPage::RequestGet(Handle<WebContext> context)
{
auto request=context->Request;
auto response=context->Response;
auto accept=request->Properties->Get("Accept");
if(accept->Contains("text/html"))
	{
	Handle<Intermediate> buf=new Intermediate();
	buf->SetFormat(StreamFormat::UTF8);
	this->WriteToStream(buf, context);
	response->Content=buf;
	response->Status=HttpStatus::Ok;
	}
if(accept->Contains("text/event-stream"))
	{
	auto session=context->Session;
	ScopedLock lock(session->Mutex);
	if(!session->EventSource)
		session->EventSource=new WebEventSource(this);
	lock.Unlock();
	session->EventSource->RequestGet(context);
	}
}

VOID WebPage::RequestNotify(Handle<WebContext> context)
{
auto request=context->Request;
auto params=request->Parameters;
auto id=params->Get("id");
if(id)
	{
	auto control=Controls->Get(id);
	if(control)
		control->OnNotified(context);
	}
auto response=context->Response;
response->Status=HttpStatus::Ok;
}

VOID WebPage::RequestPost(Handle<WebContext> context)
{
auto response=context->Response;
response->Status=HttpStatus::BadRequest;
}

}