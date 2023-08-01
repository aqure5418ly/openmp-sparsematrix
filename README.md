# 矩阵乘法项目

本项目包括两个子目录，分别针对传统矩阵乘法和稀疏矩阵乘法的计算。所有代码都使用了OpenMP 4.5版本进行并行编程，并可能需要在Linux环境下运行。

## 目录结构
```
matrix/
│
├── A*B/
│   ├── AxB.c            # 使用OpenMP的并行矩阵相乘计算
│   ├── AxB_single.c     # 不使用并行编程技术的常规矩阵相乘计算
│   ├── run.sh           # 代码运行脚本，默认运行10次
│   └── AxB.xlsx         # 记录不同线程数量下代码的运行表现的Excel表格
│
├── sparseA*B/
│   ├── sparseAxB.c      # 使用OpenMP的并行稀疏矩阵计算
│   ├── CSRcreate.c      # CSR格式随机矩阵生成函数源文件
│   ├── CSRcreate.h      # CSR格式随机矩阵生成函数头文件
│   ├── run2.sh          # 代码运行脚本，默认运行10次
│   └── sparseAxB.xlsx   # 记录不同线程数量下代码的运行表现的Excel表格
│
├── compare.xlsx         # 记录稀疏矩阵计算与常规矩阵计算之间的差别的Excel表格
└── readme.md            # 项目的README文件
```

## 运行环境
OpenMP 4.5
Linux操作系统

## 用法
切换到sh脚本所在目录下并运行脚本
```
./run.sh
```
如果需要更改运行线程数量，请修改源文件中的线程数量宏定义