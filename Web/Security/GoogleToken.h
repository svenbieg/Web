//===============
// GoogleToken.h
//===============

#pragma once


//===========
// Namespace
//===========

namespace Web {
	namespace Security {


//==============
// Google-Token
//==============

class GoogleToken: public Object
{
public:
	// Con-/Destructors
	static inline Handle<GoogleToken> Create(LPSTR Response, UINT Length)
		{
		return new GoogleToken(Response, Length);
		}

	// Common
	Handle<String> Email;

private:
	// Con-/Destructors
	GoogleToken(LPSTR Response, UINT Length);
};

}}