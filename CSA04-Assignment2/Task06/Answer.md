# Q6 – Deadlock Handling and the Banker's Algorithm (13 marks)

## A. Four necessary conditions
1. Mutual exclusion: at least one resource is non-shareable.
2. Hold and wait: a process holds resources while requesting more.
3. No preemption: resources cannot be forcibly taken away.
4. Circular wait: a cycle of processes each waits for a resource held by the next.

For the lab cluster, illustrate a cycle such as Job A holds GPU and requests licence; Job B holds licence and requests storage; Job C holds storage and requests GPU. A cycle is necessary for deadlock in a single-instance resource graph; with multiple instances it is not by itself sufficient.

## Completed program and decisions
`banker.c` completes the safety test and request algorithm. It should produce the assignment's expected initial safe sequence and the three request outcomes. Compile with `gcc -std=c11 -Wall -Wextra -O2 banker.c -o banker`.

For P0 request (0,2,0), after tentative allocation Available becomes (3,1,2), P0 allocation becomes (0,3,0), and P0 remaining need becomes (7,2,3). No process can finish with the tentative Work=(3,1,2): P0 needs too many A/C, P1 needs (1,2,2), P2 needs (6,0,0), P3 needs (0,1,1) but its allocation is not enough to resolve all jobs? Evaluate the complete scan: no full safe sequence exists, so the request is rolled back and denied. Use the program's computed trace as the definitive check.

## B. Strategy comparison
- Prevention: structurally break one necessary condition (e.g., global resource ordering breaks circular wait). Predictable but can reduce utilisation and flexibility.
- Avoidance: Banker grants only requests that preserve a safe state. Strong when maximum claims are known, but per-request checks cost CPU and require reliable maximum-demand declarations.
- Detection and recovery: allow allocations, periodically detect cycles/unsafe wait-for states, then abort/rollback a selected job or preempt recoverable resources. Better utilisation but detection delay and lost work.
- Ignore (ostrich): cheapest runtime, acceptable only if deadlocks are rare and manual recovery cost is low; poor fit for critical shared laboratory equipment.

## C. Safety/request algorithm
For each unfinished process, compute Need=Max−Allocation. If Need≤Work component-wise, assume it finishes, add its allocation to Work, and append it to the safe sequence. If no process can proceed in a pass, the state is unsafe. For a request, first check Request≤Need and Request≤Available, tentatively allocate, run safety test, and roll back if unsafe.

## D. Complexity prediction
For n processes and m resource types, a straightforward safety scan is O(m n²) in the worst case: up to n passes, each scanning n processes and m resource dimensions. Auxiliary space is O(n+m) excluding input matrices; the matrices themselves are O(nm).

## E. Measurement
`banker_bench.c` measures n=10,100,1000 with m=3. Run on your Linux machine and record outputs. The benchmark uses a deliberately safe synthetic input and reports wall-clock time; repeat runs and report median. Do not copy another machine's timings as your own. Compare growth against the O(m n²) upper bound; actual results may be lower due to early completion and cache effects.

## F. Recommendation
For the research centre, use resource ordering for resources that can be globally ordered, plus Banker-style admission control for jobs with declared GPU/licence/storage maximum claims and a detection/alerting fallback for external failures. Banker is appropriate only if maximum claims are credible and the number of concurrent jobs is moderate. For unpredictable workloads, combine quotas, leases/timeouts, transactional rollback/checkpointing and detection/recovery. A purely Banker design may reject safe-but-not-provably-safe requests and incurs O(mn²) worst-case admission checks.
