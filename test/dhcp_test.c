#include <stdio.h>
#include <string.h>

#include "dhcp.h"

void TestAllFuncs(void);
void TestCreate(void);
static void TestStringIpConversion(void);
static void TestAlloc(void);
static void TestCount(void);
static void TestFreeIP(void);

int main(void)
{
	TestAllFuncs();
	return 0;
}

void TestAllFuncs(void)
{
	printf("~~STARTING TESTING ALL FUNCS~~\n");
	/*
	TestCreate();
	TestStringIpConversion();
	TestCount();
	TestFreeIP();
	*/
	TestAlloc();
	printf("~~FINSIHED TESTING ALL FUNCS~~\n");
	printf("~~~~~~~~~~~~RUN VLG~~~~~~~~~~~\n");
}

void TestCreate(void)
{
	dhcp_t *dhcp = DHCPCreate(DHCPStringToIp("192.168.1.0"), 24);
	if (dhcp != NULL)
	{
		printf("DHCPCreate working!                                  V\n");
	}
	else
	{
		printf("DHCPCreate NOT working!                              X\n");
	}

	DHCPDestroy(dhcp);
}

static void TestStringIpConversion(void)
{
	char str[50] = "192.168.1.1";
	char str2[50] = {0};
	uint32_t ip = DHCPStringToIp(str);
	DHCPIpToString(ip, str2);

	if (0 == strcmp(str, str2))
	{
		printf("DHCPStringToIp & DHCPIpToString working!             V\n");
	}
	else
	{
		printf("DHCPStringToIp & DHCPIpToString NOT working!         X\n");
	}
}

static void TestAlloc(void)
{
	dhcp_t *dhcp = DHCPCreate(DHCPStringToIp("192.168.1.0"), 24);
	char buffer2[50] = {0};
	uint32_t tmp = DHCPStringToIp("192.168.1.1");
	uint32_t tmp3 = 0;
	int i = 0;
	int j = 0;

	for (i = 0; i < 20; i++)
	{
		DHCPAllocateIp(dhcp, tmp, &tmp3);
		printf("alloc %d %s\n", i, DHCPIpToString(tmp3, buffer2));
		for (j = 0; j < 50; j++)
		{
			buffer2[j] = '\0';
		}

		tmp3 = 0;
	}

	DHCPDestroy(dhcp);
}

static void TestCount(void)
{
	dhcp_t *dhcp = DHCPCreate(DHCPStringToIp("192.168.1.0"), 24);

	if (253 == DHCPCountFree(dhcp))
	{
		printf("DHCPCountFree working!                               V\n");
	}
	else
	{
		printf("DHCPCountFree NOT working!                           X\n");
	}
	DHCPDestroy(dhcp);
}

static void TestFreeIP(void)
{
	dhcp_t *dhcp = DHCPCreate(DHCPStringToIp("192.168.1.0"), 24);
	uint32_t tmp = DHCPStringToIp("192.168.1.1");
	uint32_t tmp2;

	DHCPAllocateIp(dhcp, tmp, &tmp2);
	DHCPFreeIp(dhcp, tmp2);

	if (253 == DHCPCountFree(dhcp))
	{
		printf("DHCPFreeIp working!                                  V\n");
	}
	else
	{
		printf("DHCPFreeIp NOT working!                              X\n");
		printf("count need to be 253 but was %ld\n", DHCPCountFree(dhcp));
	}
	DHCPDestroy(dhcp);
}