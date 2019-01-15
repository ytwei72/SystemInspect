#########################################################################
# File Name: disktool.sh
# Author: liujing
# mail: 2510034575@qq.com
# Created Time: 2015年01月07日 星期三 15时09分50秒
#########################################################################
#!/bin/bash
#echo $1 |sudo -S echo -n 2> /dev/null
#if [ $? == 0 ];then
	#sudo -S apt-get -y install sysstat > /dev/null
	iostat > /dev/null
	if [ $? -ne 0 ];then
		echo "IO测试工具安装失败sysstat（可能软件源有问题），无法测试IO性能"
	else 
		#echo "sysstat已安装"
	
	#r/s
	echo -e "每秒读I/O设备次数：\t\t\t`iostat -x -k |grep "sda"|awk '{print $4}'`"
	#w/r
	echo -e "每秒写I/O设备次数：\t\t\t`iostat -x -k |grep "sda"|awk '{print $5}'`"
	echo ""
	#rkB/s
	echo -e "每秒读K字节数：\t\t\t`iostat -x -k |grep "sda"|awk '{print $6}'`"
	#wkB/s
	echo -e "每秒写K字节数：\t\t\t`iostat -x -k |grep "sda"|awk '{print $7}'`"
	echo ""
	#avgqu-sz
	echo -e "平均I/O队列长度：\t\t\t`iostat -x -k |grep "sda"|awk '{print $9}'`"
	echo ""
	#avgrq-sz
	echo -e "平均每次设备I/O操作的数据大小(扇区)：\t`iostat -x -k |grep "sda"|awk '{print $8}'`"
	echo ""
	#await
	echo -e "平均每次设备I/O操作的等待时间(毫秒)：\t`iostat -x -k |grep "sda"|awk '{print $10}'`"
	#svctm
	echo -e "平均每次设备I/O操作的服务时间(毫秒)：\t`iostat -x -k |grep "sda"|awk '{print $13}'`"
	echo ""
	#util
	a=`iostat -x -k|grep "sda"|awk '{print int($2)}'`
	if [ $a -ge 70 -a $a -lt 95 ];then
		echo -e "一秒中有百分之多少的时间用于 I/O 操作：\t`iostat -x -k |grep "sda"|awk '{print $2}'`（I/O压力比较大）"
	elif [ $a -ge 95 -a $a -lt 100 ];then
		echo -e "一秒中有百分之多少的时间用于 I/O 操作：\t`iostat -x -k |grep "sda"|awk '{print $2}'`（I/O请求太多，磁盘可能存在瓶颈）"
	fi
	echo -e "一秒中有百分之多少的时间用于 I/O 操作：\t`iostat -x -k |grep "sda"|awk '{print $2}'`"
	echo ""
	#mpstat测系统启动以后所有硬盘IO平均等待时间
	ioindex=`mpstat |tail -1|awk '{print int($6)}'`
	if [ $ioindex -lt 20 ];then
		echo -e "系统启动后硬盘IO平均等待时间(%)：\t`mpstat |tail -1|awk '{print $6}'`（磁盘IO状态指标良好）"
	elif [ $ioindex -ge 20 ];then
		echo -e "系统启动后硬盘IO平均等待时间(%)：\t`mpstat |tail -1|awk '{print $6}'`（磁盘IO状态指标不是很良好）"

	fi
fi
#else 
#	echo "密码输入错误！"
#fi
