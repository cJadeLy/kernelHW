## Build instructions for bdaylist.c
1. Follow [these steps](http://people.westminstercollege.edu/faculty/ggagne/osc/vm/index.html) to set up your virtual environment
2. Inside of the virtual machine, run the following commands from the terminal:
```
mkdir git && cd git
git clone https://github.com/cJadeLy/kernelHW.git 
cd kernelHW
make
sudo insmod bdaylist.c

```
To verify module is loaded: 
```
lsmod | grep bday*

```
