##########################################################################
#tips:
    #相对于用date命令获取系统的启动时间，采用dmesg的方法，更为准确些，更加稳定
    #start_last.txt存放最后启动时间/时长
    #start_prev.txt存放上次启动时间/时长
##########################################################################
#/bin/bash

#此函数计算系统开机所用时间单位是秒数
function run_time (){
  #计算出dmesg中系统启动记录的时间相对文件开头的时间
  a=`cat /var/log/dmesg | grep "setting system" | awk '{print $2}'`
  run=${a%?}
  run=${run:0:1}
  #获取dmesg中系统启动时记录的时间
  start_hour=$[`cat /var/log/dmesg | grep "setting system" | awk '{print $10}' | awk   -F: '{print int($1)}'`*3600]
  start_min=$[`cat /var/log/dmesg | grep "setting system" | awk '{print $10}' |  awk -F: '{print int($2)}'`*60]
  start_sec=$[`cat /var/log/dmesg | grep "setting system" | awk '{print $10}' |  awk -F: '{print int($3)}'`]
  #做减法获取真正系统启动的时间
  start_time=$[$start_hour+$start_min+$start_sec-$run]
  #获取图形登入界面启动的时间，这里有两个要去掉父进程为1的进程，取最近时间的进程
  end_time=0
  for pid in $(pgrep lightdm); 
  do 
  t2=`ps -p ${pid} -o lstart=`
  end_hour=$[`echo $t2 | awk '{print $4}' | awk -F: '{print int($1)}'`*3600]
  end_min=$[`echo $t2 | awk '{print $4}' | awk -F: '{print int($2)}'`*60]
  end_sec=$[`echo $t2 | awk '{print $4}' | awk -F: '{print int($3)}'`]
  t1=$[$end_hour+$end_min+$end_sec]
   #echo "t1="$t1
  if [ $t1 -gt $end_time ]
  then
    end_time=$t1
  fi
  done
  #获取系统启动的时长
  cur_runtime=$[$end_time - $start_time]
  #为了判断cmos有问题，还是格林尼治时间的处理，要把结果减去28800
  if [ $cur_runtime -ge 28800 ]
  then 
     cur_runtime=$[$cur_runtime - 28800]
     
  fi     
  #返回系统启动时长
  echo $cur_runtime
}

#此函数将开机所用的的秒数格式化转换成时分秒
function date_time()
{
  min=0
  hour=0
  #一般情况下针对个人PC开机时长是不会超过一个小时的
  min=$[$[ $1 / 60 ] %60]
  second=$[$1 % 60]
  if [ $1 -gt 60 ]
  then
    echo "您本次开机用了$min分$second秒"
  else
    echo "您本次开机用了$second秒" 
  fi
}
#此函数比较本次开机时长与上次开机时长的快慢
function diff(){
  if [ $1 -gt $2 ]
	then
		dif=$[$1-$2]
		echo "比上次慢了"$dif"秒"
	elif [ $1 -lt $2 ]
	then
		dif=$[$2-$1]
		echo "比上次快了"$dif"秒"
	else [ $1 -eq $2 ]
		echo "与上次相等"  
  fi
  
}
#此函数评测开机时间的等级
function level_time(){

  if [ $1 -ge 0 -a $1 -le 5 ]
  then
     echo "恭喜你!击败了全国99%的用户" 
  elif [ $1 -gt 5 -a $1 -le 10 ]
     then
  echo "恭喜你!击败了全国95%的用户" 
     elif [ $1 -gt 10 -a $1 -le 20 ]
  then
     echo "恭喜你!击败了全国90%的用户" 
  elif [ $1 -gt 20 -a $1 -le 30 ]
  then
     echo "恭喜你!击败了全国80%的用户" 
  elif [ $1 -gt 30 -a $1 -le 40 ]
     then
  echo "恭喜你!击败了全国60%的用户" 
     elif [ $1 -gt 40 -a $1 -le 50 ]
  then
     echo "恭喜你!击败了全国40%的用户" 
  elif [ $1 -gt 50 -a $1 -le 60 ]
  then
     echo "恭喜你!击败了全国35%的用户" 
  elif [ $1 -gt 60 -a $1 -le 70 ]
  then
     echo "恭喜你!击败了全国25%的用户" 
  elif [ $1 -gt 70 -a $1 -le 80 ]
  then
     echo "恭喜你!击败了全国15%的用户" 
  elif [ $1 -gt 80 -a $1 -le 90 ]
  then
     echo "恭喜你!击败了全国5%的用户" 
  elif [ $1 -gt 60 ]
  then
     echo "你击败了全国4%的用户, 继续加油!" 
fi
}

