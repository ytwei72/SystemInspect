#!/bin/bash
#返回0表示ip都没有静态绑定，被arp攻击的风险最大;返回1表示ip都静态绑定了,可以预防arp攻击;返回小数表示已绑定ip数占总ip数的比例
totalmark=5
#统计已经静态绑定的ip-mac数目
ap1=`arp -a |grep "PERM" |wc -l`
if [ $ap1 == 0 ];then
	echo $totalmark #"当前没有IP与网关MAC静态绑定（有被ARP攻击的风险）"
elif [ $ap1 -gt 0 ];then
	#统计未静态绑定的ip数目
	uap1=`arp -a|grep -v "PERM" |wc -l`
	if [ $uap1 == 0 ];then
		echo 1 #"当前所有IP和网关MAC都已经静态绑定(被ARP攻击的风险较小)"
	else

		ipnum=$[$ap1+$uap1]
		#计算静态绑定ip数占总ip数的比例
		secureutil=$(awk 'BEGIN{printf"%.2f\n",'$uap1' / '$ipnum'}')
		mark=$(awk 'BEGIN{printf"%.0f\n",'$secureutil' * '$totalmark' }')
		echo $mark
	fi
fi

