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


// Recursion
/*
 * 1
 * LeetCode 剑指 Offer 07 : 重建二叉树
 * https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof/
 */

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
{
    if(preorder.empty() || inorder.empty())
    {
        return NULL;
    }
    TreeNode* root = new TreeNode(preorder[0]);
    int mid = distance(begin(inorder), find(inorder.begin(), inorder.end(), preorder[0]));
    vector<int> leftPre(preorder.begin()+1, preorder.begin()+mid+1);
    vector<int> rightPre(preorder.begin()+mid+1, preorder.end());
    vector<int> leftIn(inorder.begin(), inorder.begin()+mid);
    vector<int> rightIn(inorder.begin()+mid+1, inorder.end());

    root->left = buildTree(leftPre, leftIn);
    root->right = buildTree(rightPre, rightIn);
    return root;
}

/*
 * 2
 * LeetCode 687 : 最长同值路径
 * https://leetcode-cn.com/problems/longest-univalue-path/
 */
int Length;
int arrowLength(TreeNode* root)
{
    if(root == NULL)
        return 0;
    int left = arrowLength(root->left);
    int right = arrowLength(root->right);
    int arrowLeft = 0, arrowRight = 0;
    if(root->left != NULL && root->left->val == root->val)
        arrowLeft += left + 1;
    if(root->right != NULL && root->right->val == root->val)
        arrowRight += right + 1;
    Length = max(Length, arrowLeft + arrowRight);
    return max(arrowLeft, arrowRight);
}
int longestUnivaluePath(TreeNode* root)
{
    Length = 0;
    arrowLength(root);
    return Length;
}

/*
 * 3
 * LeetCode 面试题 08.06 : 汉诺塔问题
 * https://leetcode-cn.com/problems/hanota-lcci/
 */
void move(int n, vector<int>& A, vector<int>& B, vector<int>& C)
{
    if(n == 1)
    {
        C.push_back(A[0]);
        A.pop_back();
        return;
    }
    move(n-1, A, C, B);    // 将A上面n-1个通过C移到B
    C.push_back(A[0]);     // 将A最后一个移到C
    A.pop_back();          // 这时，A空了
    move(n-1, B, A, C);    // 将B上面n-1个通过空的A移到C
}
void hanota(vector<int>& A, vector<int>& B, vector<int>& C)
{
    int n = A.size();
    move(n, A, B, C);
}

/*
 * 4
 * LeetCode 894 : 所有可能的满二叉树
 * https://leetcode-cn.com/problems/all-possible-full-binary-trees/
 */
vector<TreeNode*> allPossibleFBT(int N)
{
    if(N%2 == 0)
        return {};
    if(N == 1)
        return {new TreeNode(0)};
    vector<TreeNode*> ans;
    for(int lef = 1; lef + 1 < N; lef++)
    {
        vector<TreeNode*> left = allPossibleFBT(lef);
        vector<TreeNode*> right = allPossibleFBT(N-1-lef);
        for(TreeNode* l : left)
        {
            for(TreeNode* r : right)
            {
                TreeNode *root = new TreeNode(0);
                root->left = l;
                root->right = r;
                ans.push_back(root);
            }
        }
    }
    return ans;
}

/*
 * 5
 * LeetCode 面试题 17.12 : BiNode
 * https://leetcode-cn.com/problems/binode-lcci/
 */
void inorderTraversal(TreeNode* root, TreeNode* &cur)
{
    //中序遍历
    if(root)
    {
        inorderTraversal(root->left, cur);
        cur->right = root; //将此节点赋给cur的右子树
        root->left = NULL; //将此节点的左子树赋值NULL
        cur = root; //更新
        inorderTraversal(root->right, cur);
    }
}
TreeNode* convertBiNode(TreeNode* root)
{
    TreeNode* head = new TreeNode(-1);
    TreeNode* cur = head;
    inorderTraversal(root, cur);
    return head->right;
}

/*
 * 6
 * LeetCode 783 : 二叉搜索树节点最小距离
 * https://leetcode-cn.com/problems/minimum-distance-between-bst-nodes/
 */
// 在二叉搜索树中，中序遍历会将树中节点按数值大小顺序输出。只需要遍历计算相邻数的差值，取其中最小的就可以了。
int _pre, _res;
bool _flag = true;
void inorder(TreeNode* root)
{
    if(root == NULL)
        return;
    inorder(root->left);
    if(!_flag)
    {
        _res = min(_res, root->val - _pre);
    }
    _pre = root->val;
    _flag = false;
    inorder(root->right);
}
int minDiffInBST(TreeNode* root)
{
    _res = INT_MAX;
    inorder(root);
    return _res;
}


