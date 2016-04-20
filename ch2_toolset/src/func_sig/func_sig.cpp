/**
 * [To be edited]
 * When building our program using a library, the compiler needs corresponding
 * headers we need to give the compiler needs our words/ linker system needs
 * the headers to know exactly how to combine the binary codes of the new
 * program and the library, e.g. function foo(arg1) is in libxxx, entrance at
 * 0x1234 bytes from the beginning. Note, because the information required has
 * been built in.
 *
 * [In this example]
 *
 * [Output]
 * > nm func_sig
 * 0000000100000f00 T __Z3fooc
 * 0000000100000ed0 T __Z3fooi
 * 0000000100000ea0 T __Z3fooii
 * 0000000100000000 T __mh_execute_header
 * 0000000100000f30 T _bar
 * 0000000100000f60 T _main
 *                  U _printf
 *                  U dyld_stub_binder
 *
 * We see that
 * void foo(int,int) => __Z3fooii
 * void foo(int)     => __Z3fooi
 * int  foo(char)    => __Z3fooc
 * is mangled into __Z3fooii Note that returning type is not in the signature,
 * C++ does not allow you to overload a function name by returning types.
 * We want the function bar to be encoded with plain C naming. So the
 * declaration is enclosed by extern "C"{...}.
 *
 * Another plain C function name is "_printf", but the implementaiton is not
 * in this code (indicated by "U"), i.e. the code needs some system library
 * providing "_printf" to run.
 *
 * otool -L func_sig
 * func_sig:
 *	/usr/lib/libc++.1.dylib (compatibility version 1.0.0, current version 120.1.0)
 *	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1226.10.1)
*/

#include <cstdio>


void foo(int a, int b){
  printf("a,b: %d,%d\n",a,b);
}

void foo(int a){
  printf("a: %d\n",a);
}

int foo(char a){
  printf("a: %c\n",a);
  return 0;
}

extern "C"{
  int bar(char a);
}

int bar(char a){
  printf("a: %c\n",a);
  return 0;
}

int main(int argc, char** argv)
{
  return 0;
}
