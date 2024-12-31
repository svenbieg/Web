//====================
// WebEventSource.cpp
//====================

#include "pch.h"


//=======
// Using
//=======

#include "Concurrency/DispatchedQueue.h"
#include "Storage/Streams/StreamWriter.h"
#include "Storage/Intermediate.h"
#include "Web/Elements/WebVariable.h"
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


//=========
// Scripts
//=========

constexpr CHAR STR_EVENT_SOURCE_SCRIPT[]=
"\r\n"
"function webPageUpdateElements(arg)\r\n"
"{\r\n"
"var params=arg.split(';');\r\n"
"params.forEach(function (param) {\r\n"
"\tif(param==\"\")\r\n"
"\t\treturn;\r\n"
"\tvar op=\"=\";\r\n"
"\tif(param.indexOf(\"+=\")>0)\r\n"
"\t\top=\"+=\";\r\n"
"\tvar pair=param.split(op);\r\n"
"\tvar key=pair[0];\r\n"
"\tvar value=pair[1];\r\n"
"\tvar element=document.getElementById(key);\r\n"
"\tif(element==null)\r\n"
"\t\treturn;\r\n"
"\tif(element.tagName.toLocaleLowerCase()=='input') {\r\n"
"\t\tvar edit=element;\r\n"
"\t\tif(op==\"=\")\r\n"
"\t\t\tedit.value=\"\";\r\n"
"\t\tedit.value+=value;\r\n"
"\t\treturn;\r\n"
"\t\t}\r\n"
"\tif(element.tagName.toLowerCase()=='table')\r\n"
"\t\telement=element.lastElementChild;\r\n"
"\tif(op==\"=\")\r\n"
"\t\telement.innerHTML=\"\";\r\n"
"\telement.innerHTML+=value;\r\n"
"\t});\r\n"
"}\r\n\r\n"
"\r\n"
"var event_source=new EventSource(window.location.href);\r\n"
"event_source.onmessage=function(e)\r\n"
"\t{\r\n"
"\twebPageUpdateElements(e.data);\r\n"
"\t}\r\n";


//==================
// Con-/Destructors
//==================

WebEventSource::~WebEventSource()
{
m_WebPage->Changed.Remove(this);
}


//========
// Common
//========

VOID WebEventSource::RequestGet(Handle<WebContext> context)
{
ScopedLock lock(m_Mutex);
auto response=context->Response;
while(1)
	{
	if(FlagHelper::Get(m_Flags, WebEventSourceFlags::Closing))
		{
		response->Status=HttpStatus::ConnectionClosed;
		return;
		}
	if(FlagHelper::Get(m_Flags, WebEventSourceFlags::Event))
		{
		FlagHelper::Clear(m_Flags, WebEventSourceFlags::Event);
		auto lng=context->Language;
		auto buf=Intermediate::Create();
		buf->SetFormat(StreamFormat::UTF8);
		StreamWriter writer(buf);
		writer.Print("data: ");
		for(auto it=m_WebPage->Controls->First(); it->HasCurrent(); it->MoveNext())
			{
			auto control=it->GetValue();
			auto var=dynamic_cast<WebVariable*>(control);
			if(!var)
				continue;
			var->UpdateToStream(buf, context);
			}
		writer.Print("\nretry: 0\n\n");
		response->Properties->Set("Content-type", "text/event-stream; charset=utf-8");
		response->Content=buf;
		response->Status=HttpStatus::Ok;
		return;
		}
	FlagHelper::Set(m_Flags, WebEventSourceFlags::Waiting);
	m_Signal.Wait(lock);
	FlagHelper::Clear(m_Flags, WebEventSourceFlags::Waiting);
	}
}


//==========================
// Con-/Destructors Private
//==========================

WebEventSource::WebEventSource(WebPage* page):
m_Flags(WebEventSourceFlags::None),
m_WebPage(page)
{
page->AddScript(STR_EVENT_SOURCE_SCRIPT);
page->Changed.Add(this, &WebEventSource::OnPageChanged);
}


//================
// Common Private
//================

VOID WebEventSource::DoResponse()
{
m_Signal.Trigger();
}

VOID WebEventSource::OnPageChanged()
{
ScopedLock lock(m_Mutex);
if(!FlagHelper::Get(m_Flags, WebEventSourceFlags::Event))
	{
	FlagHelper::Set(m_Flags, WebEventSourceFlags::Event);
	DispatchedQueue::Append(this, &WebEventSource::DoResponse);
	}
}

}