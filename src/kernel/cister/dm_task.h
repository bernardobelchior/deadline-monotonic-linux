#ifndef __DM_TASK_H_
#define __DM_TASK_H_

struct dm_task{
	struct list_head node;
};
void set_task_id(int id);
#endif
