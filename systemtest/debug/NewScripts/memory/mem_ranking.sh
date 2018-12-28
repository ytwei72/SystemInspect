#cpu
#echo "占用cpu最高的前三名进程"
#echo "PID号  CPU%   进程名"
#ps aux|grep -v PID|sort -rn -k +3|head -n 3|awk '{print $2"   "$3"    "$11}'
#echo
#memory
#echo "占用内存最高的前三名进程"
#echo "PID号  内存%  进程名"
ps aux|grep -v PID|sort -rn -k +4|head -n 20|awk '{print "PID:"$2"RATE:"$4"NAME:"$11"END"}'
