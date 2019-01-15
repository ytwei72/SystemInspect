#########################################################################
# File Name: tcp_rrate.sh
# Author: liujing
# mail: 2510034575@qq.com
# Created Time: 2015年01月12日 星期一 15时53分54秒
#########################################################################
#!/bin/bash
gvar=60

po=`cat /proc/net/snmp |grep "Tcp"|grep -A1 "PassiveOpens" |awk NR==2'{print int($7)}'`

idata=`cat /proc/net/snmp |grep -A1 "Udp: InDatagrams" |awk NR==2'{print int($2)}'`

odata=`cat /proc/net/snmp |grep -A1 "Udp: InDatagrams" |awk NR==2'{print int($5)}'`

sleep $gvar

ponew=`cat /proc/net/snmp |grep "Tcp"|grep -A1 "PassiveOpens" |awk NR==2'{print int($7)}'`
idatanew=`cat /proc/net/snmp |grep -A1 "Udp: InDatagrams" |awk NR==2'{print int($2)}'`
odatanew=`cat /proc/net/snmp |grep -A1 "Udp: InDatagrams" |awk NR==2'{print int($5)}'`

#平均每秒新增TCP连接数
posub=$[$ponew-$po]
pos=`awk 'BEGIN{printf"%.2f\n",'$posub' / '$gvar'}'`
echo "平均每秒新增的TCP连接数$posub"

#平均每秒的UDP接收数据报
idatasub=$[$idatanew-$idata]
idatas=`awk 'BEGIN{printf"%.2f\n",'$idatasub' / '$gvar'}'`
echo "平均每秒接收的UDP数据报：$idatas"

#平均每秒的UDP发送数据报
odatasub=$[$odatanew-$odata]
odatas=`awk 'BEGIN{printf"%.2f\n",'$odatasub' / '$gvar'}'`
echo "平均每秒发送的UDP数据报：$odatas"

 
