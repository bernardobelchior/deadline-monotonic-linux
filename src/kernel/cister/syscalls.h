#ifndef __SYSCALLS_H
#define __SYSCALLS_H

asmlinkage long sys_cister_tracing(int enable);

asmlinkage long sys_cister_set_task_id(int id);

#endif 
