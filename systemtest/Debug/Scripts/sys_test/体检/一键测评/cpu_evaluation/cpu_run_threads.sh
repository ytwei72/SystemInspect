#! /bin/bash
#计算可运行队列的线程数（测评使用）
cpu_count=$(grep 'physical id' /proc/cpuinfo | sort -u | wc -l) #cpu个数
loadavg_1min=$( cat /proc/loadavg | awk '{print $1}') #cpu一分钟平均负载
task_per_cpu=$(awk 'BEGIN{printf"%.2f\n",'$loadavg_1min' / '$cpu_count'}')
#每个cpu的当前任务数
echo $task_per_cpu
