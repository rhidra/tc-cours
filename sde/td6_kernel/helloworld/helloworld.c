#include <linux/kernel.h>
#include <linux/module.h>
 
static int greet(void)
{
    printk(KERN_INFO "Hello, World!\n") ;
      return 0 ;
}
 
static void farewell(void)
{
    printk(KERN_INFO "Goodbye, World!\n") ;
}
 
module_init(greet);
module_exit(farewell);
 
MODULE_AUTHOR("Razmig K");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Prints Hello World upon loading, and Goodbye World upon unloading.");
