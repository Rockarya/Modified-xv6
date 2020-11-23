->Execution of my code:-
    1)make clean
    2)make qemu (for running the default RR scheduler)
    3)make qemu SCHEDULER=?

->For choosing the type of scheduler we raise the flag SCHEDULER.
    where ?=FCFS/PBS/MLFQ.  and default is RR

->Made a report in which i compared all the scheduling algorithms implemented.

TASK 1 :-
->waitx:-

    1)The fields ctime (CREATION TIME), etime (END TIME), rtime (calculates RUN TIME) & iotime (IO TIME) fields have been added to proc structure of proc.h file
        proc.c contains the actual waitx() system call.

    2)Code is same as wait() and does the following:
        Search for a zombie child of parent in the proc table.
        When the child was found , following pointers were updated :
            *wtime= p->etime - p->ctime - p->rtime - p->iotime;
            *rtime=p->rtime;
        sysproc.c is just used to call waitx() which is present in proc.c. The sys_waitx() function in sysproc.c passes the parameters (rtime,wtime) to the waitx() of proc.c, just as other system calls do.

    3)Calculating ctime, etime, rtime and iotime
        ctime is recorded in allocproc() function of proc.c (When process is born). It is set to ticks.
        etime is recorded in exit() function (i.e when child exists, ticks are recorded) of proc.c.
        rtime is updated in trap() function in trap.c . IF STATE IS RUNNING , THEN UPDATE rtime.
        iotime is updated in trap() function of trap.c.(IF STATE IS SLEEPING , THEN UPDATE iotime.

    4)Tester file - time command

->ps
    1)Listing all the active process status.
    2)Implemented ps by writing a getpinfo() function in proc.c file.In this we run a loop for all valid pid's and print their details.
    3)A ps user program is implemented to get the process status of all the processes.(ps.c is created to make the user program)


TASK 2:-
->FCFS:-
    1)Selection of process is based on their ctime.The one with min ctime will be executed first and will continue running unless it gets finished.
    2)Removed yield() fxn from trap.c and the above implementation in proc.c (in scheduler function)
    3)yield() function is used for context switch.

->PBS:-
    1)Assigned default priority 60 to each entering process.
    2)Find the minimum priority process by iterating through the process table (min priority number translates to maximum preference)
    3)The process with max preference will be executed first and will continue it's execution until it get's finished.
    4)A setPriority user program is also implemented to change the priority of a process with given pid.After changing the priority rescheduling will occur.
    5)Also the return value of this user program will give user the old priority. 
    6)To implement RR for same priority processes, iterate through all the processes again. Whichever has same priority as the min priority found, execute that. 
    7)yield() is enabled for PBS in proc.c() so the process gets yielded out and if any other process with same priority is there, it gets executed next.
    8)We also have a check within the 2nd loop to ensure no other process with lower priority has come in. If it has, we break out of the 2nd loop, otherwise 
        RR is executed for same priority processes.

->MLFQ:-
    1)I have declared 5 queues with different priorities based on time slices, i.e. 1, 2, 4, 8, 16 timer ticks.
    2)These queues contain runnable processes only.
    3)Both add process to queue and remove process from queue functions are implemented in proc.c file.
    4)We add a process in a queue in userinit() and fork() and kill() functions in proc.c i.e. wherever the process state becomes runnable.
    5)Ageing is implemented by iterating through queues 1-4 and checking if any process has exceeded the age limit and subsequently moving it up in the queues.
    6)Next, we iterate over all the queues in order, increase the tick associated with that process and its number of runs.
    7)In the trap file, we check if the curr_ticks of the process >= permissible ticks of the queue. If that's the case, we call yield and push the process to the next queue. Otherwise increment the ticks and let the process remain in queue.