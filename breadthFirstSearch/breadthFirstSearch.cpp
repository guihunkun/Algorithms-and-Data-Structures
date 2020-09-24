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


// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};





/*
 * 1
 * LeetCode 剑指 Offer 32 - III : 从上到下打印二叉树 III
 * https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-iii-lcof/
 */
vector<vector<int>> levelOrder(TreeNode* root)
{
    vector<vector<int> > res;
    if(root == nullptr)
    {
        return res;
    }
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    while(!q.empty())
    {
        int num = q.size();
        vector<int> tmp;
        for(int i = 0; i < num; i++)
        {
            TreeNode* node = q.front();
            q.pop();
            tmp.push_back(node->val);
            if(node->left != nullptr) {
                q.push(node->left);
            }
            if(node->right != nullptr) {
                q.push(node->right);
            }
        }
        if((i++%2) == 0)
        {
            reverse(tmp.begin(), tmp.end());
        }
        res.push_back(tmp);
    }
    return res;
}

/*
 * 2
 * LeetCode 429 : N叉树的层序遍历
 * https://leetcode-cn.com/problems/n-ary-tree-level-order-traversal/
 */
vector<vector<int>> levelOrder(Node* root)
{
    vector<vector<int> > res;
    vector<int> tmp;
    if(root == NULL)
        return  res;
    queue<Node*> q;
    q.push(root);
    while(!q.empty())
    {
        tmp.clear();
        int count = q.size();
        while(count > 0)
        {
            Node* node = q.front();
            tmp.push_back(node->val);
            q.pop();
            count--;
            if(node->children.size() != 0)
                for(int i = 0; i < node->children.size(); i++)
                    q.push(node->children[i]);
        }
        res.push_back(tmp);
    }
    return res;
}

/*
 * 3
 * LeetCode 103. 二叉树的锯齿形层次遍历
 * https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/
 */
vector<vector<int>> zigzagLevelOrder(TreeNode* root)
{
    vector<vector<int> > res;
    if(root == NULL)
        return res;
    queue<TreeNode*> q;
    q.push(root);
    int level = 0;
    while(!q.empty())
    {
        vector<int> tmp;
        int count = q.size();
        for(int i = 0; i < count; i++)
        {
            TreeNode *t=q.front();
            q.pop();
            if(level%2 == 0)
                tmp.push_back(t->val);
            else
                tmp.insert(tmp.begin(),t->val);
            if(t->left)
                q.push(t->left);
            if(t->right)
                q.push(t->right);
        }
        level++;
        res.push_back(tmp);
    }
    return res;
}


/*
 * 4
 * LeetCode 130 : 被围绕的区域
 * https://leetcode-cn.com/problems/surrounded-regions/
 */
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
void solve(vector<vector<char>>& board)
{
    int n = board.size();
    if(n == 0) {
        return;
    }
    int m = board[0].size();
    queue<pair<int, int>> que;
    for(int i = 0; i < n; i++) {
        if(board[i][0] == 'O') {
            que.emplace(i, 0);
        }
        if(board[i][m - 1] == 'O') {
            que.emplace(i, m - 1);
        }
    }
    for(int i = 1; i < m - 1; i++) {
        if(board[0][i] == 'O') {
            que.emplace(0, i);
        }
        if(board[n - 1][i] == 'O') {
            que.emplace(n - 1, i);
        }
    }
    while(!que.empty()) {
        int x = que.front().first, y = que.front().second;
        que.pop();
        board[x][y] = 'A';
        for(int i = 0; i < 4; i++) {
            int mx = x + dx[i], my = y + dy[i];
            if(mx < 0 || my < 0 || mx >= n || my >= m || board[mx][my] != 'O') {
                continue;
            }
            que.emplace(mx, my);
        }
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
 * 5
 * LeetCode 934 : 最短的桥
 * https://leetcode-cn.com/problems/shortest-bridge/
 */
/* Method 1 : DFS + BFS
1. 找到第一个1的位置。
2. 使用 DFS 找出所有相连的1, 并将所有相连的1都放入到一个队列 queue 中，并且将该点的值改为2。
3. 使用 BFS 进行层序遍历，每遍历一层，结果 res 都增加1，当遇到1时，直接返回 res 即可。
*/
#if 1
void dfs(vector<vector<int> >& A, int x, int y, queue<int>& q)
{
    int n = A.size();
    if(x < 0 || x >= n || y < 0 || y >= n || A[x][y] == 0 || A[x][y] == 2)
        return;
    A[x][y] = 2;
    q.push(x * n + y);
    dfs(A, x + 1, y, q);
    dfs(A, x, y + 1, q);
    dfs(A, x - 1, y, q);
    dfs(A, x, y - 1, q);
}
int shortestBridge(vector<vector<int> >& A)
{
    int res = 0, n = A.size(), startX = -1, startY = -1;
    queue<int> q;
    vector<vector<int> > dirs = {{-1,0},{0,1},{1,0},{0,-1}};
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(A[i][j] == 0)
                continue;
            startX = i; startY = j;
            break;
        }
        if(startX != -1)
            break;
    }
    dfs(A, startX, startY, q);
    while(!q.empty())
    {
        for(int i = q.size(); i > 0; i--)
        {
            int t = q.front();
            q.pop();
            for(int k = 0; k < dirs.size(); k++)
            {
                int x = t / n + dirs[k][0];
                int y = t % n + dirs[k][1];
                if(x < 0 || x >= n || y < 0 || y >= n || A[x][y] == 2)
                    continue;
                if(A[x][y] == 1)
                    return res;
                A[x][y] = 2;
                q.push(x * n + y);
            }
        }
        ++res;
    }
    return res;
}

