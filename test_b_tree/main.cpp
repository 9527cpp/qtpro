#include <stdio.h>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <functional>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
TreeNode * createBinaryTree(int *arr,int len)
{
    TreeNode *root=NULL;
    TreeNode *q=NULL;
    queue<TreeNode *> qtn;
    if(!len || !arr)return root;
    root = new TreeNode(*arr++);
    qtn.push(root);
    int i = 1;
    int lor = 0;//0 left   1 right
    q = qtn.front();
    while(i < len)
    {
        TreeNode *p=NULL;
        int val = *arr;
        if(val!=0)
        {
            p = new TreeNode(val);
        }
        if(!lor)
        {
            q->left = p;
            if(p)qtn.push(p);
        }
        else
        {
            q->right = p;
            if(p)qtn.push(p);
            qtn.pop();
            q = qtn.front();
        }
        lor = !lor;
        arr++;
        i++;
    }
    return root;
}


TreeNode * createBinarySearchTree(int *arr,int len)
{
    TreeNode *root=NULL;
    TreeNode *q=NULL;
    if(!len || !arr)return root;
    root = new TreeNode(*arr++);
    int i = 1;
    while(i < len)
    {
        TreeNode *p=NULL;
        int val = *arr;
        if(val!=0)
        {
            p = new TreeNode(val);
        }
        else// jump 0
        {
            arr++;
            i++;
            continue;
        }
        q = root;
        while(1)
        {
            if(val < q->val)
            {
                if(!q->left){q->left = p;break;}
                q = q->left;
            }
            else
            {
                if(!q->right){q->right = p;break;}
                q = q->right;
            }
        }
        arr++;
        i++;
    }
    return root;
}

