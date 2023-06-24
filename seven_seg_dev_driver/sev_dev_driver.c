#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/gpio/consumer.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/mod_devicetable.h>
#include <linux/property.h>
#include <linux/platform_device.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>

#define MY_NAME "seven_seg_leds"
/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Minh");
MODULE_DESCRIPTION("A hello world LKM");

struct seven_seg_gpios{
    unsigned char val;
    struct gpio_desc *leds[7];
};

static struct seven_seg_gpios* my_led_gpios = NULL;
/* Declate the probe and remove functions */
static int dt_probe(struct platform_device *pdev);
static int dt_remove(struct platform_device *pdev);
/* Declare file operations for misc device*/
static ssize_t gpios_read(struct file *File, char *user_buffer, size_t count, loff_t *offs);
static ssize_t gpios_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs);
static int gpios_open(struct inode *inode, struct file *filp);
static int gpios_close(struct inode *inode, struct file *filp);
static struct of_device_id my_driver_ids[] = {
	{
		.compatible = "my_dev_gpio",
	}, { /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, my_driver_ids);

static struct platform_driver my_driver = {
	.probe = dt_probe,
	.remove = dt_remove,
	.driver = {
		.name = "my_device_driver",
		.of_match_table = my_driver_ids,
        .owner = THIS_MODULE
	},
    
};
static struct file_operations gpios_dev_fops = {
    .owner = THIS_MODULE,
    .read = gpios_read,
    .write = gpios_write,
	.open = gpios_open,
    .release = gpios_close
};
static struct miscdevice sev_gpios_misc = {
    .minor = MISC_DYNAMIC_MINOR, 
    .name = "seven_seg_disp", 
    .fops = &gpios_dev_fops,
};
void setting_leds(unsigned char num){
	switch (num)
	{
	case '0':
		{
			gpiod_set_value(my_led_gpios->leds[0], 1);
			gpiod_set_value(my_led_gpios->leds[1], 1);
			gpiod_set_value(my_led_gpios->leds[2], 1);
			gpiod_set_value(my_led_gpios->leds[3], 1);
			gpiod_set_value(my_led_gpios->leds[4], 1);
			gpiod_set_value(my_led_gpios->leds[5], 1);
			gpiod_set_value(my_led_gpios->leds[6], 0);
			
			break;
		}
	case '1':
		{
			gpiod_set_value(my_led_gpios->leds[0], 0);
			gpiod_set_value(my_led_gpios->leds[1], 1);
			gpiod_set_value(my_led_gpios->leds[2], 1);
			gpiod_set_value(my_led_gpios->leds[3], 0);
			gpiod_set_value(my_led_gpios->leds[4], 0);
			gpiod_set_value(my_led_gpios->leds[5], 0);
			gpiod_set_value(my_led_gpios->leds[6], 0);
			break;
		}
	case '2':
		{
			gpiod_set_value(my_led_gpios->leds[0], 1);
			gpiod_set_value(my_led_gpios->leds[1], 1);
			gpiod_set_value(my_led_gpios->leds[2], 0);
			gpiod_set_value(my_led_gpios->leds[3], 1);
			gpiod_set_value(my_led_gpios->leds[4], 1);
			gpiod_set_value(my_led_gpios->leds[5], 0);
			gpiod_set_value(my_led_gpios->leds[6], 1);
			break;
		}
	case '3':
		{
			gpiod_set_value(my_led_gpios->leds[0], 1);
			gpiod_set_value(my_led_gpios->leds[1], 1);
			gpiod_set_value(my_led_gpios->leds[2], 1);
			gpiod_set_value(my_led_gpios->leds[3], 1);
			gpiod_set_value(my_led_gpios->leds[4], 0);
			gpiod_set_value(my_led_gpios->leds[5], 0);
			gpiod_set_value(my_led_gpios->leds[6], 1);
			break;
		}
	case '4':
		{
			gpiod_set_value(my_led_gpios->leds[0], 0);
			gpiod_set_value(my_led_gpios->leds[1], 1);
			gpiod_set_value(my_led_gpios->leds[2], 1);
			gpiod_set_value(my_led_gpios->leds[3], 0);
			gpiod_set_value(my_led_gpios->leds[4], 0);
			gpiod_set_value(my_led_gpios->leds[5], 1);
			gpiod_set_value(my_led_gpios->leds[6], 1);
			break;
		}
	case '5':
		{
			gpiod_set_value(my_led_gpios->leds[0], 1);
			gpiod_set_value(my_led_gpios->leds[1], 0);
			gpiod_set_value(my_led_gpios->leds[2], 1);
			gpiod_set_value(my_led_gpios->leds[3], 1);
			gpiod_set_value(my_led_gpios->leds[4], 0);
			gpiod_set_value(my_led_gpios->leds[5], 1);
			gpiod_set_value(my_led_gpios->leds[6], 1);
			break;
		}
	case '6':
		{
			gpiod_set_value(my_led_gpios->leds[0], 1);
			gpiod_set_value(my_led_gpios->leds[1], 0);
			gpiod_set_value(my_led_gpios->leds[2], 1);
			gpiod_set_value(my_led_gpios->leds[3], 1);
			gpiod_set_value(my_led_gpios->leds[4], 1);
			gpiod_set_value(my_led_gpios->leds[5], 1);
			gpiod_set_value(my_led_gpios->leds[6], 1);
			break;
		}
	case '7':
		{
			gpiod_set_value(my_led_gpios->leds[0], 1);
			gpiod_set_value(my_led_gpios->leds[1], 1);
			gpiod_set_value(my_led_gpios->leds[2], 1);
			gpiod_set_value(my_led_gpios->leds[3], 0);
			gpiod_set_value(my_led_gpios->leds[4], 0);
			gpiod_set_value(my_led_gpios->leds[5], 0);
			gpiod_set_value(my_led_gpios->leds[6], 0);
			break;
		}
	case '8':
		{
			gpiod_set_value(my_led_gpios->leds[0], 1);
			gpiod_set_value(my_led_gpios->leds[1], 1);
			gpiod_set_value(my_led_gpios->leds[2], 1);
			gpiod_set_value(my_led_gpios->leds[3], 1);
			gpiod_set_value(my_led_gpios->leds[4], 1);
			gpiod_set_value(my_led_gpios->leds[5], 1);
			gpiod_set_value(my_led_gpios->leds[6], 1);
			break;
		}
	case '9':
		{
			gpiod_set_value(my_led_gpios->leds[0], 1);
			gpiod_set_value(my_led_gpios->leds[1], 1);
			gpiod_set_value(my_led_gpios->leds[2], 1);
			gpiod_set_value(my_led_gpios->leds[3], 1);
			gpiod_set_value(my_led_gpios->leds[4], 0);
			gpiod_set_value(my_led_gpios->leds[5], 1);
			gpiod_set_value(my_led_gpios->leds[6], 1);
			break;
		}
	default:
		pr_info("Invalide number: %d\n",num);
		break;
	}
}
static ssize_t gpios_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs){
    int to_copy, err;
	unsigned char value;

	pr_info("count = %d\n",count);
	/* Get amount of data to copy */
	to_copy = min(count, sizeof(value));

	/* Copy data from user */
	err = copy_from_user(&value, user_buffer, to_copy);
	if(err){
		pr_err("Cannot copy from user\n");
		return -EFAULT; 
	}
	my_led_gpios->val = value ;
	
	/* Setting the LED */
	setting_leds(my_led_gpios->val);
	*offs += to_copy;
	
    pr_info("Value receive from user: %d\n",value);
    return to_copy;
}

