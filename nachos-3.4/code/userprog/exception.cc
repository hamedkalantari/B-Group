// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "addrspace.h"
#include "../threads/system.h"

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------


//Function to be called by the StackAllocate. MADE FOR FORK.
void
forkedThreadExtraPrecedure(int arg)
{

    if(threadToBeDestroyed != NULL) {
        delete threadToBeDestroyed;
        threadToBeDestroyed = NULL;
    }

#ifdef USER_PROGRAM
    if(currentThread -> space != NULL)
	{
		currentThread -> RestoreUserState() ;
		currentThread -> space -> RestoreState() ;
	}

	machine -> Run();

#endif
}


void
ExceptionHandler(ExceptionType which) {
    int type = machine->ReadRegister(2);

    if ((which == SyscallException) && (type == SC_Halt))
    {
        DEBUG('a', "Shutdown, initiated by user program.\n");

        interrupt->Halt();
    }
    else if ((which == SyscallException) && (type == SC_Exit))
    {
        int exit_code = machine->ReadRegister(4);
        printf("####################### I am %d\n", exit_code);
        currentThread->Finish();
    }
    else if ((which == SyscallException) && (type == SC_Join))
    {
        int child_pid = machine->ReadRegister(4);

        Thread * child_thread;
        child_thread = (Thread*) scheduler->allThreads->last;

        if(child_thread != NULL)
        {
            currentThread -> Sleep();
        }
        else
        {
            machine -> WriteRegister(2 , -1);
        }

        machine->WriteRegister(PrevPCReg, machine->ReadRegister(PCReg));
        machine->WriteRegister(PCReg, machine->ReadRegister(NextPCReg));
        machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg)+4);
    }


    else if ((which == SyscallException) && (type == SC_Fork))
    {
        DEBUG('a', "############## FORKING ############\n");


        Thread* childThread = new Thread("forkedThread");;
        AddrSpace* childSpace  = new AddrSpace(); // copies currentThread's Address Space



        /*
        // initial child address space
        // probably we should copy virtual addresses
        childSpace = currentThread->space;

        // load page table
        // sohuldn't we initiate a new page table?
        childSpace->RestoreState();
        */

        // set child thread's address space
        childThread->space = childSpace;




        // initial registers
        // register values are stored in userRegisters array of parent thread
        // we should copy it to child's userRegisters
        // we are running the currentThread so we save its registers.
        // NOTE: we are not saving PC registers now! it's obvious from the code
        childThread->SaveUserState();
        // also we should set child's return value for fork syscall
        // we update userRegister array for simplicity
        childThread->SetRegister(2, 0);
        // we are on the forking instruction so
        // we should increment it for a single instruction (an int size)
        childThread->RestoreUserState();
        childThread->SetRegister(PCReg , machine->ReadRegister(NextPCReg));
        childThread->SetRegister(PrevPCReg , machine->ReadRegister(PCReg));
        childThread->SetRegister(NextPCReg , machine->ReadRegister(NextPCReg) + 4);

        // our forked thread is ready only thing
        // we should do is calling the Fork method to put it in ready queue
        // alocate stack for kernel thread that is attached to this forked program
        // this should have the codes that after SWITCH happens. (it's the first time)
        childThread->Fork(forkedThreadExtraPrecedure, machine->ReadRegister(4));


        // IMPORTANT BECAREFUL WITH PC! what is parent's next value?
        machine -> WriteRegister(2 , 100); //Setting the return value to be the PID of the the child thread
                                            // since threads in this system doen't have pid we provided a default number
        machine->WriteRegister(PrevPCReg, machine->ReadRegister(PCReg));
        machine->WriteRegister(PCReg, machine->ReadRegister(NextPCReg));
        machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg)+4);


        DEBUG('a', "##############FORKING ENDS############\n");

    }
    else
    {
        printf("Unexpected user mode exception %d %d\n", which, type);
        ASSERT(FALSE);
    }
}
