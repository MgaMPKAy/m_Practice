#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/tty.h>
MODULE_LICENSE("GPL");

void tty_write_messgae1(struct tty_struct *, char *);
static int my_init(void)
{
	char *msg = "Hello tty!";
	struct task_struct *task;
	struct list_head *list;
	
	printk("Info of current process\n");	
	printk("pid = %d(%s)\n", current->pid, current->comm);
	printk("ppid = %d(%s)\n", current->parent->pid,
	       current->parent->comm);
	printk("prio = %d, static_prio = %d, normal_prio = %d\n",
	       current->prio, current->static_prio,
	       current->normal_prio);
	printk("exit_state = %d, exit_code = %d\n",
	       current->exit_state, current->exit_code);
	printk("group_leader = %d(%s)\n", current->group_leader->pid,
	       current->group_leader->comm);
	printk("state = %ld\n", current->state);
	printk("flags = %hd\n", current->flags);
	printk("ptrace = %hd\n", current->ptrace);
	printk("lock_depth = %hd\n", current->lock_depth);
	
	for_each_process(task){
		if (strcmp(task->comm, "bash") == 0)
			printk("%d(%s)\n", task->pid, task->comm);	
	}
	
	return 0;
}

static void my_cleanup(void)
{
	printk("Goodbye, from the kernel...\n");
}

module_init(my_init);
module_exit(my_cleanup);

void tty_write_messgae1(struct tty_struct *tty, char *msg)
{
	if (tty && tty->driver->ops->write)
		tty->driver->ops->write(tty, msg, strlen(msg));
	return;
}
