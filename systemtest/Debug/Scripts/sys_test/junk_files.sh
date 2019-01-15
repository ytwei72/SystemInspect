#########################################################################
# File Name: junk_files.sh
# Author: liujing
# mail: 2510034575@qq.com
# Created Time: 2015年01月07日 星期三 16时24分32秒
#########################################################################
#!/bin/bash
flag=0
#查看回收站垃圾大小
a1=`du -ks $HOME/.local/share/Trash/files/ | awk '{print int($1)}'`

#查看无用软件包垃圾大小，/var/cache/apt/archives是安装软件时下载包的临时存放目录
a2=`du -ks /var/cache/apt/archives | awk '{print int($1)}'`

#查看是缩略图缓存垃圾大小
a3=`du -ks ~/.cache/thumbnails/ |awk '{print int($1)}'`


sum=$[$a1+$a2+$a3]
if [ $sum -ge 0 -a $sum -lt 1048576 ];then
	echo $flag
elif [ $sum -ge 1048576 ];then
	((flag++))
	echo $flag #"您的磁盘垃圾已超过1G，最好及时清理！"
fi





