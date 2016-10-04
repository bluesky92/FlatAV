/****************************************************************************\
*
*   FILE:       fvd.h
*
*   PURPOSE:    Functions for manipulating FlatAV database.
*
*   FUNCTIONS:
*       EXPORTS:
*               Fvd_BuildNewDb  - Build new database.
*
\****************************************************************************/

#ifndef FVD_H_FLATAV_
#define FVD_H_FLATAV_

#ifdef __cplusplus
extern "C" {
#endif

#define MD5LEN 16

#define FVD_CDBTBL  0
#define FVD_XDBTBL  1
#define FVD_SDBTBL  2
#define FVD_WDBTBL  3

#define FVD_EWRITE_FVD       -1001   /* Writing Fvd failed */

#define FVD_EOPEN_HDB        -1002   /* Opening HDB file failed */
#define FVD_EINV_HDB         -1003   /* Invalid HDB file format*/
#define FVD_EACCESS_HDB      -1004   /* HDB file couldn't be accessed */

#define FVD_EOPEN_CDB        -1005   /* Opening CDB file failed */
#define FVD_EINV_CDB         -1006   /* Invalid CDB file format*/
#define FVD_EACCESS_CDB      -1007   /* CDB file couldn't be accessed */

#define FVD_EOPEN_XDB        -1008   /* Opening XDB file failed */
#define FVD_EINV_XDB         -1009   /* Invalid XDB file format*/
#define FVD_EACCESS_XDB      -1010   /* XDB file couldn't be accessed */

#define FVD_EOPEN_SDB        -1011   /* Opening SDB file failed */
#define FVD_EINV_SDB         -1012   /* Invalid SDB file format*/
#define FVD_EACCESS_SDB      -1013   /* CDB file couldn't be accessed */

#define FVD_EOPEN_WDB        -1014   /* Opening WDB file failed */
#define FVD_EINV_WDB         -1015   /* Invalid WDB file format*/
#define FVD_EACCESS_WDB      -1016   /* CDB file couldn't be accessed */

#define FVD_EWRITE_CHECKSUM  -1017   /* Writing checksum failed */
#define FVD_EINV_MARK        -1018   /* Invalid FlatAV mark */
#define FVD_EMIN_AV_VER      -1019   /* Minimal AV version not satisfied */
#define FVD_EINV_CHECKSUM    -1020   /* Invalid checksum */
#define FVD_EPARAM           -1021   /* Invalid parameter */

/****************************************************************************/
/* STRUCTS */

typedef struct fvd_block_t
{
    unsigned int size;
    char* data;
    char szMalwareName[31+1];
    unsigned char bMalwareType;
}
FVD_BLOCK, *LPFVD_BLOCK;

typedef struct fvd_header_t
{
    char szMark[6+1];
    char szReleaseDate[8+1];
    unsigned int dwDbMajorVersion;
    unsigned char bDbMinorVersion;
    unsigned short wMinAvMajorVersion;
    unsigned char bMinAvMinorVersion;
    unsigned int dwSignCount;
    unsigned int dwCrc32Checksum;
}
FVD_HEADER, *LPFVD_HEADER;
/*
typedef struct directory_t
{
    unsigned int dwTblOffset;
    unsigned int dwTblCount;
}
FVD_DIRECTORY_ENTRY, *LPFVD_DIRECTORY_ENTRY;

#define FVD_DIRECTORY_COUNT 4

typedef struct fvd_directory_t
{
    FVD_DIRECTORY_ENTRY FvdDirEntry[FVD_DIRECTORY_COUNT];
}
FVD_DIRECTORY, *LPFVD_DIRECTORY;
*/

/* Size: 52 bytes */
typedef struct fvd_cdbrec_t
{
    char szMalwareName[31];
    unsigned char bMalwareType;
    unsigned int dwFileSize;
	unsigned char md5Hash[MD5LEN];
}
FVD_CDBREC, *LPFVD_CDBREC, FVD_WDBREC, *LPFVD_WDBREC;

/* Size: 68 bytes */
typedef struct fvd_xdbrec_t
{
    char szMalwareName[31];
    unsigned char bMalwareType;
    char szFileOffset[16];
    unsigned int dwSignLength;
	unsigned char md5Hash[MD5LEN];
}
FVD_XDBREC, *LPFVD_XDBREC;

#define FVD_MIN_SDBREC_SIZE     52	/* Without FileType and szSignHexStr */

/* Size: 52+ bytes */
typedef struct fvd_sdbrec_t
{
    unsigned int dwRecSize;    /* Real SDB rec size: FVD_MIN_SDBREC_SIZE + strlen(szSignHexStr) */
    char szMalwareName[31];
    unsigned char bMalwareType;
    char szFileOffset[16];  /* Differ from XDBRec's FileOffset, this is the Starting File Offest */
    unsigned char szSignHexStr[1];  /* Not all written to db file, only its length bytes written */
}
FVD_SDBREC, *LPFVD_SDBREC;

/* bFileType values */
#define FVD_TT_ALL      0
#define FVD_TT_PE       1
#define FVD_TT_PE64     2
#define FVD_TT_SCRIPT   3
#define FVD_TT_DOS      4
#define FVD_TT_ELF      5

typedef struct fvd_find_cdbrec_t
{
    unsigned char bTblType; /* 0 = CDBREC, 1 = WDBREC */
    unsigned int dwFileSize;
	unsigned char md5Hash[MD5LEN];
}
FVD_FIND_CWDBREC, *LPFVD_FIND_CWDBREC;

/* FileOffset String's special char */
#define FVD_FO_SECTION  '$'
#define FVD_FO_EP       '%'
#define FVD_FO_EOF      'o'
#define FVD_FO_ANY      'x'

typedef struct
{
    char bFirstChar;    /* Possible values: $, %, o, x and 0 for absolute offset */
    int nSectionIdx;    /* For $, possible values: 0 - 65535, -1 for $x and -2 for $l */
    int iDisp;          /* For $, % and o */
}
FVD_FILEOFFSET, *LPFVD_FILEOFFSET;
/****************************************************************************/


/****************************************************************************/
/* EXPORTED FUNCTIONS */


/****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif 