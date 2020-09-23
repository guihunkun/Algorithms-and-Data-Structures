#include <iostream>
#include <string>
#include "vector"
#include "map"
#include "set"
#include "queue"
#include "stack"

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


/*
 * 1
 * LeetCode 130 : 被围绕的区域
 * https://leetcode-cn.com/problems/surrounded-regions/
 */
int n, m;
void dfs(vector<vector<char>>& board, int x, int y)
{
    if(x < 0 || x >= n || y < 0 || y >= m || board[x][y] != 'O') {
        return;
    }
    board[x][y] = 'A';
    dfs(board, x + 1, y);
    dfs(board, x - 1, y);
    dfs(board, x, y + 1);
    dfs(board, x, y - 1);
}

void solve(vector<vector<char>>& board)
{
    n = board.size();
    if(n == 0) {
        return;
    }
    m = board[0].size();
    for(int i = 0; i < n; i++) {
        dfs(board, i, 0);
        dfs(board, i, m - 1);
    }

    for(int i = 1; i < m - 1; i++) {
        dfs(board, 0, i);
        dfs(board, n - 1, i);
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(board[i][j] == 'A') {
                board[i][j] = 'O';
            } else if(board[i][j] == 'O') {
                board[i][j] = 'X';
            }
        }
    }
}

/*
 * 2
 * LeetCode 1219 : 黄金矿工
 * https://leetcode-cn.com/problems/path-with-maximum-gold/
 */
int _res;
vector<vector<int> > dirs = {{-1,0},{0,1},{1,0},{0,-1}};
void dfs(vector<vector<int>>& grid, vector<vector<bool> >& vis, int x, int y, int cur)
{
    if(grid[x][y] && !vis[x][y])
    {
        vis[x][y] = true;
        cur += grid[x][y];
        _res = max(cur, _res);
        for(int i = 0; i < 4; i++)
        {
            int dx = x + dirs[i][0];
            int dy = y + dirs[i][1];
            if(dx >= 0 && dx < grid.size() && dy >= 0 && dy < grid[0].size())
            {
                dfs(grid, vis, dx, dy, cur);
            }
        }
        vis[x][y] = false;
    }
}
int getMaximumGold(vector<vector<int>>& grid)
{
    _res = 0;
    if(grid.empty() || grid[0].empty())
    {
        return _res;
    }
    vector<vector<bool> > vis(grid.size(), vector<bool>(grid[0].size(), false));
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j= 0; j < grid[i].size(); j++)
        {
            dfs(grid, vis, i, j, 0);
        }
    }
    return _res;
}

/*
 * 3
 * LeetCode 面试题 16.19 : 水域大小
 * https://leetcode-cn.com/problems/pond-sizes-lcci/
 */
vector<vector<int> > dirss = {{-1,-1}, {-1,1}, {-1,0}, {0,1}, {0,-1}, {1,-1}, {1,1}, {1,0}};
void dfs(vector<vector<int> >& land, int x, int y, int& count)
{
    land[x][y] = -1; //染色
    count++;
    for(int i = 0; i < dirss.size(); i++)
    {
        int dx = x + dirss[i][0];
        int dy = y + dirss[i][1];
        if(dx >= 0 && dx < land.size() && dy >= 0 && dy < land[0].size() && land[dx][dy] == 0)
        {
            dfs(land, dx, dy, count);
        }
    }

}
vector<int> pondSizes(vector<vector<int>>& land)
{
    vector<int> res;
    if(land.empty())
    {
        return res;
    }
    for(int i = 0; i < land.size(); i++)
    {
        for(int j = 0; j < land[i].size(); j++)
        {
            int count = 0;
            if(land[i][j] == 0)
            {
                dfs(land, i,j,count);//有效的一次dfs
                if(count != 0)//计算一片鱼塘大小
                    res.push_back(count);
            }
        }
    }
    sort(res.begin(), res.end());
    return res;
}


/*
 * 4
 * LeetCode 529 : 扫雷游戏
 * https://leetcode-cn.com/problems/minesweeper/
 */
#if 0
vector<vector<int> > dirss = {{-1,-1}, {-1,1}, {-1,0}, {0,1}, {0,-1}, {1,-1}, {1,1}, {1,0}};
void dfs(vector<vector<char>>& board, int x, int y)
{
    int cnt = 0;
    for(int i = 0; i < dirss.size(); ++i)
    {
        int tx = x + dirss[i][0];
        int ty = y + dirss[i][1];
        if(tx < 0 || tx >= board.size() || ty < 0 || ty >= board[0].size()) {
            continue;
        }
        // 不用判断 M，因为如果有 M 的话游戏已经结束了
        cnt += board[tx][ty] == 'M';
    }
    if(cnt > 0) {
        // 规则 3
        board[x][y] = cnt + '0';
    } else {
        // 规则 2
        board[x][y] = 'B';
        for(int i = 0; i < 8; ++i)
        {
            int tx = x + dirss[i][0];
            int ty = y + dirss[i][1];
            // 这里不需要在存在 B 的时候继续扩展，因为 B 之前被点击的时候已经被扩展过了
            if (tx < 0 || tx >= board.size() || ty < 0 || ty >= board[0].size() || board[tx][ty] != 'E') {
                continue;
            }
            dfs(board, tx, ty);
        }
    }
}

vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click)
{
    int x = click[0], y = click[1];
    if (board[x][y] == 'M') {
        board[x][y] = 'X';
    } else {
        dfs(board, x, y);
    }
    return board;
}
#endif

/*
 * 5
 * LeetCode 199 : 二叉树的右视图
 * https://leetcode-cn.com/problems/binary-tree-right-side-view/
 */
void dfs(TreeNode* root, int depth, vector<int>& res)
{
    if(root == NULL)
    {
        return;
    }
    // 先访问当前节点，再递归地访问右子树和左子树。
    if(depth == res.size())
    {
        // 如果当前节点所在深度还没有出现在res里，
        // 说明在该深度下当前节点是第一个被访问的节点，因此将当前节点加入res中。
        res.push_back(root->val);
    }
    depth++;
    dfs(root->right, depth, res);
    dfs(root->left, depth, res);
}
vector<int> rightSideView(TreeNode* root)
{
    vector<int> res;
    if(root == NULL)
    {
        return res;
    }
    dfs(root, 0, res);
    return res;
}

/*
 * 6
 * LeetCode 695 : 岛屿的最大面积
 * https://leetcode-cn.com/problems/max-area-of-island/
 */
#if 0
vector<vector<int> > dirs = {{-1,0},{0,1},{1,0},{0,-1}};
int dfs(vector<vector<int> >& grid, int x, int y)
{
    if(x < 0 || y < 0 || x == grid.size() || y == grid[0].size() || grid[x][y] != 1)
        return 0;
    grid[x][y] = 0;
    int ans = 1;
    for(int i = 0; i < dirs.size(); i++)
    {
        int dx = x + dirs[i][0];
        int dy = y + dirs[i][1];
        ans += dfs(grid, dx, dy);
    }
    return ans;
}
int maxAreaOfIsland(vector<vector<int> >& grid)
{
    int res = 0;
    for(int i = 0; i < grid.size(); ++i)
        for(int j = 0; j < grid[0].size(); ++j)
            res = max(res, dfs(grid, i, j));
    return res;
}
#endif

/*
 * 7
 * LeetCode 200 : 岛屿数量
 * https://leetcode-cn.com/problems/number-of-islands/
 */
/*
vector<vector<int> > dirs = {{-1,0},{0,1},{1,0},{0,-1}};
void dfs(vector<vector<char> >& grid, int x, int y, vector<vector<bool> >& vis)
{
    vis[x][y] = true;
    for(int i = 0; i < 4; i ++)
    {
        int dx = x + dirs[i][0];
        int dy = y + dirs[i][1];
        if(dx >= 0 && dx < grid.size() && dy >= 0 && dy < grid[0].size() && !vis[dx][dy] && grid[dx][dy] == '1')
        {
            dfs(grid, dx, dy, vis);
        }
    }
    return;
}
int numIslands(vector<vector<char> >& grid)
{
    if(grid.empty() || grid[0].empty())
    {
        return 0;
    }
    vector<vector<bool> > vis(grid.size(), vector<bool>(grid[0].size(), false));
    int res = 0;
    for(int i = 0; i < grid.size(); i++)
        for(int j = 0; j < grid[i].size(); j++)
            if(grid[i][j] == '1' && !vis[i][j])
            {
                dfs(grid, i, j, vis);
                res++;
            }
    return res;
}
*/

/*
 * 8
 * LeetCode 剑指 Offer 12 : 矩阵中的路径
 * https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof/
 */
vector<vector<int> > dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
bool dfs(vector<vector<char> >& board, vector<vector<bool> >&vis, int x, int y, string& word, int idx)
{
    vis[x][y] = true;
    if(idx == word.size())
        return true;
    for(int i = 0; i < dir.size(); i++)
    {
        int dx = x + dir[i][0];
        int dy = y + dir[i][1];
        if(dx >= 0 && dx < board.size() && dy >= 0 && dy < board[0].size() && !vis[dx][dy] && board[dx][dy] == word[idx])
            if(dfs(board, vis, dx, dy, word, idx+1))
                return true;
    }
    vis[x][y] = false;
    return false;
}
bool exist(vector<vector<char>>& board, string word)
{
    if(word.empty())
    {
        return true;
    }
    if(board.empty() || board[0].empty())
    {
        return false;
    }
    vector<vector<bool> > vis(board.size(), vector<bool>(board[0].size(), false));
    for(int i = 0; i < board.size(); i ++) {
        for(int j = 0; j < board[i].size(); j ++) {
            // word[0] 的位置为搜索的入口
            if(board[i][j] == word[0]) {
                if(dfs(board, vis, i, j, word, 1))
                    return true;
            }
        }
    }
    return false;
}


