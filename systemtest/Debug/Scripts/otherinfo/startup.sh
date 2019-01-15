#########################################################################
# File Name: startup.sh
# Author: liujing
# mail: 2510034575@qq.com
# Created Time: 2015年01月21日 星期三 21时12分51秒
#########################################################################
#!/bin/bash

#显示开机自启动项(S开头)
base=56
#（点击更多信息按钮时可查看到）root权限显示的信息	
#验证输入的用户名密码是否正确，并把错误信息重定向到垃圾桶里
	echo $1 | sudo -S echo -n 2> /dev/null
	if [ $? == 0 ];then
		#得到rc0.d~rc6.d、rcS.d这几个目录的路径
		filelist=`echo $1 | sudo -S find /etc -name "rc*.d"`
		for file in $filelist 
		do	
			#把rc0.d~rc6.d、rcS.d这几个目录下的所有文件名定向到result0中
			find $file -name "S*" >> result0
		done
		#去除result中的重复行，并重定向到result1中
		sort -u result0 > result1
		startup=`cat result1|wc -l`
		echo -e "系统开机自启动项总数：$startup"  #统计启动项个数
		echo ""
		echo "Ubuntu新系统的开机自启动项数一般是$base"
		echo ""
		subs=$[$startup-$base]
		sutil=`awk 'BEGIN{printf"%.2f\n",'$subs' / '$base'*100}'`
		echo "系统新增开机自启动项数：$subs"
		echo ""
		echo "比刚装的新系统增加了：$sutil%"
			echo ""
#删除result0、result1
		rm -rf result0 result1
		#筛选可建议关闭的启动项
		echo "建议可关闭的启动项如下(用户程序一般是2运行级别)："
		#find /etc/rc2.d -name "S*" >> startinfo
		#startup=`cat startinfo|wc -l`

		#softnum=`dpkg -l | awk '{if(NR!=1&&NR!=2&&NR!=3&&NR!=4&&NR!=5) {print $2}}'|wc -l`
		#dpkg -l | awk '{if(NR!=1&&NR!=2&&NR!=3&&NR!=4&&NR!=5) {print $2}}'> softinfo
		#for((i=1;i<=$softnum;i++))
		#do
			#softname=`cat softinfo|awk NR==$i'{print $1}'`
			#cat startinfo |grep -v "saned"|grep -v "grub-common" |grep -v "speech-dispatcher"|grep -v "rsync"|grep $softname 
		#done
		#rm -rf startinfo softinfo
		#筛选rc2.d的开机自启动项
		find /etc/rc2.d -name "S*" >> startinfo
		#过滤掉不能关闭的开机自启动项(有些开机自启动项关闭可能会有问题)		
		cat startinfo |grep -v "saned"|grep -v "grub-common" |grep -v "speech-dispatcher"|grep -v "rsync"|grep -v "ondemand"|grep -v "rc.local"|grep -v "kerneloops"
		rm -rf startinfo
fi
