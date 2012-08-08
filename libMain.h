//
//  libMain.h
//  IdleSow
//
//  Created by IX on 12-08-04.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef IdleSow_libMain_h
#define IdleSow_libMain_h

__attribute__ ((constructor)) void sysinject(void);
void start_agent();
void* hook_thread(void* arg);

typedef void* (*memset_t)(void *b, int c, size_t len);
extern memset_t orig_memset;// = NULL;


typedef void* (*dlopen_t)(const char *path, int mode);
extern dlopen_t orig_dlopen;// = NULL;

#endif
