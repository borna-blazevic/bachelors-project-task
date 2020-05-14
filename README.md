This project is the task run by the bootloader for this [project](https://github.com/borna-blazevic/bachelors-project).

This is the standalone version of the project.

The project can be run with after building:
```
qemu-system-arm -machine lm3s6965evb -serial stdio -kernel gcc/task.bin -s -S
```

and can be debbuged with 
```
arm-none-eabi-gdb -ex="target remote localhost:1234"
```

For debbuging it is necessary to load the debug symbols with the file command from task.axf once in gdb.