#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kfifo.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define MAX_SIZE 1024
struct device *pdev; // global
struct class *pclass;
char *pcur;
char *pbak;
dev_t pdevid;
int ndevices = 5, i;
// int ndevices=1;
typedef struct priv_obj {
  struct cdev cdev;
  struct kfifo kfifo;
  struct device *pdev;
  struct list_head *entry;
} PRIV_OBJ;

PRIV_OBJ *pobj;

for (i = 0; i <= ndevices; i++) {
  pobj = kmalloc(MAX_SIZE, GFP_KERNEL);
  kfifo_alloc(&pobj->kfifo, MAX_SIZE, GFP_KERNEL);
  cdev_init(&cdev, &fops);
  kobject_set_name(&cdev.kobj, "pdevid %d", i);
  ret = cdev_add(&cdev, pdevid + i, 1);
  // cdev_init(&pobj->kfifo,....
  // kobject_set_name
  cdev_add(&pobj->cdev, pdevid + i, 1);
  device_create(pclass, NULL, pdevid + i, NULL, "psample%d", i);
  list_add_tail(&pobj->entry, mydevlist);
}

LIST_HEAD(mydevlist);

module_param(ndevices, int, S_IRUGO);

int pseudo_open(struct inode *inode, struct file *file) {
  struct cdev *cptr = inode->i_cdev;
  PRIV_OBJ *pobj = container_of(cptr, PRIV_OBJ, cdev);
  file->private_data = pobj;
  printk("Pseudo--open method\n");
  return 0;
}
ssize_t pseudo_read(struct file *file, char __user *buf, size_t size,
                    loff_t *off) {
  PRIV_OBJ *pobj = file->private_data;
  printk("Pseudo--read method\n");
  return 0;
}
ssize_t pseudo_write(struct file *file, const char __user *buf, size_t size,
                     loff_t *off) {
  PRIV_OBJ *pobj = file->private_data;
  printk("Pseudo--write method\n");
  return -ENOSPC;
}

struct file_operations fops = {
    .open = pseudo_open,
    //.release = pseudo_close,
    .write = pseudo_write,
    .read = pseudo_read,
};

// pseudo_init:-
static int __init pseudo_init(void) {
  int ret;
  // class_create, alloc_chrdev_region
  ret = alloc_chrdev_region(&pdevid, 0, ndevices, "pseudo_sample");
  if (ret) {
    printk("Pseudo: failed to register driver \n");
    return -EINVAL;
  }
  printk("successfully registered, major=%d ,minor=%d \n ", MAJOR(pdevid),
         MINOR(pdevid));
  printk("Pseudo driver sample ...welcome \n");
  return 0;
}

// pseudo_exit:-

static void __exit pseudo_exit(void) {
  unregister_chrdev_region(pdevid, ndevices);
  printk("psudo driver sample...byr \n");
}

int i = 0;
list_for_each_safe(pcur, pbak, &mydevlist) {
  pobj = list_entry(pcur, PRIV_OBJ, entry);
  kfifo_free(&pobj->kfifo);
  cdev_del(&pobj->cdev);
  device_destroy(pclass, pdevid + i);
  i++;
}
// unregister_chrdev_region, class_destroy
unregister_chrdev_region(pdevid + i, ndevices);
device_destroy(pclass, pdevid + i);
class_destroy(pclass);

module_init(pseudo_init);
module_exit(pseudo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("P saikeerthi");
MODULE_DESCRIPTION("A simple Module not ");
