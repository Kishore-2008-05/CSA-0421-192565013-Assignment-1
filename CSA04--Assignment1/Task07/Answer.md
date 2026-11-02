# TASK 7 – Process Control System Calls (4 marks)

fork() creates a child process with a logically separate address space (implemented efficiently using copy-on-write on Linux). exec() replaces the current process image with a new program; it does not create another process. wait()/waitpid() collects a terminated child’s status and prevents a zombie from remaining. exit() terminates a process and runs normal user-space exit handlers; _exit() terminates without flushing C stdio buffers or running atexit handlers.

Shell sequence:
1. Shell reads and parses a command.
2. Shell calls fork() (or a spawn API).
3. Child calls exec() to load the requested program.
4. Parent calls waitpid() for a foreground command.
5. Kernel records termination status; parent obtains it with WIFEXITED/WEXITSTATUS or WIFSIGNALED.
6. Shell displays prompt/continues.

Zombie: a child has terminated but its parent has not yet collected its status. The kernel retains a small process-table entry. Parent should wait(). Orphan: parent terminates while child is running; the child is re-parented to an init/subreaper process, which eventually reaps it.

Why fork()+exec():
It separates process creation from program replacement and lets the child configure file descriptors, pipes, environment and redirections between the two calls. posix_spawn() packages common spawn actions more efficiently in some environments.

Expected supplied-program output:
shell: running job 1
42
job 1 exit status 0
shell: running job 2
job 2 exit status 3

stdout flushing:
Before fork(), stdout may be line-buffered on a terminal but fully buffered when redirected to a file. The child inherits a copy of the user-space stdio buffer. Flushing before fork prevents both parent and child from later flushing the same buffered text. In the second experiment, removing the second fflush and using exit(3) causes the child to flush its inherited buffer at exit, while the parent later flushes its own copy; therefore “shell: running job 2” can appear twice in redirected output. _exit(3) does not flush stdio.

Alternative:
posix_spawn() can avoid a general fork-then-exec sequence and may be efficient for launching many programs. Threads share one address space and resources, so creation can be lighter, but they are not equivalent to isolated commands: a faulty or malicious thread can corrupt shared memory. For independent shell commands, processes provide stronger isolation. For 1,000 launches, measure on the target OS; exact times depend on machine load and implementation. Complexity of creating k children/threads is O(k) operations; per-process memory overhead is generally higher than per-thread overhead, while fork uses copy-on-write rather than eagerly copying all pages.
