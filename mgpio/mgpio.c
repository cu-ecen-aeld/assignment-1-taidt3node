#include <linux/module.h>
#include <linux/gpio.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tai");
MODULE_DESCRIPTION("Simple GPIO driver for Raspberry Pi");
MODULE_VERSION("1.0");

#define GPIO_BASE 0xFE200000
#define GPFSEL2   0x08
#define GPSET0    0x1C
#define GPCLR0    0x28
#define GPLEV0    0x34

static void __iomem *gpio;

static int __init mgpio_init(void)
{
    u32 val;

    gpio = ioremap(GPIO_BASE, 0x1000);
    if (!gpio)
        return -ENOMEM;

    /* Set GPIO27 as output: FSEL27 = 001 */
    val = readl(gpio + GPFSEL2);
    val &= ~(0x7 << 21);
    val |= (0x1 << 21);
    writel(val, gpio + GPFSEL2);

    /* Set GPIO27 high */
    writel(1 << 27, gpio + GPSET0);

    val = readl(gpio + GPLEV0);
    pr_info("GPIO27 is %s\n", (val & (1 << 27)) ? "high" : "low");

    return 0;
}

static void __exit mgpio_exit(void)
{
    u32 val;

    /* Set GPIO27 low */
    writel(1 << 27, gpio + GPCLR0);

    val = readl(gpio + GPLEV0);
    pr_info("GPIO27 is %s\n", (val & (1 << 27)) ? "high" : "low");

    iounmap(gpio);
}

module_init(mgpio_init);
module_exit(mgpio_exit);
