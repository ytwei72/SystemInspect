#!/bin/bash
#计算平均IO响应时间await，一般地系统IO响应时间应该低于5ms，如果大于10ms就比较大了，await、svctm越低越好，说明io响应延迟很低，iops能力很高

#第1个域：读完成次数 ----- 读磁盘的次数，成功完成读的总次数
rio=`cat /proc/diskstats |grep "0 sda" |awk '{print int($4)}'`

#第5个域：写完成次数 ----写完成的次数，成功写完成的总次数。
wio=`cat /proc/diskstats |grep "0 sda" |awk '{print int($8)}'`

#第4个域：读花费的毫秒数，这是所有读操作所花费的毫秒数。
ruse=`cat /proc/diskstats |grep "0 sda" |awk '{print int($7)}'`

#第8个域：写操作花费的毫秒数  ---  写花费的毫秒数，这是所有写操作所花费的毫秒数
wuse=`cat /proc/diskstats |grep "0 sda" |awk '{print int($11)}'`

#await:平均每次设备I/O操作的等待时间 (毫秒)(IO Response Time),包括在请求队列中的时间和响应消耗时间，即 (ruse+wuse)/(rio+wio)
rwuse=$[$ruse+$wuse]
rwio=$[$rio+$wio]
await=`awk 'BEGIN{printf"%.2f\n",'$rwuse' / '$rwio'}'`
echo "$await"
