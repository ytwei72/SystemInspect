#!/bin/bash
#检查根分区是否正常可用
flag=0
#验证输入的用户名密码是否正确，并把错误信息重定向到垃圾桶里
echo $1 | sudo -S echo -n 2> /dev/null
if [ $? == 0 ];then
device_name=(`df -lh |grep  "^/dev/sd"|awk '{print $1}'`)
mount_dir=(`df -lh |grep  "^/dev/sd"|awk '{print $6}'`)
num=${#device_name[@]}

sudo touch ${mount_dir[0]}/file1
        if [ $? -eq 0 ]
        then
	((flag++))
        echo $flag #根分区可用，能正常创建文本文件
        else
        echo $flag #根分区不能正常创建文本文件
        fi
sudo rm -rf ${mount_dir[0]}/file1
fi
