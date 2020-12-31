The sample programs for Chapter 13 illustrate traditional I/O device
programming using VxDs that really virtualize something:

PortVirtualization   -- Shows how to "trap" a port in order to simulate
                        I/O with a nonexistent device.

MemoryVirtualization -- (Non-working sample) Shows how to virtualize a
                        memory-mapped device.

IRQVirtualization    -- Shows IRQ virtualization and port trapping. Yet
                        another way of getting a computer to say, "Hello,
                        World!"

In addition, the Ring0DMA sample shows how to perform DMA transfers within
a VxD.
