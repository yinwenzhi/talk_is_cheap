#!/usr/bin/env python
# coding: utf-8

# In[137]:


import random
# import numpy as np


# In[138]:


list(range(10, 0, -1))


# In[139]:


def insertsort(arr):
    for current in range(0,len(arr)):
#         print("current:{}".format(current))
        temp = arr[current]
#         for compare in range(current-1,-1,-1):
        compare = current - 1
        while compare >= 0 and temp < arr[compare]:
            arr[compare+1]=arr[compare]
#             print("  compare{}".format(compare))
            compare -= 1
        arr[compare+1] = temp
#         print("  {}".format(arr))
    return arr


# In[140]:


arr = [x for x in range(20)]
random.shuffle(arr)
# print(arr)
insertsort(arr)


# In[174]:


def mergesort(arr):
    ans = []
    if len(arr)<2: 
        ans.extend(arr)
        
    else:
#         print("len(arr):{} len(arr)//2:{}".format(len(arr),len(arr)//2))
        a = mergesort(arr[0:len(arr)//2])
#         print("a:{}".format(a))
        b = mergesort(arr[len(arr)//2: len(arr)])
        while a and b:
            if a[0]<b[0]:
                ans.append(a.pop(0))
            else:
                ans.append(b.pop(0))
        if a:
            ans.extend(a)
        if b:
            ans.extend(b)
    return ans


# In[175]:


arr = [x for x in range(20)]
random.shuffle(arr)
print(arr)
mergesort(arr)


# In[ ]:





# 堆的顺序存储
# 
# - 若根结点存在序号0处
#     - i结点的父结点下标就为(i-1)/2。i结点的左右子结点下标分别为2*i+1和2*i+2。
#     - 最后一个非叶子结点下标为是[n/2]向下取整减1，n为结点个数.
# - 如果根结点是从1开始
#     - i结点的父结点下标就为i/2。i节点 左右孩子结点分别是2i和2i+1。
#     - 最后一个非叶子结点下标为是[n/2]向下取整
# 
# 
# 1. 如何由一个无序序列建成一个堆？
# 2. 如何在输出堆顶元素之后，调整剩余元素成为一个新的堆？
# 
# 先考虑第二个问题，一般在输出堆顶元素之后，视为将这个元素排除，然后用表中最后一个元素填补它的位置，自上向下进行调整：首先将堆顶元素和它的左右子树的根结点进行比较，把最小的元素交换到堆顶；然后顺着被破坏的路径一路调整下去，直至叶子结点，就得到新的堆。
# 我们称这个自堆顶至叶子的调整过程为“调整”。
# 
# 那么第一个问题从无序序列建立堆的过程就是一个反复“调整”的过程。即对所有的非叶子结点进行调整。
# 
# 

# In[ ]:





# In[232]:


# 堆调整函数
# 已知H[start~end]中除了start之外均满足堆的定义
# 本函数进行调整，使H[start~end]成为一个大顶堆 end后为有序区，不调整
def HeapAdjust(H,start,end):

    temp = H[start]
    i = 2*start + 1
    while i<end: 
        # 因为假设根结点的序号为0而不是1，所以i结点左孩子和右孩子分别为2i+1和2i+2
        if(i+1<end and H[i]<H[i+1]): # 左右孩子的比较
            i+=1                   # i为较大的记录的下标
         
        if(temp > H[i]):           # 左右孩子中获胜者与父亲的比较
            break

        # 将孩子结点上位，则以孩子结点的位置进行下一轮的筛选
        H[start]= H[i]
        start = i
        i*=2
        
    H[start]= temp   # 插入最开始不和谐的元素


# In[233]:


HeapAdjust([1,3,2,5,6,9,11,7],3,7)


# In[213]:


arr = [x for x in range(10)]
random.shuffle(arr)
arr


# In[235]:


# 从一个序列构建堆
def creatHeap(A):
    i = (len(A)-1)//2
    while i >= 0 :
        HeapAdjust(A,i,len(A))
        print("i:{} H:{}".format(i,A))
        i -= 1


creatHeap([2, 3, 0, 4, 6, 8, 9, 7, 5, 1])


# In[239]:


def heapsort(A):
    # 先建立大顶堆
    # for(int i=n/2; i>=0; --i)
    n = len(A)
    i = (n-1)//2
    while i >= 0 :
        HeapAdjust(A,i,len(A))
        i -= 1
        
    # 进行排序
    j = n-1
    while j > 0:

        # 最后一个元素和第一元素进行交换
        temp=A[j];
        A[j] = A[0];
        A[0] = temp;

        #然后将剩下的无序元素继续调整为大顶堆
        HeapAdjust(A,0,j-1)
        j -= 1
    return A
    
print(heapsort([2, 3, 0, 4, 6, 8, 9, 7, 5, 1]))


# In[ ]:




