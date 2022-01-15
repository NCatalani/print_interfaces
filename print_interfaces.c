#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "print_interfaces.h"

void print_interface(pcap_if_t *interface) 
{
    pcap_addr_t     *address;

    address = NULL;

    printf("Interface object [%p]\n", interface);

    if (interface == NULL) {
        fprintf(stderr, "\tTrying to print NULL object!");
        return;
    }

    printf("\tName: %s\n",          interface->name);
    printf("\tDescription: %s\n",   interface->description);
    printf("\tAddresses: \n");

    address = interface->addresses;

    print_addr_list(address);
}

void print_interface_list(pcap_if_t *interfaces)
{

    if (interfaces == NULL) return;

    while (interfaces != NULL) {
        print_interface(interfaces);
        interfaces = interfaces->next;
    }

}

void print_addr(pcap_addr_t *pcap_addr) 
{
    size_t  addr_size;
    int     addr_version; 
    char    *addr;

    addr = NULL;

    if (pcap_addr == NULL)   return;

    addr_version = pcap_addr->addr->sa_family;
    addr_size = (addr_version == AF_INET) ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN;

    addr = (char *) malloc(addr_size);
    if (addr == NULL) {
        fprintf(stderr, "Malloc error on line %d\n", __LINE__);
        return;
    }
    memset(addr, '\0', addr_size);

    inet_ntop(addr_version, pcap_addr->addr, addr, addr_size);

    if (strcmp(addr, ""))   
        printf("\t\t \"%s\" \n", addr);

    if (addr) {
        free(addr);
        addr = NULL;
    }
}

void print_addr_list(pcap_addr_t *pcap_addrs) 
{
    if (pcap_addrs == NULL) return;

    while (pcap_addrs) {
        print_addr(pcap_addrs);
        pcap_addrs = pcap_addrs->next;
    }

}

int main () 
{
    char        errbuff[PCAP_ERRBUF_SIZE];
    pcap_if_t   *interface;

    if (pcap_findalldevs(&interface, errbuff) < 0) {
        fprintf(stderr, "Error in pcap_findalldevs, exiting...\n");
        return -1;
    }

    printf("Printing interfaces for this system!\n");

    print_interface_list(interface);

}
