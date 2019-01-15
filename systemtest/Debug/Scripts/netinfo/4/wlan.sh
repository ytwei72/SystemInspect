#/proc/uptime第一列输出的是，系统启动到现在的时间（以秒为单位）
ut=`cat /proc/uptime |awk '{print $1}'`

#无线网流量信息
num2=`cat /proc/net/dev |grep "wlan" |wc -l`
if [ $num2 -gt 0 ];then
for((j=0;j<$num2;j++))
do 
	echo "当前 wlan$j 接口流量信息(自系统启动到当前)"
#bytes 接收的总字节数
wrbytes=`cat /proc/net/dev |grep "wlan$j"|awk '{print $2}'`
echo -e "接收的总字节数：\t\t$wrbytes"
wbavg=`awk 'BEGIN{printf"%.2f\n",'$wrbytes' / '$ut'}'`
echo -e "平均每秒接收的字节数：\t$wbavg"

#packets 接收的报文总数
wrpackets=`cat /proc/net/dev |grep "wlan$j"|awk '{print $3}'`
echo -e "接收的报文总数：\t\t$wrpackets"
wpavg=`awk 'BEGIN{printf"%.2f\n",'$wrpackets' / '$ut'}'`
echo -e "平均每秒接收的报文数：\t$wpavg"

#compressed 接收的压缩报数
wrcompressed=`cat /proc/net/dev |grep "wlan$j"|awk '{print $8}'`
echo -e "接收的压缩报数：\t\t$wrcompressed"
wrbavg=`awk 'BEGIN{printf"%.2f\n",'$wrcompressed' / '$ut'}'`
echo -e "平均每秒接收的压缩报数：\t$wrbavg"

#multicast 接收到的多播报数
wrmulticast=`cat /proc/net/dev |grep "wlan$j"|awk '{print $9}'`
echo -e "接收到的多播报数：\t\t$wrmulticast"
wmavg=`awk 'BEGIN{printf"%.2f\n",'$wrmulticast' / '$ut'}'`
echo -e "平均每秒接收的多播报数：\t$wmavg"

#frame接收时帧错误数
wrframe=`cat /proc/net/dev |grep "wlan$j"|awk '{print $7}'`
echo -e "接收时帧错误数：\t\t$wrframe"
wfavg=`awk 'BEGIN{printf"%.2f\n",'$wrframe' / '$ut'}'`
#echo "平均每秒接收的错误帧：$wfavg"

#errs 接收时被设备驱动监测到的错误报文总数
wrerrs=`cat /proc/net/dev |grep "wlan$j"|awk '{print $4}'`
echo "接收时设备监测到的错误报文总数：$wrerrs"
wravg=`awk 'BEGIN{printf"%.2f\n",'$wrerrs' / '$ut'}'`
#echo "平均每秒接收的错误报文：$wravg"

#drop 由于系统资源限制，接收时被设备驱动丢弃的报文总数
wdrop=`cat /proc/net/dev |grep "wlan$j"|awk '{print $5}'`
echo -e "接收时设备丢弃的报文总数：\t$wdrop"
wdavg=`awk 'BEGIN{printf"%.2f\n",'$wdrop' / '$ut'}'`
#echo "接收时平均每秒丢弃的报文数：$wdrop"
 
echo ""

#bytes 发送的总字节数
wrbytes=`cat /proc/net/dev |grep "wlan$j"|awk '{print $10}'`
 echo -e "发送的总字节数：\t\t$wrbytes"
wbavg=`awk 'BEGIN{printf"%.2f\n",'$wrbytes' / '$ut'}'`
echo -e "平均每秒发送的字节数：\t$wbavg"

#packets 发送的报文总数
wtpackets=`cat /proc/net/dev |grep "wlan$j"|awk '{print $11}'`
echo -e "发送的报文数：\t\t$wtpackets"
wpbavg=`awk 'BEGIN{printf"%.2f\n",'$wtpackets' / '$ut'}'`
echo -e "平均每秒发送的报文数：\t$wpbavg"

#compressed 发送的压缩报数
wtcompressed=`cat /proc/net/dev |grep "wlan$j"|awk '{print $17}'`
echo -e "发送的压缩报数：\t\t$wtcompressed"
wcomavg=`awk 'BEGIN{printf"%.2f\n",'$wtcompressed' / '$ut'}'`
echo -e "平均每秒发送的压缩报数：\t$wcomavg"

#errs 发送时被设备驱动监测到的错误报文总数
wterrs=`cat /proc/net/dev |grep "wlan$j"|awk '{print $12}'`
echo -e "发送时设备检测到的错误报文数：\t$wterrs"
webavg=`awk 'BEGIN{printf"%.2f\n",'$wterrs' / '$ut'}'`
#echo "平均每秒发送的错误报文：$webavg"

#drop 由于系统资源限制，发送时被设备驱动丢弃的报文总数
wtdrop=`cat /proc/net/dev |grep "wlan$j"|awk '{print $13}'`
echo -e "发送时设备丢弃的报文总数：\t$wtdrop"
wdavg=`awk 'BEGIN{printf"%.2f\n",'$wtdrop' / '$ut'}'`
#echo "发送时平均每秒丢弃的报文数：$wdavg"

#colls 接口检测到的冲突数
wtcolls=`cat /proc/net/dev |grep "wlan$j"|awk '{print $15}'`
echo -e "接口检测到的冲突数：\t\t$wtcolls"
wcavg=`awk 'BEGIN{printf"%.2f\n",'$wtcolls' / '$ut'}'`
#echo "平均每秒的冲突数：$wcavg"

#carrier 连接介质出现故障次数, 如 : 网线接触不良
wtcarriers=`cat /proc/net/dev |grep "wlan$j"|awk '{print $16}'`
echo -e "连接介质出现故障次数：\t$wtcarriers"
wcaravg=`awk 'BEGIN{printf"%.2f\n",'$wtcarriers' / '$ut'}'`
#echo "平均每秒的连接故障数：$wcaravg"

done
else 
	echo "未检测到无线网卡的信息，本机可能没有无线网卡或者无线网卡已坏"
fi

