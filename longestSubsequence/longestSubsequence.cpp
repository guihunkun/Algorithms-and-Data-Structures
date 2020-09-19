#include <iostream>
#include <string>
#include "vector"
#include "map"
#include "set"
#include "queue"
#include "stack"
#include "unordered_set"
using namespace std;


/*
最长连续递增序列(LCIS) : Longest Continuous Increasing Subsequence
最长上升子序列(LIS): Longest Increasing Subsequence
最长连续序列(LCS): Longest Consecutive Sequence
最长公共子序列(LCS): Longest Common Subsequence
子串与子序列区别：子串不可跳跃，子序列可以跳跃，如 “ACE”是“ABCDE”的子序列，而不是子串。 而“ABC”则是其子串。
*/


/*
 * 1
 * LeetCode 674 : 最长连续递增序列
 * https://leetcode-cn.com/problems/longest-continuous-increasing-subsequence/
 */
int findLengthOfLCIS(vector<int>& nums)
{
    if(nums.size() == 0)
        return 0;
    int res = 1, cur = 1;
    for(int i = 1; i < nums.size(); i++)
    {
        if(nums[i] > nums[i-1])
            cur++;
        else
        {
            res = max(cur, res);
            cur = 1;
        }
    }
    return max(res, cur);
}
/*
int findLengthOfLCIS(vector<int>& nums)
{
    //DP
    if(nums.size() == 0)
        return 0;
    vector<int> dp(nums.size(), 1);//自身形成递增序列
    int res = 1;
    for(int i = 1; i < nums.size(); i++)
    {
        if(nums[i] > nums[i - 1])
        {
            dp[i] = dp[i - 1] + 1;
            res = max(res, dp[i]);
        }
    }
    return res;
}
*/

/*
 * 2
 * LeetCode 673 : 最长递增子序列的个数
 * https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/
 */
int findNumberOfLIS(vector<int>& nums)
{
    if(nums.empty())
        return 0;
    int N = nums.size();
    // pair<int, int> 分别为最长递增长度与对应的数目
    vector<pair<int, int> > dp(N, {1, 1});
    int mx = 1;
    for(int i = 1; i < N; ++i)
    {
        for(int j = 0; j < i; ++j)
        {
            if(nums[i] > nums[j])
            {
                if(dp[i].first < dp[j].first + 1)
                {
                    dp[i] = {dp[j].first + 1, dp[j].second};
                } else if (dp[i].first == dp[j].first + 1) {
                    dp[i].second += dp[j].second;
                }
            }
        }
        mx = max(mx, dp[i].first);
    }
    int res = 0;
    for(int i = 0; i < N; ++i)
    {
        if(dp[i].first == mx)
        {
            res += dp[i].second;
        }
    }
    return res;
}

/*
 * 3
 * LeetCode 300 : 最长上升子序列
 * https://leetcode-cn.com/problems/longest-increasing-subsequence/
 */
/*
dp[i] 为考虑前 i 个元素，以第 i 个数字结尾的最长上升子序列的长度，注意 nums[i] 必须被选取。
状态转移方程为:
dp[i]=max(dp[j])+1, 其中 0≤j<i 且 num[j]<num[i]
整个数组的最长上升子序列即所有 dp[i] 中的最大值。
LIS_{length} = max(dp[i]),其中 0≤i<n
*/
int lengthOfLIS(vector<int>& nums)
{
    if(nums.empty())
        return 0;
    vector<int> dp(nums.size(), 1);
    int res = 1;
    for(int i = 0; i < nums.size(); ++i)
    {
        for(int j = 0; j < i; ++j)
        {
            if(nums[j] < nums[i])
            {
                dp[i] = max(dp[i], dp[j] + 1);
                res = max(res, dp[i]);
            }
        }
    }
    return res;
}

/*
 * 4
 * LeetCode 128 : 最长连续序列
 * https://leetcode-cn.com/problems/longest-consecutive-sequence/
 */
