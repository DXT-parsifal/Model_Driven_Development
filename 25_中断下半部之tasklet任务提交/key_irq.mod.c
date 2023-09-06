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
	{ 0xfe990052, "gpio_free" },
	{ 0xc1514a3b, "free_irq" },
	{ 0x9545af6d, "tasklet_init" },
	{ 0x419fdde, "gpiod_direction_input" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x8693c29e, "of_get_named_gpio_flags" },
	{ 0x2072ee9b, "request_threaded_irq" },
	{ 0x90dcee93, "irq_of_parse_and_map" },
	{ 0xe180d82f, "of_find_compatible_node" },
	{ 0xfaef0ed, "__tasklet_schedule" },
	{ 0xca54fee, "_test_and_set_bit" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xc5850110, "printk" },
	{ 0xa480411c, "gpiod_get_raw_value" },
	{ 0x9a36bdf0, "gpio_to_desc" },
	{ 0x8e865d3c, "arm_delay_ops" },
};

MODULE_INFO(depends, "");