#endif


/* Method 2
1. 找到第一个1的位置。
2. 使用 BFS 找出所有相连的1, 并将所有相连的1都放入到一个队列 queue 中，并且将该点的值改为2。
3. 使用 BFS 进行层序遍历，每遍历一层，结果 res 都增加1，当遇到1时，直接返回 res 即可。

**注意 ：第一个 BFS 不需要是层序遍历的，而第二个 BFS 是必须层序遍历。
*/
#if 0
int shortestBridge(vector<vector<int>>& A)
{
    int res = 0, n = A.size();
    queue<int> que; // first BFS used
    queue<int> q;   // secod=nd BFS used

    vector<vector<int> > dirs = {{-1,0},{0,1},{1,0},{0,-1}};
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(A[i][j] == 0)
                continue;
            A[i][j] = 2;
            que.push(i * n + j);
            break;
        }
        if(!que.empty())
            break;
    }
    // first BFS
    while(!que.empty())
    {
        int t = que.front();
        que.pop();
        q.push(t);
        for(int k = 0; k < 4; k++)
        {
            int x = t / n + dirs[k][0];
            int y = t % n + dirs[k][1];
            if(x < 0 || x >= n || y < 0 || y >= n || A[x][y] == 0 || A[x][y] == 2)
                continue;
            A[x][y] = 2;
            que.push(x * n + y);
        }
    }
    // second BFS
    while(!q.empty())
    {
        for(int i = q.size(); i > 0; i--)
        {
            int t = q.front();
            q.pop();
            for(int k = 0; k < 4; k++)
            {
                int x = t / n + dirs[k][0];
                int y = t % n + dirs[k][1];
                if(x < 0 || x >= n || y < 0 || y >= n || A[x][y] == 2)
                    continue;
                if(A[x][y] == 1)
                    return res;
                A[x][y] = 2;
                q.push(x * n + y);
            }
        }
        ++res;
    }
    return res;
}
#endif


/*
 * 6
 * LeetCode 994 ： 腐烂的橘子
 * https://leetcode-cn.com/problems/rotting-oranges/
 */
int orangesRotting(vector<vector<int> >& grid)
{
    int ct = 0, res = -1;
    queue<vector<int> > q;
    vector<vector<int> > dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[i].size(); j++)
        {
            if(grid[i][j] > 0)
                ct++;
            if(grid[i][j] == 2)
                q.push({i, j});
        }
    }
    while(!q.empty())
    {
        res++;
        int n = q.size();
        for(int k = 0; k < n; k++)
        {
            vector<int> cur = q.front();
            ct--;
            q.pop();
            for(int i = 0; i < dir.size(); i++)
            {
                int x = cur[0] + dir[i][0];
                int y = cur[1] + dir[i][1];
                if(x >= grid.size() || x < 0 || y >= grid[0].size() || y < 0 || grid[x][y] != 1)
                    continue;
                grid[x][y] = 2;
                q.push({x, y});
            }
        }
    }
    if(ct == 0)
        return max(0, res);
    return -1;
}

