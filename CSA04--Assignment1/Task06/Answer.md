# TASK 6 – Cost of System Calls (4 marks)

A system call is more expensive than an ordinary function call because it crosses the user/kernel boundary, saves/restores state, validates arguments and permissions, may interact with drivers/filesystems, and may block or trigger scheduling. The exact cost depends on CPU, kernel, filesystem, cache state and workload.

For the supplied 10,000-byte test file, the program counts every read(), including the final read returning 0 (EOF):
- buffer 1: 10,000 data reads + 1 EOF read = 10,001.
- buffer 512: ceil(10,000/512) = 20 data reads + 1 EOF read = 21.
- buffer 4096: ceil(10,000/4096) = 3 data reads + 1 EOF read = 4.

Expected output:
buffer    1 bytes: 10001 read() calls
buffer  512 bytes:    21 read() calls
buffer 4096 bytes:     4 read() calls

The write loop must handle partial writes and EINTR. A single write() is not guaranteed to write every requested byte. The provided implementation below does so.

Recommendation:
For large sequential backups, use a moderate/large buffer such as 64 KiB or 256 KiB after benchmarking. The assignment's tested maximum is 4096 bytes, which reduces calls dramatically versus 1 byte. Do not claim 4096 is universally optimal; benchmark on the actual storage and workload. The fixed source array is 8192 bytes, so bufsize must not exceed 8192.

Complexity:
For n bytes copied, time is O(n) because each byte is read and written once. Auxiliary space is O(b), where b is buffer size. Increasing b reduces syscall count approximately to O(n/b), but does not change O(n) byte-processing complexity.

mmap alternative:
mmap() maps file pages into the process address space; the program accesses mapped memory rather than issuing repeated read() calls. It can reduce explicit read/write calls and avoid an extra user-space copy in some workflows, but page faults still cause kernel work, dirty pages need writeback, mapping/unmapping and synchronization have costs, and mapping very large files consumes virtual address space (not necessarily equal physical RAM). For huge files, map in windows/chunks or retain buffered I/O for simpler bounded memory use.
