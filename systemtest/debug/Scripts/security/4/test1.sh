#!/bin/bash
#******************************#
#Author:xuelimin
#Function:md5校验文件内容是否相同
#******************************#
echo $1 |sudo -S echo -n 2> /dev/null
if [ $? == 0 ];then
shopt -s -o nounset
Time=$(date +'%Y-%m-%d_%H:%M:%S')
#查找的目录
Dirs="/bin /sbin "
#新建文件
Temp=$(mktemp /tmp/check.XXXX)
#存储的文件
PWD="/usr/share/systemtest/application/systemtest"
File=" $PWD/bin.$Time.file"
#使用工具
Check_tool="/usr/bin/md5sum"
Find="/usr/bin/find"
#使用函数
#查找目录下的普通文件
search_file(){
	#局部变量
	local f
	for f in $Dirs
	do
		sudo $Find $f -type f >> $Temp
	done
}
#生成md5值
create_md5(){
	local f
	if [ -f $Temp ];then
		for f in $(cat $Temp);
			do
				$Check_tool $f >> $File
			done
	else
		echo "failed"
	fi
}
rm_file(){
	if [ -f $Temp ];then
		  rm -rf $Temp
	fi
}


search_file
create_md5
rm_file


#查找文件是否篡改
md5sum -c $File 
#查找篡改出的文件
md5sum -c $File | grep "确定"
fi
