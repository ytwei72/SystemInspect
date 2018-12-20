#!/bin/bash

################################################################################
#计算每秒无线网网速
#判断有多少个无线网卡,有的电脑可能有wlan0、wlan1
wnum=`cat /proc/net/dev |grep "wlan" |wc -l`
#判断本机有没有无线网卡
if [ $wnum -gt 0 ];then
	#循环求每个无线网卡的网速
	for((i=0;i<$wnum;i++))
	do
		m=`ethtool wlan$i |grep "Link detected: yes" |wc -l` > /dev/null #判断无线网是否连接
		if [ $m -eq 1 ] 
		then
			wla=wlan$i


			#提取下载速度
			#求出一秒前后流量的差值,作为这一秒的下载网速, 从/proc/net/dev文件中.
			RXpre=$(cat /proc/net/dev | grep $wla | tr : " " | awk '{print $2}')
			sleep 1
			RXnext=$(cat /proc/net/dev | grep $wla | tr : " " | awk '{print $2}')

			RX=$((${RXnext}-${RXpre}))

			#流量单位转换
			if [[ $RX -lt 1024 ]];then
				RX="${RX}B/s"
			elif [[ $RX -gt 1048576 ]];then
				RX=$(echo $RX | awk '{print $1/1048576 "MB/s"}')
			else
				RX=$(echo $RX | awk '{print $1/1024 "KB/s"}')
			fi	
			#输出下载速度
			#echo -e "当前下载速度为 $RX"

			#提取上传速度
			#求出一秒前后流量的差值,作为这一秒的上传网速, 从/proc/net/dev文件中
			TXpre=$(cat /proc/net/dev | grep $wla | tr : " " | awk '{print $10}')
			sleep 1
			TXnext=$(cat /proc/net/dev | grep $wla | tr : " " | awk '{print $10}')
			TX=$((${TXnext}-${TXpre}))
			#流量单位转换	 
			if [[ $TX -lt 1024 ]];then
				TX="${TX}B/s"
			elif [[ $TX -gt 1048576 ]];then
				TX=$(echo $TX | awk '{print $1/1048576 "MB/s"}')
			else
				TX=$(echo $TX | awk '{print $1/1024 "KB/s"}')
			fi
			#输出下载速度
			echo -e "无线网下载速度 $RX 上传速度 $TX " 

		else
			echo "无线网未连接"
		fi
	done
else
	echo "本机没有有线网卡"
fi

