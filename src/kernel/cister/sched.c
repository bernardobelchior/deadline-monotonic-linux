#include "../sched/sched.h"

/*
* Deadline Monotonic scheduling class.
* Implements SCHED_DM
*/
static void enqueue_task_dm(struct rq *rq, struct task_struct *p, int flags)
{

	spin_lock(&rq->dm_rq.lock);
	
	//inserts the new rb node into the existing tree
	rb_insert_node_item(&rq->dm_rq.root,p.deadline);
	
	//Updates the current task with the lower priority in the tree
	rq->dm_rq.task = rb_first(&rq->dm_rq.root);
	
	spin_unlock(&rq->dm_rq.lock);

#ifdef CONFIG_CISTER_TRACING
	cister_trace(ENQUEUE_RQ,p);
#endif
}

static void dequeue_task_dm(struct rq *rq, struct task_struct *p, int flags)
{
	struct dm_task *t = NULL;
	spin_lock(&rq->dm_rq.lock);
	rb_erase_node_item(&p->rb_node,&rq->dm_rq.root);
	
	//Updates the current task with the lower priority in the tree
	rq->dm_rq.task = rb_first(&rq->dm_rq.root);
	
	spin_unlock(&rq->dm_rq.lock);
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
		case SCHED_DM:
			resched_curr(rq);
			break;
	}
}

static struct task_struct *pick_next_task_dm(struct rq *rq, struct task_struct *prev, struct rq_flags *rf)
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
static int select_task_rq_dm(struct task_struct *p, int _task_cpu, int sd_flag, int flags)
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

void rb_insert_node_item(struct rb_root * root, struct task_struct *p){
	struct rb_node ** n = &root->rb_node;
	struct rb_node * parent = NULL;
	struct rb_node * source = &p->tree_node;
	
	//our task structure to access deadline field??
	struct dm_task * ans; 
	
	//foreach node
	while(*n){
		parent =*n;
		//getting the current node task 
		ans = rb_entry(parent,struct dm_task, node);
		//if new task deadline is earlier than the deadline obtained from current node??
		if(p.deadline <= ans->deadline)
			n = &parent->rb_left;
		else if	(target > ans->deadline)
			n = &parent->rb_right;
	}
	
	//source = (struct node_item*)kmalloc(sizeof(struct struct node_item),GFP_KERNEL);
	
	rb_link_node(source, parent, n);
	//Insert this new node as a red leaf.
	rb_insert_color(source, root);
	//Rebalance the tree, finish inserting
	 
}

void rb_erase_node_item(struct rb_node* source,struct rb_root* root){
	struct dm_task * target;
	target = rb_entry(source,struct dm_task, node);
	rb_erase(source, root);
	//Erase the node
	kfree(target);
	//Free the memory
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