// Backtracking
/*
回溯算法的基本思想是：从一条路往前走，能进则进，不能进则退回来，换一条路再试。
*/
/*
 * 1
 * LeetCode 79 : 单词搜索
 * https://leetcode-cn.com/problems/word-search/
 */
vector<vector<int> > dirs = {{-1,0},{0,1},{1,0},{0,-1}};
bool dfs(vector<vector<char>>& board, string& word, int id, int dx, int dy, vector<vector<bool> >& visited)
{
    if(id == word.size()-1)
    {
        return word[id] == board[dx][dy];
    }
    if(word[id] == board[dx][dy])
    {
        for(int i = 0; i < 4; i++)
        {
            visited[dx][dy] = true;
            int ndx = dx + dirs[i][0];
            int ndy = dy + dirs[i][1];
            if(ndx >= 0 && ndx < board.size() && ndy >= 0 && ndy < board[0].size() && (!visited[ndx][ndy]) && dfs(board, word, id+1, ndx, ndy, visited))
            {
                return true;
            }
        }
        visited[dx][dy] = false;
    }
    return false;
}
bool exist(vector<vector<char>>& board, string word)
{
    if(board.size() == 0 || board[0].size() == 0)
    {
        return false;
    }
    if(word.empty())
    {
        return true;
    }
    vector<vector<bool> > visited(board.size(), vector<bool>(board[0].size(), false));
    for(int i = 0; i < board.size(); i++)
    {
        for(int j= 0; j < board[i].size(); j++)
        {
            if(dfs(board, word, 0, i, j, visited))
            {
                return true;
            }
        }
    }
    return false;
}

/*
 * 2
 * LeetCode 131 : 分割回文串
 * https://leetcode-cn.com/problems/palindrome-partitioning/
 */
bool isPalindrome(string s)
{
    int first = 0;
    int end = s.size()-1;
    while(first < end)
    {
        if(s[first++] != s[end--])
            return false;
    }
    return true;
}
void helper(string& s, int pos, vector<string>& path, vector<vector<string> >& result)
{
    if(pos == s.size())
    {
        result.push_back(path);
        return ;
    }
    for(int i = pos; i < s.size(); i++)
    {
        if(isPalindrome(s.substr(pos, i-pos+1)))
        {
            path.push_back(s.substr(pos, i-pos+1));
            helper(s, i+1, path, result);
            path.pop_back();
        }
    }
}
vector<vector<string>> partition(string s)
{
    vector<string> path;
    vector<vector<string> > result;
    helper(s, 0, path, result);
    return result;
}

/*
 * 3
 * LeetCode 面试题 08.08 : 有重复字符串的排列组合
 * https://leetcode-cn.com/problems/permutation-ii-lcci/
 */
void backtrack(const int len, map<char, int>& rec, string pre, vector<string>& res)
{
    if(pre.size() == len)
    {
        res.push_back(pre);
        return;
    }
    auto iter = rec.begin();
    for(; iter != rec.end(); iter++)
    {
        if(iter->second)
        {
            (iter->second)--;
            backtrack(len, rec, pre + iter->first, res);
            (iter->second)++;
        }
    }
    return;
}
vector<string> permutation(string S)
{
    vector<string> res;
    map<char, int> rec;
    for(int i = 0; i < S.size(); i++)
    {
        if(rec.count(S[i])) {
            rec[S[i]]++;
        } else {
            rec[S[i]] = 1;
        }
    }
    backtrack(S.size(), rec, "", res);
    return res;
}

/*
 * 4
 * LeetCode 39 : 组合总和
 * https://leetcode-cn.com/problems/combination-sum/
 */
void backtrack(vector<int>& candidates, int target, int id, vector<int>& item, vector<vector<int> >& res)
{
    if(target < 0)
    {
        return;
    }
    if(target == 0)
    {
        res.push_back(item);
        return;
    }
    for(int i = id; i < candidates.size(); i++)
    {
        item.push_back(candidates[i]);
        backtrack(candidates, target-candidates[i], i, item, res);
        item.pop_back();
    }
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target)
{
    vector<vector<int> > res;
    if(candidates.empty())
    {
        return res;
    }
    vector<int> item;
    backtrack(candidates, target, 0, item, res);
    return res;
}

