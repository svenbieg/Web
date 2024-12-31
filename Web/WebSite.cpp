//=============
// WebSite.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Filesystem/Directory.h"
#include "WebSite.h"

using namespace Storage;


//===========
// Namespace
//===========

namespace Web {


//============================
// Con-/Destructors Protected
//============================

WebSite::WebSite(Handle<String> host_name)
{
s_Current=this;
Accounts=WebAccountMap::Create();
Public=Workspace::Create("Public");
auto public_dir=Filesystem::Directory::Open("Public");
Public->AddDirectory(public_dir);
if(host_name)
	{
	Protected=Workspace::Create("Protected");
	Protected->AddDirectory(Public);
	auto protected_dir=Filesystem::Directory::Open("Protected");
	Protected->AddDirectory(protected_dir);
	}
m_WebServer=WebServer::Create(this, host_name);
m_WebServer->Listen();
}


//================
// Common Private
//================

WebSite* WebSite::s_Current=nullptr;

}