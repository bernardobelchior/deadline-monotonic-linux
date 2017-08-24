ifndef __LF_RQ_H_
#define __LF_RQ_H_

#include <linux/sched.h>
#include <linux/list.h>
#include <linux/spinlock.h>

struct dm_rq{
	struct list_head tasks;
	struct task_struct *task;
	spinlock_t lock;
};

void init_dm_rq(struct dm_rq *rq);

#endif