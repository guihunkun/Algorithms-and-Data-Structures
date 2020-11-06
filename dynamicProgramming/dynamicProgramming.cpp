#include <iostream>
#include <string>
#include "vector"
#include "map"
#include "set"
#include "queue"
#include "stack"

using namespace std;


#if 0
动态规划是编程面试中的热门话题，如果面试题是求解一个问题的最优解(通常是求最大值或者最小值)。
而且该问题能够分解成若干个子问题，并且子问题之间还有重叠的更小的子问题，就可以考虑用动态规划的方法来求解这个问题。


“未来与过去无关”，这就是无后效性。(严格定义：如果给定某一阶段的状态，则在这一阶段以后过程的发展不受这阶段以前各段状态的影响。)

大问题的最优解可以由小问题的最优解推出，这个性质叫做“最优子结构性质”。

如何判断一个问题能否使用DP解决: 能将大问题拆成几个小问题，且满足无后效性、最优子结构性质。

DP的核心思想：尽量缩小可能解空间。

#endif






/*
 * 1
 * LeetCode 64 : 最小路径和
 * https://leetcode-cn.com/problems/minimum-path-sum/
 */
int minPathSum(vector<vector<int>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int> > dp(m,vector<int>(n,0));
    dp[0][0] = grid[0][0];
    for(int i = 1; i < m; i++)
        dp[i][0] = dp[i-1][0] + grid[i][0];
    for(int j = 1; j < n; j++)
        dp[0][j] = dp[0][j-1] + grid[0][j];
    for(int i = 1; i < m; i++)
        for(int j = 1; j < n; j++)
            dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
    return dp[m-1][n-1];
}


/*
 * 2
 * LeetCode 53 : 最大子序和
 * https://leetcode-cn.com/problems/maximum-subarray/
 */
int maxSubArray(vector<int> &nums)
{
#if 0
    //dp[i]表示nums中以nums[i]结尾的最大子序和
    if(nums.empty())
    {
        return -1;
    }
    vector<int> dp(nums.size());
    dp[0] = nums[0];
    int res = nums[0];
    for (int i = 1; i < nums.size(); i++)
    {
        dp[i] = max(dp[i - 1] + nums[i], nums[i]);
        res = max(res, dp[i]);
    }
    return res;
#endif
#if 1
    // 因为dp[i]只与dp[i-1]有关，所以可以只用只用一个变量 pre 来维护对于当前dp[i]的dp[i-1]的值是多少
    if(nums.empty())
    {
        return -1;
    }
    int pre = nums[0];
    int res = nums[0];
    for (int i = 1; i < nums.size(); i++)
    {
        pre = max(pre + nums[i], nums[i]);
        res = max(res, pre);
    }
    return res;
#endif
}


/*
 * 3
 * LeetCode 198 : 打家劫舍
 * https://leetcode-cn.com/problems/house-robber/
 */
#if 0
int rob(vector<int>& nums)
{
    /*
     * dp[i] 表示前 i 间房屋能偷窃到的最高总金额
     * dp[i] = max(dp[i−2]+nums[i], dp[i−1])
     * dp[0]=nums[0]                只有一间房屋，则偷窃该房屋
     * dp[1]=max(nums[0],nums[1])   只有两间房屋，选择其中金额较高的房屋进行偷窃
     */
    if(nums.empty())
        return 0;
    if(nums.size() == 1)
    {
        return nums[0];
    }
    vector<int> dp(nums.size(), -1);
    //memo[i]表示抢劫nume[0,....i]所能获得的最大收益
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    for(int i = 2; i < nums.size(); i++)
    {
        dp[i] = max(dp[i-2]+nums[i], dp[i-1]);
    }
    return dp[nums.size()-1];
}
#endif


/*
 * 4
 * LeetCode 213 : 打家劫舍 II
 * https://leetcode-cn.com/problems/house-robber-ii/
 */
int getRob(const vector<int>& nums, int start, int end)
{
    int len = end-start+1;
    vector<int> dp(len, -1);
    if(len == 0)
        return 0;
    if(len == 1)
        return nums[start];
    dp[0] = nums[start];
    dp[1] = max(nums[start], nums[start+1]);
    for(int i = 2; i < len; i++)
    {
        dp[i] = max(nums[start+i]+dp[i-2], dp[i-1]);
    }
    return dp[len-1];
}
int rob(vector<int>& nums)
{
    /*
     * 因为第一个element 和最后一个element不能同时出现. 则分两次call House Robber I.
     * case 1: 不包括最后一个element.
     * case 2: 不包括第一个element.
     * 两者的最大值即为全局最大值
     */
    if(nums.empty())
        return 0;
    if(nums.size() == 1)
        return nums[0];
    int a = getRob(nums, 0, nums.size() - 2);
    int b = getRob(nums, 1, nums.size() - 1);
    return max(a, b);
}


/*
 * 5
 * Leetcode 931 : 下降路径最小和
 * https://leetcode-cn.com/problems/minimum-falling-path-sum/
 */
