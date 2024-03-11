#include <iostream>
#include <map>
using namespace std;

class Solution {
public:
    int longestSubstring(string s, int k) {
        map<char,int> mp;
        int len=0,flag=1,loc_now=0,loc_bef=0,max=1,count=0;

        len=s.length();
        for(int i=0;i<len;++i)
        {
            if(mp.count(s[i]))
                ++mp[s[i]];
            else
                mp.insert({s[i],1});
        }
        for(int i=0;i<len;++i)
        {
            if(mp[s[i]]<k)
            {
                flag=0;
                break;
            }
        }
        if(flag==1)
            return len;
        else
        {
            while(true)
            {
                loc_bef=loc_now;
                for(;loc_now<len;++loc_now)
                {
                    if(mp[s[loc_now]]<k)
                        break;
                }
                string mid(s,loc_bef,loc_now-loc_bef);
                count=longestSubstring(mid,k);
                if(max<count)
                    max=count;
                if(loc_now==len)
                    break;
                ++loc_now;
            }
            return max;
        }
    }
};

int main() 
{
	Solution s;
	
	cout<<s.longestSubstring("bbaaacbd",3);
	return 0;
}
