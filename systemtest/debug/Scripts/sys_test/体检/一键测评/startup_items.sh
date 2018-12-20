#!/bin/bash
#显示开机自启动项(S开头)
if [ -n "$1" ];then
#验证输入的用户名密码是否正确，并把错误信息重定向到垃圾桶里
	echo $1 | sudo -S echo -n 2> /dev/null
	if [ $? == 0 ];then
#得到rc0.d~rc6.d、rcS.d这几个目录的路径
		filelist=`echo $1 | sudo -S find /etc -name "rc*.d"`
		for file in $filelist 
		do	
#把rc0.d~rc6.d、rcS.d这几个目录下的所有文件名定向到./shell/result0中
			find $file -name "S*" >> result0
		done
#去除./shell/result中的重复行，并重定向到./shell/result1中
		sort -u result0 > result1
		startup=`cat result1|wc -l`
		echo $startup  #统计启动项个数
#删除./shell/result0、result1
		rm result0 
		rm result1
	fi
fi


