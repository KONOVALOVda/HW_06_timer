#include <linux/module.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>

#define INTERVAL_SEC 30
#define MAX_MINUTES 5

static struct timer_list my_timer;
static int count = 0;

static void timer_callback(struct timer_list *t)
{
    int min = count / 2; // каждые 30 сек = 0.5 мин
    if (count >= MAX_MINUTES * 2)
        return;

    pr_info("min=%d: Hello, timer!\n", min);

    count++;
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(INTERVAL_SEC * 1000));
}

static int __init timer_init(void)
{
    pr_info("Timer module loaded\n");
    timer_setup(&my_timer, timer_callback, 0);
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(INTERVAL_SEC * 1000));
    return 0;
}

static void __exit timer_exit(void)
{
    del_timer_sync(&my_timer);
    pr_info("Timer module unloaded\n");
}

module_init(timer_init);
module_exit(timer_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("HW");
MODULE_DESCRIPTION("Timer example: prints message every 30s for 5 minutes");
