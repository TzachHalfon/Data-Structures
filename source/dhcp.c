/*============================LIBRARIES && MACROS =================================*/
#include <stdlib.h> /*malloc free strtol*/
#include <stdint.h> /*unit32_max*/
#include <stdio.h>	/*sprintf*/
#include <assert.h> /*assert*/
#include <string.h> /*strlen*/

#include "dhcp.h"

#define FAIL 1
#define BYTE 8
#define FULL 1
#define LEAF 0
#define FREE (-1)
#define SUCCESS 0
#define NETWORK 0
#define NOT_FULL 0
#define SERVER 254
#define DEC_BASE 10
#define BROADCAST 255
#define END_OF_MASK 1
#define IP_SIZE_IN_BITS 32
#define SHIFT_OFFSET ((IP_SIZE_IN_BITS)-1)
/*================================= STRUCTS =======================================*/
typedef struct dhcp_node dhcp_node_t;
typedef enum children
{
	ZERO = 0,
	ONE,
	NUM_OF_CHILDREN
} children_t;

struct dhcp
{
	dhcp_node_t *root;
	uint32_t subnet_ID;
	size_t mask_length;
};

struct dhcp_node
{
	dhcp_node_t *children[NUM_OF_CHILDREN];
	int is_full;
};
/*=========================== FUNCTION DECLARATION ================================*/
static int AllocateIP(dhcp_node_t *node, uint32_t requested_ip, uint32_t *result_ip, int index);
static uint32_t GetNextAvailableIP(uint32_t requested_ip, dhcp_node_t *node, int index);
static int IsIPFree(uint32_t requested_ip, dhcp_node_t *node, int index);
static int IsIpInSubnet(const dhcp_t *dhcp, uint32_t requested_ip);
static dhcp_node_t *FreeIP(dhcp_node_t *node, uint32_t ip);
static size_t GetIPCount(dhcp_node_t *node, int index);
static children_t GetPosition(uint32_t ip, int index);
static dhcp_node_t *GoToSubnetRoot(dhcp_t *dhcp);
static int CreateSubnetMaskTree(dhcp_t *dhcp);
static dhcp_node_t *CreateNode(int is_full);
static void DestroyNodes(dhcp_node_t *node);
static void UpdateIfFull(dhcp_node_t *node);
/*
	why do we need subnet id? narrow possibilities of ips + validation(IsIPinSubnet)
	create - make 3 cases for addresses
	root - if pointer then malloc in create
	if alloc fails return next
	update result ip in alloc every iteration/recursion
	make sure there are no dangling pointer in free
	mask length - make sure its 32 minus len
	destroy needs to be post order
*/
/*=========================== FUNCTION DEFINITION =================================*/
dhcp_t *DHCPCreate(uint32_t subnet_ID, size_t subnet_length)
{
	dhcp_t *dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
	if (dhcp != NULL)
	{
		dhcp->mask_length = subnet_length;
		dhcp->subnet_ID = subnet_ID;
		dhcp->root = CreateNode(NOT_FULL);
		if (NULL == dhcp->root)
		{
			free(dhcp);
			return (NULL);
		}
		if (FAIL == CreateSubnetMaskTree(dhcp))
		{
			DHCPDestroy(dhcp);
			return (NULL);
		}
	}
	return (dhcp);
}

void DHCPDestroy(dhcp_t *dhcp)
{
	assert(NULL != dhcp);
	DestroyNodes(dhcp->root);
	free(dhcp);
}

int DHCPAllocateIp(dhcp_t *dhcp, uint32_t requested_ip, uint32_t *result_ip)
{
	dhcp_node_t *subnet_root = NULL;

	assert(NULL != dhcp);
	assert(NULL != result_ip);

	subnet_root = GoToSubnetRoot(dhcp);
	*result_ip = dhcp->subnet_ID;
	requested_ip = GetNextAvailableIP(requested_ip, subnet_root, (SHIFT_OFFSET - dhcp->mask_length));
	if (FAIL == requested_ip && IsIpInSubnet(dhcp, requested_ip))
	{
		return (FAIL);
	}
	return (AllocateIP(subnet_root, requested_ip, result_ip, (SHIFT_OFFSET - dhcp->mask_length)));
}

void DHCPFreeIp(dhcp_t *dhcp, uint32_t ip)
{
	assert(NULL != dhcp);
	dhcp->root = FreeIP(dhcp->root, ip);
}

size_t DHCPCountFree(dhcp_t *dhcp)
{
	size_t total;
	assert(NULL != dhcp);
	total = ((UINT32_MAX) / (1 << dhcp->mask_length) + 1);

	return (total - GetIPCount(dhcp->root, 0));
}

char *DHCPIpToString(uint32_t ip, char *dest_ip)
{
	int i = 3;
	unsigned char tmp = ' ';
	for (i = 3; 0 <= i; --i)
	{
		tmp = (ip >> (i * 8)) & 0xFF;
		sprintf(dest_ip + strlen(dest_ip), "%d.", tmp);
	}
	dest_ip[strlen(dest_ip) - 1] = '\0';
	return (dest_ip);
}

uint32_t DHCPStringToIp(char *ip)
{
	uint32_t to_return = 0;
	assert(NULL != ip);

	while (*ip != '\0')
	{
		to_return <<= BYTE;
		to_return |= strtol(ip, &ip, DEC_BASE);
		if ('\0' != *ip)
		{
			++ip;
		}
	}

	return (to_return);
}

