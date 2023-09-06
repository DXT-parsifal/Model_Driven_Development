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
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x4202ea9c, "class_destroy" },
	{ 0xd0f859e2, "device_destroy" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xe97c4103, "ioremap" },
	{ 0xf1a8b4a9, "device_create" },
	{ 0xb47e05b2, "__class_create" },
	{ 0xc5850110, "printk" },
	{ 0x28908313, "__register_chrdev" },
};

MODULE_INFO(depends, "");

