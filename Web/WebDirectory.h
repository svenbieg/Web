//================
// WebDirectory.h
//================

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/OutputStream.h"
#include "Storage/Directory.h"
#include "WebPage.h"


//===========
// Namespace
//===========

namespace Web {


//===============
// Web-Directory
//===============

class WebDirectory: public WebPage
{
private:
	// Using
	using Directory=Storage::Directory;
	using OutputStream=Storage::Streams::OutputStream;

public:
	// Con-/Destructors
	static inline Handle<WebDirectory> Create(Handle<Directory> Directory)
		{
		return new WebDirectory(Directory);
		}

	// Common
	SIZE_T WriteToStream(OutputStream* Stream, Handle<String> Root);

private:
	// Con-/Destructors
	WebDirectory(Handle<Directory> Directory): m_Directory(Directory) {}

	// Common
	Handle<Directory> m_Directory;
};

}