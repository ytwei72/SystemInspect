#!/bin/bash
#有线网卡信息
ecnum=`lspci |grep "Ethernet controller:"|grep -v "Wireless"|wc -l`
if [ $ecnum -ne 0 ];then
	echo "有线网卡"
	echo -e "个数：\t       $ecnum "
	echo -e "生产商：\t       `lspci | grep -i eth | grep -v "Wireless" | awk '{print $4,$5}'`" 
	echo -e "型号：\t      `lspci | grep -i eth | grep -v "Wireless" | cut -f3 -d ":" | sed 's/([^>]*)//g'`" 

	count_wireless=`lspci | grep -i Wireless | wc -l`

	#判断是否在虚拟情况下
	v_judge=`ethtool eth0 |wc -l`
	if [ $v_judge -ge 19 ];then
		echo -e "支持的端口：    `ethtool eth0 |grep "Supported ports:" |awk '{print $4}'`"
		echo -e "工作带宽：        `ethtool eth0 |grep "Speed:" |awk '{print $2}'`"

		estatus=`ethtool eth0 |grep "Link detected: yes" |wc -l`
		if [ $estatus -eq 1 ];then
			echo -e "当前状态：\t       连接"
		else 
			echo -e "当前状态：\t       未连接"
		fi

		echo ""

	fi
fi
########################################################################
#无线网卡信息
ncnum=`lspci |grep "Wireless Network Adapter" |wc -l`
echo "无线网卡"
echo -e "个数：\t       $ncnum "

if [ $count_wireless -ne 0 ]
then
	echo -e "生产商：\t       `lspci | grep "Wireless" | awk '{print $4,$5}'`" #（可优化）
	echo -e "型号：\t      `lspci | grep "Wireless" | cut -f3 -d ":" | sed 's/([^>]*)//g'`" 
	wstatus=`ethtool wlan0 |grep "Link detected: yes" |wc -l`
	if [ $wstatus -eq 1 ];then
		echo -e "当前状态：\t       连接"
	else 
		echo -e "当前状态：\t       未连接"
	fi
else
	echo -e "无线网卡：\t       无"
fi

echo ""
#提取硬件MAC地址
echo -e "网卡MAC地址：`ifconfig |grep "eth0" |awk '{print $5}'`" 

#内核路由表(U路由被启用,H目标是一个主机,G使用网关)
#route -n
#echo "注：标志Flags U表示路由被启用、H表示目标是一个主机、G表示使用网关"
echo ""
#查看ipv6是否开启
ip6=`cat /proc/sys/net/ipv6/conf/all/disable_ipv6`
if [ $ip6 == 0 ];then
	echo "IPv6是开启状态（目前网络主要使用IPv4协议，开启IPv6可能影响网络性能）"
fi



