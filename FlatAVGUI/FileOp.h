/****************************************************************************\
*
*	File operation functions
*
\****************************************************************************/

#ifndef FILEOP_H_9754
#define FILEOP_H_9754

BOOL DeleteFileToRecycleBin (LPCTSTR szFilePathName);
int DeleteFileEx (LPCTSTR szFilePathName, BOOL bDelPermanent, BOOL bDelLockedFiles);
int MoveRenameFileEx (LPCTSTR szFilePathName, LPCTSTR szDestFolderPath, 
                       BOOL bRenFile, BOOL bMoveFile, BOOL bMoveRenLockedFiles);

#endif