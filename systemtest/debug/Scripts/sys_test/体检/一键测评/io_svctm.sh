#!/bin/bash
##svctm:平均每次设备I/O操作的服务时间 (毫秒),svctm不超过5
#第1个域：读完成次数 ----- 读磁盘的次数，成功完成读的总次数
rio=$(cat /proc/diskstats |grep " 0 sda " |awk NR==1'{print int($4)}')

#第5个域：写完成次数 ----写完成的次数，成功写完成的总次数。
wio=$(cat /proc/diskstats |grep " 0 sda " |awk NR==1'{print int($8)}')

#第10个域：输入/输出操作花费的毫秒数--花在I/O操作上的毫秒数，这个域会增长只要field 9不为0,系统真正花费在I/O上的时间，除去重复等待时间(use)（从系统启动时的累积值）
use=$(cat /proc/diskstats |grep " 0 sda " |awk NR==1'{print int($13)}')

rwio=$[$rio+$wio]
#svctm:平均每次设备I/O操作的服务时间 (毫秒)，即 use/(rio+wio)
svctm=$(awk 'BEGIN{printf"%.2f\n",'$use' / '$rwio'}')
echo $svctm  #平均每次设备I/O操作的服务时间svctm
