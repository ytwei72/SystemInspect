#!/bin/bash
root_pwd=$1
echo ${root_pwd}
 
#获取当前脚本目录
#cmddir=`dirname $0`
#cmddir=`cd ${cmddir}/;pwd`

#get the current user path
cmddir=$HOME
#echo ${cmddir}

#定义一个临时脚本，该脚本用于输出切换用户后的当前用户
temp_script="${cmddir}/temp.sh"
 
#生成temp_script脚本及其内容
echo  '#!/bin/bash' >${temp_script}
input_pwd='echo ' + ${root_pwd}
echo ${input_pwd} >>${temp_script}
echo 'pwd' >>${temp_script}
 
#定义切换用户函数
get_user()
{
su - root<<EOF
bash ${temp_script}
EOF
}
 
#执行切换函数，并获取输出结果
user=`get_user`
 
#判断是否root用户
echo ${user}
if [ "${user}" == "/root" ]
then
     echo "Y"
else
     echo "N"
fi
