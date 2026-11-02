# Compare FCFS, non-preemptive SJF, SRTF, non-preemptive priority and RR.
# Priority assumption (not supplied in assignment): smaller number = higher priority.
jobs = [("P1",0,8,3), ("P2",1,4,1), ("P3",2,9,4), ("P4",3,5,2)]
Q = 3

def report(label, segments, finish, first):
    rows=[]
    for name,arr,burst,prio in jobs:
        tat=finish[name]-arr; wt=tat-burst; response=first[name]-arr
        rows.append((name,tat,wt,response))
    print(f"\n{label}: " + " ".join(f"{p}({a}-{b})" for p,a,b in segments))
    for r in rows: print("%s TAT=%d WT=%d RT=%d"%r)
    print("averages TAT=%.2f WT=%.2f RT=%.2f"%tuple(sum(r[i] for r in rows)/len(rows) for i in (1,2,3)))

def nonpreemptive(key):
    t=0; done=set(); seg=[]; fin={}; first={}
    while len(done)<len(jobs):
        ready=[j for j in jobs if j[0] not in done and j[1]<=t]
        if not ready: t=min(j[1] for j in jobs if j[0] not in done); ready=[j for j in jobs if j[0] not in done and j[1]<=t]
        j=min(ready,key=key); n,a,b,p=j
        first[n]=t; seg.append((n,t,t+b)); t+=b; fin[n]=t; done.add(n)
    return seg,fin,first

def srtf():
    rem={n:b for n,a,b,p in jobs}; t=0; fin={}; first={}; seg=[]
    while len(fin)<len(jobs):
        ready=[j for j in jobs if j[1]<=t and rem[j[0]]>0]
        if not ready: t+=1; continue
        j=min(ready,key=lambda x:rem[x[0]]); n=j[0]
        if n not in first:first[n]=t
        if seg and seg[-1][0]==n and seg[-1][2]==t: seg[-1]=(n,seg[-1][1],t+1)
        else: seg.append((n,t,t+1))
        rem[n]-=1;t+=1
        if rem[n]==0:fin[n]=t
    return seg,fin,first

def rr(q):
    from collections import deque
    rem={n:b for n,a,b,p in jobs}; added=set(); qready=deque(); t=0; fin={}; first={}; seg=[]
    while len(fin)<len(jobs):
        for n,a,b,p in jobs:
            if a<=t and n not in added: qready.append(n);added.add(n)
        if not qready:
            t=min(a for n,a,b,p in jobs if n not in added);continue
        n=qready.popleft()
        if n not in first:first[n]=t
        run=min(q,rem[n]); start=t;t+=run;rem[n]-=run;seg.append((n,start,t))
        for nn,a,b,p in jobs:
            if a<=t and nn not in added:qready.append(nn);added.add(nn)
        if rem[n]:qready.append(n)
        else:fin[n]=t
    return seg,fin,first

for label, result in [
    ("FCFS",nonpreemptive(lambda j:j[1])),
    ("SJF",nonpreemptive(lambda j:j[2])),
    ("SRTF",srtf()),
    ("Priority (1 is highest)",nonpreemptive(lambda j:j[3])),
    (f"Round Robin q={Q}",rr(Q))
]:
    report(label,*result)
for q in (1,3,5,20):
    seg,fin,first=rr(q)
    report(f"Round Robin q={q}",seg,fin,first)
