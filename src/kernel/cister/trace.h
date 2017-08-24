#ifndef __TRACE_H_
#define __TRACE_H_

#include <linux/sched.h>

#define TRACE_ENTRY_NAME "cister_trace"
#define TRACE_BUFFER_SIZE 5000
#define TRACE_BUFFER_LEN 200

enum evt
{
	SCHED_TICK = 0,
	SWITCH_AWAY,
	SWITCH_TO,
	ENQUEUE_RQ,
	DEQUEUE_RQ
};

#define TRACE_TASK_COMM_LEN 16

struct trace_evt
{
	enum evt event;
	unsigned long long time;
	pid_t pid;
	int state;
	int prio;
	int policy;
	char comm[TRACE_TASK_COMM_LEN];

#ifdef CONFIG_CISTER_SCHED_DM_POLICY
	int task_id;
#endif
};

struct trace_evt_buffer
{
	struct trace_evt events[TRACE_BUFFER_SIZE];
	int write_item;
	int read_item;
	spinlock_t lock;
};

void cister_trace(enum evt event, struct task_struct *p);

void enable_tracing(int enable);
#endif