/**/
static ssize_t gpios_read(struct file *File, char *user_buffer, size_t count, loff_t *offs){
    int to_copy, err;
	unsigned char value = my_led_gpios->val;

	/* Get amount of data to copy */
	to_copy = min(count, sizeof(value));

	/* Copy data to user */
	err = copy_to_user(user_buffer, &value ,to_copy);
	if(err){
		pr_err("Cannot copy to user\n");
		return -EFAULT; 
	}
	
    pr_info("Value send to user: %d\n",value);
	
   
    return 0;
}
static int gpios_open(struct inode *inode, struct file *filp){
	pr_info("Open device driver\n");
	
	pr_info("misc_test - Device Numbers: %d %d\n", imajor(inode), iminor(inode));
	if(filp->f_mode & FMODE_READ) 
		pr_info("misc_test - Open called with read permissions\n");
	if(filp->f_mode & FMODE_WRITE) 
		pr_info("misc_test - Open called with write permissions\n");
	return 0;
	
}
static int gpios_close(struct inode *inode, struct file *filp){
	pr_info("Close device driver\n");
	return 0;
}

/**
 * @brief This function is called on loading the driver 
 */
static int dt_probe(struct platform_device *pdev) {
	struct device *dev = &pdev->dev;
	const char *label;
	int my_value, ret;

	pr_info("dt_probe - Now I am in the probe function!\n");
     /* Register the misc device with the kernel */
    misc_register(&sev_gpios_misc);

    //Allocate memory
    my_led_gpios = kzalloc(sizeof(struct seven_seg_gpios),GFP_KERNEL);
    
    if(!my_led_gpios){
        return -ENOMEM;
    }
    my_led_gpios->val = 0;

	/* Check for device properties */
	if(!device_property_present(dev, "label")) {
		pr_err("dt_probe - Error! Device property 'label' not found!\n");
		return -1;
	}
	if(!device_property_present(dev, "my_value")) {
		pr_err("dt_probe - Error! Device property 'my_value' not found!\n");
		return -1;
	}

	/* Read device properties */
	ret = device_property_read_string(dev, "label", &label);
	if(ret) {
		pr_err("dt_probe - Error! Could not read 'label'\n");
		return -1;
	}
	pr_info("dt_probe - label: %s\n", label);
	ret = device_property_read_u32(dev, "my_value", &my_value);
	if(ret) {
		pr_err("dt_probe - Error! Could not read 'my_value'\n");
		return -1;
	}
	pr_info("dt_probe - my_value: %d\n", my_value);

   if(!device_property_present(dev, "seven-seg-gpios")) {
		pr_err("dt_gpio - Error! Device property 'seven-seg-gpios' not found!\n");
		return -1;
	}
    
	
    for(int i = 0 ;i < 7 ;i++){
        my_led_gpios->leds[i] = gpiod_get_index(dev,"seven-seg",i ,GPIOD_OUT_LOW);
        if(IS_ERR( my_led_gpios->leds[i])){
            dev_err(dev, "Could not get gpio %d\n", i);
            kfree(my_led_gpios);
            return PTR_ERR( my_led_gpios->leds[i]);
        }
	
    }
	
    
	return 0;
}

/**
 * @brief This function is called on unloading the driver 
 */
static int dt_remove(struct platform_device *pdev) {
	struct device *dev = &pdev->dev;
	pr_info("dt_probe - Now I am in the remove function\n");
	
    for(int i = 0 ;i < 7 ;i++){
        gpiod_put(my_led_gpios->leds[i]);
    }
   
   
	kfree(my_led_gpios);
	misc_deregister(&sev_gpios_misc);
	return 0;
}

/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init my_init(void) {
	pr_info("dt_probe - Loading the driver...\n");
    
	if(platform_driver_register(&my_driver)) {
		pr_err("dt_probe - Error! Could not load driver\n");
		return -1;
	}

	return 0;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit my_exit(void) {
	pr_info("dt_probe - Unload driver");
	platform_driver_unregister(&my_driver);
}

module_init(my_init);
module_exit(my_exit);