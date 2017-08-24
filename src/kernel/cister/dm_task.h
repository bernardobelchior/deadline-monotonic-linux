#ifndef __DM_TASK_H_
#define __DM_TASK_H_

struct dm_task{
	int id;
	struct rb_node tree_node;
	unsigned long long deadline;
	 
};
void set_task_id(int id);
#endif
