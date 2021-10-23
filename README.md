# MpyCollarTx
This is a micropython module for controlling dog collars. The TX/RF part of the code is based on [CrashOverride85/collar](https://github.com/CrashOverride85/collar) reverse engineering and implementation.
**This was code was written for educational purposes to learn how to create simple user modules in micropython**

The module only implements transmitting because I didn't feel trying to implement interrupts, tho I'm sure it's possible somehow.

## Building
Make sure that you can build micropython normally, in my case I tested on an esp32 so for me, it looks like this:
```bash
samuel@ubuntu:~$ source esp-idf/export.sh
samuel@ubuntu:~$ cd micropython/ports/esp32
samuel@ubuntu:~/micropython/ports/esp32$ make USER_C_MODULES=/path/to/this/repo/micropython.cmake
samuel@ubuntu:~/micropython/ports/esp32$ idf.py -B build-GENERIC/ flash
```

## Usage
After flashing, you can use it like this:
```python
import machine
import collartx

remote_id = 0x1EEF #You'll need to obtain your remote id or pair your receiver with this id. See the manual
channel = collartx.CHANNEL_1 #Can be channel 1/2/3

trasmitter_pin = machine.Pin(25, machine.Pin.OUT)

collartx.shock(trasmitter_pin, remote_id, channel, 10)
collartx.vibrate(trasmitter_pin, remote_id, channel, 75)
collartx.beep(trasmitter_pin, remote_id, channel)
```

## Licence
See LICENSE.md
