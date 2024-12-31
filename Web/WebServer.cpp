//===============
// WebServer.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StreamHelper.h"
#include "Storage/Buffer.h"
#include "Web/Security/GoogleToken.h"
#include "RandomHelper.h"
#include "WebPage.h"
#include "WebServer.h"
#include "WebSite.h"

using namespace Concurrency;
using namespace Devices;
using namespace Network::Http;
using namespace Storage;
using namespace Storage::Streams;
using namespace Web::Security;


//===========
// Namespace
//===========

namespace Web {


//========
// Common
//========

VOID WebServer::Close()
{
if(m_Clock)
	{
	m_Clock->Hour.Remove(this);
	m_Clock=nullptr;
	}
m_HttpServer=nullptr;
m_HttpsServer=nullptr;
m_Sessions.clear();
m_WebSite=nullptr;
}

VOID WebServer::Listen()
{
m_HttpServer->Listen();
if(m_HttpsServer)
	m_HttpsServer->Listen();
}


//==========================
// Con-/Destructors Private
//==========================

WebServer::WebServer(WebSite* web_site, Handle<String> host_name):
m_WebSite(web_site)
{
m_HttpServer=HttpServer::Create();
m_HttpServer->ConnectionReceived.Add(this, &WebServer::OnConnectionReceived);
if(host_name)
	{
	m_HttpsServer=HttpsServer::Create(host_name);
	m_HttpsServer->ConnectionReceived.Add(this, &WebServer::OnConnectionReceived);
	}
m_Clock=Clock::Get();
m_Clock->Hour.Add(this, &WebServer::OnClockHour);
}


//================
// Common Private
//================

VOID WebServer::DoAccept(Handle<HttpConnection> con)
{
auto request=con->GetRequest();
auto sid=request->Cookies->Get("sid");
ScopedLock lock(m_Mutex);
Handle<WebSession> session;
if(!m_Sessions.try_get(sid, &session))
	{
	while(1)
		{
		sid=RandomHelper::GetString(16);
		if(!m_Sessions.contains(sid))
			break;
		}
	session=WebSession::Create(sid);
	m_Sessions.set(sid, session);
	}
lock.Unlock();
auto response=HttpResponse::Create(HttpStatus::BadRequest);
response->Cookies->Set("sid", sid);
auto host_name=request->Properties->Get("Host");
if(!host_name)
	return;
ScopedLock session_lock(session->Mutex);
auto doc_root=m_WebSite->Public;
if(con->IsProtected())
	{
	doc_root=m_WebSite->Protected;
	auto account=session->Account;
	if(account)
		doc_root=account->DocumentRoot;
	}
else
	{
	session->Account=nullptr;
	}
session->TimeOut=GetTickCount64()+60*60*1000;
session_lock.Unlock();
auto context=WebContext::Create(m_WebSite);
context->Connection=con;
context->DocumentRoot=doc_root;
context->HostName=host_name;
context->Language=request->GetLanguage();
context->Protocol=con->IsProtected()? "https": "http";
context->Request=request;
context->Response=response;
context->Session=session;
context->TimeStamp=GetTickCount64();
context->Url=String::Create("%s://%s%s", context->Protocol, context->HostName, request->Path);
switch(request->Method)
	{
	case HttpMethod::Get:
		{
		DoGet(context);
		break;
		}
	case HttpMethod::Notify:
		{
		DoNotify(context);
		break;
		}
	case HttpMethod::Post:
		{
		DoPost(context);
		break;
		}
	default:
		break;
	}
con->Send(response);
}

VOID WebServer::DoGet(Handle<WebContext> context)
{
auto request=context->Request;
auto response=context->Response;
auto path=request->Path;
if(path=="/"||path=="/gen_204")
	{
	auto url=String::Create("%s://%s/index.html", context->Protocol, context->HostName);
	response->Status=HttpStatus::MovedPermanently;
	response->Properties->Add("Location", url);
	return;
	}
auto doc_root=context->DocumentRoot;
Handle<Object> obj=doc_root->Get(path);
if(!obj)
	{
	response->Status=HttpStatus::SiteNotFound;
	return;
	}
auto web_page=obj.As<WebPage>();
if(web_page)
	{
	web_page->RequestGet(context);
	return;
	}
auto file=obj.As<File>();
if(file)
	{
	if(Failed(file->Create(FileCreateMode::OpenExisting, FileAccessMode::ReadOnly, FileShareMode::ShareRead)))
		{
		response->Status=HttpStatus::InternalServerError;
		return;
		}
	auto file_name=file->GetName();
	UINT64 file_size=file->GetSize();
	response->Content=file;
	response->Properties->Set("Content-Disposition", String::Create("attachment; filename=%s", file_name->Begin()));
	response->Properties->Set("Content-Length", String::Create("%u", file_size));
	response->Status=HttpStatus::Ok;
	return;
	}
}

VOID WebServer::DoNotify(Handle<WebContext> context)
{
auto request=context->Request;
auto response=context->Response;
auto path=request->Path;
auto doc_root=context->DocumentRoot;
auto web_page=doc_root->Get(path).As<WebPage>();
if(!web_page)
	{
	response->Status=HttpStatus::SiteNotFound;
	return;
	}
web_page->RequestNotify(context);
}

VOID WebServer::DoPost(Handle<WebContext> context)
{
auto request=context->Request;
auto path=request->Path;
auto doc_root=context->DocumentRoot;
auto obj=doc_root->Get(path);
auto web_page=obj.As<WebPage>();
if(web_page)
	{
	web_page->RequestPost(context);
	return;
	}
auto response=context->Response;
while(1)
	{
	auto range=request->Properties->Get("Content-Range");
	if(!range)
		return;
	UINT64 file_start=0;
	UINT64 file_end=0;
	UINT64 file_size=0;
	if(range->Scan("%u-%u/%u", &file_start, &file_end, &file_size)!=3)
		return;
	Handle<File> file;
	if(file_start==0)
		{
		auto name=request->Parameters->Get("name");
		auto path=String::Create("%s/%s", request->Path, name);
		file=doc_root->CreateFile(path, FileCreateMode::CreateAlways, FileAccessMode::ReadWrite, FileShareMode::ShareRead);
		if(file)
			{
			if(!file->SetSize(file_size))
				file=nullptr;
			}
		}
	if(!file)
		{
		response->Status=HttpStatus::InternalServerError;
		return;
		}
	auto con=context->Connection;
	SIZE_T copy=(SIZE_T)(file_end-file_start);
	SIZE_T written=StreamHelper::Copy(file, con, copy);
	if(written!=copy)
		{
		file=nullptr;
		response->Status=HttpStatus::InternalServerError;
		return;
		}
	response->Status=HttpStatus::Ok;
	file_start+=written;
	if(file_start>=file_size)
		{
		file->Flush();
		file=nullptr;
		return;
		}
	response->KeepAlive(true);
	con->Send(response);
	request=con->GetRequest();
	}
}

VOID WebServer::OnClockHour()
{
ScopedLock lock(m_Mutex);
auto time=GetTickCount64();
for(auto it=m_Sessions.begin(); it.has_current();)
	{
	auto item=it.get_current();
	auto session=item.get_value();
	if(session->TimeOut<time)
		{
		it.remove_current();
		continue;
		}
	it.move_next();
	}
}

VOID WebServer::OnConnectionReceived(Handle<HttpConnection> con)
{
Task::Create(this, [this, con]() { DoAccept(con); });
}

}