static void DestroyNodes(dhcp_node_t *node)
{
	if (NULL != node)
	{
		DestroyNodes(node->children[ZERO]);
		node->children[ZERO] = NULL;
		DestroyNodes(node->children[ONE]);
		node->children[ONE] = NULL;
		free(node);
	}
}

static dhcp_node_t *CreateNode(int is_full)
{
	dhcp_node_t *node = (dhcp_node_t *)malloc(sizeof(dhcp_node_t));
	if (NULL != node)
	{
		node->is_full = is_full;
		node->children[ONE] = NULL;
		node->children[ZERO] = NULL;
	}
	return (node);
}

static size_t GetIPCount(dhcp_node_t *node, int index)
{
	if (node != NULL)
	{
		if (node->is_full == FULL)
		{
			return (1 << (IP_SIZE_IN_BITS - index));
		}
		return (GetIPCount(node->children[ZERO], index + 1) + GetIPCount(node->children[ONE], index + 1));
	}
	return (0);
}

static dhcp_node_t *FreeIP(dhcp_node_t *node, uint32_t ip)
{
	children_t side = GetPosition(ip, SHIFT_OFFSET);
	if (NULL != node)
	{
		node->children[side] = FreeIP(node->children[side], ip << 1);
		if (node->children[ZERO] == NULL && node->children[ONE] == NULL)
		{
			free(node);
			return (NULL);
		}
		UpdateIfFull(node);
	}
	return (node);
}

static int AllocateIP(dhcp_node_t *node, uint32_t requested_ip, uint32_t *result_ip, int index)
{
	uint32_t side = 0;

	if (index >= 0)
	{
		side = GetPosition(requested_ip, index);
		if (NULL == node->children[side])
		{
			node->children[side] = (CreateNode(LEAF == index));
			if (NULL == node->children[side])
			{
				return (FAIL);
			}
		}
		*result_ip |= (side << index);

		if (FAIL == AllocateIP(node->children[side], requested_ip, result_ip, index - 1))
		{
			return (FAIL);
		}
	}

	if (NULL != node)
	{
		UpdateIfFull(node);
	}
	return (SUCCESS);
}

static void UpdateIfFull(dhcp_node_t *node)
{
	if (NULL == node->children[ZERO] && NULL == node->children[ONE])
	{
		node->is_full = FULL;
		return;
	}
	if (NULL != node->children[ZERO] && FULL == node->children[ZERO]->is_full &&
		NULL != node->children[ONE] && FULL == node->children[ONE]->is_full)
	{
		node->is_full = FULL;
		return;
	}
	node->is_full = NOT_FULL;
}

static int CreateSubnetMaskTree(dhcp_t *dhcp)
{
	dhcp_node_t *node = dhcp->root;
	uint32_t subnet_id = dhcp->subnet_ID;
	uint32_t garbage = 0;
	size_t make_length = dhcp->mask_length;
	children_t side;

	while (0 < make_length)
	{
		side = GetPosition(subnet_id, SHIFT_OFFSET);
		node->children[side] = CreateNode(NOT_FULL);
		if (NULL == node->children[side])
		{
			return (FAIL);
		}

		node = node->children[side];
		subnet_id <<= 1;
		--make_length;
	}

	DHCPAllocateIp(dhcp, dhcp->subnet_ID, &garbage);
	DHCPAllocateIp(dhcp, dhcp->subnet_ID | SERVER, &garbage);
	DHCPAllocateIp(dhcp, dhcp->subnet_ID | BROADCAST, &garbage);

	return (SUCCESS);
}

static dhcp_node_t *GoToSubnetRoot(dhcp_t *dhcp)
{
	dhcp_node_t *node = dhcp->root;
	uint32_t subnet_id = dhcp->subnet_ID;
	size_t mask_length = dhcp->mask_length;

	while (0 < mask_length)
	{
		node = node->children[GetPosition(subnet_id, SHIFT_OFFSET)];
		subnet_id <<= 1;
		--mask_length;
	}
	return (node);
}

static children_t GetPosition(uint32_t ip, int index)
{
	return (!!(ip & (1 << index)));
}

static int IsIPFree(uint32_t requested_ip, dhcp_node_t *node, int index)
{
	while (0 < index--)
	{
		node = node->children[GetPosition(requested_ip, index)];
		if (NULL == node)
		{
			return (FREE);
		}
		if (FULL == node->is_full)
		{
			return (index);
		}
	}
	return (FAIL);
}

static uint32_t GetNextAvailableIP(uint32_t requested_ip, dhcp_node_t *node, int index)
{
	int curr_index;
	do
	{
		curr_index = IsIPFree(requested_ip, node, index + END_OF_MASK);
		if (curr_index == index)
		{
			return (FAIL); /*subroot is full*/
		}
		if (FREE != curr_index)
		{
			requested_ip += (1 << curr_index);
		}
	} while (FREE != curr_index);

	return (requested_ip);
}

static int IsIpInSubnet(const dhcp_t *dhcp, uint32_t requested_ip)
{
	return (0 == ((requested_ip ^ dhcp->subnet_ID) & (UINT32_MAX << (IP_SIZE_IN_BITS - dhcp->mask_length))));
}