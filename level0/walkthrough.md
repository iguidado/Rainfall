# Level0

## Description
Connect to the vm using login level0:level0

The level 0 have a level0 executable so we will try to find something to exploit in it.

```shell
gdb ./level0 
[...]
Reading symbols from ./level0...
(No debugging symbols found in ./level0)
(gdb) disassemble
No frame selected.
(gdb) disassemble main
Dump of assembler code for function main:
```

```as
	push   %ebp
	mov    %esp,%ebp
	and    $0xfffffff0,%esp
	sub    $0x20,%esp
	mov    0xc(%ebp),%eax
	add    $0x4,%eax
	mov    (%eax),%eax
	mov    %eax,(%esp)
	call   0x8049710 <atoi>
	cmp    $0x1a7,%eax
	jne    0x8048f58 <main+152>
	movl   $0x80c5348,(%esp)
	call   0x8050bf0 <strdup>
	mov    %eax,0x10(%esp)
	movl   $0x0,0x14(%esp)
	call   0x8054680 <getegid>
	mov    %eax,0x1c(%esp)
	call   0x8054670 <geteuid>
	mov    %eax,0x18(%esp)
	mov    0x1c(%esp),%eax
```
## Solution

- We tried to understand what does the code by ltrace , or ghidra but this didn't work so we used __gdb__. <br>

- In the gdb code there is __hard coded variable__ . <br>

- The code __compare the argument with a value__ , this value is hard coded and is ___423___. <br>

- Just use `cat /home/user/level1/.pass` and you have th flag !!