flag=0
#检查firefox有没有安装
a=`dpkg -l | awk '{if(NR!=1&&NR!=2&&NR!=3&&NR!=4&&NR!=5) {print $2}}' |grep "firefox" |wc -l`
if [ $a -gt 0 ];then
#检测有没有firefox跟踪cookies
path=`find ~/.mozilla/firefox -type d -name "*.default"`
cd $path
fc0=`ls -l |grep "cookies.sqlite" |wc -l`
if [ $fc0 -eq 1 ];then
	fc1=`ls -l cookies.sqlite |awk '{print $5}'`
	if [ $fc1 -gt 0 ];then
		((flag++))
		echo $flag
	else
		echo $flag
	fi
else
	echo $flag
fi
fi
