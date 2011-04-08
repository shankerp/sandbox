#include <stdio.h> 
#include <iostream> 
#include <map> 
#include <utility> 
typedef struct _MsgAddrInfo 
{ 
    int senderaddrlen; 
    const char* senderaddr; 
    int receiveraddrlen; 
    const char* receiveraddr; 
}MsgAddrInfo; 
typedef struct _MsgHandle 
{ 
    int upper; 
    int lower; 
}MsgHandle; 
//typedef map<int, MsgAddrInfo> FcMsgAddrInfo; 
typedef map<MsgHandle, MsgAddrInfo> FcMsgAddrInfo; 
int main(int argc, char *argv[]) 
{ 
    typedef char s8; 
    MsgHandle handle; 
    MsgAddrInfo dummy; 
    handle.upper = 43; 
    handle.lower = 44; 
    dummy.senderaddrlen = 12; 
    dummy.senderaddr = "vinoth"; 
    dummy.receiveraddrlen = 3; 
    dummy.receiveraddr = "kumar"; 
    FcMsgAddrInfo m_mapMsgAddr; 
    //m_mapMsgAddr.insert(pair<int, MsgAddrInfo>(53, dummy)); 
    m_mapMsgAddr.insert(pair<MsgHandle, MsgAddrInfo>(handle, dummy)); 
    printf ("size is :%d\n", m_mapMsgAddr.size()); 
    if ( m_mapMsgAddr.find(handle) != m_mapMsgAddr.end() ) 
    { 
        printf ("\nyou did it\n"); 
        printf("\nlen %d\n", m_mapMsgAddr.find( handle)->second.senderaddrlen); 
        printf("\nlen %s\n", m_mapMsgAddr.find( handle)->second.senderaddr); 
    } 
    return 1; 
} 
