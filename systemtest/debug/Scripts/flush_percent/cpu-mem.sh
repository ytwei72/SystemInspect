#cpu
echo "占用cpu最高的前三名进程"
echo "PID号  CPU%   进程名"
ps aux|grep -v PID|sort -rn -k +3|head -n 3|awk '{print $2"   "$3"    "$11}'  
echo 
echo "占用内存最高的前三名进程"
echo "PID号  内存%  进程名"
ps aux|grep -v PID|sort -rn -k +4|head -n 3|awk '{print $2"   "$4"    "$11}' 