/*
 * 7
 * LeetCode 542 : 01 矩阵
 * https://leetcode-cn.com/problems/01-matrix/
 */
/*
BFS:
从每一个0位置向上下左右四个方向进行广播，如果广播到的位置距离0的距离大于当前位置距离0的距离加一，
则将广播到的位置距离0的位置更新为当前位置距离0的距离加一。
*/
vector<vector<int>> updateMatrix(vector<vector<int>>& matrix)
{
    int R = matrix.size();
    if(R == 0)
        return matrix;
    int C = matrix[0].size();
    vector<vector<int> > dist(R, vector<int>(C, INT_MAX));
    queue<pair<int,int> > q;
    for(int i = 0; i < R; i++)
    {
        for(int j = 0; j < C; j++)
        {
            if(matrix[i][j] == 0)
            {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }
    vector<vector<int> > dir = {{-1,0},{0,1},{1,0},{0,-1}};
    while(!q.empty())
    {
        pair<int, int> curr = q.front();
        q.pop();
        for(int i = 0; i < 4; i++)
        {
            int new_r = curr.first + dir[i][0];
            int new_c = curr.second + dir[i][1];
            if(new_r >= 0 && new_c >= 0 && new_r < R && new_c < C)
            {
                if(dist[new_r][new_c] > dist[curr.first][curr.second] + 1)
                {
                    dist[new_r][new_c] = dist[curr.first][curr.second] + 1;
                    q.push({ new_r, new_c });
                }
            }
        }
    }
    return dist;
}
















/*
 * Hard
 * LeetCode 1293 : 网格中的最短路径
 * https://leetcode-cn.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/
 */
struct Nagato
{
    int x, y;
    int rest;
    Nagato(int _x, int _y, int _r): x(_x), y(_y), rest(_r) {}
};

class Solution
{
public:
    vector<vector<int> > dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int shortestPath(vector<vector<int>>& grid, int k)
    {
        if(grid.empty() || grid[0].empty())
        {
            return 0;
        }
        int m = grid.size(), n = grid[0].size();
        if(m == 1 && n == 1)
        {
            return 0;
        }
        k = min(k, m + n - 3);
        vector<vector<vector<bool> > > vis(m, vector<vector<bool> >(n, vector<bool>(k+1, false)));
        queue<Nagato> q;
        q.push(Nagato(0, 0, k));
        vis[0][0][k] = true;
        for(int step = 1; q.size() > 0; ++step)
        {
            int cnt = q.size();
            for(int j = 0; j < cnt; ++j)
            {
                Nagato cur = q.front();
                q.pop();
                for(int i = 0; i < dirs.size(); ++i)
                {
                    int nx = cur.x + dirs[i][0];
                    int ny = cur.y + dirs[i][1];
                    if(nx >= 0 && nx < m && ny >= 0 && ny < n)
                    {
                        if(grid[nx][ny] == 0 && !vis[nx][ny][cur.rest]) {
                            if(nx == m - 1 && ny == n - 1) {
                                return step;
                            }
                            q.push(Nagato(nx, ny, cur.rest));
                            vis[nx][ny][cur.rest] = true;
                        } else if(grid[nx][ny] == 1 && cur.rest > 0 && !vis[nx][ny][cur.rest - 1]) {
                            q.push(Nagato(nx, ny, cur.rest - 1));
                            vis[nx][ny][cur.rest - 1] = true;
                        }
                    }
                }
            }
        }
        return -1;
    }
};




int main()
{
    cout<<"Breadth First Search"<<endl;
    return 0;
}




/* 模版
queue<T> q;
while(!q.empty())
{
    ...//
    int n = q.size();
    for(int k = 0; k < n; k++)
    {
        T t = q.front();
        ...//
        q.pop();
        for(扩展方式)
        {
            if(扩展方式所达到状态合法)
            {
                ....//根据题意来添加
                q.push()；
            }
        }
    }
}
*/
