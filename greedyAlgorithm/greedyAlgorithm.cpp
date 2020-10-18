#include <iostream>
#include <string>
#include "vector"
#include "map"
#include "set"
#include "queue"
#include "stack"

using namespace std;

/*
贪心算法（又称贪婪算法）是指，在对问题求解时，总是做出在当前看来是最好的选择。
也就是说，不从整体最优上加以考虑，他所做出的是在某种意义上的局部最优解。

贪心算法不是对所有问题都能得到整体最优解，关键是贪心策略的选择，
选择的贪心策略必须具备无后效性，即某个状态以前的过程不会影响以后的状态，只与当前状态有关。
*/


/*
 * 1
 * LeetCode 1403 : 非递增顺序的最小子序列
 * https://leetcode-cn.com/problems/minimum-subsequence-in-non-increasing-order/
 */
vector<int> minSubsequence(vector<int>& nums)
{
    sort(nums.begin(), nums.end(), greater<int>());
    int sum = 0;
    for(auto num : nums)
    {
        sum += num;
    }
    int cur = 0;
    for(int i = 0; i < nums.size(); i++)
    {
        cur += nums[i];
        if(cur > sum-cur)
        {
            return vector<int>(nums.begin(), nums.begin()+i+1);
        }

    }
    return nums;
}


/*
 * 2
 * LeetCode 455 : 分发饼干
 * https://leetcode-cn.com/problems/assign-cookies/
 */
int findContentChildren(vector<int>& g, vector<int>& s)
{
/*
 * 利用贪心算法的思想：每次都先满足胃口最小的孩子，直到有效饼干分完，或者孩子都被满足则停止分发。
 */
    int res = 0;
    sort(g.begin(),g.end());
    sort(s.begin(),s.end());
    int gi = 0, si = 0;
    while(gi<g.size() && si<s.size())
    {
        if(s[si]>=g[gi])
        {
            gi++;
            si++;
            res++;
        }
        else
            si++;
    }
    return res;
}


/*
 * 3
 * LeetCode 1046 : 最后一块石头的重量
 * https://leetcode-cn.com/problems/last-stone-weight/
 */
int lastStoneWeight(vector<int>& stones)
{
/*
 * 优先队列 : priority_queue
 * 对于基础类型 默认是大根堆(降序队列) : priority_queue<int> pq;
 * 小根堆(升序队列) : priority_queue<int, vector<int>, greater<int> > pq;
 */
    priority_queue<int> record;
    for(int weight : stones)
        record.push(weight);
    while(! record.empty())
    {
        if(record.size() == 1)
            return record.top();
        else
        {
            int max1 = record.top();
            record.pop();
            int max2 = record.top();
            record.pop();
            if(abs(max1 - max2) != 0)
                record.push(max1 - max2);
        }
    }
    return 0;
}

/*
 * 4
 * LeetCode 1578. 避免重复字母的最小删除成本
 * https://leetcode-cn.com/problems/minimum-deletion-cost-to-avoid-repeating-letters/
 */
int minCost(string s, vector<int>& cost)
{
    /*
     * 如果字符串中有若干相邻的重复字母，则这些字母中最多只能保留一个。
     * 因此我们可以采取贪心的策略：在这一系列重复字母中，我们保留删除成本最高的字母，
     * 并删除其他字母。这样得到的删除成本一定是最低的。
     *
     */
    int n = s.size();
    int sum = 0;
    for(int i = 0; i < n-1; i++)
    {
        if(s[i] == s[i+1])
        {
            sum += min(cost[i], cost[i+1]);
            if(cost[i] > cost[i+1])
                swap(cost[i], cost[i+1]);
        }
    }
    return sum;
}

/*
 * 5
 * LeetCode 435. 无重叠区间
 * https://leetcode-cn.com/problems/non-overlapping-intervals/
 */
static bool compareLeft(const vector<int>& a, const vector<int>& b)
{
    return a[1] < b[1];
}
int eraseOverlapIntervals(vector<vector<int> >& intervals)
{
    //区间右端点的贪心算法
    if(intervals.size() == 0)
        return 0;
    sort(intervals.begin(),intervals.end(), compareLeft);
    int res = 1;
    int pre = 0;
    for(int i = 1; i < intervals.size(); i++)
        if(intervals[i][0] >= intervals[pre][1])
        {
            res++;
            pre = i;
        }
    return intervals.size()-res;
}

