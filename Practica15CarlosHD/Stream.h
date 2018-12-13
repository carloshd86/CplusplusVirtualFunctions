#pragma once

class CStream
{

public:

	virtual void * Open() =0;
	virtual int Close() =0;
	virtual int Read(char * outputBuffer, unsigned int charactersToRead) =0;
	virtual int Write(const char * inputBuffer, unsigned int inputLength) =0;

};