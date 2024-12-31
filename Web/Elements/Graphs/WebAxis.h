//===========
// WebAxis.h
//===========

#pragma once


//=======
// Using
//=======

#include "Collections/Map.h"
#include "Culture/Sentence.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {
		namespace Graphs {


//==========
// Web-Axis
//==========

class WebAxis: public Object
{
public:
	// Using
	using Sentence=Culture::Sentence;
	using PointMap=Collections::Map<INT, Handle<Sentence>>;

	// Con-/Destructors
	static inline Handle<WebAxis> Create() { return new WebAxis(); }

	// Common
	Handle<Sentence> Name;
	Handle<PointMap> Points;
	Handle<Sentence> Unit;

private:
	// Con-/Destructors
	WebAxis();
};

}}}