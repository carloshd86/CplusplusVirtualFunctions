#include "stdafx.h"
#include "Com.h"


void* CCom::Open()
{
	void* result = nullptr;

	printf("\nCCom: Open\n");

	return result;
}

int CCom::Close()
{
	int result = 0;

	printf("\nCCom: Close\n");

	return result;
}

int CCom::Read(char * outputBuffer, unsigned int charactersToRead)
{
	int result = 0;

	printf("\nCCom: Read\n");

	return result;
}

int CCom::Write(const char * inputBuffer, unsigned int inputLength)
{
	int result = 0;

	printf("\nCCom: Write\n");

	return result;
}