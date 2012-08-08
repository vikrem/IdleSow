//
//  syscalls.h
//  IdleSow
//
//  Created by IX on 2012-08-08.
//
//

#ifndef IdleSow_syscalls_h
#define IdleSow_syscalls_h

// forward decls of hooked syscalls
void* memset(void*b, int c, size_t len);
void* dlopen(const char *path, int mode);


#endif
