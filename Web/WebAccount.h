//==============
// WebAccount.h
//==============

#pragma once


//=======
// Using
//=======

#include "Storage/Workspace.h"


//===========
// Namespace
//===========

namespace Web {


//======================
// Forward-Declarations
//======================

class WebSite;


//=============
// Web-Account
//=============

class WebAccount: public Object
{
public:
	// Using
	using Workspace=Storage::Workspace;

	// Con-/Destructors
	static inline Handle<WebAccount> Create(WebSite* WebSite, Handle<String> Email, Handle<String> Name)
		{
		return new WebAccount(WebSite, Email, Name);
		}

	// Common
	Handle<Workspace> DocumentRoot;
	Handle<String> const Email;
	Handle<String> const Name;

private:
	// Con-/Destructors
	WebAccount(WebSite* WebSite, Handle<String> Email, Handle<String> Name);
};

}