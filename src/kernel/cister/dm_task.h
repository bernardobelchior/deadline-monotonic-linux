#ifndef __DM_TASK_H_
#define __DM_TASK_H_

struct dm_task{
	struct list_head node;
	int id;
};
void set_task_id(int id);
#endif
