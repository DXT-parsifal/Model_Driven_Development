#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
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
__used __section(__versions) = {
	{ 0x3e549f1d, "module_layout" },
	{ 0xb013481f, "platform_driver_unregister" },
	{ 0xd7362d1, "__platform_driver_register" },
	{ 0xfaef0ed, "__tasklet_schedule" },
	{ 0xca54fee, "_test_and_set_bit" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x189c5980, "arm_copy_to_user" },
	{ 0x49970de8, "finish_wait" },
	{ 0x647af474, "prepare_to_wait_event" },
	{ 0x1000e51, "schedule" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x3dcf1ffa, "__wake_up" },
	{ 0x39dc96e9, "gpiod_set_raw_value" },
	{ 0xa480411c, "gpiod_get_raw_value" },
	{ 0x8e865d3c, "arm_delay_ops" },
	{ 0x4202ea9c, "class_destroy" },
	{ 0xd0f859e2, "device_destroy" },
	{ 0xc1514a3b, "free_irq" },
	{ 0xfe990052, "gpio_free" },
	{ 0x5bbe49f4, "__init_waitqueue_head" },
	{ 0x9545af6d, "tasklet_init" },
	{ 0x2072ee9b, "request_threaded_irq" },
	{ 0xc480d467, "platform_get_irq" },
	{ 0x419fdde, "gpiod_direction_input" },
	{ 0x507c67b4, "gpiod_direction_output_raw" },
	{ 0x9a36bdf0, "gpio_to_desc" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x8693c29e, "of_get_named_gpio_flags" },
	{ 0xf1a8b4a9, "device_create" },
	{ 0xb47e05b2, "__class_create" },
	{ 0x28908313, "__register_chrdev" },
	{ 0xc5850110, "printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

MODULE_INFO(depends, "");

