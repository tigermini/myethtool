#include <stdio.h>
#include <string.h>
#include "myethtool.h"

int main(void)
{
    int speed, duplex, autoneg, link;
    int eth_ret;
    char devname[20];

    speed = duplex = autoneg = link = -1;
    printf("please input the devname:\n");

    scanf("%s", devname);

    eth_ret = ethtool_methset(devname, &speed, &duplex, &autoneg, &link);

    if (eth_ret < 0) {
        printf("ethtool_methset error\n");
    }

    printf("the lookup info is \n devname = %s, speed = %d, \
    duplex = %d, autoneg = %d, link =%d\n", devname, speed, duplex, autoneg, link);

    return 0;
}
