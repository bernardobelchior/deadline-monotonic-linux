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