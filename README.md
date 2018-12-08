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
