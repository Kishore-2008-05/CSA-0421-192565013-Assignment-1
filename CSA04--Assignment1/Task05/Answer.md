# TASK 5 – System Calls (4 marks)

System calls are the controlled interface through which a user program requests privileged OS services.

Categories and examples:
- Process control: fork(), execve(), wait(), exit(), kill().
- File management: open(), read(), write(), close(), stat(), unlink().
- Device management: ioctl(), read(), write(); device-specific operations are mediated by drivers.
- Information maintenance: getpid(), uname(), clock_gettime(), gettimeofday().
- Communication: pipe(), socket(), send(), recv(), shmget() (API availability varies).
- Protection: chmod(), chown(), setuid(), access(); modern systems also use capabilities and security modules.

What happens during read(fd, buffer, count):
1. Application calls the C library wrapper read().
2. The wrapper places the system-call number and arguments in the architecture-defined registers/ABI locations.
3. A syscall/trap instruction transfers control to the kernel and changes CPU privilege from user mode to kernel mode.
4. Kernel validates the descriptor, permissions and user buffer; it locates the file/device operation.
5. VFS/filesystem or device driver performs the operation; the process may block if data is not ready.
6. Kernel returns a byte count or -1 with errno set; CPU returns to user mode.
7. The library wrapper returns to the application.

Parameter passing:
Most modern Linux architectures pass syscall number and arguments in registers. Some interfaces can pass a pointer to a structure/block in memory. The stack is used by normal calling conventions and may hold data, but the kernel ABI defines how syscall arguments are passed; it is not universally “the stack”.

strace:
`strace -o trace.txt ./program` records system calls and signals.
`strace -c ./program` summarizes syscall counts and time. Output includes calls made by the program and runtime/library startup, so isolate the relevant calls when comparing.

Buffered stdio alternative:
fopen(), fread() and fwrite() are C library functions, not direct system calls. They maintain a user-space buffer. For a file of n bytes and a library buffer of about 4096 bytes, data transfers can require roughly ceil(n/4096) read/write syscalls rather than one syscall per tiny application read/write of b bytes (roughly ceil(n/b), plus EOF/metadata effects). Buffering consumes about the buffer size per stream and may add a copy between the library buffer and the application buffer. It usually improves throughput for small operations; direct system calls offer more control.
