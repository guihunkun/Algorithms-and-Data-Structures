#include <iostream>
#include <string>
#include "vector"
#include "map"
#include "set"
#include "queue"
#include "stack"
#include "unordered_map"

using namespace std;


#if 0


#endif


/*
 * 1
 * LeetCode 1423. 可获得的最大点数
 * https://leetcode-cn.com/problems/maximum-points-you-can-obtain-from-cards/
 */
int maxScore(vector<int>& cardPoints, int k)
{
    // 求两边最大值，就是求中间的最小值，即以求中间的数组连续部分的最小值
    int sum = 0;
    for(auto num : cardPoints)
    {
        sum += num;
    }
    int n = cardPoints.size();
    int window = 0;
    for(int i = 0; i < n - k; i++)
    {
        window += cardPoints[i];
    }
    int minW = window;
    for(int i = n-k; i < n; i++)
    {
        window += cardPoints[i];
        window -= cardPoints[i-n+k];
        minW = min(minW, window);
    }
    return sum - minW;
}


/*
 * 2
 * LeetCode 3 : 无重复字符的最长子串
 * https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/
 */
int lengthOfLongestSubstring(string s)
{
    set<char> record;
    int res=0,left=0,right=0;
    while(right<s.size())
    {
        if(record.find(s[right])==record.end())
        {
            record.insert(s[right++]);
            res=max(res,(int)record.size());
        }
        else
        {
            record.erase(s[left++]);
        }
    }
    return res;
}


/*
 * 3
 * LeetCode 1004 : 最大连续1的个数 III
 * https://leetcode-cn.com/problems/max-consecutive-ones-iii/
 */
int longestOnes(vector<int>& nums, int k)
{
    //使从区间[l , r] 内部0的数量不超过k就行
    int l = 0,r = 0, ans = 0, cnt = 0;
    while(r < nums.size())
    {
        if(nums[r] == 0)
            cnt++;
        if(cnt > k)
        {
            if(nums[l] == 0)
                cnt--;
            l++;
        }
        ans = max(ans, r-l+1);
        r++;
    }
    return ans;
}


/*
 * 4
 * LeetCode 1438 : 绝对差不超过限制的最长连续子数组
 * https://leetcode-cn.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/
 */
int longestSubarray(vector<int>& nums, int limit)
{
    // multiset能时刻保证序列中的数是有序的，而且序列中可以存在重复的数。
    multiset<int> s;
    int ans = 0;
    int i = 0;
    for(int j = 0; j < nums.size(); j++)
    {
        s.insert(nums[j]);
        while(*s.rbegin() - *s.begin() > limit)
        {
            s.erase(s.find(nums[i]));
            i++;
        }
        ans = max(ans, j - i + 1);
    }
    return ans;
}


/*
 * 5
 * LeetCode 76 : 最小覆盖子串
 * https://leetcode-cn.com/problems/minimum-window-substring/
 */
string minWindow(string s, string t)
{
    /*
     * 滑动窗口:，首先左右指针指向S的开头，然后右指针右移直到可以包含T，
     * 这个时候记录下来子字符串的长度，然后左指针左移，判断当前子字符串是否包含T，
     * 直到左指针左移到不包含T为止。然后右指针右移。
     */
    unordered_map<char, int> rec;
    for(auto c : t)
        rec[c] ++;
    int len = 0, n = s.size();
    int minlen = n;
    string res = "";
    int l = 0, r = 0;
    for( ; r < n; r++)
    {
        rec[s[r]]--;
        if(rec[s[r]] >= 0)
            len++;
        while(len == t.size())
        {
            if(r - l + 1 <= minlen)
            {
                minlen = r - l + 1;
                res = s.substr(l, r - l + 1);
            }
            rec[s[l]] ++;
            if(rec[s[l]] > 0)
                len--;
            l++;
        }
    }
    return res;
}


int main()
{
    cout<<"Sliding Window"<<endl;
    return 0;
}
