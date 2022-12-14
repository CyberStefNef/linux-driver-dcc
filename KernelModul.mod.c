#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x826b8746, "module_layout" },
	{ 0x5105d7f, "cdev_del" },
	{ 0xb33af203, "device_destroy" },
	{ 0x695bf5e9, "hrtimer_cancel" },
	{ 0xa362bf8f, "hrtimer_init" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xa54133aa, "kobject_put" },
	{ 0x5e657d97, "class_destroy" },
	{ 0x8360e9, "device_create" },
	{ 0x93c8fa59, "__class_create" },
	{ 0x8e6ad741, "cdev_add" },
	{ 0x6453db1a, "cdev_alloc" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xfe990052, "gpio_free" },
	{ 0xb77942ad, "gpiod_direction_output_raw" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xc358aaf8, "snprintf" },
	{ 0x526c3a6c, "jiffies" },
	{ 0x5cc2a511, "hrtimer_forward" },
	{ 0xa339085b, "gpiod_set_raw_value" },
	{ 0xf7d5fff7, "gpio_to_desc" },
	{ 0xff178f6, "__aeabi_idivmod" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x3ea1b6e4, "__stack_chk_fail" },
	{ 0xec523f88, "hrtimer_start_range_ns" },
	{ 0x37a0cba, "kfree" },
	{ 0xaa152108, "hrtimer_active" },
	{ 0x5f754e5a, "memset" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0x92997ed8, "_printk" },
	{ 0xb7744793, "kmem_cache_alloc_trace" },
	{ 0xbe301f03, "kmalloc_caches" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "9745EC3F329B40EB1072B4E");
