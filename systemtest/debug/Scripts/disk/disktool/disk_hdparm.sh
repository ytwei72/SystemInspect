#########################################################################
# File Name: disk_speed.sh
# Author: liujing
# mail: 2510034575@qq.com
# Created Time: 2015年01月06日 星期二 20时06分08秒
#########################################################################
#!/bin/bash
#hdparm工具磁盘读取速度
echo $1 |sudo -S echo -n 2> /dev/null
if [ $? == 0 ];then
	#lshw命令测磁盘信息	
#	sudo lshw > disk_lshw
#	echo "磁盘类型：`cat disk_lshw |grep -B10 "capabilities: partitioned partitioned:dos" |grep "description:"|awk -F: '{print $2}'`" > diskinfo

#	#echo "产品：`cat disk_lshw |grep -B10 "capabilities: partitioned partitioned:dos" |grep "product:"|awk -F: '{print $2}'`" >> diskinfo

#	echo "供应商：`cat disk_lshw |grep -B10 "capabilities: partitioned partitioned:dos" |grep "vendor:"|awk -F: '{print $2}'`" >> diskinfo

#	echo "逻辑名称：`cat disk_lshw |grep -B10 "capabilities: partitioned partitioned:dos" |grep "logical name:"|awk -F: '{print $2}'`" >> diskinfo

#	echo "版本：`cat disk_lshw |grep -B10 "capabilities: partitioned partitioned:dos" |grep "version:"|awk -F: '{print $2}'`" >> diskinfo

#	#echo "序列号：`cat disk_lshw |grep -B10 "capabilities: partitioned partitioned:dos" |grep "serial:"|awk -F: '{print $2}'`">> diskinfo

#	#echo "大小：`sudo lshw |grep -B10 "capabilities: partitioned partitioned:dos" |grep "size:"|awk -F: '{print $2}'`" >> diskinfo
#	rm -rf disk_lshw
	#######################################################################################
	#hdparm命令测磁盘信息
	sudo hdparm -I /dev/sda > hdparm_test
	v_judge=`cat hdparm_test |wc -l` 2> /dev/null
	if [ $v_judge -gt 50 ];then
	hs=`cat hdparm_test |grep "Rotation" |awk '{print int($5)}'`
	if [ $hs -eq 5400 ];then
		echo -e "磁盘转速：\t\t\t`cat hdparm_test |grep "Rotation" |awk '{print $5}'` 转/s（普通速度，笔记本磁盘主流转速）" 
	elif [ $hs == 7200 ];then
		echo -e "磁盘转速：\t\t\t`cat hdparm_test |grep "Rotation" |awk '{print $5}'` 转/s（中等速度，台式机磁盘主流转速）" 
	elif [ $hs == 10000 ];then
		echo -e "磁盘转速：\t\t\t`cat hdparm_test |grep "Rotation" |awk '{print $5}'` 转/s（中高等速度）" 
	elif [ $hs == 15000 ];then
		echo -e "磁盘转速：\t\t\t`cat hdparm_test |grep "Rotation" |awk '{print $5}'` 转/s（高速）"
	else
		echo -e "磁盘转速：\t\t\t`cat hdparm_test |grep "Rotation" |awk '{print $5}'` 转/s（目前硬盘速度一般在5400-15000转/s）" 
	fi
	fi
	sudo hdparm -Tt /dev/sda >> hdparm_test
	echo -e "磁盘缓存的读取速度：\t\t`cat hdparm_test |grep "cached" |awk '{print $10 $11}'`" 
	echo -e "磁盘的读取速度：\t\t`cat hdparm_test |grep "disk" |awk '{print $11 $12}'`"
	rm -rf hdparm_test
fi
