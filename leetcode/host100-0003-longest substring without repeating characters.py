class Solution:
    @classmethod
    def isRepeat(self,s :str) -> bool:
        myset=set([])
        for index, si in enumerate(s):
            print(' index = {}   myset = {}'.format(index,myset))
            if si in myset :
               
                return True
            myset.add(si )
            print(' myset added  change to {} '.format(myset))
        return False


    
    @classmethod
    def lengthOfLongestSubstring(self, s: str) -> int:
        longest = 0
        for i in range(len(s)):
            for j in range(i+1,len(s)+1):
                print('s[i:j] is  {}'.format(s[i:j]))
                if not Solution.isRepeat(s[i:j]):

                    if (j -i  ) > longest:
                        longest = j - i 
                else:
                    pass
        return longest  

if __name__=="__main__":
    string = "aaaaaaac"


    k = Solution.lengthOfLongestSubstring(string)
    print("string={}\nk = {}".format(string,k))



   
