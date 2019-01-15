#!/bin/bash
#查看是否开机自动绑定IP和MAC地址
ap=`cat /etc/init.d/rc.local |grep "arp -f /etc/ip-mac" |wc -l`
if [ $ap == 0 ];then
	echo 0 #"开机自启动ARP欺骗防护未开启！"
else
	echo 1 #"开机自启动ARP欺骗防护已开启！"
fi
