#!/bin/sh
########################################################################################################################################
#FileName: dhcp-to-static
#Info:  Converting DHCP scope to static IP address
########################################################################################################################################

echo "Converting DHCP scope to static IP address"
###
#RDEVICE=`route -n|grep '^0.0.0.0'|awk '{print $8}'`
###Get device name(NIC logical name,normally named [eth0]),status is "link ok"

#DEVICE=`ip -o link show | awk '{print $2,$9}' |grep -e 'UP' -e 'UNKNOWN'|awk -F : '{print $1}'|head -2|tail -1`
DEVICE=`ifconfig -a| awk '{print $1}'|head -1| cut -c -4` 
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

###
IPADDR=`ifconfig $DEVICE|grep 'inet addr:'|awk '{sub(/addr:/,""); print $2}'`
###
NETMASK=`ifconfig $DEVICE|grep 'Mask'|awk '{sub(/Mask:/,""); print $4}'`
###
GATEWAY=`route -n|grep '^0.0.0.0'|awk '{print $2}'`

HWADDR=`ifconfig $DEVICE|grep 'HWaddr'|awk '{print $5}'`
###
HOSTNAME=`hostname`
###DNS
DNS_google="8.8.8.8"
DNS_Aliyun="223.5.5.5"
DNS_Telecom="202.103.224.68"
DNS_Unicom="221.7.128.68"




###configure the network （modify:/etc/network/interfaces）
cat <<EOF >/etc/sysconfig/network-scripts/ifcfg-$DEVICE
DEVICE=$DEVICE
HWADDR=$HWADDR
TYPE=Ethernet
UUID=538d8b6a-53ac-4818-96ca-8e1ea12a5be0
ONBOOT=yes
NM_CONTROLLED=yes
BOOTPROTO=static
IPADDR=$IPADDR
NETMASK=$NETMASK
GATEWAY=$GATEWAY
NM_CONTROLLED=no	
DNS=$DNS_google
EOF



echo "Restsart network"
/etc/init.d/network restart


###Modify hosts file
echo "Config hosts"
cat <<EOF >/etc/sysconfig/network
NETWORKING=yes
NETWORKING_IPV6=no
HOSTNAME=localhost.localdomain
GATEWAY=$GATEWAY
EOF

echo "Restsart network"
/etc/init.d/network restart
exit 0
