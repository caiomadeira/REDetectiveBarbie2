# REDetectiveBarbieII
RE on Barbie Detective Barbie(R) II (1998).
Some patches made by me can found in patches and release.

--- 
### Patch: d2_patchv3.exe:
- Changes windowStyle (0x8008000) to 0xCF0000 (Border, Minimize/ Maximaze Buttons);

- Changes Window name;

---
### Install Shield 3 Problem
https://archive.org/details/installshield3

The install shield 3 don't work (16/32 bit) anymore.
```
30b0:err:file:RedirectDriveRoot c:\stopthis.now => C:\Users\caiom\DOWNLO~1\OTVDM-~1.0\OTVDM-~1.0\c\stopthis.now  

Strange error set by CreateProcess: 740
The requested operation requires elevation" (administrator privileges). This typically occurs when a program attempts to perform a task that requires administrative permissions (like installing software, modifying system files, or changing system settings) but is not running with those privileges. 
```

## Tools:

- Ghidra;
- x32dbg;
- Microsoft Visual Studio;