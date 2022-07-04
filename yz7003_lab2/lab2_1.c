#include <linux/init.h>
#include <linux/module.h>
#include<linux/jiffies.h>
#include<linux/time.h>
MODULE_LICENSE("Dual BSD/GPL");
unsigned long j;
unsigned long  init_time;
static int hello_init(void)
{
unsigned long  msec;
j = jiffies;
init_time = ktime_divns(ktime_get_boottime(), NSEC_PER_MSEC);
msec = j * 1000 / HZ;
printk(KERN_ALERT "Hello, world %ld msec\n", msec);

return 0;
}
static void hello_exit(void)
{
unsigned long j_diff, msec_diff1, exit_time, msec_diff2;
j_diff = jiffies - j;
msec_diff1 = j_diff * 1000 / HZ;
exit_time = ktime_divns(ktime_get_boottime(), NSEC_PER_MSEC);
msec_diff2 = exit_time - init_time;
printk(KERN_ALERT "Goodbye, cruel world %ld msec difference1 % ld msec difference2\n", msec_diff1, msec_diff2);
}
module_init(hello_init);
module_exit(hello_exit);
