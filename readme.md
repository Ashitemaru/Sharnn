# SHA-RNN

SHA-RNN: Recurrent Neural Network and Chaotic System for hash functions

[Abstract] 

## Introduction

## Related Works

### Sponge Function

![123](https://s2.loli.net/2022/05/14/jPtJW9BGEbS35au.png)

<center>Figure 1: 海绵函数的示意图<br/>Credit: Wikipedia [1]</center>

​		**海绵函数（Sponge Function）**是一种算法，它可以接受任意长度的输入比特流，得到任意长度的输出。它的参数为单次输出比特长度 $r$，隐藏状态长度 $r+c$，状态转移函数 $f$。其工作流程可以分为**吸收（Absorb）**与**挤出（Squeeze）**两个阶段，其工作流程如图 1 所示，描述如下。

​		在吸收阶段，海绵函数单次接受长度为 $r$ 的消息分组，与上个阶段的隐藏状态 $r$ 比特进行异或，将异或后的隐藏状态经过状态转移函数 $f$ 得到新的隐藏状态。在挤出阶段，我们每次从隐藏状态中提取 $r$ 比特，然后将隐藏状态再经过状态转移函数 $f$，如此往复，直到我们得到足够长的消息摘要为止。

### Recurrent Neural Network





## SHA-RNN

## Evalutaion

## References

[1] Bertoni G, Daemen J, Peeters M, et al. Sponge functions[C]//ECRYPT hash workshop. 2007, 2007(9).

[2] 