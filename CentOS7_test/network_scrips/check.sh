#!/bin/sh
############################################################################################################################
# FileName£º CheckNetwork.sh
# Info:      A script to check and configure network
############################################################################################################################
ScriptHome="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
string=""
LogDir=/var/log
####Network IP type
DHCP="dhcp"
STATIC="static"

echo `date` >CheckNetwork.log
####Logical NIC name£¬normally named [eth0]
#RDEVICE=`route -n|grep '^0.0.0.0'|awk '{print $8}'`
#DEVICE=`ip -o link show | awk '{print $2,$9}' |grep -e 'UP' -e 'UNKNOWN'|awk -F : '{print $1}'|head -2|tail -1`

####boot device
DEVICE=`ifconfig -a| awk '{print $1}'|head -1| cut -c -4` 
ifup $DEVICE

####IP address
IPADDR=`ifconfig $DEVICE|grep 'inet addr:'|awk '{sub(/addr:/,""); print $2}'`
####netmask
NETMASK=`ifconfig $DEVICE|grep 'Mask'|awk '{sub(/Mask:/,""); print $4}'`
#NETWORK= `/usr/bin/perl /root/ipcalc.pl $IPADDR -n |grep 'Network:' |awk '{print $2}'`
####gateway
GATEWAY=`route -n|grep '^0.0.0.0'|awk '{print $2}'`


###If configured device is null, means there's no NIC available or network cable is not connected.
if [ ! -n "$DEVICE" ];then   
   #Try another method to check the active NIC
   ####Logical NIC name with status "link ok"
   DEVICE=`/sbin/mii-tool |grep 'link ok' |awk '{sub(/:/,""); if(NR==1) print $1}'`
   if [ ! -n "$DEVICE" ];then
      echo "Network cable not connected or No network adapter is available!"|tee -a >CheckNetwork.log
	  exit 1
   else
      echo "The linked device is ["$DEVICE"]" |tee -a >CheckNetwork.log
   fi
else
    echo "The linked device is ["$DEVICE"]" |tee -a >CheckNetwork.log
fi
####Get the device(NIC name) which has been configured. 

 
setDEVICE=$DEVICE
echo "The configured DEVICE is ["$setDEVICE"]"  |tee -a >CheckNetwork.log

####Get current Network type(dhcp or static)
configFile="/etc/sysconfig/network-scripts/ifcfg-$setDEVICE"
TYPE=`cat $configFile |grep 'BOOTPROTO'|cut -c 11-`
echo "The configured network type is ["$TYPE"]" |tee -a >CheckNetwork.log

####If the IP is null£¬means the network is not configured,that we need to set to DHCP and then convert to static IP
   
if [ "$IPADDR"x = "$string"x ] || [ "$GATEWAY"x = "$string"x ];then
        echo "Get network information fail, configure dhcp now" |tee -a >CheckNetwork.log

        echo "Restart network ..." |tee -a >CheckNetwork.log
        /etc/init.d/network restart
        /bin/bash $ScriptHome/dhcp-to-static.sh  
        ####If the current configured network type is DHCP £¬and the devices also match(The configured device and the linked device are the same£©£¬then convert static IP directly.
else if [ "$TYPE"x = "$DHCP"x ];then 
            echo "Network has been set to DHCP and device is match,convert to static IP now!" |tee -a >CheckNetwork.log
          /bin/bash $ScriptHome/dhcp-to-static.sh
			
       fi
fi
