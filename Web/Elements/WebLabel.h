//============
// WebLabel.h
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


//===========
// Web-Label
//===========

class WebLabel: public WebVariable
{
public:
	// Con-/Destructors
	~WebLabel();
	static inline Handle<WebLabel> Create(HtmlNode* Parent, Handle<Variable> Variable, Handle<String> Id=nullptr)
		{
		return new WebLabel(Parent, Variable, Id);
		}

	// Common
	SIZE_T UpdateToStream(OutputStream* Stream, WebContext* Context)override;

protected:
	// Common
	SIZE_T WriteElementsToStream(OutputStream* Stream, WebContext* Context, UINT Level)override;

private:
	// Con-/Destructors
	WebLabel(HtmlNode* Parent, Handle<Variable> Variable, Handle<String> Id);

	// Common
	VOID OnVariableChanged();
	Handle<Variable> m_Variable;
	UINT64 m_TimeChanged;
};

}}