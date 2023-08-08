#!/bin/bash

# 编译源文件
gcc -fopenmp sparseAxB.c CSRcreate_bak.c -o run2 -lm

# 检查编译是否成功
if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

# 清空time.txt文件
echo "" > times2.txt

# 运行程序10次，并将Time数据记录到time.txt文件中
for i in {1..10}; do
    echo "Running iteration $i..."
    ./run2 | grep "Time" | awk '{print $3}' >> times2.txt
done

# 计算平均时间，并打印到控制台
echo "Calculating average time..."
awk '{ sum += $1; n++ } END { if (n > 0) print "Average Time =", sum / (n-1); }' times2.txt
