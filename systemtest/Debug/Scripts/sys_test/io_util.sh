#!/bin/bash
#一秒中有百分之多少的时间用于I/O操作%util，小于等于70%，如果 %util 接近 100%，说明产生的I/O请求太多，I/O系统已经满负荷，该磁盘可能存在瓶颈。

#/proc/uptime第一列输出的是，系统启动到现在的时间（以秒为单位）
ut=`cat /proc/uptime |awk '{print $1}'`

#第10个域：输入/输出操作花费的毫秒数--花在I/O操作上的毫秒数，这个域会增长只要field 9不为0。
use=`cat /proc/diskstats |grep " 0 sda " |awk NR==1'{print int($13)}'`

#%util: 一秒中有百分之多少的时间用于 I/O 操作，或者说一秒中有多少时间 I/O 队列是非空的，即 delta(use)/s/1000 (因为use的单位为毫秒)
util=`awk 'BEGIN{printf"%.2f\n",'$use' / '$ut' / 1000 * 100}'`
echo "$util"
