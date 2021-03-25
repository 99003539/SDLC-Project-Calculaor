#include <linux/fs.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
dev_t pdevid;
int ndevices=1;

static int __init pseudo_init(void)
{
  int ret;
  ret=alloc_chrdev_region(&pdevid, 0, ndevices, "pseudo_sample");
  if(ret)
    {
       printk("Pseudo: failed to register driver \n");
       return  -EINVAL;
     }
   printk("successfully registered, major=%d ,minor=%d \n ",MAJOR(pdevid), MINOR(pdevid));
   printk("Pseudo driver sample ...welcome \n");
   return 0;
}
static void __exit pseudo_exit(void)
{
  unregister_chrdev_region(pdevid, ndevices);
  printk("psudo driver sample...byr \n");
}
module_init(pseudo_init);
module_exit(pseudo_exit);
MODULE_LICENSE("GPL");

