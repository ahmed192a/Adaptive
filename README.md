# Adaptive 

Adaptive AUTOSAR is a simulated _Adaptive Platform_ enviroment over Linux defined by [AUTOSAR](https://www.autosar.org/standards/adaptive-platform/).

## General steps
-----

- to use the ".sh" files you need first to run this command in terminal 
```bash
chmod +x \*.sh
```
- you have to cinfigure the project before any thing
- build and run the project

-------------

### First of all

- open terminal in the project dir
- change the dir to quick_test 
```bash
cd quick_test
```

### steps for configuration

- run this command 
```bash
./configure.sh
```

### steps for building

- run this command 
```bash
./build.sh
```

### steps for running

- run this command 
```bash
./run.sh
```

### steps for testing

- run this command 
```bash
./test.sh
```


## steps for SD test
--------

- Run this command just one time
```bash
./configure.sh
```
```bash
./build.sh
./sd_test.sh
```
