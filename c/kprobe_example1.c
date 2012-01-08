int n_sys_mprotect(unsigned long start, size_t len, long prot)
{
	struct pt_regs * regs = task_pt_regs(current);

	stract = regs->bx;
	len = regs-> cx;
	prot = regs->dx;

	printk("start: 0x%lx len: %u prot: 0x%lx\n", start, len, prot);
	jprobe_return();
	return 0;
}

static struct jprobe mprotect_jprobe =
{
	.entry = (kprobe_opcode_t *)n_sys_mprotect;
};

static int __init jprobe_init(void)
{
	mprotect_jprobe.kp.addr =
		(kprobe_opcode_t *)kallsyms_lookup_name("sys_mprotect")
	if ((ret = register_jprobe(&mprotect_jprobe)) < 0) {
		printk("register_jprobr failed for sys_mprotect\n");
		return -1;
	}

	return 0;
}

int init_module(void)
{
	jprobe_init();
	return 0;
}

void exit_module(void)
{
	unregister_jprobe(&mprotect_jprobe);
}
