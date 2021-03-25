#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
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
	{ 0x9de7765d, "module_layout" },
	{ 0x43ded081, "debugfs_remove" },
	{ 0xc5850110, "printk" },
	{ 0xb5d13003, "debugfs_create_x16" },
	{ 0x88db56b, "debugfs_create_u8" },
	{ 0x71eb2925, "debugfs_create_file" },
	{ 0x44dcfa5c, "debugfs_create_dir" },
	{ 0x619cb7dd, "simple_read_from_buffer" },
	{ 0xbb4f4766, "simple_write_to_buffer" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "E09F38032F390950B6DAC97");
