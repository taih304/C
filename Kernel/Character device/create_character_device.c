#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>

#define BASE_MINOR              0
#define TOTAL_MINOR_NUMBER      1
#define DEVICE_NAME				"Character device"
#define CLASS_NAME				"Class name"

MODULE_LICENSE("GPL");

dev_t dev_id;

struct cdev *character_device;
struct class *device_class;
struct device *device;

int device_init(void)
{
	int ret;

	ret = alloc_chrdev_region(&dev_id, BASE_MINOR, TOTAL_MINOR_NUMBER, "alloc_chrdev_region");
	if(ret)
	{
		printk("can not register major no\n");
		return ret;
	}
	printk(KERN_INFO "register successfully major now is: %d\n", MAJOR(dev_id));
	character_device = cdev_alloc();
	character_device->owner = THIS_MODULE;
	character_device->dev = dev_id;
	cdev_add(character_device, dev_id, 1);
	device_class = class_create(THIS_MODULE, CLASS_NAME);
	device = device_create(device_class, NULL, dev_id, NULL, DEVICE_NAME);

	return 0;
}

void device_exit(void)
{
	printk("Device remove\n");
	unregister_chrdev_region(dev_id, 0);
	cdev_del(character_device);
	device_destroy(device_class, dev_id);
	class_destroy(device_class);
}

module_init(device_init);
module_exit(device_exit);