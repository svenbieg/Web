//============
// WebInput.h
//============

#pragma once


//=======
// Using
//=======

#include "WebVariable.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//============
// Input-Type
//============

enum class WebInputType
{
Text,
Number,
Password
};


//===========
// Web-Input
//===========

class WebInput: public WebVariable
{
public:
	// Con-/Destructors
	~WebInput();
	static inline Handle<WebInput> Create(HtmlNode* Parent, Handle<Variable> Variable, Handle<String> Id=nullptr, WebInputType InputType=WebInputType::Text)
		{
		return new WebInput(Parent, Variable, Id, InputType);
		}

	// Common
	VOID OnNotified(Handle<WebContext> Context)override;
	SIZE_T UpdateToStream(OutputStream* Stream, WebContext* Context)override;

protected:
	// Common
	SIZE_T WriteAttributesToStream(OutputStream* Stream, WebContext* Context)override;

private:
	// Con-/Destructors
	WebInput(HtmlNode* Parent, Handle<Variable> Variable, Handle<String> Id, WebInputType InputType);

	// Common
	VOID OnVariableChanged();
	WebInputType m_InputType;
	UINT64 m_TimeChanged;
	Handle<Variable> m_Variable;
};

}}