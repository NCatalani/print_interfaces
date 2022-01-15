#ifndef __PRINT_INT_HEADER__
#define __PRINT_INT_HEADER__

#include <pcap.h>

void print_interface(pcap_if_t *interface);
void print_interface_list(pcap_if_t *interfaces);
void print_addr(pcap_addr_t *pcap_addr);
void print_addr_list(pcap_addr_t *pcap_addrs);

#endif