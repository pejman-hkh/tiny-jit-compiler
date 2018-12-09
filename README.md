# Tiny jit compiler
Toy x86 32bit jit compiler

# Compile 

```
gcc compile.c asm.c
```


# Tests
```
./a.out 4*-3-1*-20 => 8
./a.out -2*-3-1*-20 => 26
./a.out -2*5+1*-8 => -18
```

# Sample output

```
./a.out -2*5+1*-8
-2*5+1*-8
mov eax, 2
mov ecx, 0
sub eax, ecx
neg eax
push eax
mov eax, 5
pop ecx
imul eax, ecx
push eax
mov eax, 1
push eax
mov eax, 8
mov ecx, 0
sub eax, ecx
neg eax
pop ecx
imul eax, ecx
pop ecx
add eax, ecx
leave
ret
-18
```