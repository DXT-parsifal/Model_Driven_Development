#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x3d6976bf, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xe02b9e90, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x6a08c31c, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0xcb9749d1, __VMLINUX_SYMBOL_STR(platform_get_irq) },
	{ 0xa3f6274a, __VMLINUX_SYMBOL_STR(platform_get_resource) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "14D22279F3D56DC857C01D8");
