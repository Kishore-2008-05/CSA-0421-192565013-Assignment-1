# Q3 – Threads (6 marks)

The program simulates 64 independent camera-frame workloads and measures serial processing, 64 threads (one per camera), and pools of 4, 8 and 16 workers. Compile with `gcc -std=c11 -Wall -Wextra -O2 -pthread camera_threads.c -o camera_threads`.

Threads in one process share code, global data/heap, open file descriptors and process credentials. Each thread has its own registers, program counter, stack and thread-local storage. User-level threads are scheduled by a runtime and may have cheap switching but can block together if mapped many-to-one. Kernel-level threads are scheduled independently by the OS. Models: many-to-one (many user threads to one kernel thread), one-to-one (each user thread maps to a kernel thread), many-to-many (many user threads multiplexed over a set of kernel threads).

The benchmark uses synthetic CPU work, not real image recognition; replace/augment it with a representative OpenCV workload if available. Speed-up = serial time / parallel time. It may stop increasing because of physical-core limits, memory bandwidth, cache contention, thread creation/join overhead, lock contention and Amdahl's serial fraction. A plain `counter++` shared by threads is a data race; use a mutex or C11 atomics.

Alternative: multiple processes provide address-space isolation but cost more creation/memory and require IPC to combine results. Threads communicate through shared memory directly, but need synchronisation. For N frames and fixed per-frame work F, useful computation is O(NF); worker-pool scheduling overhead is O(N) and worker storage O(W), while one thread per camera uses O(N) thread resources. Pooling is the safer scalable design.
