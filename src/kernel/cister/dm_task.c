#include <linux/sched.h>
#include "dm_task.h"

void set_task_id(int id){
	current->dm_task.id = id;
}
