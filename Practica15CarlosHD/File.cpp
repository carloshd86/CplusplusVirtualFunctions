#include "stdafx.h"
#include "File.h"


// Constructor

CFile::CFile()
{
	Open();
	m_foo1 = 999111;
}


// Public

void* CFile::Open()
{
	void* result = nullptr;

	printf("\nCFile: Open %d\n", m_foo1);

	return result;
}

int CFile::Close()
{
	int result = 0;

	printf("\nCFile: Close\n");

	return result;
}

int CFile::Read(char * outputBuffer, unsigned int charactersToRead)
{
	int result = 0;

	printf("\nCFile: Read\n");

	return result;
}

int CFile::Write(const char * inputBuffer, unsigned int inputLength)
{
	int result = 0;

	printf("\nCFile: Write\n");

	return result;
}