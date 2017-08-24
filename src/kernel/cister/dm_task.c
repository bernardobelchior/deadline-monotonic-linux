#include <linux/sched.h>
#include "dm_task.h"

void set_task_id(int id)
{
	current->dm_task.id = id;
}

void set_task_deadline(unsigned long long deadline)
{
	current->dm_task.deadline = deadline;
}