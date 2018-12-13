#include "stdafx.h"
#include "FileNoStream.h"

void* CFileNoStream::Open()
{
	void* result = nullptr;

	printf("\nCFileNoStream: Open\n");

	return result;
}

int CFileNoStream::Close()
{
	int result = 0;

	printf("\nCFileNoStream: Close\n");

	return result;
}

int CFileNoStream::Read(char * outputBuffer, unsigned int charactersToRead)
{
	int result = 0;

	printf("\nCFileNoStream: Read\n");

	return result;
}

int CFileNoStream::Write(const char * inputBuffer, unsigned int inputLength)
{
	int result = 0;

	printf("\nCFileNoStream: Write\n");

	return result;
}