#此函数获取系统开机时间
function boot_time(){
   boottime=`cat /var/log/dmesg | grep "setting system" | awk '{print $9$10}'`
   echo $boottime
}
#此函数获取start_last.txt文件中的开机时间
function earn_last1(){
   last1=`cat /usr/share/systemtest/application/systemtest/start_last.txt | awk NR==1'{print $1}'` 
   echo $last1 
}
#此函数获取start_last.txt文件中的开机时长
function earn_last2(){
   last2=`cat /usr/share/systemtest/application/systemtest/start_last.txt | awk NR==2'{print int($1)}'`
   echo $last2
}
#此函数获取start_prev.txt文件中的开机时间
function earn_prev1(){
   prev1=`cat /usr/share/systemtest/application/systemtest/start_prev.txt | awk NR==1'{print $1}'` 
   echo $prev1 
}
#此函数获取start_prev.txt文件中的开机时长
function earn_prev2(){
   prev2=`cat /usr/share/systemtest/application/systemtest/start_prev.txt | awk NR==2'{print int($1)}'`
   echo $prev2
}
  
  btime=$(boot_time)  
  timelength=$(run_time)
#-s 表示文件是否存在并且是否为非空
if [ -s /usr/share/systemtest/application/systemtest/start_last.txt ]
then
  #如果有时间，将时间和时长保存到变量  
  last_1=$(earn_last1)
  last_2=$(earn_last2) 
  #如果stat_last.txt文件中最后启动时间与现在系统本次取得的启动时间一样
  #一样（本次启动后多次运行）
  if [ $last_1 = $btime ]
  then
      #判断start_prev.txt是否有数据
      if [ -s /usr/share/systemtest/application/systemtest/start_prev.txt ]
      #如果有，将其保存变量
      then
          
           prev_1=$(earn_prev1)          
           prev_2=$(earn_prev2)
           #用上次启动时长和最后启动时长作比较           
           last_1=$(earn_last1)           
           last_2=$(earn_last2)
           date_time $last_2
           diff $last_2 $prev_2
           level_time $last_2           
      #如果没有，输出本次启动时长和评测等级(第一次启动后的多次运行)
      else
          echo $btime >/usr/share/systemtest/application/systemtest/start_last.txt
          echo $timelength >>/usr/share/systemtest/application/systemtest/start_last.txt
          #输出本次启动时长和评测等级  
          date_time $timelength
          level_time $timelength
      fi  
  #如果不一样（二次启动后的第一次运行）
  else
      #用start_last.txt中的最后启动时长和系统中的本次启动时长作比较
      
      last_1=$(earn_last1)
      
      btime=$(boot_time)
      if [ last_1 != btime ]
      then
        `mv  /usr/share/systemtest/application/systemtest/start_last.txt /usr/share/systemtest/application/systemtest/start_prev.txt`
         echo $btime >/usr/share/systemtest/application/systemtest/start_last.txt         
         timelength=$(run_time)
         echo $timelength >>/usr/share/systemtest/application/systemtest/start_last.txt
         #计算启动时差         
         last_2=$(earn_last2)        
         prev_2=$(earn_prev2)
         #输出本次启动时长和评测等级
         date_time $last_2
         #计算差值输出比上次的快慢
         diff $last_2 $prev_2
         level_time $last_2      
      fi
  fi
  
else
  #如果没有，记录本次时间和时长到文件start_last.txt中
  echo $btime >/usr/share/systemtest/application/systemtest/start_last.txt
  echo $timelength >>/usr/share/systemtest/application/systemtest/start_last.txt
  #输出本次启动时长和评测等级  
  date_time $timelength
  level_time $timelength  
fi






