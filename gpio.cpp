

#define BCM2708_PERI_BASE_DEFAULT   0x20000000
#define BCM2709_PERI_BASE_DEFAULT   0x3f000000
#define GPIO_BASE_OFFSET            0x200000
#define FSEL_OFFSET                 0   // 0x0000
#define SET_OFFSET                  7   // 0x001c / 4
#define CLR_OFFSET                  10  // 0x0028 / 4
#define PINLEVEL_OFFSET             13  // 0x0034 / 4
#define EVENT_DETECT_OFFSET         16  // 0x0040 / 4
#define RISING_ED_OFFSET            19  // 0x004c / 4
#define FALLING_ED_OFFSET           22  // 0x0058 / 4
#define HIGH_DETECT_OFFSET          25  // 0x0064 / 4
#define LOW_DETECT_OFFSET           28  // 0x0070 / 4
#define PULLUPDN_OFFSET             37  // 0x0094 / 4
#define PULLUPDNCLK_OFFSET          38  // 0x0098 / 4

#define PULLUPDN_OFFSET_2711_0      57
#define PULLUPDN_OFFSET_2711_1      58
#define PULLUPDN_OFFSET_2711_2      59
#define PULLUPDN_OFFSET_2711_3      60

#define PAGE_SIZE  (4*1024)
#define BLOCK_SIZE (4*1024)

#define SETUP_OK           0
#define SETUP_DEVMEM_FAIL  1
#define SETUP_MALLOC_FAIL  2
#define SETUP_MMAP_FAIL    3
#define SETUP_CPUINFO_FAIL 4
#define SETUP_NOT_RPI_FAIL 5

#define INPUT  1 // is really 0 for control register!
#define OUTPUT 0 // is really 1 for control register!
#define ALT0   4

#define HIGH 1
#define LOW  0

#define PUD_OFF  0
#define PUD_DOWN 1
#define PUD_UP   2


static volatile uint32_t *gpio_map;


void short_wait(void)
{
    int i;

    for (i=0; i<150; i++) {    // wait 150 cycles
        asm volatile("nop");
    }
}

void set_pullupdn(int gpio, int pud)
{
    // Check GPIO register
    int is2711 = *(gpio_map+PULLUPDN_OFFSET_2711_3) != 0x6770696f;
    if (is2711) {
        // Pi 4 Pull-up/down method
        int pullreg = PULLUPDN_OFFSET_2711_0 + (gpio >> 4);
        int pullshift = (gpio & 0xf) << 1;
        unsigned int pullbits;
        unsigned int pull = 0;
        switch (pud) {
            case PUD_OFF:  pull = 0; break;
            case PUD_UP:   pull = 1; break;
            case PUD_DOWN: pull = 2; break;
            default:       pull = 0; // switch PUD to OFF for other values
        }
        pullbits = *(gpio_map + pullreg);
        pullbits &= ~(3 << pullshift);
        pullbits |= (pull << pullshift);
        *(gpio_map + pullreg) = pullbits;
    } else {
        // Legacy Pull-up/down method
        int clk_offset = PULLUPDNCLK_OFFSET + (gpio/32);
        int shift = (gpio%32);

        if (pud == PUD_DOWN) {
            *(gpio_map+PULLUPDN_OFFSET) = (*(gpio_map+PULLUPDN_OFFSET) & ~3) | PUD_DOWN;
        } else if (pud == PUD_UP) {
            *(gpio_map+PULLUPDN_OFFSET) = (*(gpio_map+PULLUPDN_OFFSET) & ~3) | PUD_UP;
        } else  { // pud == PUD_OFF
            *(gpio_map+PULLUPDN_OFFSET) &= ~3;
        }
        short_wait();
        *(gpio_map+clk_offset) = 1 << shift;
        short_wait();
        *(gpio_map+PULLUPDN_OFFSET) &= ~3;
        *(gpio_map+clk_offset) = 0;
    }
}

void setup_gpio(int gpio, int direction, int pud)
{
    int offset = FSEL_OFFSET + (gpio/10);
    int shift = (gpio%10)*3;

    set_pullupdn(gpio, pud);
    if (direction == OUTPUT)
        *(gpio_map+offset) = (*(gpio_map+offset) & ~(7<<shift)) | (1<<shift);
    else  // direction == INPUT
        *(gpio_map+offset) = (*(gpio_map+offset) & ~(7<<shift));
}
