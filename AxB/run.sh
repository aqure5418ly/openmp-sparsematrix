#!/bin/bash


# 编译程序
gcc -fopenmp AxB.c -o AxB

# 初始化一个变量来存储总时间
total_time=0

# 运行程序10次
echo "" > times.txt
for i in {1..10}
do
    # 运行程序并把结果输出到一个文件
    ./AxB > output.txt

    # 从文件中提取时间并添加到总时间
    time=$(tail -n 1 output.txt | awk '{print $3}')  # 假设时间在输出的最后一行，第三个字段
    total_time=$(echo "$total_time + $time" | bc)
    echo $time >> times.txt

    # 删除输出文件
    rm output.txt
done

# 计算平均时间
average_time=$(echo "scale=6; $total_time / 10" | bc)
echo "Average time: $average_time"
