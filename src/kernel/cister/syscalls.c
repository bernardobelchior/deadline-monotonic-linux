#include <linux/syscalls.h>
#include "trace.h"

asmlinkage long sys_cister_tracing(int enable)
{

#ifdef CONFIG_CISTER_TRACING
	enable_tracing(enable);
#endif

	return 0;
}

asmlinkage long sys_cister_set_task_id(int pid)
{

#ifdef CONFIG_CISTER_SCHED_DM_POLICY
	set_task_id(pid);
#endif

	return 0;
}
