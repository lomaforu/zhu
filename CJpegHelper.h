#pragma once 
#include <string.h> 
#include <stdio.h> 

class CJpegHelper
{
public:
	explicit CJpegHelper(const char* filename) :
		weidth(0), height(0), buffer(NULL), length(0),
		file(filename ? filename : NULL), name(NULL) {}

	~CJpegHelper(void);

private:
	CJpegHelper(CJpegHelper&);
private:
	int weidth;
	int height;
	unsigned char* buffer;
	long length;
	const char* file;
	char* name;
	CJpegHelper& operator=(const CJpegHelper& j);
	int GetSize(unsigned char* buffer, long length);
public:
	int ReadImage();
	int inline GetWidth() const
	{
		return weidth;
	}

	int inline GetHeight() const
	{
		return height;
	}
};