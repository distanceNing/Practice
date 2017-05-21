#!/bin/sh
############################################################################################################################
# FileName： CheckNetwork.sh
# Info:      A script to check and configure network
# Author:    ZL
############################################################################################################################
ScriptHome="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
string=""
LogDir=/var/log
####Network IP type
DHCP="dhcp"
STATIC="static"

echo `date` >$LogDir/CheckNetwork.log
####Logical NIC name，normally named [eth0]
#RDEVICE=`route -n|grep '^0.0.0.0'|awk '{print $8}'`
DEVICE=`ip -o link show | awk '{print $2,$9}' |grep -e 'UP' -e 'UNKNOWN'|awk -F : '{print $1}'|head -2|tail -1`
#
####IP address
IPADDR=`ifconfig $DEVICE|grep 'inet addr:'|awk '{sub(/addr:/,""); print $2}'`
####netmask
NETMASK=`ifconfig $DEVICE|grep 'Mask'|awk '{sub(/Mask:/,""); print $4}'`
#NETWORK= `/usr/bin/perl /root/ipcalc.pl $IPADDR -n |grep 'Network:' |awk '{print $2}'`
####gateway
GATEWAY=`route -n|grep '^0.0.0.0'|awk '{print $2}'`
#
#BROADCAST=`/usr/bin/perl /root/ipcalc.pl $IPADDR -n |grep 'Broadcat:' |awk '{print $2}'`
#HWADDR=`ifconfig $DEVICE|grep 'HWaddr'|awk '{print $5}'`
####hostname
#HOSTNAME=`hostname`
#
####Info in the network configurat-*on file
该文件描述系统上可用的网络接口以及如何激活它们。有关详细信息，请参阅接口（5）。
Info1="#This file describes the network interfaces available on your system and how to activate them. For more information, see interfaces(5)."

环回网络接口
Info2="# The loopback network interface"

主要网络接口
Info3="# The primary network interface"

LOOP="auto lo"
LOOPBACK="iface lo inet loopback"



###If configured device is null, means there's no NIC available or network cable is not connected.
如果配置的设备为空，表示没有NIC网卡可用或网络电缆未连接。
if [ ! -n "$DEVICE" ];then   
	尝试其他方法寻找网卡
   #Try another method to check the active NIC
   ####Logical NIC name with status "link ok"
   DEVICE=`/sbin/mii-tool |grep 'link ok' |awk '{sub(/:/,""); if(NR==1) print $1}'`
   if [ ! -n "$DEVICE" ];then
      echo "Network cable not connected or No network adapter is available!"|tee -a $LogDir/CheckNetwork.log
	  exit 1
   else
      echo "The linked device is ["$DEVICE"]" |tee -a $LogDir/CheckNetwork.log
   fi
else
    echo "The linked device is ["$DEVICE"]" |tee -a $LogDir/CheckNetwork.log
fi
####Get the device(NIC name) which has been configured. 

 
查找到网卡 进行配置
setDEVICE=`cat /etc/network/interfaces |grep '^auto'|awk '{if(NR==2) print $2}'`
echo "The configured DEVICE is ["$setDEVICE"]"  |tee -a >CheckNetwork.log

####Get current Network type(dhcp or static)
TYPE=`cat /etc/network/interfaces |grep '^iface'|awk '{if(NR==2) print $4}'`
echo "The configured network type is ["$TYPE"]" |tee -a $LogDir/CheckNetwork.log

   ####If the IP is null，means the network is not configured,that we need to set to DHCP and then convert to static IP
   
	如果IP为空，表示网络未配置，我们需要设置为DHCP，然后转换为静态IP
if [ "$IPADDR"x = "$string"x ] || [ "$GATEWAY"x = "$string"x ];then
        echo "Get network information fail, configure dhcp now" |tee -a $LogDir/CheckNetwork.log
        cat <<EOF >/etc/network/interfaces
		searching for a valid kernel header path
$Info1
$Info2
$LOOP
$LOOPBACK
auto $DEVICE
iface $DEVICE inet dhcp
EOF
        echo "Restart network ..." |tee -a $LogDir/CheckNetwork.log
        /etc/init.d/networking restart
        /etc/network/interfaces
        /bin/bash $ScriptHome/DHCP-to-STATIC.sh  这里要使用DHCP脚本
        ####If the current configured network type is DHCP ，and the devices also match(The configured device and the linked device are the same），then convert static IP directly.
		设备匹配且网络类型为DHCP，直接转换为静态IP
else if [ "$TYPE"x = "$DHCP"x ] && [ "$setDEVICE"x = "$DEVICE"x ];then 
            echo "Network has been set to DHCP and device is match,convert to static IP now!" |tee -a $LogDir/CheckNetwork.log
            /bin/bash $ScriptHome/DHCP-to-STATIC.sh
			######## If the current configured network type is DHCP ，But the devices not match(The configured device and the linked device are NoT the same）
			######## We need to modify the configured device correctly first,restart network and then convert static .
			重新启动网络，然后转换静态:
     else if [ "$setDEVICE"x != "$DEVICE"x ] && [ "$TYPE"x = "$DHCP"x ];then
                 echo "Network has set to DHCP ,but device not match,need to be reset and convert to STATIC!" |tee -a $LogDir/CheckNetwork.log
                 cat <<EOF >/etc/network/interfaces
$Info1
$Info2
$LOOP
$LOOPBACK
auto $DEVICE
iface $DEVICE inet dhcp
EOF
                echo "Restart network ..." |tee -a $LogDir/CheckNetwork.log
                /etc/init.d/networking restart
                cat /etc/network/interfaces
                sudo /bin/bash $ScriptHome/DHCP-to-STATIC.sh   
          else if [ "$setDEVICE"x != "$DEVICE"x ] && [ "$TYPE"x = "$STATIC"x ];then
		  网络配置为静态，但是设备不匹配，需要重置！
                     echo "Network has set to STATIC ,but device not match,need to be reset!" |tee -a $LogDir/CheckNetwork.log
                     sed -i "s/$setDEVICE/$DEVICE/g" /etc/network/interfaces
                     echo "Restart network ..." |tee -a $LogDir/CheckNetwork.log
                     /etc/init.d/networking restart
                     echo "Network config is:" |tee -a $LogDir/CheckNetwork.log
                     cat /etc/network/interfaces |tee -a $LogDir/CheckNetwork.log
               else
                     echo "Network has been configured!" |tee -a $LogDir/CheckNetwork.log
               fi
           fi
       fi
fi



