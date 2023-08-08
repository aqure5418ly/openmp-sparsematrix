#!/bin/bash

# ����Դ�ļ�
gcc -fopenmp sparseAxB.c CSRcreate_bak.c -o run2 -lm

# �������Ƿ�ɹ�
if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

# ���time.txt�ļ�
echo "" > times2.txt

# ���г���10�Σ�����Time���ݼ�¼��time.txt�ļ���
for i in {1..10}; do
    echo "Running iteration $i..."
    ./run2 | grep "Time" | awk '{print $3}' >> times2.txt
done

# ����ƽ��ʱ�䣬����ӡ������̨
echo "Calculating average time..."
awk '{ sum += $1; n++ } END { if (n > 0) print "Average Time =", sum / (n-1); }' times2.txt
