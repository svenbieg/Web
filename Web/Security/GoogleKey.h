//=============
// GoogleKey.h
//=============

#pragma once


//=======
// Using
//=======

#include "Security/Rsa/RsaKey.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Security {


//============
// Google-Key
//============

class GoogleKey: public ::Security::Rsa::RsaKey
{
public:
	// Con-/Destructors
	static inline Handle<GoogleKey> Create(Handle<String> Id, Handle<Buffer> Exponent, Handle<Buffer> Modulus)
		{
		return new GoogleKey(Id, Exponent, Modulus);
		}

	// Common
	static Handle<GoogleKey> Get(Handle<String> Id);
	Handle<String> Id;

private:
	// Con-/Destructors
	GoogleKey(Handle<String> Id, Handle<Buffer> Exponent, Handle<Buffer> Modulus);
};

}}