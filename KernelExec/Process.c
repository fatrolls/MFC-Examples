#include "Process.h"

typedef enum
{
    OriginalApcEnvironment,
	AttachedApcEnvironment,
	CurrentApcEnvironment
} KAPC_ENVIRONMENT;

void ApcKernelRoutine( IN struct _KAPC *Apc, IN OUT PKNORMAL_ROUTINE *NormalRoutine, IN OUT PVOID *NormalContext, IN OUT PVOID *SystemArgument1, IN OUT PVOID *SystemArgument2 ) ;
NTSTATUS InstallUserModeApc(LPSTR lpProcess, PKTHREAD pTargetThread, PEPROCESS pTargetProcess);
void ApcCreateProcess(PVOID NormalContext, PVOID  SystemArgument1, PVOID SystemArgument2);
void ApcCreateProcessEnd();


#pragma alloc_text(PAGE, RunProcess)
#pragma alloc_text(PAGE, ApcKernelRoutine)
#pragma alloc_text(PAGE, InstallUserModeApc)
#pragma alloc_text(PAGE, ApcCreateProcess)
#pragma alloc_text(PAGE, ApcCreateProcessEnd)


//=====================================================================================//
//Name: void RunProcess()                                                              //
//                                                                                     //
//Descripion: This routine retrieves the list of all processes running on the machine, //
//            searches for 'explorer.exe', gets one thread from it's PEPROCESS struct, //
//            then it queues an APC to that thread                                     //
//=====================================================================================//
void RunProcess(LPSTR lpProcess)
{

	PEPROCESS pTargetProcess = NULL;     //self explanatory
	PKTHREAD pTargetThread = NULL;       //thread that can be either alerable or non-alertable
	PKTHREAD pNotAlertableThread = NULL; //non-alertable thread
	PEPROCESS pSystemProcess = NULL;     //May not necessarily be the 'System' process
	
	PETHREAD pTempThread = NULL;
	PLIST_ENTRY	pNextEntry, pListHead, pThNextEntry; 


	if(strlen(lpProcess)>300) return; //name not longer than 300 characters

	pSystemProcess = PsGetCurrentProcess(); //make sure you are running at IRQL PASSIVE_LEVEL

	if(!pSystemProcess) 
	{
		DbgPrint("KernelExec -> Cannot find 'System' process!");
		return;
	}
	
	if(IsListEmpty(&pSystemProcess->ActiveProcessLinks))
		DbgPrint("KernelExec -> No processes found!");
	else
	{
		pListHead = &pSystemProcess->ActiveProcessLinks;
		pNextEntry = pListHead->Flink;

		while(pNextEntry != pListHead) //start looping through the available processes
		{
			pSystemProcess = CONTAINING_RECORD(pNextEntry,EPROCESS,ActiveProcessLinks);

			if(pSystemProcess->ActiveThreads)
			{
				if(!IsListEmpty(&pSystemProcess->ThreadListHead))
				{
					//Is this explorer.exe? 
					if(_strnicmp(pSystemProcess->ImageFileName,"explorer.exe",12)==0)
					{
						pTargetProcess = pSystemProcess; //Yes,we have found it!
						pTargetThread = pNotAlertableThread = NULL;

						pThNextEntry = pSystemProcess->ThreadListHead.Flink;
						
						//Now we loop through it's threads, seeking an alertable thread
						while(pThNextEntry != &pSystemProcess->ThreadListHead)
						{
							pTempThread = CONTAINING_RECORD(pThNextEntry,ETHREAD,ThreadListEntry);							
						
							if(pTempThread->Tcb.Alertable) //Tcb is the KTHREAD of this ETHREAD and stands for 'Thread Control Block'
							{
								//Good, an alertable thread was found. 
								pTargetThread = &pTempThread->Tcb;

								DbgPrint("KernelExec -> Found alertable thread");
								//We will be using this one, so break now
								break;
							}
							else
							{
								//Didn't find an alertable thread yet, so we'll keep this one
								//just in case we won't find ANY alertable threads
								pNotAlertableThread = &pTempThread->Tcb;
							}

							pThNextEntry = pThNextEntry->Flink; //check next thread
						}
						break;	
					}
				}		
			}
			
			pSystemProcess = NULL;
			pNextEntry = pNextEntry->Flink; //get next process
		}
	}
	
	if(!pTargetProcess)
	{
		DbgPrint("KernelExec -> Couldn't find Explorer.exe!"); 
		return;
	}
	
	if(!pTargetThread)
	{
		//No alertable thread was found, so let's hope we've at least got a non-alertable one (we'll set its alertable flag ON)
		//There's no problem with non-alertable threads, except for the fact that it takes
		//a little longer for them to return from KernelMode. (that means our process execution will be delayed)
		pTargetThread = pNotAlertableThread;
	}

	if(pTargetThread)
	{
		DbgPrint("KernelExec -> Targeted thread: 0x%p",pTargetThread);
		//We have one thread (alertable or n/a), now install the APC
		InstallUserModeApc(lpProcess, pTargetThread,pTargetProcess);
	}
	else
		DbgPrint("KernelExec -> No thread found!"); //Explorer exe with NO threads (???)
}



PMDL pMdl = NULL;
//===================================================================//
//Name: VOID ApcKernelRoutine()                                      //
//                                                                   //
//Descripion: This routine gets called after the APC routine returns //
//            (our process should have been executed by then)        //
//            It frees all the memory allocated by InstallUserModeApc//
//            (APC and MDL)                                          //
//===================================================================//
void ApcKernelRoutine( IN struct _KAPC *Apc, IN OUT PKNORMAL_ROUTINE *NormalRoutine, 
										   IN OUT PVOID *NormalContext, IN OUT PVOID *SystemArgument1, IN OUT PVOID *SystemArgument2 ) 
{
	
	if (Apc)
		ExFreePool(Apc);
	if(pMdl)
	{
		MmUnlockPages(pMdl);
		IoFreeMdl (pMdl);
		pMdl = NULL;
	}
	DbgPrint("KernelExec -> ApcKernelRoutine called. Memory freed.");
}


