#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/module.h>
#include <asm/uaccess.h>

#define DEV_NAME "fibdev"
#define MSG_LEN 80
#define SUCCESS 0

static int fibdev_open(struct inode*, struct file*) ;
static int fibdev_release(struct inode*, struct file *) ;
static ssize_t fibdev_read(struct file*, char*, size_t, loff_t*) ;
static ssize_t fibdev_write(struct file*, const char*, size_t, loff_t*) ;

static int major_number ;
static int dev_open = 0 ;
static char msg[MSG_LEN] ;
static char* pMsg = 0 ;
static int fib_counter = 0 ;

static struct file_operations fops = {
  .open = fibdev_open,
  .read = fibdev_read,
  .write = fibdev_write,
  .release = fibdev_release
} ;

static int fibonacci_series(int n)
{
  if ((n == 0) || (n == 1))
    return n ;
  else
    return fibonacci_series(n - 1) + fibonacci_series(n - 2) ;
}

static int fibdev_init(void)
{
  major_number = register_chrdev(0, DEV_NAME, &fops) ;
  if (major_number < 0) {
    printk(KERN_ALERT "Registering char device %s with major number %d failed!\n", DEV_NAME, major_number) ;
    return major_number ;
  }

  printk(KERN_INFO "fibdev registered with kernel, to cat from and echo to,\n") ;
  printk(KERN_INFO "create a device file with 'mknod /dev/%s c %d 0',\n", DEV_NAME, major_number) ;
  printk(KERN_INFO "remove the device file when done.\n") ;

  return SUCCESS ;
}

static void fibdev_exit(void)
{
  unregister_chrdev(major_number, DEV_NAME) ;
  printk(KERN_ALERT "Unregistering char device %s with major number %d.\n", DEV_NAME, major_number) ;
}

static int fibdev_open(struct inode* inode, struct file* file)
{
  if (dev_open)
    return -EBUSY ;

  ++dev_open ;

  sprintf(msg, "Fibonacci series number %d = %d\n", fib_counter, fibonacci_series(fib_counter)) ;
  pMsg = msg ;
  ++fib_counter ;

  try_module_get(THIS_MODULE) ;

  return SUCCESS ;
}

static int fibdev_release(struct inode* inode, struct file* file)
{
  --dev_open ;
  module_put(THIS_MODULE) ;
  return SUCCESS ;
}

static ssize_t fibdev_read(struct file* filep, char* buffer, size_t length, loff_t* offset)
{
  int bytesRead = 0 ;

  if (*pMsg == 0)
    return 0 ;

  while (length && *pMsg) {
    put_user(*(pMsg++), buffer++) ;
    --length ;
    ++bytesRead ;
  }

  return bytesRead ;
}

static ssize_t fibdev_write(struct file* filep, const char* buffer, size_t length, loff_t* offset)
{
  int result ;
  char localBuffer[MSG_LEN] = {0} ;
  copy_from_user(localBuffer, buffer, length) ;

  if (sscanf(localBuffer, "%d", &result) != -1) {
    fib_counter = result ;
    return strlen(localBuffer) ;
  }
  else {
    printk( KERN_ALERT "Cannot convert %s to a number.\n", localBuffer) ;
    return -EINVAL ;
  }
}

module_init(fibdev_init) ;
module_exit(fibdev_exit) ;

MODULE_AUTHOR("Razmig KECHICHIAN") ;
MODULE_LICENSE("GPL") ;
MODULE_DESCRIPTION("Simple character device that returns the next number in Fibonacci series and can be initialized.") ;