/*
 * 9
 * LeetCode 329 : 矩阵中的最长递增路径
 * https://leetcode-cn.com/problems/longest-increasing-path-in-a-matrix/
 */
#if 0
// Method 1
vector<vector<int> > dirr = {{-1,0},{0,1},{1,0},{0,-1}};
int dfs(vector<vector<int> > &matrix, int x, int y, vector<vector<bool> > &vis)
{
    vis[x][y] = true;
    int res = 0;
    for(int i = 0; i < 4; ++i)
    {
        int dx = x + dirr[i][0];
        int dy = y + dirr[i][1];
        if (dx >= 0 && dx < matrix.size() && dy >= 0 && dy < matrix[0].size() && !vis[dx][dy] && matrix[dx][dy] > matrix[x][y]) {
            res = max(res, dfs(matrix, dx, dy, vis) );
        }
    }
    vis[x][y] = false;
    return res+1;
}
int longestIncreasingPath(vector< vector<int> > &matrix)
{
    if(matrix.empty() || matrix[0].empty())
    {
        return 0;
    }
    vector<vector<bool> > vis(matrix.size(), vector<bool>(matrix[0].size(), false));
    int res = 0;
    for(int i = 0; i < matrix.size(); ++i)
    {
        for(int j = 0; j < matrix[i].size(); ++j)
        {
            res = max(res, dfs(matrix, i, j, vis));
        }
    }
    return res;
}
#endif
#if 1
// Method 2
/*
记忆化深度优先搜索
当访问到一个单元格 (i,j) 时，如果 memo[i][j] != 0，说明该单元格的结果已经计算过，
则直接从缓存中读取结果，如果 memo[i][j] == 0，说明该单元格的结果尚未被计算过，则进行搜索，并将计算得到的结果存入缓存中。
*/
vector<vector<int> > dirr = {{0,1}, {0,-1}, {-1, 0}, {1,0}};
int dfs(vector<vector<int> >& matrix, vector<vector<int> >& memo, int x, int y)
{
    if(memo[x][y] > 0)
        return memo[x][y];
    int r = matrix.size(), c = matrix[0].size();
    int len = 0;
    for(int i = 0; i < dirr.size(); i++)
    {
        int dx = x + dirr[i][0];
        int dy = y + dirr[i][1];
        if((dx < 0) || (dx >= r) || (dy < 0) || (dy >= c) || (matrix[dx][dy] <= matrix[x][y]))
            continue;
        len = max(len, dfs(matrix, memo, dx, dy));
    }
    memo[x][y] = len + 1;
    return len + 1;
}
int longestIncreasingPath(vector<vector<int>>& matrix)
{
    if(matrix.size() == 0 || matrix[0].size() == 0)
        return 0;
    int r = matrix.size(), c = matrix[0].size();
    vector<vector<int> > memo(r, vector<int>(c, 0));
    int res = 0;
    for(int i = 0; i < r; i++)
        for(int j =0; j < c; j++)
        {
            res = max(res, dfs(matrix, memo, i, j));
        }
    return res;
}
#endif


int main()
{
    cout<<"depth first search"<<endl;
    // The case answer is 140.
    vector<vector<int> > matrix = {{0,1,2,3,4,5,6,7,8,9},{19,18,17,16,15,14,13,12,11,10},{20,21,22,23,24,25,26,27,28,29},{39,38,37,36,35,34,33,32,31,30},{40,41,42,43,44,45,46,47,48,49},{59,58,57,56,55,54,53,52,51,50},{60,61,62,63,64,65,66,67,68,69},{79,78,77,76,75,74,73,72,71,70},{80,81,82,83,84,85,86,87,88,89},{99,98,97,96,95,94,93,92,91,90},{100,101,102,103,104,105,106,107,108,109},{119,118,117,116,115,114,113,112,111,110},{120,121,122,123,124,125,126,127,128,129},{139,138,137,136,135,134,133,132,131,130},{0,0,0,0,0,0,0,0,0,0}};
    cout<<longestIncreasingPath(matrix);
    return 0;
}


/*
void dfs()//参数用来表示状态
{
    if(到达终点状态)
    {
        ...//根据题意来添加
        return;
    }
    if(越界或者是不符合法状态)
    {
        ...//
        return;
    }
    标记；
    for(扩展方式)
    {
        if(扩展方式所达到状态合法)
        {
            ....//根据题意来添加
            dfs（）；
        }
        
    }
    (还原标记)；
    //是否还原标记根据题意
    //如果加上（还原标记）就是 回溯法
}
*/


