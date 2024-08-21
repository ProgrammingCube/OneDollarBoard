# One Dollar Board

## What is it?
This ATtiny85 board is a bit different than most. In fact, it is a spiritual successor to the [One Dollar Board](https://www.indiegogo.com/projects/one-dollar-board--5/x/14830965#/updates/all) Indiegogo project from 2016. This campaign made more than its goal and failed to deliver. Now, I am much more experienced than I was then. This project is my attempt to bring its idea to fruition.

While I have no where the buisness connections to create a true $1 board, this kit is something you can [buy]() or print yourself!

## Build process

[![Watch the video](https://i.sstatic.net/Vp2cE.png)](https://youtu.be/vt5fpE0bzSY)

This video will help you through the build process of the board. If you wish to have a writeup, [this]() is a link to the build how-to PDF. Those who purchase this kit will have also have a physical manual.

## Arduino IDE Setup
[Download Arduino IDE]()

In order to use this board seamlessly with the Arduino IDE, you need to install the Digispark Boards. These boards seem to be discontinued, but the json file is still extant.

Simply go to `File >> Preferencess` and click on the `Additional Boards Manager URLs` to add this entry:

`https://raw.githubusercontent.com/digistump/arduino-boards-index/master/package_digistump_index.json`

Click on OK.

Then, go `Tools >> Board... >> Boards Manager`. From here, search `Digistump`. Install the Digistump AVR Boards package. Accept any driver installs, we need these to talk to the boards because we are using a special bootloader.

#### Special note on the Bootloader***
Your ATtiny85 comes with a bootloader preinstalled, the [Micronucleus]() bootloader. This allows one to program the chip via USB instead of using a middle-man ISP. You can still use an ISP if you want though, and its easy enough to flash back to the Micronucleus bootloader.

Here is the [link]() for the Micronucleus bootloader I have used. You can use a different one if you want, or if you're good enough, you can [write your own]()!


Once you have the board installed, select the correct board by doing `Tools >> Boards... >> Digistump AVR Boards >> Digispark (Default, 16.5mhz)`. Then select `Tools >> Programmer >> Micronucleus`.
**IF YOU CAN'T UPLOAD CODE AND YOU GET A MESSAGE WITH ONLY 60% UPLOADED, CHECK YOUR PROGRAMMER SELECTION** For some reason, Arduino IDE likes to deselect this.

## Microchip Studio Setup
[Download Microchip Studio]()

Setup is a bit more nuanced, and it can be a bit more difficult if your computer setup is different. However, the setup is almost the same!

Refer to the **Arduino IDE Setup** section and follow the guide to install the board in the Boards Manager. From there, we pick up.

To start a new project, you need to select what language you will use. From there, you need to add an `External Tool`.

`External Tools` is a fantastic feature in which you can run user-arbitrary executables with whatever command line options you want. Most uses exercise this feature to add custom binary upload programs to the IDE, making a seamless environment from code, compile, to upload.

Here's what to do. Go to `Tools >> External Tools...`. From there, click `Add`. Name the tool something meaningful, like `ATtiny85_VUSB` or `ATtiny85_Micronucleus` or something like that.

Next, we will fill out the `Command` field. This will specify which .exe to run when the External Tool is selected. For us, we need to use the `launcher.exe` supplied by the Arduino board install.

In order to find this tool, go to the Arduino IDE, go to `File >> Preferences` and enable `Show verbose output during` for `upload`. Then, select the Digistump board as in the **Arduino IDE Setup**, and build/upload a blank sketch to your ATtiny85 board.

In the `Output` window, you should see something like this:

`C:\Users\yourusername\AppData\Local\Arduino15\packages\digistump\tools\micronucleus\2.0a4/launcher.exe`

or wherever you have installed Arduino IDE. Copy this text to the `Command` field in the `External Tools...` window.

Next, you can copy this text directly to the `Arguments` field:

`-cdigispark --timeout 60 -Uflash:w:"$(TargetName)\$(TargetName)\Debug\$(TargetName).hex":i`

The variables `$(TargetNamee)` are used so the default .hex file will be uploaded, regardless of what the source file is named.

Next, we need to change the `Initial Directory` field. This directory will be the `Atmel Studio/7.0` folder's location like this:

`C:\Users\yourusername\Documents\Atmel Studio\7.0`

There's a strange bug in Microchip Studio in which spaces in the directory aren't handled right, so we'll do this to avoid problems.

Perfect! Now, when you use Microchip Studio, you can press `F7` to compile/assemble your program, then use `Tools >> your-external-tool` to upload! If you're good, you can [keybind your tool]()!
# FAQ
### The PWR LED doesn’t turn on!!!
- Check to make sure the power LED is installed the right way round. The molded flat plastic should be facing USER RIGHT.
- Double-check your USB connector solder joints. This LED is a direct power to ground connection, so if this doesn’t turn on, something simple is wrong.
- If your computer pops a message saying Overcurrent Detection, you may have a short in the upper-left quadrant of your board, or a short on the ATtiny85 IC socket. Ensure that all solder joints are isolated.
### The PB0 LED doesn’t blink!!!1!
Unfortunately, there can be many causes for this problem.
- Check if the LEDs are installed the right way round. The molded flat plastic should be facing USER RIGHT.
- Be sure that the ATtiny85 is installed correctly. Its index notch should be facing USER LEFT. Also, make sure its pins aren’t bent or sticking out from the socket.
- Double-check your soldering of the ATtiny85 IC socket. You wouldn’t believe how many times veteran hobbyists forget to solder entire chips!
### When I start using the other chips, nothing works!
- Check to see if there are shorts on the IC sockets.
- Check if the LD117V33 regulator is installed correctly. Refer to the images.
- Be careful on where you plug power and data cables. By design, this board is EXTREMELY flexible. I have tried to do my best to make the silkscreen clear, but it is still possible to accidentally switch around power and data pins. Refer to the pinout diagrams.