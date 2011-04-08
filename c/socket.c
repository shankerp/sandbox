#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

int main()
{
    int s32_socketId = 0;

/*  socketId = socket(int domain, int type, int protocol); */

/*  Valid Domain Parameters (Address Format)
 * =========================================
 *  AF_UNIX, AF_LOCAL   Local communication              unix(7)
 *  AF_INET             IPv4 Internet protocols          ip(7)
 *  AF_INET6            IPv6 Internet protocols          ipv6(7)
 *  AF_IPX              IPX - Novell protocols
 *  AF_NETLINK          Kernel user interface device     netlink(7)
 *  AF_X25              ITU-T X.25 / ISO-8208 protocol   x25(7)
 *  AF_AX25             Amateur radio AX.25 protocol
 *  AF_ATMPVC           Access to raw ATM PVCs
 *  AF_APPLETALK        Appletalk                        ddp(7)
 *  AF_PACKET           Low level packet interface       packet(7)
 *
 *  Valid Type Parameters
 * =======================
 *  SOCK_STREAM - For TCP
 *         Provides sequenced, reliable, two-way, connection-based byte streams.  An out-of-band data transmission mechanism may be supported.
 *
 *  SOCK_DGRAM - For UDP
 *         Supports datagrams (connectionless, unreliable messages of a fixed maximum length).
 *
 *  SOCK_SEQPACKET
 *         Provides a sequenced, reliable, two-way connection-based data transmission path for datagrams of fixed maximum  length;  a  consumer  is
 *         required to read an entire packet with each input system call.
 *
 *  SOCK_RAW
 *         Provides raw network protocol access.
 *
 *  SOCK_RDM
 *         Provides a reliable datagram layer that does not guarantee ordering.
 *
 *  SOCK_PACKET
 *         Obsolete and should not be used in new programs; see packet(7).
 *
 */


}
