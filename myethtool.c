#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <linux/ethtool.h>
#include <linux/sockios.h>
#include <linux/if.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h> //close

#include "myethtool.h"

extern int ethtool_methset(char *devname, int *speed, int *duplex, int *autoneg, int *link)
{
    struct ethtool_cmd ecmd;
    struct ethtool_value edata;
    int fd, err;
    struct ifreq ifr;

    if (devname == NULL) {
        printf("devname is invalid!\n");
        return -1;
    }

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("ethtool_methset can't create socket!\n");
    }

    ecmd.cmd = ETHTOOL_GSET;    /* ethtool.h */

    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, devname);   /* devname like eth0 */
    ifr.ifr_data = (caddr_t)&ecmd;
    err = ioctl(fd, SIOCETHTOOL, &ifr);
    if (err < 0) {
        perror("cannot get device settings!\n");
        close(fd);
        return -1;
    }

    printf("PHY xx -%d/%s", ecmd.speed, (ecmd.duplex == DUPLEX_FULL) ? "Full" : "Half");
    printf("Auto-negotiation: %s", (ecmd.autoneg == AUTONEG_DISABLE) ? "off" : "on");

    switch (ecmd.speed) {
        case SPEED_10:
        case SPEED_100:
        case SPEED_1000:
        case SPEED_2500:
        case SPEED_10000:
            *speed = ecmd.speed;
            break;
        default:
            printf("Unknown! %d \n", ecmd.speed);
            break;
    };

    switch (ecmd.duplex) {
        case DUPLEX_FULL:
        case DUPLEX_HALF:
            *duplex = ecmd.duplex;
            break;
        default:
            printf("Unknown! %d\n", ecmd.duplex);
            break;
    };

    *autoneg = ecmd.autoneg;

    edata.cmd = ETHTOOL_GLINK;
    ifr.ifr_data = (caddr_t)&edata;
    err = ioctl(fd, SIOCETHTOOL, &ifr);
    if (err == 0) {
        *link = edata.data ? 1 : 0;
        printf("%s\n", edata.data ? "Up" : "Down");
    } else if (errno != EOPNOTSUPP) {
        perror("Cannot get link status!\n");
    }

    close(fd);

    return 0;
}
