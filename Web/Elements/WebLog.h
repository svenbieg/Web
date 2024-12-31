//==========
// WebLog.h
//==========

#pragma once


//=======
// Using
//=======

#include "Collections/Log.h"
#include "WebButton.h"
#include "WebVariable.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//=========
// Web-Log
//=========

class WebLog: public WebVariable
{
public:
	// Using
	using Log=Collections::Log;

	// Con-/Destructors
	~WebLog();
	static inline Handle<WebLog> Create(HtmlNode* Parent, Handle<String> Id, Handle<Log> Log)
		{
		return new WebLog(Parent, Id, Log);
		}

	// Common
	SIZE_T UpdateToStream(OutputStream* Stream, WebContext* Context)override;
	SIZE_T WriteToStream(OutputStream* Stream, WebContext* Context, UINT Level)override;

private:
	// Con-/Destructors
	WebLog(HtmlNode* Parent, Handle<String> Id, Handle<Log> Log);

	// Common
	VOID OnClearButtonClicked();
	VOID OnLogChanged();
	Handle<Log> m_Log;
	UINT64 m_TimeChanged;
};

}}