//===========
// WebSite.h
//===========

#pragma once


//=======
// Using
//=======

#include "Collections/Map.h"
#include "Network/Http/HttpConnection.h"
#include "Storage/Workspace.h"
#include "WebAccount.h"
#include "WebServer.h"


//===========
// Namespace
//===========

namespace Web {


//==========
// Web-Site
//==========

class WebSite: public Object
{
public:
	// Using
	using HttpConnection=Network::Http::HttpConnection;
	using WebAccountMap=Collections::Map<Handle<String>, Handle<WebAccount>>;
	using Workspace=Storage::Workspace;

	// Con-/Destructors
	~WebSite() { s_Current=nullptr; }
	static inline Handle<WebSite> Create(Handle<String> HostName=nullptr)
		{
		return new WebSite(HostName);
		}
	static inline WebSite* Get() { return s_Current; }

	// Common
	Handle<WebAccountMap> Accounts;
	Handle<Workspace> Protected;
	Handle<Workspace> Public;

protected:
	// Con-/Destructors
	WebSite(Handle<String> HostName=nullptr);

private:
	// Common
	Handle<WebServer> m_WebServer;
	static WebSite* s_Current;
};

}