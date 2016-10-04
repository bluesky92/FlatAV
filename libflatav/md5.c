#include <windows.h>
#include <Wincrypt.h>
#include <tchar.h>
#include <io.h>
#include "debug.h"

#define BUFFER_SIZE    1024

int md5Buffer(unsigned char* buffer, size_t bufferLen, unsigned char* md5Result, size_t md5ResultSize)
{
	size_t dwBytesRead;
	HCRYPTPROV hProv = 0;
	HCRYPTHASH hHash = 0;
	DWORD dwStatus = 0;
	int retVal = 0;

	if (!CryptAcquireContext(&hProv,
		NULL,
		NULL,
		PROV_RSA_FULL,
		CRYPT_VERIFYCONTEXT))
	{
		dwStatus = GetLastError();
		dbg_printf("CryptAcquireContext failed: %d\n", dwStatus);
		return -1;
	}

	if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
	{
		dwStatus = GetLastError();
		dbg_printf("CryptCreateHash failed: %d\n", dwStatus);
		CryptReleaseContext(hProv, 0);
		return -1;
	}

	dwBytesRead = bufferLen;
	if (!CryptHashData(hHash, buffer, dwBytesRead, 0))
	{
		dwStatus = GetLastError();
		dbg_printf("CryptHashData failed: %d\n", dwStatus);
		CryptReleaseContext(hProv, 0);
		CryptDestroyHash(hHash);
		return -1;
	}

	dwBytesRead = md5ResultSize;
	if (!CryptGetHashParam(hHash, HP_HASHVAL, md5Result, &dwBytesRead, 0))
	{
		dwStatus = GetLastError();
		dbg_printf("CryptGetHashParam failed: %d\n", dwStatus);
		retVal = -1;
	}

	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);

	return retVal;
}

int md5File(int fileHandle, size_t fileLen, unsigned char* md5Result, size_t md5ResultSize)
{
    unsigned char buffer[BUFFER_SIZE];
    size_t dwBytesRead;
	HCRYPTPROV hProv = 0;
	HCRYPTHASH hHash = 0;
	DWORD dwStatus = 0;
	int retVal = 0;

	if (!CryptAcquireContext(&hProv,
		NULL,
		NULL,
		PROV_RSA_FULL,
		CRYPT_VERIFYCONTEXT))
	{
		dwStatus = GetLastError();
		dbg_printf("CryptAcquireContext failed: %d\n", dwStatus);
		return -1;
	}

	if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
	{
		dwStatus = GetLastError();
		dbg_printf("CryptCreateHash failed: %d\n", dwStatus);
		CryptReleaseContext(hProv, 0);
		return -1;
	}

    do {
        dwBytesRead = _read (fileHandle, buffer, sizeof(buffer));
        if (dwBytesRead == 0)
            break;

		if (dwBytesRead == -1)
		{
			dbg_printf("ReadFile failed\n");
			CryptReleaseContext(hProv, 0);
			CryptDestroyHash(hHash);
			return -1;
		}
		
		if (!CryptHashData(hHash, buffer, dwBytesRead, 0))
		{
			dwStatus = GetLastError();
			dbg_printf("CryptHashData failed: %d\n", dwStatus);
			CryptReleaseContext(hProv, 0);
			CryptDestroyHash(hHash);
			return -1;
		}

        fileLen -= dwBytesRead;
    } while (fileLen > 0);

	dwBytesRead = md5ResultSize;
	if (!CryptGetHashParam(hHash, HP_HASHVAL, md5Result, &dwBytesRead, 0))
	{
		dwStatus = GetLastError();
		dbg_printf("CryptGetHashParam failed: %d\n", dwStatus);
		retVal = -1;
	}

	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);

    return retVal;
}
