# Q5 – Synchronisation: Critical Sections, Semaphores and Monitors (11 marks)

The critical-section requirements are mutual exclusion (only one conflicting update at a time), progress (if no one is inside, eligible contenders can proceed), and bounded waiting (a contender cannot be postponed forever). Peterson's algorithm satisfies these for two processes under a sequentially consistent memory model, but compiler/CPU reordering and modern memory models require appropriate atomic operations and fences; it is not a practical general-purpose lock.

The bounded-buffer implementation uses `empty_slots` to count free slots, `full_slots` to count occupied slots, and a mutex to protect buffer indexes and the shared item counter. `wait(empty)` reserves capacity; producer locks, inserts, unlocks and posts `full`. Consumer waits on `full`, locks, removes and updates accounting, unlocks and posts `empty`. The code supports 1–16 producers/consumers and 20 unique items. Run `bash run_100.sh`; expected sum is 210 on each successful run.

Semaphore patterns:
- Producer-consumer: `empty`, `full`, and mutex as above.
- Readers-writers: a reader-count mutex protects `read_count`; first reader acquires the resource lock and last reader releases it. Writers acquire the resource lock exclusively. Add a turnstile/fair queue to avoid writer or reader starvation.
- Dining philosophers: acquire both forks with a global resource ordering, or use a waiter semaphore limiting simultaneous eaters to N−1; this prevents circular wait/deadlock.

A monitor encapsulates shared state and methods under one implicit lock, with condition variables such as `notFull` and `notEmpty`. Waiting atomically releases the monitor lock and re-acquires it on wakeup; always re-check predicates in a loop.

Booking deployment: one global lock is simple but serialises unrelated trains. A lock per train allows parallel bookings across trains and prevents double-selling within a train. Per-coach locks may improve concurrency further but require a consistent lock order for multi-coach operations and more complex availability queries. Prefer per-train locking as the safer initial balance; benchmark realistic contention before splitting further.

Alternative: C11 atomic fetch-add is suitable for a simple counter, but it cannot by itself protect a multi-step seat allocation invariant. Spin locks waste CPU while waiting and are suitable only for extremely short critical sections on systems where the owner is running. A blocking mutex/semaphore is better for longer sections. Complexity: each insert/remove is O(1); buffer space O(SIZE), plus O(P+C) thread stacks. Synchronisation throughput is workload-dependent and must be measured.
