// 简化版：用 host gcc 编译，加 kernel 头文件路径
// 不需要 oplus vendor 那些 broken include
#include <linux/sched.h>
#include <linux/cred.h>
#include <linux/seccomp.h>
#include <linux/sched/signal.h>
#include <linux/sched/task.h>
#include <linux/mm_types.h>
#include <linux/fs.h>
#include <linux/pipe_fs_i.h>
#include <linux/sysctl.h>
#include <linux/types.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <linux/rbtree.h>
#include <linux/rculist.h>
#include <linux/refcount.h>
#include <linux/init_task.h>
#include <linux/cpumask.h>
#include <linux/sched/cputime.h>
#include <linux/sched/topology.h>
#include <linux/sched/sysctl.h>
#include <linux/sched/nohz.h>
#include <linux/sched/debug.h>
#include <linux/sched/isolation.h>
#include <linux/sched/stat.h>
#include <linux/rtmutex.h>
#include <linux/sched/wake_q.h>
#include <linux/sched/autogroup.h>
#include <net/sock.h>
#include <linux/android_kabi.h>
#include <uapi/linux/sched/types.h>
#include <uapi/linux/seccomp.h>
#include <uapi/linux/ioprio.h>
#include <uapi/linux/resource.h>
#include <linux/key.h>
#include <linux/seq_file.h>
#include <linux/perf_event.h>
#include <linux/hrtimer.h>
#include <linux/timer.h>
#include <linux/nsproxy.h>
#include <linux/audit.h>
#include <linux/poll.h>
#include <linux/resource.h>
#include <linux/kcov.h>
#include <linux/sched_clock.h>
#include <linux/rseq.h>
#include <linux/uaccess.h>
#include <asm/processor.h>
#include <asm/thread_info.h>
#include <asm/current.h>
#include <linux/livepatch.h>
#include <linux/security.h>
#include <linux/capability.h>
#include <linux/lockdep.h>
#include <linux/spinlock_types.h>
#include <linux/posix-timers.h>
#include <linux/cgroup.h>
#include <linux/user_namespace.h>
#include <linux/atomic.h>
#include <linux/ftrace.h>
#include <linux/completion.h>
#include <linux/wait.h>
#include <linux/workqueue.h>
#include <linux/taskstats_kern.h>
#include <linux/cpuidle.h>

#define OFF(s, f) printf("#define %-45s 0x%03lx\n", #s "_" #f "_OFF", (unsigned long)__builtin_offsetof(struct s, f))
#define SIZE(s)   printf("#define SIZEOF_%s 0x%lx\n", #s, (unsigned long)sizeof(struct s))

