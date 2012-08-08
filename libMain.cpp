//
//  libMain.cpp
//  IdleSow
//



#include "globals.h"
memset_t orig_memset = NULL;
dlopen_t orig_dlopen = NULL;

__attribute__ ((constructor)) void sysinject(void)
{
    printf("Injecting!\n");
    fflush(stdout);
    
    orig_memset = (memset_t) dlsym(RTLD_NEXT, "memset");
    orig_dlopen = (dlopen_t) dlsym(RTLD_NEXT, "dlopen");
    
    // Start a thread that will repeatedly poll to see if pImports and whatnot is correct
    
    start_agent();
    
    
}

// Creates a thread that will poll structures for updates
void start_agent()
{
    // Start hook thread
    pthread_t threadInfo;
    pthread_create( &threadInfo, NULL, &hook_thread, NULL);
}


void* hook_thread(void* arg)
{
    while(true)
    {
        if(oImport)
            if(oImport->Print) // Game has been initialized
                if(oImport->R_RenderScene != &hk_R_RenderScene) // RenderScene hasn't been hooked
                {
                    start_hook(); // Inject the hook
                    sleep(10); // Wait 10 sec
                    return NULL; // Exit this thread
                }
        sleep(5);
        
    }
    return NULL; // Exit the thread
}


//#include "../SDK/warsow_0.62_sdk/source/ref_gl/r_shader.h"

