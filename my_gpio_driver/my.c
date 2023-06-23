/**/
static ssize_t usr_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs){
    int to_copy, not_copied, delta;
	unsigned char value;

	/* Get amount of data to copy */
	to_copy = min(count, sizeof(value));

	/* Copy data from user */
	not_copied = copy_from_user(&value, user_buffer, to_copy);

	/* Setting the LED */
    pr_info("Value receive from user: %d\n",value);
    gpio_set_value(led, value);
    delta = not_copied - to_copy;
    return delta;
}

/**/
static ssize_t usr_read(struct file *File, const char *user_buffer, size_t count, loff_t *offs){
    int to_copy, not_copied, delta;
	unsigned char value;

	/* Get amount of data to copy */
	to_copy = min(count, sizeof(value));

	/* Copy data from user */
	not_copied = copy_to_user(&value, user_buffer, to_copy);

	/* Setting the LED */
    pr_info("Value send to user: %d\n",value);
    gpiod_set_value(led, value);
    delta = to_copy - not_copied;
    return delta;
}
static int my_open(struct inode *inode, struct file *filp){
	return 0;
}
static struct file_operations fops{
    .owner = THIS_MODULE,
    .open = my_open,
    .read = usr_read,
    .write = usr_write,
    .release = my_close
};