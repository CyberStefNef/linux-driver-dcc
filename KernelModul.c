#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/hrtimer.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#include "transferStruct.h"

#define GPIO_PIN 17

static struct hrtimer mytimer;

static struct transferStruct strus;

static int sampling_period_us = 58;
static int position = 0;
static int resendcount = 0;

 static dev_t myDevNumber;
 static struct cdev *myCdev;
 static struct class *myClass;
 static struct device *myDevice;
 static int index=0;

struct node {
   int data;
   struct node *next;
};

struct node *head = NULL;
struct node *currentelement = NULL;
static int list_length = 0;

int datenbits[32]= {   1, 1, 1 , 1, 1, 1, 1, 1, 1, 1, 1, 1,   	// Framing
						0,                                      // 0
						0,                                      // Direction
						0, 0, 0, 0, 0, 0, 0,                    // Motoraddress
						0,                                      // 0
						0, 0, 0, 0, 0, 0, 0, 0,                 // Drehzahl
						0,                                      // Dont Care
						1                                       // End of Word
						};

static void printList(void) {
   struct node *ptr = head;
   printk("\n[ ");
	
   //start from the beginning
   while(ptr != NULL) {
      printk("(%d) ",ptr->data);
      ptr = ptr->next;
   }
   printk(" ]");
}

static int transferToMotor(void) {
	datenbits[13] = strus.direction;

	int n = strus.motor_address;
	printk("%d\n", n);
	int a[7] = {0},i;
	for (i = 0; n>0; i++)
	{
		a[i] = n % 2;
		n = n/2;
	}
	
	int k = sizeof(a)/sizeof(a[0]) - 1;
	for (k= k; k >= 0; k--)
	{
		datenbits[14 + (sizeof(a)/sizeof(a[0]) - 1-k)] = a[k];
	}

	int speed = strus.speed;
	int speed_array[8] = {0},j;
	for (j = 0; speed>0; j++)
	{
		speed_array[j] = speed % 2;
		speed = speed/2;
	}
	int s = sizeof(speed_array)/sizeof(speed_array[0]) - 1;
	for (s= s; s >= 0; s--)
	{
		datenbits[22 + (sizeof(speed_array)/sizeof(speed_array[0]) - 1 -s)] = speed_array[s];
	}

	/*
	int o;
	for(o = 0; o < sizeof(datenbits)/sizeof(datenbits[0]); o++) {
		printk("Stelle: %d, Wert: %d", o, datenbits[o]);
	}
	*/

	
	return 0;

}

 static int init_gpio(int pin) {
	 int err;
	 char name[20];
	 snprintf(name,sizeof(name),"gpio-%d",pin);
	 err=gpio_request(pin,name);
	 if(err)
	 {
		 printk("gpio_request failed %d\n",err);
		 return -1;
	 }
	 err=gpio_direction_output(pin,0);
	 if(err)
	 {
		 printk("direction_output failed %d\n",err);
		 		 gpio_free(pin);
		 return -1;
     }
     return pin;
 }

static void insertFirst(int data) {
   //create a link
   struct node *link = (struct node*) kmalloc(sizeof(struct node), GFP_KERNEL);
	
   link->data = data;
	
   //point it to old first node
   link->next = head;
	
   //point first to new first node
   head = link;
}

static void translate_signal(void) {
	int i = sizeof(datenbits) / sizeof(datenbits[0]) - 1;
	for (i; i >= 0; i--)
	{
		if(datenbits[i]) {
			insertFirst(0);
			insertFirst(1);
		} else {
			insertFirst(0);
			insertFirst(0);
			insertFirst(1);
			insertFirst(1);
		}
	}
	
}

static int getListLength(void) {
   int length = 0;
   struct node *currentelement;
	
   for(currentelement = head; currentelement != NULL; currentelement = currentelement->next) {
      length++;
   }
	
   return length;
}

static void freeList(void)
{
   struct node* tmp;
	currentelement = NULL;
   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       kfree(tmp);
    }

}


