#include <linux/module.h>
#include <linux/init.h>
#include <linux/sysfs.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/gpio/consumer.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/mod_devicetable.h>
#include <linux/property.h>
#include <linux/platform_device.h>
#include <linux/device.h>


#define MY_NAME "seven_seg_leds"
/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Minh");
MODULE_DESCRIPTION("A platform driver with sysfs ");

struct seven_seg_gpios{
    unsigned char val;
    struct gpio_desc *leds[7];
};

static struct seven_seg_gpios* my_led_gpios = NULL;
/* Declate the probe and remove functions */
static int dt_probe(struct platform_device *pdev);
static int dt_remove(struct platform_device *pdev);
/* Declare the read and write functions for sysfs class */
static ssize_t my_show(struct class *class, struct class_attribute *attr,char *buf); // To read
static ssize_t my_store(struct class *class, struct class_attribute *attr,
			const char *buf, size_t count); // To write

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
		.name = "my_sysfs_driver",
		.of_match_table = my_driver_ids,
        .owner = THIS_MODULE
	},
    
};
static const struct class_attribute class_attr_myleds =__ATTR(myleds, 0644, my_show, my_store);
void setting_leds(unsigned char num){
	switch (num)
	{
	case 0:
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
	case 1:
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
	case 2:
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
	case 3:
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
	case 4:
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
	case 5:
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
	case 6:
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
	case 7:
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
	case 8:
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
	case 9:
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
/**
* @brief This function is to write when open file driver
*/
static ssize_t my_store(struct class *class, struct class_attribute *attr, const char *buf, size_t count){
    int var, ret;
    ret = kstrtoint(buf, 10, &var);
    if (ret) {
        /* Negative error code. */
        pr_info("ko = %d\n", ret);
        return ret;
    } else {
        pr_info("ok = %d\n", var);
        my_led_gpios->val = var;
        setting_leds(my_led_gpios->val);
        
        return count;
    }
    
   
}

/**
* @brief This function is to read when open file driver
*/
static ssize_t my_show(struct class *class, struct class_attribute *attr,char *buf){
	int err;
    err = scnprintf(buf, PAGE_SIZE,"%d\n", my_led_gpios->val);
	pr_info("buf: %s\n", buf);
	pr_info("buf[0]: %c\n",buf[0]);
	pr_info("buf[1]: %c\n",buf[1]);
	pr_info("buf[1]_n: %d\n", buf[1]);
	pr_info("buf[2]: %c\n",buf[2]);
	pr_info("err = %d\n",err);
	return err;
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
    

    //Allocate memory
    my_led_gpios =  devm_kzalloc(dev ,sizeof(struct seven_seg_gpios),GFP_KERNEL);
    
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
            return PTR_ERR( my_led_gpios->leds[i]);
        }
	
    }
    /*Create entry /sys/class/sev_leds */
	dev->class = class_create(THIS_MODULE,"sev_leds");
    if(IS_ERR(dev->class)){
        pr_err("Device class can not be created!\n");
		return PTR_ERR(dev->class);
    }
    ret = class_create_file(dev->class, &class_attr_myleds);
    if(ret){
        pr_err("class file can not be created!\n");
        goto ClassError;
    }
    
	return 0;
ClassError:
    class_destroy(dev->class);
    return -1;
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
 
   class_remove_file(dev->class, &class_attr_myleds);
	class_destroy(dev->class);
	return 0;
}

/* Register for platform driver */
module_platform_driver(my_driver);