int minFallingPathSum(vector<vector<int> >& A)
{
    /*
     * dp(r,c) : 从第r层，第c列开始的最小路径和。
     * 当r为最后一层时，dp(r,c) = A[r][c];
     * 当r不为最后一层时，dp(r,c) = A[r][c] + 下一层的子问题的解的最小值。
     * 状态转移方程 (在不考虑边界的情况下)
     * dp(r,c) = A[r][c] + min(dp[r+1][c-1], dp[r+1][c], dp[r+1][c+1])
     */
    int row = A.size();
    int col = A[0].size();
    for(int r = row-2; r >= 0; r--)
    {
        for(int c = 0; c < col; c++)
        {
            // best = min(A[r+1][c-1], A[r+1][c], A[r+1][c+1])
            int best = A[r+1][c];
            if(c > 0)
                best = min(best, A[r+1][c-1]);
            if(c+1 < col)
                best = min(best, A[r+1][c+1]);
            A[r][c] += best;
        }
    }
    int res = INT_MAX;
    for(auto x : A[0])
        res = min(res, x);
    return res;
}


/*
 * 6
 * LeetCode 322 : 零钱兑换
 * https://leetcode-cn.com/problems/coin-change/
 */
int coinChange(vector<int>& coins, int amount)
{
    /*
     * dp(i) 为组成金额 i 所需最少的硬币数量
     * dp(i) = min{dp(i - c_j)} + 1  (j = 0, ... n-1)
     * 其中 c_j 代表的是第 j 枚硬币的面值
     */
    int Max = amount + 1;
    vector<int> dp(amount + 1, Max);
    dp[0] = 0;
    for(int i = 1; i <= amount; ++i)
    {
        for(int j = 0; j < (int)coins.size(); ++j)
        {
            if(coins[j] <= i)
            {
                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }
        }
    }
    return dp[amount] > amount ? -1 : dp[amount];
}


/*
 * 7
 * LeetCode 62 : 不同路径
 * https://leetcode-cn.com/problems/unique-paths/
 */
int uniquePaths(int m, int n)
{
    /*
    * dp[i][j] 是到达 (i, j) 最多路径
    * 动态方程：dp[i][j] = dp[i-1][j] + dp[i][j-1]
    * 对于第一行 dp[0][j]，或者第一列 dp[i][0]，由于都是在边界，所以只能为 1
    */
    vector<vector<int> > memo(n, vector<int>(m, 0) );
    for(int i = 0; i < n; i++)
        memo[i][0] = 1;
    for(int j = 0; j < m; j++)
        memo[0][j] = 1;
    for(int i = 1; i < n; i++)
        for(int j = 1; j < m; j++)
            memo[i][j] = memo[i][j-1] + memo[i-1][j];
    return memo[n-1][m-1];
}
#if 0
int uniquePaths(int m, int n)
{
    /* 排列组合
     * 因为机器到底右下角，向下几步，向右几步都是固定的，
     * 所以有 C(m+n-2,m-1)（或C(m+n-2,n-1)）
     */
    long ans = 1;
    for(int i = 0; i < min(m-1, n-1); i++)
    {
        // 乘以分子
        ans *= m+n-2-i;
        // 直接除以分母 将阶乘拆开 防止溢出
        ans /= i+1;
    }
    return (int)ans;
}
#endif


/*
 * 8
 * LeetCode 面试题 08.02 : 迷路的机器人
 * https://leetcode-cn.com/problems/robot-in-a-grid-lcci/
 */
vector<vector<int>> pathWithObstacles(vector<vector<int> > &obstacleGrid)
{
    /*
     * 动态规划
     * 移动方向决定了当前坐标只能够从垂直向上的一个坐标或者左边的一个坐标达来到
     * 左边的第一列，只能从上往下 dp[i][0] = !obstacleGrid[i-1][0] && dp[i-1][0]
     * 上面的第一行，只能从左往右 dp[0][j] = !obstacleGrid[0][j-1] && dp[0][j-1]
     * 状态转移方程 ：dp[i][j] = dp[i-1][j] || dp[i][j-1]
     *
     * dp[row][col] == 1, 说明存在路径从起点到终点，根据dp矩阵就能逆推回去得到一条路径
     */

    int row = obstacleGrid.size();
    int col = obstacleGrid[0].size();
    vector<vector<int> > res;
    //起点和终点是障碍
    if(obstacleGrid[0][0] || obstacleGrid[row-1][col-1])
        return res;
    vector<vector<bool> > dp(row, vector<bool>(col, false));
    dp[0][0] = true;
    //初始化首列
    for(int r = 1; r < row; r++)
    {
        dp[r][0] = !obstacleGrid[r][0] && dp[r - 1][0];
    }
    //初始化首行
    for(int c = 1; c < col; c++)
    {
        dp[0][c] = !obstacleGrid[0][c] && dp[0][c - 1];
    }
    for(int i = 1; i < row; i++)
    {
        for(int j = 1; j < col; j++)
        {
            dp[i][j] = !obstacleGrid[i][j] && (dp[i - 1][j] || dp[i][j - 1]);
        }
    }
    //如果终点不可达
    if(!dp[row-1][col-1])
        return res;
    int r = row-1, c = col-1;
    while(r > 0 || c > 0)
    {
        res.push_back({r, c});
        //先考虑上面的坐标, 不管是先上面还是左边，只要坐标可用，最终肯定能回到起点(这是前面动态递推的结果)
        if(r > 0 && dp[r - 1][c])
            r--;
        else if(c > 0 && dp[r][c - 1])
            c--;
    }
    res.push_back({0, 0});

    reverse(res.begin(), res.end());
    return res;
}



int main()
{
    cout<<"Dynamic Programming"<<endl;
    return 0;
}
