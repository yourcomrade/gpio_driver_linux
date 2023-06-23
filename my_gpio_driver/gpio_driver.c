#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio/consumer.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/mod_devicetable.h>
#include <linux/property.h>
#include <linux/platform_device.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Minh");
MODULE_DESCRIPTION("A simple platform gpio driver");

/* Declate the probe and remove functions */
static int dt_probe(struct platform_device *pdev);
static int dt_remove(struct platform_device *pdev);

static struct of_device_id my_driver_ids[] = {
	{
		.compatible = "my_dev_gpio",
	}, { /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, my_driver_ids);
/*Declare gpio dexcriptor */
static struct gpio_desc* led = NULL;
static struct platform_driver my_driver = {
	.probe = dt_probe,
	.remove = dt_remove,
	.driver = {
		.name = "my_device_driver",
		.of_match_table = my_driver_ids,
        .owner = THIS_MODULE
	},
    
};


/**
 * @brief This function is called on loading the driver 
 */
static int dt_probe(struct platform_device *pdev) {
	struct device *dev = &pdev->dev;
	const char *label;
	int my_value, ret;

	pr_info("dt_probe - Now I am in the probe function!\n");

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

   if(!device_property_present(dev, "led-gpio")) {
		pr_err("dt_gpio - Error! Device property 'led-gpio' not found!\n");
		return -1;
	}

    led = gpiod_get(dev,"led",GPIOD_OUT_LOW);
    if(IS_ERR(led)){
        pr_err("Cannot set up GPIO\n");
        return -1;
    }
	ret = gpiod_export(led,0);
	if(ret){
        pr_err("Cannot export GPIO\n");
        return -1;
    }
	ret = gpiod_export_link(dev,"led_gpio",led);
	if(ret){
        pr_err("Cannot create sysfs file\n");
        return -1;
    }
	return 0;
}

/**
 * @brief This function is called on unloading the driver 
 */
static int dt_remove(struct platform_device *pdev) {
	struct device *dev = &pdev->dev;
	pr_info("dt_probe - Now I am in the remove function\n");
	sysfs_remove_link(&dev->kobj, "led_gpio");
	gpiod_unexport(led);
    gpiod_put(led);
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