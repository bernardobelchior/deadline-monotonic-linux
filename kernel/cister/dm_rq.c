#include "dm_rq.h"

void init_dm_rq(struct dm_rq *rq)
{
	INIT_LIST_HEAD(&rq->tasks);
	spin_lock_init(&rq->lock);
	rq->task = NULL;
}