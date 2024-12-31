//==============
// JavaScript.h
//==============

#pragma once


//=======
// Using
//=======

#include "Collections/list.hpp"
#include "Storage/Streams/OutputStream.h"
#include "Web/WebContext.h"
#include "Function.h"


//======================
// Forward-Declarations
//======================

namespace Html
{
class HtmlDocument;
}


//===========
// Namespace
//===========

namespace Java {


//=============
// Java-Script
//=============

class JavaScript: public Object
{
public:
	// Using
	using GlobalsList=Collections::list<LPCSTR>;
	using HtmlDocument=Html::HtmlDocument;
	using OutputStream=Storage::Streams::OutputStream;
	using WebContext=Web::WebContext;

	// Types
	typedef Function<SIZE_T(OutputStream*, WebContext*)> JavaFunction;
	typedef Collections::list<JavaFunction> JavaFunctionList;

	// Con-/Destructors
	static inline Handle<JavaScript> Create() { return new JavaScript(); }

	// Common
	VOID Add(LPCSTR Global);
	VOID Add(JavaFunction Function);
	SIZE_T WriteToStream(OutputStream* Stream, WebContext* Context);

private:
	// Con-/Destructors
	JavaScript() {}

	// Common
	JavaFunctionList m_Functions;
	GlobalsList m_Globals;
};

}