int main(void) {
    SIZE(task_struct);
    OFF(task_struct, thread_info);
    OFF(task_struct, __state);
    OFF(task_struct, stack);
    OFF(task_struct, usage);
    OFF(task_struct, flags);
    OFF(task_struct, ptrace);
    OFF(task_struct, on_cpu);
    OFF(task_struct, prio);
    OFF(task_struct, static_prio);
    OFF(task_struct, normal_prio);
    OFF(task_struct, rt_priority);
    OFF(task_struct, se);
    OFF(task_struct, rt);
    OFF(task_struct, dl);
    OFF(task_struct, sched_class);
    OFF(task_struct, sched_task_group);
    OFF(task_struct, stats);
    OFF(task_struct, policy);
    OFF(task_struct, cpus_mask);
    OFF(task_struct, nr_cpus_allowed);
    OFF(task_struct, sched_info);
    OFF(task_struct, tasks);
    OFF(task_struct, pushable_tasks);
    OFF(task_struct, mm);
    OFF(task_struct, active_mm);
    OFF(task_struct, exit_state);
    OFF(task_struct, exit_code);
    OFF(task_struct, exit_signal);
    OFF(task_struct, pdeath_signal);
    OFF(task_struct, jobctl);
    OFF(task_struct, personality);
    OFF(task_struct, atomic_flags);
    OFF(task_struct, pid);
    OFF(task_struct, tgid);
    OFF(task_struct, real_parent);
    OFF(task_struct, parent);
    OFF(task_struct, children);
    OFF(task_struct, sibling);
    OFF(task_struct, group_node);
    OFF(task_struct, comm);
    OFF(task_struct, real_cred);
    OFF(task_struct, cred);
    OFF(task_struct, seccomp);
    OFF(task_struct, seccomp_mode);
    OFF(task_struct, pi_lock);
    OFF(task_struct, pi_waiters);
    OFF(task_struct, pi_top_task);
    OFF(task_struct, pi_blocked_on);

    printf("\n");
    SIZE(cred);
    OFF(cred, usage);
    OFF(cred, uid);
    OFF(cred, gid);
    OFF(cred, suid);
    OFF(cred, sgid);
    OFF(cred, euid);
    OFF(cred, egid);
    OFF(cred, fsuid);
    OFF(cred, fsgid);
    OFF(cred, securebits);
    OFF(cred, cap_inheritable);
    OFF(cred, cap_permitted);
    OFF(cred, cap_effective);
    OFF(cred, cap_bset);
    OFF(cred, cap_ambient);
    OFF(cred, user);
    OFF(cred, user_ns);
    OFF(cred, group_info);
    OFF(cred, rcu);
    OFF(cred, security);

    printf("\n");
    SIZE(rt_mutex_waiter);
    OFF(rt_mutex_waiter, tree_entry);
    OFF(rt_mutex_waiter, pi_tree_entry);
    OFF(rt_mutex_waiter, task);
    OFF(rt_mutex_waiter, lock);
    OFF(rt_mutex_waiter, wake_state);
    OFF(rt_mutex_waiter, prio);
    OFF(rt_mutex_waiter, deadline);
    OFF(rt_mutex_waiter, ww_ctx);

    printf("\n");
    SIZE(file_operations);
    OFF(file_operations, owner);
    OFF(file_operations, llseek);
    OFF(file_operations, read);
    OFF(file_operations, write);
    OFF(file_operations, read_iter);
    OFF(file_operations, write_iter);
    OFF(file_operations, iopoll);
    OFF(file_operations, iterate);
    OFF(file_operations, iterate_shared);
    OFF(file_operations, poll);
    OFF(file_operations, unlocked_ioctl);
    OFF(file_operations, compat_ioctl);
    OFF(file_operations, mmap);
    OFF(file_operations, open);
    OFF(file_operations, flush);
    OFF(file_operations, release);
    OFF(file_operations, fsync);
    OFF(file_operations, fasync);
    OFF(file_operations, lock);
    OFF(file_operations, get_unmapped_area);
    OFF(file_operations, check_flags);
    OFF(file_operations, setfl);
    OFF(file_operations, splice_read);
    OFF(file_operations, splice_write);
    OFF(file_operations, setlease);
    OFF(file_operations, show_fdinfo);

    printf("\n");
    SIZE(ctl_table);
    OFF(ctl_table, procname);
    OFF(ctl_table, data);
    OFF(ctl_table, maxlen);
    OFF(ctl_table, mode);
    OFF(ctl_table, child);
    OFF(ctl_table, proc_handler);
    OFF(ctl_table, extra1);
    OFF(ctl_table, extra2);

    printf("\n");
    SIZE(seccomp);
    OFF(seccomp, mode);
    OFF(seccomp, filter);

    printf("\n");
    SIZE(file);
    OFF(file, f_op);
    OFF(file, private_data);
    OFF(file, f_inode);
    OFF(file, f_cred);

    printf("\n");
    SIZE(struct vm_operations_struct);
    OFF(struct vm_operations_struct, open);
    OFF(struct vm_operations_struct, close);
    OFF(struct vm_operations_struct, fault);
    OFF(struct vm_operations_struct, page_mkwrite);
    OFF(struct vm_operations_struct, access);
    OFF(struct vm_operations_struct, name);
    OFF(struct vm_operations_struct, mremap);

    return 0;
}
