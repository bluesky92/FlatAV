/****************************************************************************\
*
*	Memory process functions
*
\****************************************************************************/

#ifndef MEMORYOP_H_9754
#define MEMORYOP_H_9754

BOOL SuspendResumeProcess (DWORD dwProcessId, BOOL bResume);
BOOL KillProcess (DWORD dwProcessId);
BOOL StopAndDeleteService (LPCTSTR szServiceName, BOOL bIsActive);

#endif