/*
1. 我们考虑枚举数组中的每个数 x，考虑以其为起点，不断尝试匹配 x+1,x+2,⋯ 是否存在，假设最长匹配到了
   x+y，那么以 x 为起点的最长连续序列即为 x,x+1,x+2,⋯,x+y，其长度为 y+1，我们不断枚举并更新答案即可。
2. 如果已知有一个 x,x+1,x+2,⋯,x+y 的连续序列，而我们却重新从 x+1，x+2 或者是 x+y 处开始尝试匹配，
   那么得到的结果肯定不会优于枚举 x 为起点的答案，因此我们在外层循环的时候碰到这种情况跳过即可。
3. 由于我们要枚举的数 x 一定是在数组中不存在前驱数 x−1 的，不然按照上面的分析我们会从 x−1 开始尝试匹配，
   因此我们每次在哈希表中检查是否存在 x−1 即能判断是否需要跳过了。
4. 外层循环需要 O(n) 的时间复杂度，只有当一个数是连续序列的第一个数的情况下才会进入内层循环，
   然后在内层循环中匹配连续序列中的数，因此数组中的每个数只会进入内层循环一次。根据上述分析可知，总时间复杂度为 O(n)。
*/
int longestConsecutive(vector<int>& nums)
{
    int res = 0;
    unordered_set<int> rec(nums.begin(),nums.end());
    for(auto n : rec)
    {
        if(rec.count(n-1))
            continue;   //去重，当n前面的数字不存在时才可以作为一段序列的开头
        int cnt = 1;
        while(rec.count(++n))
            ++cnt;     //统计以n为第一个数字的序列的长度
        res = max(res,cnt);
    }
    return res;
}

/*
 * 5
 * LeetCode 1143 : 最长公共子序列
 * https://leetcode-cn.com/problems/longest-common-subsequence/
 */
// method 1
#if 0
自底向上 动态规划
dp[i][j]表示的是s1[0...i−1]与s2[0...j−1]的最长公共子序列的长度,要求的是dp[m−1][n−1]
动态转移方程：
dp[i][j] =
{
    dp[i−1][j−1]+1                 s1[i]==s2[j]
    max(dp[i−1][j],dp[i][j−1])     s1[i]!=s2[j]
​}
#endif
int longestCommonSubsequence(string text1, string text2)
{
    if(text1.empty() || text2.empty())
    {
        return 0;
    }
    vector<vector<int> > dp(text1.size() + 1, vector<int>(text2.size() + 1, 0));
    for(int i = 0; i < text1.size(); i++)
    {
        for(int j = 0; j < text2.size(); j++)
        {
            if(text1[i] == text2[j])
                dp[i+1][j+1] = dp[i][j] + 1;
            else
                dp[i+1][j+1] = max(dp[i][j+1], dp[i+1][j]);
        }
    }
    return dp[text1.size()][text2.size()];
}

// method 2
#if 0
// 自顶向下 递归 + 记忆化搜索
int recursion(string& text1, string& text2, int m, int n, vector<vector<int> >& memo)
{
    if(m < 0 || n < 0)
        return 0;
    if(memo[m][n] != -1)
        return memo[m][n];
    if(text1[m] == text2[n])
        memo[m][n] = recursion(text1, text2, m-1, n-1, memo) + 1;
    else
        memo[m][n] = max(recursion(text1, text2, m, n-1, memo), recursion(text1, text2, m-1, n, memo));
    return memo[m][n];
}
int longestCommonSubsequence(string text1, string text2)
{
    if(text1.size() == 0 || text2.size() == 0)
        return 0;
    vector<vector<int> > memo(text1.size(), vector<int>(text2.size(), -1));
    return recursion(text1, text2, text1.size() - 1, text2.size() - 1, memo);
}
#endif


int main()
{
    cout<<"Dynamic Programming"<<endl;
    return 0;
}
