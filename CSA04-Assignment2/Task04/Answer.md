# Q4 – Inter-Process Communication (6 marks)

`pipe_ipc.c` completes the supplied TODO: the child reads one integer until `read()` returns 0, updates count/sum/max, and prints the aggregate. The parent closes its write descriptor after sending all readings. Closing the final write end is the EOF signal. If the parent leaves `fd[1]` open, the kernel still sees a possible writer; the child blocks waiting for more bytes and never observes EOF.

`shm_ipc.c` demonstrates POSIX shared memory (`shm_open` + `mmap`) and a process-shared semaphore. Shared memory avoids copying every payload through the pipe kernel buffer, but requires explicit coordination so the consumer does not read incomplete data. Pipes provide a simple byte stream and kernel-mediated transfer; message passing generally copies data, while shared memory maps the same physical pages into both address spaces.

For n bytes, both methods have O(n) data movement. A pipe incurs kernel buffer copy/management and context transitions; shared memory can avoid per-message copying but still incurs memory writes/reads and synchronisation. Benchmark 1, 10 and 100 MiB on your Linux host, repeat at least five times, and report median throughput. The small sample program verifies correctness, not a valid large-payload performance benchmark.
