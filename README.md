# BBB

Everything working for sure on Debian 7.11 (kernel 3.8.13-bone80).

# Instruction

```bash
sudo su
apt-get install am335x-pru-package
mkdir src
cd src
wget https://www.freebasic-portal.de/dlfiles/592/libpruio-0.2.tar.bz2
tar xjf libpruio-0.2.tar.bz2
cd libpruio-0.2
cp src/c_wrapper/libpruio.so /usr/local/lib
ldconfig
cp src/c_wrapper/pruio*.h* /usr/local/include
cp src/config/libpruio-0A00.dtbo /lib/firmware
vim /boot/uEnv.txt
```
Unocommect line under
Disable HDMI/eMMC (v3.8.x)
```bash
reboot
```
After reboot:
```bash
sudo su
echo BB-BONE-PRU-01 > /sys/devices/bone_capemgr.9/slots
mv /home/Debian/src/libpruio-0.2 /opt
cd /opt
git clone https://github.com/MaciekDudynski/BBB.git
cd BBB/
```
On each reboot:
```bash
sudo su
echo BB-BONE-PRU-01 > /sys/devices/bone_capemgr.9/slots
cd /opt/BBB/
```
Checking capes:
```bash
cat /sys/devices/bone_capemgr.9/slots
```

# Sources

#### _first
Just reads 1 000 000 times AIN-0 and writes that to file.
#### _second
Prints current value of AIN-0 and current number of reads.
#### _third
Writes to binary files all reads from AIN-0 (200 kHz). Configuration described in source file.

# TODO

- Simplyfy instuction
- Add more sources
- Add DAC
- Add filters
- Add libprui recompile instruction
