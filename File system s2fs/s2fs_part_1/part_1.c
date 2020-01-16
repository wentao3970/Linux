#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <asm/current.h>
#include <linux/list.h>

MODULE_LICENSE("GPL");

void getProcessInfo(struct task_struct* task, int indent);

static int mod_init(void){

    struct task_struct *task=current;
    int indent = 0;

    while(task->pid != 0 ){
        task=task->parent;
    }

    printk(KERN_INFO "%*s  %s [%i] \n", 0, "", task->comm, task->pid);
    //printk(KERN_INFO "%*s  %s [%i] \n", indent + 2, "", task->comm, task->pid);
    getProcessInfo(task, indent + 2);
    return 0; 
}

static void mod_exit(void)
{
}

void getProcessInfo(struct task_struct* task, int indent){

    struct list_head *children_tasks;

    children_tasks = &(task->children);

    list_for_each(children_tasks, &(task->children)){

        struct task_struct *child_task;

        child_task = list_entry(children_tasks, struct task_struct, sibling);
        printk(KERN_INFO "%*s  %s [%i] \n", indent, "", child_task->comm, child_task->pid);
        getProcessInfo(child_task, indent+2);
    }
}

module_init(mod_init);
module_exit(mod_exit);
