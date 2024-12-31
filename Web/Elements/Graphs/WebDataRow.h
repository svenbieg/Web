//==============
// WebDataRow.h
//==============

#pragma once


//=======
// Using
//=======

#include "Collections/Vector.h"
#include "Culture/Sentence.h"
#include "Graphics/Color.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {
		namespace Graphs {


//======================
// Forward-Declarations
//======================

class WebGraph;


//=========
// Web-Row
//=========

class WebDataRow: public Object
{
public:
	// Using
	using COLOR=Graphics::COLOR;
	using OutputStream=Storage::Streams::OutputStream;
	using Sentence=Culture::Sentence;
	using ValueVector=Collections::Vector<INT>;

	// Con-/Destructors
	static inline Handle<WebDataRow> Create(WebGraph* Graph, LPCSTR Id, Handle<Sentence> Name, COLOR Color, Handle<ValueVector> Values)
		{
		return new WebDataRow(Graph, Id, Name, Color, Values);
		}

	// Common
	COLOR Color;
	LPCSTR Id;
	Handle<Sentence> Name;
	SIZE_T WriteToStream(OutputStream* Stream, INT Offset=0, UINT Divisor=1, INT Min=INT_MIN, INT Max=INT_MAX-1);
	Handle<ValueVector> Values;

private:
	// Con-/Destructors
	WebDataRow(WebGraph* Graph, LPCSTR Id, Handle<Sentence> Name, COLOR Color, Handle<ValueVector> Values);
};

}}}