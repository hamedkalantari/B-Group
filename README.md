# Nachos_Operating_Systems_Fall_2017
The Fork system call implementation:
First we should create a thread object,
Then create an address space,
Then we will create a brand new PageTable for addressing,
Then we will copy the contents of the parent memory space into the new address space.

1. After that we have fully prepare our thread’s memory for compiling, these parts of codes are implemented in “addrspace.cc” file at lines 123-152 (we define another constructor that do these memory management things)

2. Then we make the childThread->space point to the newly created address space. (implemented in “exception.cc” line 136)

3. Next step we have to load parent’s registers and their states into a variable for next uses.
(implemented in “exception.cc” line 146)

4. Now we have to set fork’s return value for the child thread (that is zero), so for this purpose we should put it in register 2 (r2), the system automatically assign the amount in the register 2 to our variable. (implemented in “exception.cc” line 149)

5 .After that we load the register that we saved in step 2. (implemented in “exception.cc” line 152)

6. Then we should increment the PC value, because we restore the pc value of parent’s, so our PC is pointing to the fork instruction, and if we don’t increment it, we get stuck in an infinite loop. (implemented in “exception.cc” lines 153-155)

7. Then we call Fork procedure of thread class (Thread->fork call occurs in “exception.cc” line 159). Our newly thread will begin from the function that we provided to the function. Since the system will consider this thread as a new thread (actually, it’s not, it has been forked), it won’t free the parent’s memory and procedures that must occur before switching to a new thread! So the function that we passed to this will close the parent thread from running and deallocate it’s memory, and then start to run the newly forked thread. (The function implemented in “exception.cc” lines 55-74)

Our forking system is running in a manner that the child will start to run, before the parent. So in case we don’t need a join callback (Since we have implemented the JOIN system call).

8. Then we should put Thread’s PID to parent register 2 (r2), so the value that is returned to parent is in this register and system will automatically assign it to the variable. (implemented in “exception.cc” line 165)

9. Then we should increment parent’s PC (since we increment child’s PC not the parent’s) so that parent starts executing from the next instruction, and doesn’t get stuck in an infinite loop. (implemented in “exception.cc” lines 167-169)


Exit system call implementation:
It’s simple.
First we get the passed parameter from Exit system call by reading from the register 4 (r4).
Then we call currentThread->Finish() so our thread will be killed and this prevents our forked thread to being zombie.


Join system call implementation:

First we get the passed parameter to Join system call by reading from the register 4 (r4). It’s the PID of the desired thread.

Then we check our threads list (we implemented a new list that contains all of running processes) if we find the desired thread (with that PID) we can ensure that our child thread is not finished, so we call Sleep() function on parent’s thread (we put parent on sleep and this will not allow parent to continue it’s execution and the scheduler switch to other processes).

And in case that we can’t find that thread, this means that our thread is finished and we continue execution instruction on parent’s routine.
