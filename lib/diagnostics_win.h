// This file is part of BOINC.
// http://boinc.berkeley.edu
// Copyright (C) 2008 University of California
//
// BOINC is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// BOINC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BOINC.  If not, see <http://www.gnu.org/licenses/>.

#ifndef _BOINC_DIAGNOSTICS_WIN_
#define _BOINC_DIAGNOSTICS_WIN_

#include "boinc_win.h"

#define STATUS_INFO_LENGTH_MISMATCH             ((NTSTATUS)0xC0000004L)

typedef LONG       NTSTATUS;

typedef LONG       KPRIORITY;

typedef struct _CLIENT_ID {
    DWORD          UniqueProcess;
    DWORD          UniqueThread;
} CLIENT_ID;

typedef struct _VM_COUNTERS {
#ifdef _WIN64
// the following was inferred by painful reverse engineering
	SIZE_T		   PeakVirtualSize;	// not actually
    SIZE_T         PageFaultCount;
    SIZE_T         PeakWorkingSetSize;
    SIZE_T         WorkingSetSize;
    SIZE_T         QuotaPeakPagedPoolUsage;
    SIZE_T         QuotaPagedPoolUsage;
    SIZE_T         QuotaPeakNonPagedPoolUsage;
    SIZE_T         QuotaNonPagedPoolUsage;
    SIZE_T         PagefileUsage;
    SIZE_T         PeakPagefileUsage;
    SIZE_T         VirtualSize;		// not actually
#else
    SIZE_T         PeakVirtualSize;
    SIZE_T         VirtualSize;
    ULONG          PageFaultCount;
    SIZE_T         PeakWorkingSetSize;
    SIZE_T         WorkingSetSize;
    SIZE_T         QuotaPeakPagedPoolUsage;
    SIZE_T         QuotaPagedPoolUsage;
    SIZE_T         QuotaPeakNonPagedPoolUsage;
    SIZE_T         QuotaNonPagedPoolUsage;
    SIZE_T         PagefileUsage;
    SIZE_T         PeakPagefileUsage;
#endif
} VM_COUNTERS;

typedef struct _SYSTEM_THREADS {
    LARGE_INTEGER  KernelTime;
    LARGE_INTEGER  UserTime;
    LARGE_INTEGER  CreateTime;
    ULONG          WaitTime;
    PVOID          StartAddress;
    CLIENT_ID      ClientId;
    KPRIORITY      Priority;
    KPRIORITY      BasePriority;
    ULONG          ContextSwitchCount;
    LONG           State;
    LONG           WaitReason;
} SYSTEM_THREADS, * PSYSTEM_THREADS;

typedef struct _SYSTEM_PROCESSES {
    ULONG          NextEntryDelta;
    ULONG          ThreadCount;
    ULONG          Reserved1[6];
    LARGE_INTEGER  CreateTime;
    LARGE_INTEGER  UserTime;
    LARGE_INTEGER  KernelTime;
    UNICODE_STRING ProcessName;
    KPRIORITY      BasePriority;
#ifdef _WIN64
	ULONG pad1;
    ULONG          ProcessId;
	ULONG pad2;
    ULONG          InheritedFromProcessId;
	ULONG pad3, pad4, pad5;
#else
    ULONG          ProcessId;
    ULONG          InheritedFromProcessId;
#endif
    ULONG          HandleCount;
    ULONG          Reserved2[2];
    VM_COUNTERS    VmCounters;
    IO_COUNTERS    IoCounters;
    SYSTEM_THREADS Threads[1];
} SYSTEM_PROCESSES, * PSYSTEM_PROCESSES;

typedef enum _THREAD_STATE {
    ThreadStateInitialized,
    ThreadStateReady,
    ThreadStateRunning,
    ThreadStateStandby,
    ThreadStateTerminated,
    ThreadStateWaiting,
    ThreadStateTransition
} THREAD_STATE, *PTHREAD_STATE;

typedef enum _THREAD_WAIT_REASON {
    ThreadWaitReasonExecutive,
    ThreadWaitReasonFreePage,
    ThreadWaitReasonPageIn,
    ThreadWaitReasonPoolAllocation,
    ThreadWaitReasonDelayExecution,
    ThreadWaitReasonSuspended,
    ThreadWaitReasonUserRequest,
    ThreadWaitReasonWrExecutive,
    ThreadWaitReasonWrFreePage,
    ThreadWaitReasonWrPageIn,
    ThreadWaitReasonWrPoolAllocation,
    ThreadWaitReasonWrDelayExecution,
    ThreadWaitReasonWrSuspended,
    ThreadWaitReasonWrUserRequest,
    ThreadWaitReasonWrEventPairHigh,
    ThreadWaitReasonWrEventPairLow,
    ThreadWaitReasonWrLpcReceive,
    ThreadWaitReasonWrLpcReply,
    ThreadWaitReasonWrVirtualMemory,
    ThreadWaitReasonWrPageOut,
    ThreadWaitReasonMaximumWaitReason
} THREAD_WAIT_REASON;

#endif
