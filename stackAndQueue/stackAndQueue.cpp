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


// 栈 stack
/*
利用栈的特性先进后出(FILO)去解决问题,主要用以下特性：
1) 数据是线性的；
2) 问题中常常涉及到数据的来回比较；比如每日温度、括号比配、字符串解码、去掉重读字母等问题；
3) 问题中涉及到数据的转置，例如进制问题，链表倒序打印问题；
*/

/*
 * 1
 * LeetCode 20 : 有效的括号
 * https://leetcode-cn.com/problems/valid-parentheses/
 */
bool isValid(string s)
{
    stack<char> rec;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '(' || s[i] == '{' || s[i] == '[') {
            rec.push(s[i]);
        } else {
            if(rec.empty()) {
                return false;
            }
            char c = rec.top();
            rec.pop();
            char match;
            if(s[i] == ')') {
                match = '(';
            } else if(s[i] == '}') {
                match = '{';
            } else {
                match = '[';
            }
            if(match != c) {
                return false;
            }
        }
    }
    if(!rec.empty()) {
        return false;
    }
    return true;
}


/*
 * 2
 * LeetCode 844 : 比较含退格的字符串
 * https://leetcode-cn.com/problems/backspace-string-compare/
 */
void helper(string& s, stack<char>& res)
{
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] != '#')
        {
            res.push(s[i]);
        }
        else if(!res.empty())
        {
            res.pop();
        }
    }
}
bool backspaceCompare(string S, string T)
{
    stack<char> s,t;
    helper(S,s);
    helper(T,t);
    if(s.size() != t.size())
    {
        return false;
    }
    while(!t.empty())
    {
        if(s.top() != t.top())
        {
            return false;
        }
        s.pop();
        t.pop();
    }
    return true;
}


/*
 * 3
 * LeetCode 144 : 二叉树的前序遍历
 * https://leetcode-cn.com/problems/binary-tree-preorder-traversal/
 */
vector<int> preorderTraversal(TreeNode* root)
{
    vector<int> res;
    if(root == NULL)
        return res;
    stack<TreeNode*> sta;
    sta.push(root);
    while(!sta.empty())
    {
        TreeNode* node = sta.top();
        sta.pop();
        res.push_back(node->val);

        if(node->right)
            sta.push(node->right);
        if(node->left)
            sta.push(node->left);
    }
    return res;
}


/*
 * 4
 * LeetCode 94 : 二叉树的中序遍历
 * https://leetcode-cn.com/problems/binary-tree-inorder-traversal/
 */
vector<int> inorderTraversal(TreeNode* root)
{
    vector<int> res;
    if(root == NULL)
        return res;
    stack<TreeNode*> sta;
    TreeNode* node = root;
    while(!sta.empty() || node != NULL) {
        while(node != NULL) {
            sta.push(node);
            node = node->left;
        }
        if(!sta.empty()) {
            node = sta.top();
            sta.pop();
            res.push_back(node->val);
            node = node->right;
        }
    }
    return res;
}



/*
 * 5
 * LeetCode 150 : 逆波兰表达式求值
 * https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/
 */

int evalRPN(vector<string>& tokens)
{
    stack<int> stack;
    int size = tokens.size();
    for(int i = 0;i<size;i++) {
        string str = tokens[i];
        int first;
        int second;
        if(str=="+") {
            second = stack.top();stack.pop();
            first = stack.top();stack.pop();
            stack.push(second+first);
        } else if(str=="-") {
            second = stack.top();stack.pop();
            first = stack.top();stack.pop();
            stack.push(first-second);
        } else if(str=="*") {
            second = stack.top();stack.pop();
            first = stack.top();stack.pop();
            stack.push(first*second);
        } else if(str=="/") {
            second = stack.top();stack.pop();
            first = stack.top();stack.pop();
            stack.push(first/second);
        } else {//为整数，解析并压栈
            int val = atoi(str.c_str());
            stack.push(val);
        }
    }
    return stack.top();
}