/*
 * 5
 * LeetCode 40 : 组合总和 II
 * https://leetcode-cn.com/problems/combination-sum-ii/
 */
void backtrack2(vector<int>& candidates, int start, int target, vector<int>& item, vector<vector<int>> & res)
{
    if(target < 0)
        return;
    if(target == 0)
    {
        res.push_back(item);
        return;
    }
    for(int i = start; i < candidates.size(); i++)
    {
        if(i > start && candidates[i] ==candidates[i - 1])
            continue;
        item.push_back(candidates[i]);
        backtrack2(candidates, i+1, target - candidates[i], item, res);
        item.pop_back();
    }
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
{
    vector<vector<int>> res;
    vector<int> item;
    sort(candidates.begin(),candidates.end());
    backtrack2(candidates,0,target,item,res);
    return res;
}

/*
 * 6
 * LeetCode 面试题 08.07 : 无重复字符串的排列组合
 * https://leetcode-cn.com/problems/permutation-i-lcci/
 */
/*
// method 1
vector<string> permutation(string S)
{
    vector<string> res;
    dfs(S, 0, res);
    return res;
}
void dfs(string& S, int index, vector<string>& res)
{
    if(index == S.size())
    {
        res.push_back(S);
        return;
    }
    for(int i = index; i < S.size(); ++i)
    {
        swap(S[i], S[index]);
        dfs(S, index + 1, res);
        swap(S[i], S[index]);
    }
}

// method 2
vector<string> permutation(string S)
{
    sort(S.begin(), S.end());
    vector<string> res;
    res.emplace_back(S);
    while(next_permutation(S.begin(), S.end()))
        res.emplace_back(S);
    return res;
}

// method 3
vector<string> permutation(string S)
{
    vector<string> res;
    if(S.size() == 0)
    {
        return res;
    }
    vector<bool> vis(S.size(), false);
    backtrack(S, "", vis, res);
    return res;
}
void backtrack(string& S, string item, vector<bool>& vis, vector<string>& res)
{
    if(S.size() == item.size())
    {
        res.push_back(item);
    } else {
        for(int i = 0; i < vis.size(); i++)
        {
            if(!vis[i])
            {
                item += S[i];
                vis[i] = true;
                backtrack(S, item, vis, res);
                item.pop_back();
                vis[i] = false;
            }
        }
    }
}
*/

/*
 * 7
 * LeetCode 47 : 全排列 II
 * https://leetcode-cn.com/problems/permutations-ii/
 */
void generate(vector<int>& nums, int index, vector<int>& item, vector<bool>& vis, vector<vector<int> >& res)
{
    if(index == nums.size()){
        res.push_back(item);
        return;
    }
    for(int i = 0; i < nums.size(); i++)
    {
        if(vis[i])
            continue;
        if((i > 0) && (nums[i-1] == nums[i]) && (!vis[i-1]))
            continue;
        item.push_back(nums[i]);
        vis[i] = true;
        generate(nums, index+1, item, vis, res);
        item.pop_back();
        vis[i] = false;
    }
}
vector<vector<int>> permuteUnique(vector<int>& nums)
{
    vector<vector<int> > res;
    if(nums.empty())
        return res;
    vector<bool> vis(nums.size(), false);
    vector<int> item;
    sort(nums.begin(),nums.end());
    generate(nums, 0, item, vis, res);
    return res;
}

/*
 * 8
 * LeetCode 1079 : 活字印刷
 * https://leetcode-cn.com/problems/letter-tile-possibilities/
 */
int mres;
void dfs(string& tiles, vector<bool>& vis)
{
    for(int i = 0; i < tiles.size(); i++)
    {
        if((i > 0) && (tiles[i] == tiles[i-1] && !vis[i-1]))
            continue;
        if(!vis[i])
        {
            vis[i] = true;
            mres++;
            dfs(tiles, vis);
            vis[i] = false;
        }
    }
}
int numTilePossibilities(string tiles)
{
    mres = 0;
    if(tiles.empty())
        return mres;
    sort(tiles.begin(), tiles.end());
    vector<bool> vis(tiles.size(), false);
    dfs(tiles, vis);
    return mres;
}





int main()
{
    cout<<"recursion And Backtracking"<<endl;
    return 0;
}