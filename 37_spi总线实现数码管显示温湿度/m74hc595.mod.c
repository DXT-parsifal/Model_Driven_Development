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
	{ 0x43fbdf86, "driver_unregister" },
	{ 0xf2010e8b, "__spi_register_driver" },
	{ 0xf1a8b4a9, "device_create" },
	{ 0xb47e05b2, "__class_create" },
	{ 0x28908313, "__register_chrdev" },
	{ 0x8e865d3c, "arm_delay_ops" },
	{ 0xee307cd, "spi_sync" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x5f754e5a, "memset" },
	{ 0x514cc273, "arm_copy_from_user" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x4202ea9c, "class_destroy" },
	{ 0xd0f859e2, "device_destroy" },
	{ 0xc5850110, "printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

MODULE_INFO(depends, "");

