#include <stdio.h>
#include <unistd.h>
#include <directfb.h>

int main (int argc, char **argv)
{
    DFBResult dfberr;

    if( (dfberr = DirectFBInit( &argc, &argv )) != DFB_OK )
    { DirectFBErrorFatal("DirectFBInit( &argc, &argv )", dfberr); }

    IDirectFB * main_interface = NULL;
    IDirectFB * main_interface_2 = NULL;                                  
    /* 1) */

    if( (dfberr = DirectFBCreate( &main_interface )) != DFB_OK )
    { DirectFBErrorFatal( "DirectFBCreate( &main_interface )", dfberr); }
#if 0
        /* 2) */
    if( (dfberr = DirectFBCreate( &main_interface )) != DFB_OK )          
    { DirectFBErrorFatal( "DirectFBCreate( &main_interface )", dfberr); }
#endif

/*if( (dfberr 
= main_dfb_interface->SetVideoMode( main_interface, 100, 100, 0 )) != 
DFB_OK ) { fprintf(stderr, "File: %s, Line: %d:\n", __FILE__, __LINE__); 
DirectFBErrorFatal( "SetVideoMode( main_interface, 100, 100, 100 )", 
dfberr); }*/
            
    if( (dfberr = DirectFBCreate( &main_interface_2 )) != DFB_OK )
    { DirectFBErrorFatal( "DirectFBCreate( &main_interface_2 )", dfberr); }

if (main_interface == main_interface_2)
{
printf("Returns same\n");
printf("Returns same\n");
printf("Returns same\n");
sleep(10);
}

    if( (dfberr = main_interface->SetCooperativeLevel( main_interface, DFSCL_FULLSCREEN )) != DFB_OK )
    { DirectFBErrorFatal( "SetCooperativeLevel( main_interface, DFSCL_FULLSCREEN )", dfberr); }
        if( (dfberr = main_interface_2->SetCooperativeLevel( main_interface_2, DFSCL_FULLSCREEN )) != DFB_OK )         /* 3) */
        { DirectFBErrorFatal( "SetCooperativeLevel( main_interface_2, DFSCL_FULLSCREEN )", dfberr); }
}
