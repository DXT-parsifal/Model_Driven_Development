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
	{ 0x3c36113d, "i2c_del_driver" },
	{ 0x5b116911, "i2c_register_driver" },
	{ 0x189c5980, "arm_copy_to_user" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x14bc48d4, "i2c_transfer" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x4202ea9c, "class_destroy" },
	{ 0xd0f859e2, "device_destroy" },
	{ 0xf1a8b4a9, "device_create" },
	{ 0xb47e05b2, "__class_create" },
	{ 0x28908313, "__register_chrdev" },
	{ 0xc5850110, "printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

MODULE_INFO(depends, "");

