#pragma once

#include "stdafx.h"
#include "Stream.h"

class CCom : public CStream
{
public:
	void* Open();
	int Close();
	int Read(char * outputBuffer, unsigned int charactersToRead);
	int Write(const char * inputBuffer, unsigned int inputLength);
};