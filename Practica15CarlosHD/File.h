#pragma once

#include "stdafx.h"
#include "Stream.h"

class CFile : public CStream
{
public:
	CFile();

	void* Open();
	int Close();
	int Read(char * outputBuffer, unsigned int charactersToRead);
	int Write(const char * inputBuffer, unsigned int inputLength);

	int m_foo1;
	int m_foo2;
};