#if 0
static bool compareRight(const vector<int>& a, const vector<int>& b)
{
    return a[0] < b[0];
}
int eraseOverlapIntervals(vector<vector<int> >& intervals)
{
    //区间左端点的贪心算法
    if(intervals.size() == 0) {
        return 0;
    }
    sort(intervals.begin(), intervals.end(), compareRight);
    int end = intervals[0][1];
    int prev = 0;
    int count = 0;
    for(int i = 1; i < intervals.size(); i++)
    {
        if(intervals[prev][1] > intervals[i][0]) {
            if(intervals[prev][1] > intervals[i][1])
            {
                prev = i;
            }
            count++;
        } else {
            prev = i;
        }
    }
    return count;
}
#endif



/*
 * 6
 * LeetCode 1288. 删除被覆盖区间
 * https://leetcode-cn.com/problems/remove-covered-intervals/
 */


/*
1. 对起点进行升序排序，如果起点相同，则对终点进行降序排序。
2. 初始化没有被覆盖的区间数：count=0。
3. 迭代排序后的区间并且比较终点大小。
   如果当前区间不被前一个区间覆盖 end > prev_end，则增加 count，指定当前区间为下一步的前一个区间。
   否则，当前区间被前一个区间覆盖，不做任何事情。
4. 返回 count。
*/
static bool compare(const vector<int>& a, const vector<int>& b)
{
    if(a[0] == b[0]) {
        return a[1] > b[1];
    } else {
        return a[0] < b[0];
    }
}
int removeCoveredIntervals(vector<vector<int> >& intervals)
{
    sort(intervals.begin(), intervals.end(), compare);
    int count = 0;
    int end, prev_end = 0;
    for(auto curr : intervals)
    {
        end = curr[1];
        // if current interval is not covered
        // by the previous one
        if(prev_end < end) {
            ++count;
            prev_end = end;
        }
    }
    return count;
}


/*
 * 7
 * LeetCode 134. 加油站
 * https://leetcode-cn.com/problems/gas-station/
 */
int canCompleteCircuit(vector<int>& gas, vector<int>& cost)
{
    int n = gas.size();
    int total_tank = 0;
    int curr_tank = 0;
    int starting_station = 0;
    for(int i = 0; i < n; ++i)
    {
        total_tank += gas[i] - cost[i];
        curr_tank += gas[i] - cost[i];
        // If one couldn't get here,
        if(curr_tank < 0)
        {
            // Pick up the next station as the starting one.
            starting_station = i + 1;
            // Start with an empty tank.
            curr_tank = 0;
        }
    }
    return total_tank >= 0 ? starting_station : -1;
}

/*
 * 8
 * LeetCode 763. 划分字母区间
 * https://leetcode-cn.com/problems/partition-labels/
 */
/*
算法：对于遇到的每一个字母，去找这个字母最后一次出现的位置，用来更新当前的最小区间。
1. 定义数组 last[char] 来表示字符 char 最后一次出现的下标。
2. 定义 anchor 和 j 来表示当前区间的首尾。
   如果遇到的字符最后一次出现的位置下标大于 j， 就让 j=last[c] 来拓展当前的区间。
   当遍历到了当前区间的末尾时(即 i==j )，把当前区间加入答案，同时将 start 设为 i+1 去找下一个区间。
*/
vector<int> partitionLabels(string S)
{
    vector<int> last(26, 0);
    for(int i = 0; i < S.size(); ++i)
        last[S[i] - 'a'] = i;

    int j = 0, anchor = 0;
    vector<int> res;
    for(int i = 0; i < S.size(); ++i)
    {
        j = max(j, last[S[i] - 'a']);
        if(i == j)
        {
            res.push_back(i - anchor + 1);
            anchor = i + 1;
        }
    }
    return res;
}

int main()
{
    cout<<"Gready Algorithm"<<endl;
    return 0;
}