/*
 * 6
 * LeetCode 155 : 最小栈
 * https://leetcode-cn.com/problems/min-stack/
 */
class MinStack
{
/*
在入栈时，如果这个元素比最小值小，那么，我们让最小值入栈，然后将元素值赋给最小值，即新的最小值，
然后正常将这个元素入栈；在出栈时，如果栈顶元素与最小值相等，说明他的下一个元素是之前push的最小值（上一个），
出栈后，将这个之前的最小值赋值给最新的最小值。（每次push进去的最小值都是下面元素的最小值）
*/
public:
    /** initialize your data structure here. */
    stack<int> s;
    int min;
    void push(int x) {
        if(s.empty()) {
            s.push(x);
            min = x;
        } else {
            if(x <= min) {
                s.push(min);
                min = x;
            }
            s.push(x);
        }
    }
    void pop() {
        if(s.empty())
            return ;
        int p = s.top();
        s.pop();
        if(!s.empty() && p == min)
        {
            min = s.top();
            s.pop();
        }
    }

    int top() {
        return s.top();
    }

    int getMin() {
        return min;
    }
};

/*
 * 7
 * LeetCode 225 : 用队列实现栈
 * https://leetcode-cn.com/problems/implement-stack-using-queues/
 */
class MyStack
{
public:
    queue<int> q;
public:
    /** Initialize your data structure here. */
    MyStack()
    {
    }

    /** Push element x onto stack. */
    void push(int x) {
        int n = q.size();
        q.push(x);
        while(n > 0) {
            q.push(q.front());
            q.pop();
            n--;
        }
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int n = q.front();
        q.pop();
        return n;
    }

    /** Get the top element. */
    int top() {
        return q.front();
    }

    /** Returns whether the stack is empty. */
    bool empty() {
        if(q.empty())
            return true;
        return false;
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

/*
 * 8
 * LeetCode 224 : 基本计算器
 * https://leetcode-cn.com/problems/basic-calculator/
 */
int calculate(string s)
{
    int res = 0, sign = 1, n = s.size();
    if(n == 0)
        return 0;
    stack<int> st;
    for(int i = 0; i < n; i++)
    {
        if(s[i] >= '0') {
            int num = 0;
            while(i < n && s[i] >= '0')
            {
                num = num*10 + s[i++] - '0';
            }
            res += sign*num;
            i--;
        } else if(s[i] == '+') {
            sign=1;
        } else if(s[i] == '-') {
            sign=-1;
        } else if(s[i] == '(') {
            st.push(res);
            st.push(sign);
            res = 0;
            sign = 1;
        } else if(s[i] == ')') {
            res *= st.top(); st.pop();
            res += st.top(); st.pop();
        }
    }
    return res;
}


// 队列 queue
/*
 * 1
 * 剑指 Offer 59 - I : 滑动窗口的最大值
 * https://leetcode-cn.com/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof/
 */

/*
deque : 双端队列
// 在队头插入元素 n
void push_front(int n);
// 在队尾插入元素 n
void push_back(int n);
// 在队头删除元素
void pop_front();
// 在队尾删除元素
void pop_back();
// 返回队头元素
int front();
// 返回队尾元素
int back();
*/
vector<int> maxSlidingWindow(vector<int>& nums, int k)
{
    // 单调队列，从队头到队尾递减
    vector<int> ans;
    deque<int> deq;
    for(int i = 0; i < nums.size(); i++)
    {
        while(!deq.empty() && nums[deq.back()] <= nums[i]){
            deq.pop_back();
        }
        while(!deq.empty() && (deq.front() < i-k+1)) {
            //if判断条件中的第二个是为了判断队头是否过期，也就是说队头的索引是否小于当前索引
            deq.pop_front();
        }
        deq.push_back(i);
        if(i >= k-1)
            ans.push_back(nums[deq.front()]);
    }
    return ans;
}

int main()
{
    cout<<"stack and queue"<<endl;
    return 0;
}