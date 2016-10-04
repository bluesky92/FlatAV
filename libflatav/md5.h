#ifndef MD5FILE_H
#define MD5FILE_H

//#include <tchar.h>

#ifdef __cplusplus
extern "C" {
#endif

	int md5Buffer(unsigned char* buffer, size_t bufferLen, char* md5Result, size_t md5ResultSize);
	int md5File(int fileHandle, size_t fileLen, char* md5Result, size_t md5ResultSize);

#ifdef __cplusplus
}
#endif

#endif
