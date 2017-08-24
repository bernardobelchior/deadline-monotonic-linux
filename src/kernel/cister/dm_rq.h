#ifndef __DM_RQ_H_
#define __DM_RQ_H_

#include <linux/sched.h>
#include <linux/rbtree.h>
#include <linux/spinlock.h>

struct dm_rq{
	struct rb_root root;
	struct task_struct *task;
	spinlock_t lock;
};

void init_dm_rq(struct dm_rq *rq);

#endif
