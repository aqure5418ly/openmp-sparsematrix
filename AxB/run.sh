#!/bin/bash


# �������
gcc -fopenmp AxB.c -o AxB

# ��ʼ��һ���������洢��ʱ��
total_time=0

# ���г���10��
echo "" > times.txt
for i in {1..10}
do
    # ���г��򲢰ѽ�������һ���ļ�
    ./AxB > output.txt

    # ���ļ�����ȡʱ�䲢��ӵ���ʱ��
    time=$(tail -n 1 output.txt | awk '{print $3}')  # ����ʱ������������һ�У��������ֶ�
    total_time=$(echo "$total_time + $time" | bc)
    echo $time >> times.txt

    # ɾ������ļ�
    rm output.txt
done

# ����ƽ��ʱ��
average_time=$(echo "scale=6; $total_time / 10" | bc)
echo "Average time: $average_time"
