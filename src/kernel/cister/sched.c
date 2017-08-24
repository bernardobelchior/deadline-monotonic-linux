#include "../sched/sched.h"

/*
* LIFO scheduling class.
* Implements SCHED_DM
*/
static void enqueue_task_dm(struct rq *rq, struct task_struct *p, int flags)
{
	spin_lock(&rq->dm_rq.lock);
	list_add(&p->dm_task.node,&rq->dm_rq.tasks);
	rq->dm_rq.task = p;
	spin_unlock(&rq->dm_rq.lock);
#ifdef CONFIG_CISTER_TRACING
	cister_trace(ENQUEUE_RQ,p);
#endif
}

static void dequeue_task_dm(struct rq *rq, struct task_struct *p, int flags)
{
	struct dm_task *t = NULL;
	spin_lock(&rq->dm.lock);
	list_del(&p->dm_task.node);
	if(list_empty(&rq->dm_rq.tasks)){
		rq->dm_rq.task = NULL;
	}else{
		t = list_first_entry(&rq->dm_rq.tasks,struct dm_task, node);
		rq->dm.task = container_of(t,struct task_struct, dm_task);
	}
	spin_unlock(&rq->dm.lock);
#ifdef CONFIG_CISTER_TRACING
	cister_trace(ENQUEUE_RQ,p);
#endif
}

static void yield_task_dm(struct rq *rq)
{
}


static void check_preempt_curr_dm(struct rq *rq, struct task_struct *p, int flags)
{
	switch(rq->curr->policy){
		case SCHED_DEADLINE:
		case SCHED_FIFO:
		case SCHED_RR:
			break;
		case SCHED_NORMAL:
		case SCHED_BATCH:
		case SCHED_IDLE:
		//case SCHED_RESET_ON_FORK:
		case SCHED_LIFO:
			resched_task(rq->curr);
			break;
	}
}

static struct task_struct *pick_next_task_dm(struct rq *rq)
{
	struct task_struct * p = NULL;
	spin_lock(&rq->dm.lock);
	p = rq->dm.task;
	spin_unlock(&rq->dm.lock);
	return p;
}
static void put_prev_task_dm(struct rq *rq, struct task_struct *prev)
{
}

#ifdef CONFIG_SMP
static int select_task_rq_dm(struct task_struct *p, int sd_flag, int flags)
{
	return task_cpu(p);
}
#endif

/* CONFIG_SMP */
static void set_curr_task_dm(struct rq *rq)
{
}
static void task_tick_dm(struct rq *rq, struct task_struct *curr, int queued)
{
}
static unsigned int get_rr_interval_dm(struct rq *rq, struct task_struct *task)
{
	return 0;
}
static void switched_to_dm(struct rq *rq, struct task_struct *p)
{
}
static void prio_changed_dm(struct rq *rq, struct task_struct *p, int oldprio)
{
}

static void update_curr_dm(struct rq *rq)
{
}
void cister_trace(enum evt event, struct task_struct *p)
{
	//this is a filter for collecting DM tasks data
	if(p->policy != SCHED_LIFO)
		return;
	if(enabled){
		unsigned long long time = ktime_to_ns(ktime_get());
		enqueue(event, time, p);
	}
}

const struct sched_class dm_sched_class = {
	.next    = &fair_sched_class,
	.enqueue_task  = enqueue_task_dm,
	.dequeue_task  = dequeue_task_dm,
	.yield_task  = yield_task_dm,
	.check_preempt_curr = check_preempt_curr_dm,
	.pick_next_task  = pick_next_task_dm,
	.put_prev_task  = put_prev_task_dm,
#ifdef CONFIG_SMP
	.select_task_rq  = select_task_rq_dm,
#endif
	.set_curr_task = set_curr_task_dm,
	.task_tick  = task_tick_dm,
	.get_rr_interval = get_rr_interval_dm,
	.prio_changed  = prio_changed_dm,
	.switched_to  = switched_to_dm,
	.update_curr  = update_curr_dm,
};
