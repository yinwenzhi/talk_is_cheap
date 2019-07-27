# 0003 无重复字符的最长字串
这道题让我想起了算法课讲起的一个问题，什么样的问题适合用分治，什么样的问题适合用递归。

## 问题描述
给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

示例 1:

输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

示例 2:

输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。

示例 3:

输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-substring-without-repeating-characters
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

## 解题思路
采用 分治法 果然最难的是如何合并两个分支。  做到两点也没做出来,这就是不成功的做法
```
class Solution:
    @classmethod
    def lengthOfMid(self,s:str) -> int:
        if len(s)%2 ==0  :
            ll = len(s)//2-1
            lr = len(s)//2
            if s[ll] == s[lr]:
                return 1
        else :
            ll = lr = len(s)//2+1
            
        lml1 = 0
        lmr1 = 0
        lml2 = 0
        lmr2 = 0
        i = 0
       
        while not (  lmr1 and lmr2) : 
            neg = 1
            
            if (lr + 1) >= len(s)  or (ll-1) < 0  :
                lml2 = -1
                lmr2 = -1

            # 如果左边一位不在中间子串中 就把左边界左移一位
            if s[ll+i*neg] in s[ll:lr+1]:
                if lml1 == 0:
                    lml1 = ll
                else : 
                    lml2 = ll
            else:
                if ll !=0:
                    ll -=1
                else:
                    ll =0
            neg *= -1
                
            # 如果右边一位不在中间子串中 就把右边界右移一位
            if s[lr+i*neg] in s[ll:lr+1]:
                if  lmr1 == 0:
                    lmr1 = lr  
                else : 
                    lmr2 = lr 
            else:
                if lr <= len(s):
                    lr +=1
                else:
                    lr =len(s)+1
        lm = max(lmr1-lml1+1,max(lmr2-lml1+1, lmr1-lml2+1) )

        return lm
    
    
    def lengthOfLongestSubstring(self, s: str) -> int:
        
        if len(s)==0:
            return 0
        if len(s)==1:
            return 1
        else:
            ll = self.lengthOfLongestSubstring(s[:len(s)//2])
            lr = self.lengthOfLongestSubstring(s[len(s)//2:])
            return max(lr,max(ll,self.lengthOfMid(s)))
```

然后修改了下 但是总有样例不能通过
```
class Solution:
    @classmethod
    def isRepeat(self,s :str) -> bool:
        myset=set([])
        for i in (s):
            if i in myset :
                # print('i in set ', i )
                return True
            myset.add(i )
            # print('set = ', set )
        return False


    
    @classmethod
    def lengthOfLongestSubstring(self, s: str) -> int:
        longest = 0
        if(len(s) == 0):
            return 0
        if(len(s) == 1):
            return 1
        for i in range(len(s)):
            
            for j in range(i+1,len(s)+1):
                # print('Solution.isRepeat(s[i:j]) is  {}'.format(Solution.isRepeat(s[i:j])))
                if not Solution.isRepeat(s[i:j]):
                    if (j -i ) > longest:
                        longest = j - i  
                else:
                    break
        return longest 
```



## 查看了官方结题思路
### 方法一：
逐个检查所有的子字符串 ，看它是否含有重复的字符。
1. 假设字串从i到j 那么，所有的字串是 0 <= i <= j <= n,那么 i从0到n-1循环，j从 i+1 到 n-1 循环 
2. 检查是否包含有重复的字符的实现。对于一个字符串，从第一个开始放入一个集合中，每次放入的时候判断是否包含重复的字串。

```
class Solution:

     def lengthOfLongestSubstring(self, s: str) -> int:
          longest = 0
          max_Long = 0
          for i in range(len(s)):
               myset = ''
               myset += s[i]
               longest = 1
               max_Long = max_Long if max_Long > longest else longest
               for j in range(i+1,len(s)):
                    # print('Solution.isRepeat(s[i:j]) is  {}'.format(Solution.isRepeat(s[i:j])))
                    #  if not Solution.isRepeat(s[i:j]):
                    if s[j] not in myset:
                         myset += s[j]
                         if (len(myset)  > longest ):
                         longest = len(myset)
                         max_Long = max_Long if max_Long > longest else longest
                    else:
                         break
          return max_Long
```


### 方法二：滑动窗口的方法
1. 假设有个从零开始的窗口，这个窗口在字符串的开始位置，加入这个窗口可以向右增长，而且窗口内的字符串不重复，那么窗口就一直增长，直到不能再增长为止。
2. 这时，把窗口中重复的那个字符及之前的字符丢弃，如果这时候窗口长度可以增长，就增长窗口长度直到不能增长为止，然后再向右移动窗口，如此循环往复，直到窗口到达字符串的最右端。

方法一修改以下就是滑动窗口方法
```
class Solution:

    def lengthOfLongestSubstring(self, s: str) -> int:
        longest = 0
        i = 0
        j = i + 1
        
        if len(s) == 0 :
            return 0
        if len(s) == 1 :
            return 1
        myset = s[0]
        
        while (j < len(s)):

            if s[j] not in myset:
                j += 1
            else:
                i = i + myset.index( s[j] ) + 1
                j += 1
            myset = s[i:j]
            if (len(myset)  > longest ):
                longest = len(myset)                
        return longest 

```

