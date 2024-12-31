//=============
// HtmlLabel.h
//=============

#pragma once


//=======
// Using
//=======

#include "HtmlNode.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//============
// HTML-Label
//============

class HtmlLabel: public HtmlNode
{
public:
	// Con-/Destructors
	static inline Handle<HtmlLabel> Create(HtmlNode* Parent, Handle<Sentence> Label, Handle<Sentence> Unit=nullptr)
		{
		return new HtmlLabel(Parent, Label, Unit);
		}

protected:
	// Common
	SIZE_T WriteElementsToStream(OutputStream* Stream, WebContext* Context, UINT Level)override;

private:
	// Con-/Destructors
	HtmlLabel(HtmlNode* Parent, Handle<Sentence> Label, Handle<Sentence> Unit);

	// Common
	Handle<Sentence> m_Label;
	Handle<Sentence> m_Unit;
};

}}