#include "irq.h"
#include "pic.h"
#include "io.h"
#include "i8259.h"
#include <stddef.h>
#include <stdio.h>
#include <util/arrays.h>
#include "stdio.h"

#define PIC_REMAP_OFFSET        0x20

IRQHandler g_IRQHandlers[16];
static const PICDriver* g_PIC_Driver = NULL;

void i686_IRQ_Handler(Registers* regs)
{
    int irq = regs->interrupt - PIC_REMAP_OFFSET;

    if (g_IRQHandlers[irq] != NULL)
    {
        // handle IRQ
        g_IRQHandlers[irq](regs);
    }
    else
    {
        printf("Unhandled IRQ %d...\n", irq);
    }

    // send EOI
    g_PIC_Driver->SendEndOfInterrupt(irq);
}

void i686_IRQ_Initialize()
{
    const PICDriver* drivers[] = {
        i8259_GetDriver(),
    };

    for (int i = 0; i < SIZE(drivers); i++) {
        if (drivers[i]->Probe()) {
            g_PIC_Driver = drivers[i];
        }
    }

    if (g_PIC_Driver == NULL) {
        printf("Warning: No PIC found!\n");
        return;
    }

    printf("Found %s PIC.\n", g_PIC_Driver->Name);
    g_PIC_Driver->Initialize(PIC_REMAP_OFFSET, PIC_REMAP_OFFSET + 8, false);

    // register ISR handlers for each of the 16 irq lines
    for (int i = 0; i < 16; i++)
        i686_ISR_RegisterHandler(PIC_REMAP_OFFSET + i, i686_IRQ_Handler);

    // enable interrupts
    i686_EnableInterrupts();

    g_PIC_Driver->Unmask(0);
    g_PIC_Driver->Unmask(1);
}

void i686_IRQ_RegisterHandler(int irq, IRQHandler handler)
{
    g_IRQHandlers[irq] = handler;
}