//// BFS queue   DFS stack
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

        
    }


    TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode *parent = root;
        while(parent)
        {
            if((p->val <= parent->val && q->val >= parent->val)
              ||(p->val >= parent->val && q->val <= parent->val))break;
            else if(p->val < parent->val && q->val < parent->val)
            {
                parent = parent->left;
            }
            else if(p->val > parent->val && q->val > parent->val)
            {
                parent = parent->right;
            }
        }
        return parent;
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> vs;
        stack<TreeNode *>stn;
        stack<string>ss;
        stringstream sstream;
        if(!root)return vs;
        TreeNode * p = root;
        TreeNode *lastp = NULL;
        sstream<<p->val;
        string s = string(sstream.str() );
        stn.push(p);
        ss.push(s);
        while(p->left)
        {
            stn.push(p->left);
            sstream.str("");
            sstream<<p->left->val;
            ss.push(string(ss.top()+"->"+string(sstream.str())));
            p = p->left;
        }
        while(!stn.empty())
        {
            TreeNode *p = stn.top();
            if(p->right)
            {
                if(lastp && p->right == lastp)
                {
                    lastp = p;
                    ss.pop();
                    stn.pop();
                    continue;
                }
                p = p->right;
                while(p)
                {
                    stn.push(p);
                    sstream.str("");
                    sstream<<p->val;
                    ss.push(string(ss.top()+"->"+string(sstream.str())));
                    p = p->left;
                }
            }
            else
            {
                lastp = p;
                if(!p->left)
                vs.push_back(ss.top());
                ss.pop();
                stn.pop();
            }
        }
        return vs;
    }
    bool isValidBST(TreeNode* root) {
        stack<TreeNode *>stn;
        if(!root)return false;
        while(root)
        {
            stn.push(root);
            root = root->left;
        }
        TreeNode *p = stn.top();
        int val = p->val;
        while(!stn.empty())
        {
            TreeNode *p = stn.top();
            if(p->val < val)return false;
            val = p->val;
            stn.pop();
            if(p->right)
            {
                p = p->right;
                while(p)
                {
                    stn.push(p);
                    p = p->left;
                }
            }
        }
        return true;
    }
    vector<vector<int> > zigzagLevelOrder(TreeNode* root) {
        queue<TreeNode *>qtn;
        vector<vector<int> > vvi;
        if(!root)return vvi;
        qtn.push(root);
        int nCount = 1;
        int dir = 0;// 0 -->    1<---
        int i = 0;
        int j = 0;
        while(!qtn.empty())
        {
            vector<int>vi;
            while(j < nCount)
            {
                TreeNode * p = qtn.front();
                qtn.pop();
                vi.push_back(p->val);
                if(p->left){qtn.push(p->left); i++;}
                if(p->right){qtn.push(p->right); i++;}
                j++;
            }
            nCount = i;
            i = 0;
            j = 0;
            if(dir)reverse(vi.begin(),vi.end());
            dir = !dir;
            vvi.push_back(vi);
        }
        return vvi;
    }
    vector<vector<int> > levelOrder(TreeNode* root) {
        queue<TreeNode *>qtn;
        vector<vector<int> > vvi;
        if(!root)return vvi;
        qtn.push(root);
        int nCount = 1;
        int i = 0;
        int j = 0;
        while(!qtn.empty())
        {
            vector<int>vi;
            while(j < nCount)
            {
                TreeNode * p = qtn.front();
                qtn.pop();
                vi.push_back(p->val);
                if(p->left){qtn.push(p->left); i++;}
                if(p->right){qtn.push(p->right); i++;}
                j++;
            }
            nCount = i;
            i = 0;
            j = 0;
            vvi.push_back(vi);
        }
        return vvi;
    }
    bool isSymmetric(TreeNode* root) {
        stack<TreeNode *>lstn;
        stack<TreeNode *>rstn;
        if(root==NULL)return true;
        if((!root->left && root->right)
         || (root->left && !root->right))return false;
        if(!root->left&&!root->right)return true;
        if(root->left->val!=root->right->val)return false;
        lstn.push(root->left);
        rstn.push(root->right);
        while(!lstn.empty() &&!rstn.empty())
        {
            TreeNode *pl = lstn.top();
            TreeNode *pr = rstn.top();
            lstn.pop();
            rstn.pop();
            if(pl->left && pr->right)
            {
                if(pl->left->val == pr->right->val){
                lstn.push(pl->left);
                rstn.push(pr->right);
                }
                else return false;
            }
            else if((pl->left && !pr->right)||(!pl->left && pr->right))return false;

            if(pl->right && pr->left)
            {
                if(pl->right->val == pr->left->val){
                lstn.push(pl->right);
                rstn.push(pr->left);
                }
                else return false;
            }
            else if((pl->right && !pr->left)||(!pl->right && pr->left))return false;

        }
        return true;
    }
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode *> parents;
        vector<int> ans;
        if(root==NULL)return ans;
        parents.push(root);
        while(!parents.empty())
        {
            TreeNode*p = parents.top();
            ans.push_back(p->val);
            //printf("%d,",p->val);
            parents.pop();
            if(p->right)parents.push(p->right);
            if(p->left)parents.push(p->left);

        }
        return ans;
    }

    vector<int> preorderTraversal_re(TreeNode* root) {
        stack<TreeNode *> parents;
        vector<int> ans;
        if(root==NULL)return ans;
    #if 0
        void preorderTraversal__re_internal(vector<int> &ans,TreeNode *root)
        {
            ans.push_back(root->val);
            if(root->left)preorderTraversal__re_internal(ans,root->left);      
            if(root->right)preorderTraversal__re_internal(ans,root->right);
        }    
        preorderTraversal__re_internal(ans,root); 
    #else
        function<void(vector<int> &,TreeNode*)> preorderTraversal_re_internal_lambada = [&preorderTraversal_re_internal_lambada](vector<int> &ans,TreeNode *root)
        {
            ans.push_back(root->val);
            if(root->left)preorderTraversal_re_internal_lambada(ans,root->left);                    
            if(root->right)preorderTraversal_re_internal_lambada(ans,root->right);        
        }; 
        preorderTraversal_re_internal_lambada(ans,root);    
    #endif          
        return ans;
    }

    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode *> parents;
        vector<int> ans;
        if(root==NULL)return ans;
        while(root)
        {
            parents.push(root);
            root = root->left;
        }
        while(!parents.empty())
        {
            TreeNode *p = parents.top();
            ans.push_back(p->val);
            //printf("%d,",p->val);
            parents.pop();
            if(p->right)
            {
                p = p->right;
                while(p)
                {
                    parents.push(p);
                    p = p->left;
                }
            }
        }
        return ans;
    }

    vector<int> inorderTraversal_re(TreeNode* root) 
    {
        stack<TreeNode *> parents;
        vector<int> ans;
        if(root==NULL)return ans;
    #if 0    
        void inorderTraversal_re_internal(vector<int> &ans,TreeNode *root)
        {      
            if(root->left)inorderTraversal_re_internal(ans,root->left);  
            ans.push_back(root->val);    
            if(root->right)inorderTraversal_re_internal(ans,root->right);
        }
        inorderTraversal_re_internal(ans,root);  
    #else
        function<void(vector<int> &,TreeNode*)> inorderTraversal_re_internal_lambada = [&inorderTraversal_re_internal_lambada](vector<int> &ans,TreeNode *root)
        {
            if(root->left)inorderTraversal_re_internal_lambada(ans,root->left);   
            ans.push_back(root->val);         
            if(root->right)inorderTraversal_re_internal_lambada(ans,root->right);        
        }; 
        inorderTraversal_re_internal_lambada(ans,root);
    #endif          
        return ans;
    }

   
    vector<int> postorderTraversal_re(TreeNode * root)
    {
        stack<TreeNode *> parents;
        vector<int> ans;
        if(root==NULL)return ans;
    #if 0
        void postorderTraversal_re_internal(vector<int> &ans,TreeNode *root)
        {      
            if(root->left)postorderTraversal_re_internal(ans,root->left);            
            if(root->right)postorderTraversal_re_internal(ans,root->right);
            ans.push_back(root->val);
        } 
        //postorderTraversal_re_internal(ans,root);
    #else
        function<void(vector<int> &,TreeNode*)> postoderTraversal_re_internal_lambada = [&postoderTraversal_re_internal_lambada](vector<int> &ans,TreeNode *root)
        {
            if(root->left)postoderTraversal_re_internal_lambada(ans,root->left);            
            if(root->right)postoderTraversal_re_internal_lambada(ans,root->right);
            ans.push_back(root->val);
        }; 
        postoderTraversal_re_internal_lambada(ans,root);
    #endif    
        return ans;
    }

    bool isSameTree(TreeNode* p, TreeNode* q) {
        stack<TreeNode*>vtn_p;
        stack<TreeNode*>vtn_q;
        if((!p&&q)||(!q&&p)||((p&&q)&&(p->val!=q->val)))return false;
        if(!p&&!q)return true;
        vtn_p.push(p);
        vtn_q.push(q);

        while(!vtn_p.empty() && !vtn_q.empty())
        {
            TreeNode*pp = vtn_p.top();
            TreeNode*qq = vtn_q.top();
            //printf("pp:%x,qq:%x\r\n",pp,qq);
            if(pp && qq &&pp->val == qq->val)
            {
                vtn_p.pop();
                vtn_q.pop();
                if((!pp->left&&qq->left)||(!qq->left&&pp->left)){printf("1");return false;}
                if(pp->left &&qq->left){
                    vtn_p.push(pp->left);
                    vtn_q.push(qq->left);
                }
                if((!pp->right&&qq->right)||(!qq->right&&pp->right)){printf("2");return false;}
                if(pp->right&&qq->right)
                {
                    vtn_p.push(pp->right);
                    vtn_q.push(qq->right);
                }
            }
            else {printf("3");return false;}
        }
        return true;
    }
    int maxDepth(TreeNode* root) {
        int mDepth = 0;
        stack<TreeNode *>stn;
        if(!root)return mDepth;
        TreeNode*p = root;
        TreeNode*plast = NULL;
        while(p)
        {
            stn.push(p);
            p = p->left;
        }
        while(!stn.empty())
        {
            p = stn.top();
            while(p->right &&p->right!=plast)
            {
                p = p->right;
                plast = p;
                stn.push(p);
                while(p->left)
                {
                    stn.push(p->left);
                    p = p->left;
                    plast = p;
                }
            }
            plast = p;
            //printf("%d\r\n",stn.size());
            if(stn.size() > mDepth) mDepth = stn.size();
            stn.pop();
        }
        return mDepth;
    }
    int minDepth(TreeNode* root) {
        unsigned int minLeafDepth = 0xFFFFFFFF;
        stack<TreeNode *>stn;
        if(!root)return 0;
        TreeNode*p = root;
        TreeNode*plast = NULL;
        while(p)
        {
            stn.push(p);
            p = p->left;
        }
        while(!stn.empty())
        {
            p = stn.top();
            while(p->right &&p->right!=plast)
            {
                p = p->right;
                plast = p;
                stn.push(p);
                while(p->left)
                {
                    stn.push(p->left);
                    p = p->left;
                    plast = p;
                }
            }
            if(!p->left&&!p->right)
            {
                //printf("%d\r\n",stn.size());
                if(stn.size() < minLeafDepth) minLeafDepth = stn.size();
            }
            plast = p;
            stn.pop();
        }
        return minLeafDepth;
    }
    int sumOfLeftLeaves(TreeNode* root) {
        int numOfLeftLeaves = 0;
        stack<TreeNode *> stn;
        vector<int> ans;
        if(root==NULL)return numOfLeftLeaves;
        TreeNode*p = root;
        TreeNode*pp = NULL;
        TreeNode*plast = NULL;

        while(root)
        {
            stn.push(root);
            root = root->left;
        }
        while(!stn.empty())
        {
            p = stn.top();
            while(p->right &&p->right!=plast)
            {
                p = p->right;
                plast = p;
                stn.push(p);
                while(p->left)
                {
                    stn.push(p->left);
                    p = p->left;
                    plast = p;
                }
            }
            plast = p;
            stn.pop();
            if(stn.size()>=1){
                pp = stn.top();
                if(!p->left &&!p->right && p == pp->left)
                {
                    //printf("p:%d,pp:%d\r\n",p->val,pp->val);
                    numOfLeftLeaves+=p->val;
                }
            }
        }
        return numOfLeftLeaves;
    }
};

