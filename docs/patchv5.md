I want intercept windows system call and change to a modern window "window"(?). 

I need to find where's in the code set the resolution.

I know: 
- 640 = 0x280 in hex; 
- 480 = 0x1E0 in hex;

On little endian (inverted) the bytes must be:
- 280 = 80 02 00 00;
- 1E0 = E0 01 00 00;


- the resolution is hardcoded. Too much 0x280 (640) and checks.
- We are looking for functions. Functions receive arguments by PUSH instruction.

![alt text](image.png)

candidate 1
![alt text](image-1.png)

candidate 2
![alt text](image-2.png)

candidate 3
![alt text](image-3.png)

candidate 4
![alt text](image-4.png)

candidate 5
![alt text](image-5.png)

candidate 6
![alt text](image-6.png)

candidate 7
![alt text](image-7.png)

candidate 8 
![alt text](image-8.png)

candidate 9
![alt text](image-9.png)

candidate 10
![alt text](image-10.png)
----
![alt text](image-14.png)
![alt text](image-13.png)
![alt text](image-12.png)
![alt text](image-11.png)
![alt text](image-15.png)
Mudar de push 0xCF0000 para push 0x10CF0000 funcionou a ponte de aparecer a janela preta.  

---
Functions looked
https://learn.microsoft.com/pt-br/windows/win32/api/wingdi/nf-wingdi-getdevicecaps

---