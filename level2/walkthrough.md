- after analysing the binary it appear that there is no function launching shell access or exec or eval, whatsoever. But since there is no NX bit activated in the system it appear that we can probably execute function directly on the stack or on the heap.

- We will first put a breakpoint right after the gets call to analys the program at this point.


- Since there is a gets call we will try to input a payload on the stack then jump on it overwriting the return address of the `p()` function.


- There is a protection against stack jumping by comparing the content of return adress to 0xb000000 so we will probably need to use the hesap instead since there is no protection aggainst heap jumping and there is a stdup that take content of the stack and put it on the heap

- cheak 0x0804853d
