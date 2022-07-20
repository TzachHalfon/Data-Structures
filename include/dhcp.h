/*
	team: OL125-126
	version: 1.0

*/

#ifndef _DHCP_H_
#define _DHCP_H_

#include <stddef.h> /* size_t */
#include <stdint.h>

typedef struct dhcp dhcp_t;

/* DESCRIPTION:
 * Function creates an empty dhcp
 *
 * PARAMS:
 * subnet_ID
 * subnet length
 *
 * RETURN:
 * Returns a pointer to the created Dhcp
 *
 * COMPLEXITY:
 * time:  O(1)
 * space: O(1)
 */
dhcp_t *DHCPCreate(uint32_t subnet_ID, size_t subnet_length);

/* DESCRIPTION:
 * Function DESTROY THE DHCP
 *
 * PARAMS:
 * dhcp  - DHCP to destroy
 *
 *
 * RETURN:
 * VOID
 *
 * COMPLEXITY:
 * time:  O(1)
 * space: O(1)
 */
void DHCPDestroy(dhcp_t *dhcp);

/* DESCRIPTION:
 * if requested ip is not avialable returns smallest avialable bigger ip.
 * if requested ip is 0 returns smallest avialable.
 *
 * PARAMS:
 * dhcp - pointer to the required dhcp to allocate IP from
 * requested_ip - preferred ip address
 * result_ip - pointer to memory location to store new ip in
 *
 * RETURN:
 * status
 *
 * COMPLEXITY:
 * time: O(log n)
 * space: O(1)
 */
int DHCPAllocateIp(dhcp_t *dhcp, uint32_t requested_ip, uint32_t *result_ip);

/* DESCRIPTION:
 * Function free the given IP from the given dhcp.
 *
 * PARAMS:
 * ip - ip the free.
 * dhcp - dhcp to free ip from.
 *
 * RETURN:
 * void
 *
 * COMPLEXITY:
 * time: O(log n)
 * space: O(1)
 */
void DHCPFreeIp(dhcp_t *dhcp, uint32_t ip);

/* DESCRIPTION:
 * Function counts free IPs available for allocation.
 *
 * PARAMS:
 * dhcp	  - dhcp to count free IPs.
 *
 * RETURN:
 * number of free IPs to allocate.
 *
 * COMPLEXITY:
 * time:  O(n)
 * space: O(1)
 */
size_t DHCPCountFree(dhcp_t *dhcp);

/**
 * @brief function to view the ip in human readable.
 *
 * @param ip ip to get its value.
 * @param dest_ip string to save the ip to.
 * @return char* string to save the ip to.
 */
char *DHCPIpToString(uint32_t ip, char *dest_ip);

/**
 * @brief function to get the ip in a way to use with the functions
 *
 * @param ip ip to get its value.
 * @return uint32_t ip value
 */
uint32_t DHCPStringToIp(char *ip);

#endif /* _DHCP_H_ */
