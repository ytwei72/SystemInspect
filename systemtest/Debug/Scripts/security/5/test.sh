#!/bin/bash
#******************************#
#Author:xuelimin
#Function:md5校验文件内容是否相同
#******************************#
echo $1 |sudo -S echo -n 2> /dev/null
if [ $? == 0 ];then
PWD=$(pwd)
dir=$(ls -l $PWD|grep usr.bin.* |awk '{print $NF}')
#echo $dir
cd $PWD
#查找文件是否篡改
md5sum -c $dir
#查找篡改出的文件
md5sum -c $dir | grep "确定"
fi
