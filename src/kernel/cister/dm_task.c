#include <linux/sched.h>
#include "lf_task.h"

void set_task_id(int id){
	current->lf_task.id = id;
}
