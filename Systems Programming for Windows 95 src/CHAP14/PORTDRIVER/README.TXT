The PortDriver sample is a complete, working serial port driver that
illustrates how to write a VCOMM port driver.

To build this sample, prepare your system according to the general
directions in the root directory of this disc. Run "nmake -f serial.mak" to
build from a command prompt, or open the PortDriver project in Microsoft
Developer Studio and build within that environment.

To test this sample, rename the SERIAL.VXD that's already in your Windows
system directory and copy the SERIAL.VXD from this project directory. The new
driver will be used the next time VCOMM needs to load SERIAL. Clean up by restoring
the original SERIAL.VXD.