/*
     3
    / \
   9   20
      /  \
     15  7


    BST:
     3
      \
       9
      /  \
     7   20
        /
       15
*/




int main()
{
    Solution s;
    int array[]={3,9,20,0,0,15,7};//0 present null
    //int array[]={1};
    //int array[]={2,1};
    //int array[]={1,0,2};
    //int array[]={1,2,2,3,4,4,3};
    //int array[]={1,2,2,0,3,0,3};
    //int array[]={1,2,3,0,5};
    int len = sizeof(array)/sizeof(array[0]);
    TreeNode * root = createBinaryTree(array,len);
    TreeNode * bstroot = createBinarySearchTree(array,len);
    vector<int>vi;
    printf("preorder:");
    vi = s.preorderTraversal(root);
    copy(vi.begin(),vi.end(),ostream_iterator<int>(cout,","));

    printf("\r\npreorder_re:");
    vi = s.preorderTraversal_re(root);
    copy(vi.begin(),vi.end(),ostream_iterator<int>(cout,","));

    printf("\r\ninorder:");
    vi = s.inorderTraversal(root);
    copy(vi.begin(),vi.end(),ostream_iterator<int>(cout,","));

    printf("\r\ninorder_re:");
    vi = s.inorderTraversal_re(root);
    copy(vi.begin(),vi.end(),ostream_iterator<int>(cout,","));

    printf("\r\npostorder_re:");
    vi = s.postorderTraversal_re(root);
    copy(vi.begin(),vi.end(),ostream_iterator<int>(cout,","));

    int val = s.maxDepth(root);
    printf("\r\nmaxDepth:%d",val);
    val = s.minDepth(root);
    printf("\r\nminDepth:%d",val);
    val = s.sumOfLeftLeaves(root);
    printf("\r\nsumOfLeftLeaves:%d",val);
    val = s.isSymmetric(root);
    printf("\r\nisSymmetric:%s",val?"true":"false");
    vector<vector<int> > vvi;
    printf("\r\nlevelOrder:");
    vvi = s.levelOrder(root);
    for(vector<vector<int> >::iterator itr = vvi.begin();itr!=vvi.end();itr++)
    {
        copy((*itr).begin(),(*itr).end(),ostream_iterator<int>(cout,","));
        cout<<"-->";
    }
    printf("\r\nzigzagLevelOrder:");
    vvi = s.zigzagLevelOrder(root);
    for(vector<vector<int> >::iterator itr = vvi.begin();itr!=vvi.end();itr++)
    {
        copy((*itr).begin(),(*itr).end(),ostream_iterator<int>(cout,","));
        cout<<"-->";
    }

    printf("\r\nbst inorder:");
    vi = s.inorderTraversal(bstroot);
    copy(vi.begin(),vi.end(),ostream_iterator<int>(cout,","));
    val = s.isValidBST(bstroot);
    printf("\r\nisValidBST:%s",val?"true":"false");
    printf("\r\nbinaryTreePaths:");
    vector<string> vs =s.binaryTreePaths(root);
    copy(vs.begin(),vs.end(),ostream_iterator<string>(cout,","));
    printf("\r\nlowestCommonAncestorBST:");
    TreeNode * parent = s.lowestCommonAncestorBST(bstroot,new TreeNode(9),new TreeNode(7));
    printf("%d",parent?parent->val:0);

    return 0;
}
