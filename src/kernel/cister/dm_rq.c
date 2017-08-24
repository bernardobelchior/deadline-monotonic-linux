#include "dm_rq.h"

void init_dm_rq(struct dm_rq *rq)
{
	rq->root = RB_ROOT;
	spin_lock_init(&rq->lock);
	rq->task = NULL;
}