static enum hrtimer_restart hrtimer_callback (struct hrtimer *hrt)
{
	if(resendcount < 3) {
		if (position > -1) {
			int i = 0;
			int data;
			struct node *ptr = head;

			for(i; i <= position % list_length; i++) {
				data = ptr->data;
				ptr = ptr->next;
			}

			gpio_set_value(GPIO_PIN, data);
			position++;
			if(position == list_length) {
				position = 0;
				resendcount++;
				printk("End of List! Length: %d\n", list_length);
			}
			hrtimer_forward_now(&mytimer, ktime_set(0, sampling_period_us * 1000));
			return HRTIMER_RESTART;
		}
	}
	printk("Finished Timer!\n");
	position = 0;
	return HRTIMER_NORESTART;
}

static int init_hr_timer(void) {
	hrtimer_init(&mytimer,CLOCK_MONOTONIC,HRTIMER_MODE_REL);
	mytimer.function=hrtimer_callback;
	
	return 0;
}

static int timer_start(void) {
	printk("Start Timer!\n");
	static ktime_t mytime;
	mytime=ktime_set(0, sampling_period_us * 1000);
	hrtimer_start(&mytimer,mytime,HRTIMER_MODE_REL);
	return 0;
}

static ssize_t my_drv_write(struct file *instanz, const char  __user *user, 
							size_t count, loff_t *offset)
{   
	int notCopied;
	int j;
	printk("write aufgerufen mit count  %d\n",count);
	printk("requesting  %d bytes\n",sizeof(strus));
	notCopied=copy_from_user((void*)&strus,user,sizeof(strus));
	
	printk("Direction:%d Motor Address:%d  Speed:%d",strus.direction,strus.motor_address,strus.speed);

	*offset+=count;
	printk("not copied %d\n",notCopied);

	bool active = hrtimer_active(&mytimer);
	position = 0;
	resendcount = 0;
	printk("Active: %d \n",active);
	if(!active) {
		transferToMotor();
		freeList();
		translate_signal();
		//printList();
		list_length = getListLength();
		timer_start();
	}
	return count; 
}


static struct file_operations fops={
	.owner=THIS_MODULE,
	.write=my_drv_write,
	};

static int init_dev(void) {
	if(alloc_chrdev_region(&myDevNumber,0,1,"KernelModul")<0)
		return EIO;
	 
	myCdev=cdev_alloc();
	if(myCdev==NULL)
		
	goto free_device_number;
	
	myCdev->owner=THIS_MODULE;
	myCdev->ops=&fops;
	
	if(cdev_add(myCdev,myDevNumber,1))
	goto free_cdev;
	
	myClass=class_create(THIS_MODULE,"KernelModul");
	if(IS_ERR(myClass))
	{
		pr_err("Keine Anmeldung beim Udev\n");
		goto free_cdev;
	}
	
	myDevice=device_create(myClass,NULL,myDevNumber,NULL,"%s","KernelModul");
	
	if(IS_ERR(myDevice))
	{
		pr_err("create_device failed\n");
		goto free_class;
	}
	return 0;

	free_class:
		class_destroy(myClass);
	
	free_cdev:
		kobject_put(&myCdev->kobj);
	
	free_device_number:
		unregister_chrdev_region(myDevNumber,1);
	return -EIO;
}

static int mod_init(void)
{	
	printk("mod_init aufgerufen bei %lu\n", jiffies);
	
	if(init_gpio(GPIO_PIN)<0){
        return -1;
	}
	if(init_dev()<0){
        return -1;
	}
	
	init_hr_timer();


	return 0;
}
	 
 static void  mod_exit(void)
 {
	printk("mod_exit aufgerufen\n");
	gpio_free(GPIO_PIN);
	hrtimer_cancel(&mytimer);
	device_destroy(myClass,myDevNumber);
	class_destroy(myClass);
	cdev_del(myCdev);
	unregister_chrdev_region(myDevNumber,1);
	return;
 }
	 	

module_init( mod_init );
module_exit( mod_exit );


 MODULE_LICENSE("GPL");
 MODULE_AUTHOR("Stefan Müller");
 MODULE_DESCRIPTION("Modul for DCC");
