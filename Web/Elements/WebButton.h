//=============
// WebButton.h
//=============

#pragma once


//=======
// Using
//=======

#include "WebControl.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//============
// Web-Button
//============

class WebButton: public WebControl
{
public:
	// Con-/Destructors
	static inline Handle<WebButton> Create(HtmlNode* Parent, Handle<String> Id, Handle<Sentence> Text=nullptr)
		{
		return new WebButton(Parent, Id, Text);
		}

	// Common
	Event<WebButton, Handle<WebContext>> Clicked;
	VOID OnNotified(Handle<WebContext> Context)override;
	LPCSTR Script;

protected:
	// Common
	SIZE_T WriteAttributesToStream(OutputStream* Stream, WebContext* Context)override;

private:
	// Con-/Destructors
	WebButton(HtmlNode* Parent, Handle<String> Id, Handle<Sentence> Text);
};

}}