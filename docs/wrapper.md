### Making a Wrapper

The main goal is not change the .exe file running on disk (like a patch). The idea is fake a system DLL.

If we look to d2.exe import table (on ghidra) or file system, we can see in the files a dll called ddraw.dll. If we create an fake ddraw.dll and put in the folder, windows can load our dll first.
![alt text](image-16.png)