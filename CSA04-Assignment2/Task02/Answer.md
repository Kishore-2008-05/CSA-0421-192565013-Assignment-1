# Q2 – CPU Scheduling (8 marks)

Workload: P1(A=0,B=8), P2(1,4), P3(2,9), P4(3,5). Run `python3 scheduling.py` for Gantt segments and TAT/WT/response-time calculations. Run `round_robin.c` for the required completed C implementation.

**Priority assumption:** The assignment does not provide priority values. The comparison script explicitly assumes P1=3, P2=1, P3=4, P4=2, where 1 is highest. State this assumption in the submitted report or replace it with the faculty-provided priorities.

Definitions: Turnaround time (TAT)=completion−arrival; waiting time (WT)=TAT−CPU burst; response time (RT)=first CPU start−arrival.

Evaluation: FCFS is simple but convoy-prone: a long film can delay a 2-second thumbnail. SJF improves average waiting when burst estimates are accurate but may starve long films. SRTF improves short-job response by preempting a long job, at the cost of more preemptions and estimates. Priority scheduling can starve low-priority work; ageing gradually raises waiting jobs' priority. Round Robin provides fairness and bounded response, but a very small quantum creates excessive context switches while a very large quantum approaches FCFS.

Recommendation: Use a multilevel-feedback-queue (MLFQ) or size-aware hybrid: new/short jobs begin in a high-priority queue with a short quantum; jobs repeatedly consuming a full quantum move to lower queues with longer quanta. Add ageing and reserved capacity for long jobs to prevent starvation. Monitor throughput, p95 response time and average waiting time, not CPU utilisation alone.

Complexity: With a ready list scanned each dispatch, SJF/SRTF/priority selection is O(n) per decision (or O(log n) with a heap); RR queue enqueue/dequeue is O(1) per decision. Across K time slices RR bookkeeping is O(K), with O(n) queue storage. MLFQ operations are O(1) with a fixed number of FIFO queues; promotion/demotion policy must be tuned.
