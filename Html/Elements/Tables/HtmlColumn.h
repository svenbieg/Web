//==============
// HtmlColumn.h
//==============

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/OutputStream.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {
		namespace Tables {


//======================
// Forward-Declarations
//======================

class HtmlTable;


//=============
// HTML-Column
//=============

class HtmlColumn: public Object
{
public:
	// Using
	using OutputStream=Storage::Streams::OutputStream;

	// Con-/Destructors
	static inline Handle<HtmlColumn> Create(HtmlTable* Table, LPCSTR Style=nullptr)
		{
		return new HtmlColumn(Table, Style);
		}

	// Common
	SIZE_T WriteToStream(OutputStream* Stream, UINT Level);

private:
	// Con-/Destructors
	HtmlColumn(HtmlTable* Table, LPCSTR Style);

	// Common
	LPCSTR m_Style;
};

}}}