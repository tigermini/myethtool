#ifndef _MYETHTOOL_H_
#define _MYETHTOOL_H_

extern int ethtool_methset(char *devname, int *speed, int *duplex, int *autoneg, int *link);

#endif