//===================================================================//
//Name:                                                              //
//     NTSTATUS InstallUserModeApc()                                 //
//                                                                   //
//Paramters:                                                         //
//          lpProcess - Full path of the process to be executes      //
//          pTargetThread - This is where we queue our APC           //
//          pTargetProcess - Should point to Explorer's EPROCESS     //
//                                                                   //
//Descripion: This routine attaches to 'pTargetThread' and it queues //
//            a UserMode APC that will be excuted next time the      //
//            thread returns from KernelMode                         //
//===================================================================//
NTSTATUS 
InstallUserModeApc(LPSTR lpProcess, PKTHREAD pTargetThread, PEPROCESS pTargetProcess)
{
	PRKAPC pApc = NULL; //Our APC
	
	PVOID pMappedAddress = NULL; //This is where the UserMode routine's code will be placed at
	ULONG dwSize = 0; //Size of code to be executed in Explorer's address space

	KAPC_STATE ApcState; // Needed for KeStackAttachProcess
	
	ULONG *data_addr=0; //just a helper to change the address of the 'push' instruction
	                    //in the ApcCreateProcess routine
	ULONG dwMappedAddress = 0; //same as above
	
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	if (!pTargetThread || !pTargetProcess)
		return STATUS_UNSUCCESSFUL;


	//Allocate memory for our APC
	pApc = ExAllocatePool (NonPagedPool,sizeof (KAPC)); 
	if (!pApc)
	{
		DbgPrint("KernelExec -> Failed to allocate memory for the APC structure");
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	//Get the size of our UserMode code
	dwSize = (unsigned char*)ApcCreateProcessEnd-(unsigned char*)ApcCreateProcess;
	
	//Allocate an MDL describing our ApcCreateProcess' memory
	pMdl = IoAllocateMdl (ApcCreateProcess, dwSize, FALSE,FALSE,NULL);
	if (!pMdl)
	{
		DbgPrint("KernelExec -> Failed to allocate MDL");
		ExFreePool (pApc);
		return STATUS_INSUFFICIENT_RESOURCES;
	}
	
	__try
	{
		//Probe the pages for Write access and make them memory resident
		MmProbeAndLockPages (pMdl,KernelMode,IoWriteAccess);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		DbgPrint("KernelExec -> Exception during MmProbeAndLockPages");
		IoFreeMdl (pMdl);
		ExFreePool (pApc);
		return STATUS_UNSUCCESSFUL;
	}
	
	//Attach to the Explorer's address space
	KeStackAttachProcess(&(pTargetProcess->Pcb),&ApcState);

	//Now map the physical pages (our code) described by 'pMdl'
	pMappedAddress = MmMapLockedPagesSpecifyCache (pMdl,UserMode,MmCached,NULL,FALSE,NormalPagePriority);
	
	if (!pMappedAddress)
	{
		DbgPrint("KernelExec -> Cannot map address");

		KeUnstackDetachProcess (&ApcState);
		IoFreeMdl (pMdl);
		ExFreePool (pApc);

		return STATUS_UNSUCCESSFUL;
	}
	else 
		DbgPrint("KernelExec -> UserMode memory at address: 0x%p",pMappedAddress);

	dwMappedAddress = (ULONG)pMappedAddress;
	
	memset ((unsigned char*)pMappedAddress + 0x14, 0, 300);//zero everything out ecxept our assembler code
    memcpy ((unsigned char*)pMappedAddress + 0x14, lpProcess,strlen (lpProcess)); //copy the path to the executable

	data_addr = (ULONG*)((char*)pMappedAddress+0x9); //address pushed on the stack (originaly 0xabcd)...
	*data_addr = dwMappedAddress+0x14; //..gets changed to point to our exe's path 
	
	//all done, detach now
	KeUnstackDetachProcess (&ApcState);
	
	//Initialize the APC...
	KeInitializeApc(pApc,pTargetThread,
		OriginalApcEnvironment,
		&ApcKernelRoutine,NULL,
		pMappedAddress, UserMode, (PVOID) NULL);
	
	//...and queue it
	if (!KeInsertQueueApc(pApc,0,NULL,0))
	{
		DbgPrint("KernelExec -> Failed to insert APC");
		MmUnlockPages(pMdl);
		IoFreeMdl (pMdl);
		ExFreePool (pApc);
		return STATUS_UNSUCCESSFUL;
	}
	else
	{
		DbgPrint("KernelExec -> APC delivered");
	}

	//is this a non-alertable thread?
	if(!pTargetThread->ApcState.UserApcPending)
	{
		//if yes then alert it
		pTargetThread->ApcState.UserApcPending = TRUE;
	}

	return 0;
}


//=====================================================================================//
//Name: void ApcCreateProcess()                                                        //
//                                                                                     //
//Descripion: This is the code that runs in UserMode. 0x7X86114D is the address of     //
//            WinExec on WinXP SP2. You can do everything here and not crash the system//
//            (but Explorer WILL crash, if you do something stupid)                    //
//=====================================================================================//
__declspec(naked) void ApcCreateProcess(PVOID NormalContext, PVOID  SystemArgument1, PVOID SystemArgument2)
{
    __asm 
    {
		mov eax,0x7C86114D
		push 1
		nop
		push 0xabcd
		call eax
		jmp end       
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
end:
		nop
		ret 0x0c
    }

}
void ApcCreateProcessEnd(){}
