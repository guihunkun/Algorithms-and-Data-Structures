#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include "map"

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


// LinkedList 测试辅助函数

// 根据n个元素的数组arr创建一个链表, 并返回链表的头
ListNode* createLinkedList(int arr[], int n)
{
    if(n == 0)
        return NULL;
    ListNode* head = new ListNode(arr[0]);
    ListNode* curNode = head;
    for(int i = 1 ; i < n ; i ++)
    {
        curNode->next = new ListNode(arr[i]);
        curNode = curNode->next;
    }

    return head;
}

// 打印以head为头结点的链表信息内容
void printLinkedList(ListNode* head)
{

    ListNode* curNode = head;
    while(curNode != NULL)
    {
        cout << curNode->val << " -> ";
        curNode = curNode->next;
    }
    cout << "NULL" << endl;
    return;
}

// LeetCode 206 ：反转链表
ListNode* reverseList(ListNode* head)
{
    if(head==NULL)
        return NULL;
    ListNode* pre=NULL;
    ListNode* cur=head;
    while(cur!=NULL)
    {
        ListNode* next=cur->next;
        cur->next=pre;
        pre=cur;
        cur=next;
    }
    return pre;
}

// LeetCode 21 ：合并两个有序链表
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
    if(l1 == NULL)
        return l2;
    if(l2 == NULL)
        return l1;
    ListNode* root = NULL;
    if(l1->val <= l2->val) {
        root = l1;
        l1 = l1->next;
    } else {
        root = l2;
        l2 = l2->next;
    }
    ListNode* cur = root;
    while(l1 != NULL && l2 != NULL) {

        if(l1->val <= l2->val) {
            cur->next = l1;
            l1 = l1->next;
        } else {
            cur->next = l2;
            l2 = l2->next;
        }
        cur = cur->next;
    }
    if(l1 == NULL)
        cur->next = l2;
    if(l2 == NULL)
        cur->next = l1;
    return root;
}

// LeetCode 剑指 Offer 22 ： 链表中倒数第k个节点
ListNode* getKthFromEnd(ListNode* head, int k)
{
    ListNode* fast = head;
    int i = 1;
    while(fast != NULL && i <= k)
    {
        fast = fast->next;
        i++;
    }
    ListNode* slow = head;
    while(fast != NULL)
    {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}

// LeetCode 面试题 02.08 ： 环路检测
ListNode *detectCycle(ListNode *head)
{
    if(!head || !head->next) {
        return NULL;
    }
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast&&fast->next) {
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow) {
            break;
        }
    }
    if(fast != slow) {
        return NULL;
    }
    fast = head;
    while(fast != slow) {
        fast = fast->next;
        slow = slow->next;
    }
    return fast;
}

// LeetCode 160 ：相交链表
/*
 * A指针遍历到NULL就返回headB重新开始，B指针遍历到NULL就返回headA，终有一刻会相交。
 * 假设交点为O，头分别记为A，B，尾记为E；则AO + OE + BO = BO + OE + AO。
 */
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
    if(headA==NULL || headB==NULL)
        return NULL;
    ListNode * pa=headA;
    ListNode * pb=headB;
    int count=0;
    while(pa && pb)
    {
        if(count>2)
            break;
        if(pa==pb)
            return pa;
        if(pa->next==NULL || pb->next==NULL)
            count++;
        pa=(pa->next==NULL)?headB:pa->next;
        pb=(pb->next==NULL)?headA:pb->next;
    }
    return NULL;
}

// LeetCode 83 : 删除排序链表中的重复元素
ListNode* deleteDuplicates(ListNode* head)
{
    if(head == NULL || head->next == NULL)
        return head;
    ListNode* cur = head;
    ListNode* ne = head->next;
    while(ne != NULL) {
        if(cur->val == ne->val)
            ne = ne->next;
        else {
            cur->next = ne;
            cur = ne;
            ne = ne->next;
        }
    }
    cur->next = NULL;
    return head;
}

// LeetCode 25 : K 个一组翻转链表
ListNode* reverseOperator(ListNode* n,ListNode *b)
{
    ListNode *pre, *cur, *nxt;
    pre = NULL; cur = n; nxt = n;
    while(cur != b) {
        nxt = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nxt;
    }
    return pre;
}

ListNode* reverseKGroup(ListNode* head, int k)
{
    if(head == NULL)
        return NULL;
    ListNode *a = head;
    ListNode *b = head;
    for(int i = 0; i < k; i++) {
        if(b == NULL)
            return head;
        b = b->next;
    }

    ListNode *newNode = reverseOperator(a,b);
    a->next = reverseKGroup(b,k);
    return newNode;
}

// LeetCode 92 ： 反转链表 II
/*
 * 设置一个头节点，同时保存m之前的节点
 */
ListNode* reverseBetween(ListNode* head, int m, int n)
{
    ListNode dumb(0);
    dumb.next = head;
    if(m == n)
        return head;
    ListNode* preM = &dumb;//保存m之前结点
    ListNode* pM = head,*pN = head ,*temp = head;
    int index=1;
    while(pN != NULL) {
        if(index < m) {
            index++;
            preM = pM;
            pM = pM->next;
            pN = pN->next;
        }
        else if(index >= m && index <= n) {
            temp = pN->next;
            pN->next = preM->next;
            preM->next =pN;
            pN = temp;
            index++;
        }
        else if(index > n)
            break;
    }
    pM->next = pN;
    return dumb.next;
}

// LeetCode 61 ：旋转链表
/*
 * 1. 找到旧的尾部并将其与链表头相连 old_tail.next = head，整个链表闭合成环，同时计算出链表的长度 n。
 * 2. 找到新的尾部，第 (n - k % n - 1) 个节点 ，新的链表头是第 (n - k % n) 个节点。
 * 3. 断开环 new_tail.next = None，并返回新的链表头 new_head。
 */
ListNode* rotateRight(ListNode* head, int k)
{
    if(head == NULL || head->next == NULL)
        return head;
    if(k == 0)
        return head;
    ListNode* fast=head;
    ListNode* slow=head;
    int count = 1;
    while(fast->next != NULL) {
        count++;
        fast = fast->next;
    }
    if(k%count == 0)
        return head;
    ListNode* last = fast;
    k=k%count;
    for(int i = 1; i < count-k; i++)
    {
        slow = slow->next;
    }
    ListNode* newhead = slow->next;
    slow->next = NULL;
    last->next = head;
    return newhead;
}

// Leetcode 2 : 两数相加
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
    if(l1 == NULL && l2 == NULL)
        return NULL;
    ListNode *root = NULL;
    ListNode *tail = NULL;
    int sum=0;
    while(l1 != NULL || l2 != NULL) {
        if(l1 != NULL) {
            sum += l1->val;
            l1 = l1->next;
        }
        if(l2 != NULL) {
            sum += l2->val;
            l2 = l2->next;
        }
        ListNode *p = new ListNode(sum%10);
        if(root == NULL) {
            root = p;
            tail = p;
        } else {
            tail->next = p;
            tail = p;
        }
        sum = sum/10;
    }
    if(sum != 0) {
        ListNode *p = new ListNode(sum%10);
        if(root == NULL) {
            root = p;
            tail = p;
        } else {
            tail->next = p;
            tail=p;
        }
    }
    return root;
}


int main()
{
    int arr[] = {1,2,3,4,5,6};
    int n = sizeof(arr)/sizeof(int);

    cout<<"inital list"<<endl;
    ListNode* head = createLinkedList(arr, n);
    printLinkedList(head);

    ListNode* res = reverseList(head);
    cout<<"after reverse the list"<<endl;
    printLinkedList(res);

    return 0;
}