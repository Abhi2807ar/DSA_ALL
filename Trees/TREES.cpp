iterative 
1.preorder

vector<int> preorderTraversal(TreeNode* root) {

    vector<int> ans;

    if (root == NULL)
        return ans;

    stack<TreeNode*> st;
    st.push(root);

    while (!st.empty()) {

        TreeNode* node = st.top();
        st.pop();

        // Root
        ans.push_back(node->val);
//Lekin stack mein agar hume Left ko pehle 
//process karwana hai, 
//toh Right ko pehle push karna padega.
        // Right first
        if (node->right != NULL)
            st.push(node->right);

        // Left second
        if (node->left != NULL)
            st.push(node->left);
    }

    return ans;
}

2.inorder
vector<int> inorderTraversal(TreeNode* root) {

    vector<int> ans;
    stack<TreeNode*> st;

    TreeNode* curr = root;

    while (curr != NULL || !st.empty()) {

        // 1. Leftmost node tak jao
        while (curr != NULL) {
            st.push(curr);
            curr = curr->left;
        }

        // 2. Leftmost node nikalo
        curr = st.top();
        st.pop();

        // 3. Root process karo
        ans.push_back(curr->val);

        // 4. Right subtree par jao
        curr = curr->right;
    }

    return ans;
}

3.Postorder

vector<int> postorderTraversal(TreeNode* root) {

    vector<int> ans;

    stack<TreeNode*> st;
    TreeNode* curr = root;
    TreeNode* lastVisited = NULL;

    while (curr != NULL || !st.empty()) {

        // Leftmost jao
        while (curr != NULL) {
            st.push(curr);
            curr = curr->left;
        }

        TreeNode* node = st.top();

        // Right child available hai
        // aur abhi visit nahi hua
        if (node->right != NULL && node->right != lastVisited) {
            curr = node->right;
        }
        else {
            ans.push_back(node->val);
            lastVisited = node;
            st.pop();
        }
    }

    return ans;
}

Trick

1.Path problems mein:

PUSH
 ↓
EXPLORE
 ↓
SUCCESS → return
 ↓
FAIL → POP


2.Whenever you see:

longest path between two nodes


think:LEFT HEIGHT + RIGHT HEIGHT

3.DFS → recursion
4.BFS → queue

Trees
             1
           /   \
          2     3
         / \   / \
        4   5 6   7
--har node

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {
        val = x;
        left = NULL;
        right = NULL;
    }
};
//Sabse important thought:

Har tree problem = 
current node par kya karna hai + 
left subtree se kya chahiye + 
right subtree se kya chahiye.

Level order traversal

vector<vector<int>> levelOrder(TreeNode* root) {

    vector<vector<int>> ans;

    if(root == NULL)
        return ans;

    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {

        int size = q.size();

        vector<int> level;

        for(int i = 0; i < size; i++) {

            TreeNode* curr = q.front();
            q.pop();

            level.push_back(curr->val);

            if(curr->left)
                q.push(curr->left);

            if(curr->right)
                q.push(curr->right);
        }

        ans.push_back(level);
    }

    return ans;
}

// har level order ka traversal skelton

queue<TreeNode*> q;

q.push(root);

while (!q.empty())
{
    int size = q.size();

    vector<int> level;

    for (int i = 0; i < size; i++)
    {
        TreeNode* node = q.front();
        q.pop();

        // CURRENT NODE KA KAAM

        if (node->left)
            q.push(node->left);

        if (node->right)
            q.push(node->right);
    }

    // CURRENT LEVEL KA KAAM
    ans.push_back(level);
}
/////
leftside view
vector<int> leftSideView(TreeNode* root)
{
    vector<int> result;

    if (root == NULL)
        return result;

    queue<TreeNode*> que;

    que.push(root);

    while (!que.empty())
    {
        int n = que.size();

        for (int i = 0; i < n; i++)
        {
            TreeNode* node = que.front();
            que.pop();

            // First node of every level
            if (i == 0)
                result.push_back(node->val);

            if (node->left != NULL)
                que.push(node->left);

            if (node->right != NULL)
                que.push(node->right);
        }
    }

    return result;
}

// right view
vector<int> rightSideView(TreeNode* root)
{
    vector<int> result;

    if (root == NULL)
        return result;

    queue<TreeNode*> que;

    que.push(root);

    while (!que.empty())
    {
        int n = que.size();

        TreeNode* node = NULL;

        while (n--)
        {
            node = que.front();
            que.pop();

            if (node->left != NULL)
                que.push(node->left);

            if (node->right != NULL)
                que.push(node->right);
        }

        // Last node of this level
        result.push_back(node->val);
    }

    return result;
}

***
Difference sirf itna:
Right View
result.push_back(node->val);
after entire level
→ last node.

Left View
Current level ka first node chahiye
**
/// DEPTH OF TRESS///////////////
// class Solution {
// public:
    
//     int diameter(TreeNode* root, int& result) {
//         if(!root)
//             return 0;
        
//         int left  = diameter(root->left, result);
//         int right = diameter(root->right, result);
        
//         result = max(result, left + right); //What if I longest diamenter passes through left -> me -> right
        
//         return max(left, right) + 1; //But I will return max I can afford if (left -> me -> right) was not answer
        
//     }
    
//     int diameterOfBinaryTree(TreeNode* root) {
//         if(!root)
//             return 0;
        
//         int result = INT_MIN;
        
//         diameter(root, result);
        
//         return result;
//     }
// };


/////SUM OF LEFT LEAVES////////////////
//approach2
int sumOfLeftLeaves(TreeNode* root) {

    if(root == NULL)
        return 0;

    int sum = 0;

    // Check whether left child is a leaf
    if(root->left != NULL &&
       root->left->left == NULL &&
       root->left->right == NULL) {

        sum += root->left->val;
    }

    // Go into left subtree
    sum += sumOfLeftLeaves(root->left);

    // Go into right subtree
    sum += sumOfLeftLeaves(root->right);

    return sum;
}
///////////
Sabse common mistake
if(root->left == NULL && root->right == NULL)
    sum += root->val;
Isse saare leaves add ho jayenge.

//Approach-1 (Using Parent Pointer)
//T.C : O(n)
//S.C : O(1) Auxiiliary Space and O(depth of tree) recursion system stack space
// class Solution {
// public:
//     int sum(TreeNode* curr, TreeNode* parent) {
//         if(!curr)
//             return 0;
        
//         int left  = sum(curr->left, curr);
//         int right = sum(curr->right, curr);
        
//         int sum = 0;
//         if(curr->left == NULL && curr->right == NULL) {
//             if(parent && parent->left == curr)
//                 sum += curr->val;
//         }
        
//         return left+right+sum;
//     }
//     int sumOfLeftLeaves(TreeNode* root) {
//         if(!root)
//             return 0;
//         TreeNode* parent = NULL;
//         return sum(root, parent);
//     }
// };



//////UNIQUE BINARY SEARCH TREE 2//////////////////////////
// class Solution {
// public:
    
//     map<pair<int, int>, vector<TreeNode*>> mp;  //for memoization
    
//     vector<TreeNode*> solve(int start, int end) {
        
//         if(start > end) {
//             return {NULL};
//         }
        
//         if(start == end) {
//             TreeNode* root = new TreeNode(start);
//             return {root};
//         }
        
//         if(mp.find({start, end}) != mp.end())
//             return mp[{start, end}];
        
//         vector<TreeNode*> result;
//         for(int i = start; i <= end; i++) {  ///sab node pe try marne k liye
            
//             vector<TreeNode*> leftList  = solve(start, i-1);
//             vector<TreeNode*> rightList = solve(i+1, end);
            
//             for(TreeNode* leftRoot : leftList) {   ///sara left side wala k liye
                
//                 for(TreeNode* rightRoot : rightList) {   ////right side wal ke liye and pairing v
                    
//                     TreeNode* root = new TreeNode(i);
//                     root->left  = leftRoot;
//                     root->right = rightRoot;
                    
//                     result.push_back(root);
                    
//                 }
                
//             }
            
//         }
        
//         return mp[{start, end}] = result;
        
//     }
    
//     vector<TreeNode*> generateTrees(int n) {
//         return solve(1, n);
//     }
// };


//////////right side view of tree(bfs)/
// class Solution {
// public:
//     vector<int> rightSideView(TreeNode* root) {
//         if(!root)
//             return {};
        
//         queue<TreeNode*> que;
//         vector<int> result;
        
//         que.push(root);
        
//         while(!que.empty()) {
//             int n = que.size();
//             TreeNode* rightNode = NULL;
//             while(n--) {
//                 rightNode = que.front();
//                 que.pop();
                
//                 if(rightNode->left)
//                     que.push(rightNode->left);
//                 if(rightNode->right)
//                     que.push(rightNode->right);
//             }
//             result.push_back(rightNode->val);
//         }
//         return result;
//     }
// };

/////////////lca of binry treesd//
// class Solution {
// public:
//     TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
//         if (root== NULL)
//             return NULL;
        
//            if(root==p || root==q)
//            return root;

// TreeNode* leftN = lowestCommonAncestor(root->left,p,q);
// TreeNode* rightN = lowestCommonAncestor(root->right,p,q);


// if ( leftN != NULL && rightN !=NULL){
// return root;
// }

// if (leftN != NULL && rightN ==NULL)
// return leftN;

// return rightN;

        
//     }
// };


//////INVERT A TREE///////////
// class Solution {
// public:
//     TreeNode* invertTree(TreeNode* root) {
//         if(root==NULL)
//         return NULL;
//         invertTree(root->left);
//         invertTree(root->right);
//         TreeNode*temp=root->left;
//         root->left=root->right;
//         root->right=temp;
//          return root;
        
//     }
// };

/////inorder traversal////////////
// class Solution {
// public:
//   vector<int> ans;
//     vector<int> inorderTraversal(TreeNode* root) {
//         if(root==NULL) return {};
//         inorderTraversal(root->left);
//         ans.push_back(root->val);
//         inorderTraversal(root->right);
//         return ans;
//     }
// };

///////////PREORDER TRAVERSAL////////////////
// class Solution {
// public:
//  vector<int> ans;
//     vector<int> preorderTraversal(TreeNode* root) {
//           if(root==NULL) return {};
//           ans.push_back(root->val);
//       preorderTraversal(root->left);
        
//       preorderTraversal(root->right);
//         return ans;
//     }
// };



//////////////PREORDER TRAVERSAL//////////////////////////
// class Solution {
// public:
//     vector<int> ans;
//     vector<int> postorderTraversal(TreeNode* root) {

//         if (root == NULL)
//             return {};

        
//         postorderTraversal(root->left);
//         postorderTraversal(root->right);
//         ans.push_back(root->val);
//         return ans;
//     }
// };


////////Binary tree morris inorder traversal///////////////
// class Solution {
// public:
//     // Function to perform iterative Morris
//     // inorder traversal of a binary tree
//     vector<int> getInorder(TreeNode* root) {
//         // Vector to store the
//         // inorder traversal result
//         vector<int> ans;
//         // Pointer to the current node,
//         // starting from the root
//         TreeNode* cur = root;
        
//         // Loop until the current
//         // node is not NULL
//         while (cur != NULL) {
//             // If the current node's
//             // left child is NULL
//             //left child null hai to print krke right move kar jao current ko
//             if (cur->left == NULL) {
//                 // Add the value of the current
//                 // node to the inorder vector
//                ans.push_back(cur->val);
//                 // Move to the right child
//                 cur = cur->right;
//             } else {
//                 // If the left child is not NULL,
//                 // find the predecessor (rightmost node
//                 // in the left subtree)

                
//                 //left tree mein right most guy ko dhundo or thread connection bnao
//                 TreeNode* prev = cur->left;
//                 while (prev->right && prev->right != cur) {
//                     prev = prev->right;
//                 }
                
//                 // If the predecessor's right child
//                 // is NULL, establish a temporary link
//                 // and move to the left child
//                 if (prev->right == NULL) {
//                     prev->right = cur;
//                     cur = cur->left;
//                 } else {
//                     // If the predecessor's right child
//                     // is already linked, remove the link,
//                     // add current node to inorder vector,
//                     // and move to the right child

//             //thread tod do
//                     prev->right = NULL;
//                    ans.push_back(cur->val);
//                     cur = cur->right;
//                 }
//             }
//         }
        
//         // Return the inorder
//         // traversal result
//         return ans;
//     }
// };



//////////////moris preorder traversal mein///////////////////
// class Solution {
// public:
//     // Function to perform iterative Morris
//     // inorder traversal of a binary tree
//     vector<int> getpreorder(TreeNode* root) {
//         // Vector to store the
//         // inorder traversal result
//         vector<int> ans;
//         // Pointer to the current node,
//         // starting from the root
//         TreeNode* cur = root;
        
//         // Loop until the current
//         // node is not NULL
//         while (cur != NULL) {
//             // If the current node's
//             // left child is NULL
//             //left child null hai to print krke right move kar jao current ko
//             if (cur->left == NULL) {
//                 // Add the value of the current
//                 // node to the inorder vector
//                ans.push_back(cur->val);
//                 // Move to the right child
//                 cur = cur->right;
//             } else {
//                 // If the left child is not NULL,
//                 // find the predecessor (rightmost node
//                 // in the left subtree)

                
//                 //left tree mein right most guy ko dhundo or thread connection bnao
//                 TreeNode* prev = cur->left;
//                 while (prev->right && prev->right != cur) {
//                     prev = prev->right;
//                 }
                
//                 // If the predecessor's right child
//                 // is NULL, establish a temporary link
//                 // and move to the left child
//                 if (prev->right == NULL) {
                    
//                     prev->right = cur;
//                      ans.push_back(cur->val); //bas yeh change hoaga inorder ka code mein or preorder m badal jauga
//                     cur = cur->left;
//                 } else {
//                     // If the predecessor's right child
//                     // is already linked, remove the link,
//                     // add current node to inorder vector,
//                     // and move to the right child

//             //thread tod do
//                     prev->right = NULL;
//                   //bas yeh change hoaga inorder ka code mein or preorder m badal jauga
//                     cur = cur->right;
//                 }
//             }
//         }
        
//         // Return the inorder
//         // traversal result
//         return ans;
//     }
// };



//////////LEFT SIDE VIEW OF TREE//////////////////////
// class Solution {
//   public:
  
//     vector<int> leftView(Node *root) {
//          vector<int>result;
//         recursion(root,0,result);
//         return result;
//        }
        
//      void recursion(Node *root, int level , vector<int> &result){
//         if(root == NULL)
//         return;
   
//    if(level == result.size() )
   
//       result.push_back(root->data);
      
//    recursion(root->left, level+1, result);
//    recursion(root->right, level+1, result);
         

// }
// };


/////////RIGHTSIDE VIEW OF TREE//////////
// class Solution {
//   public:
  
//     vector<int> RIGHTtView(Node *root) {
//          vector<int>result;
//         recursion(root,0,result);
//         return result;
//        }
        
//      void recursion(Node *root, int level , vector<int> &result){
//         if(root == NULL)
//         return;
   
//    if(level == result.size() )
   
//       result.push_back(root->data);

//    recursion(root->right, level+1, result);
//    recursion(root->left, level+1, result);
   
         

// }
// };


///////top view of bt/////////////////
// class Solution
// {
//     public:
//     //Function to return a list of nodes visible from the top view 
//     //from left to right in Binary Tree.
//     vector<int> topView(Node *root)
//     {
//           vector<int> ans;
        
//         // Check if the tree is empty
//         if(root == NULL){
//             return ans;
//         }
        
//         // Map to store the top view nodes
//         // based on their vertical positions
//         map<int, int> mpp;
        
//         // Queue for BFS traversal, each element
//         // is a pair containing node 
//         // and its vertical position
//         queue<pair<Node*, int>> q;
        
//         // Push the root node with its vertical
//         // position (0) into the queue
//         q.push({root, 0});
        
//         // BFS traversal
//         while(!q.empty()){
//             // Retrieve the node and its vertical
//             // position from the front of the queue
//             auto it = q.front();
//             q.pop();
//             Node* node = it.first;
//             int line = it.second;
            
//             // If the vertical position is not already
//             // in the map, add the node's data to the map
//             if(mpp.find(line) == mpp.end()){
//                 mpp[line] = node->data;
//             }
            
//             // Process left child
//             if(node->left != NULL){
//                 // Push the left child with a decreased
//                 // vertical position into the queue
//                 q.push({node->left, line - 1});
//             }
            
//             // Process right child
//             if(node->right != NULL){
//                 // Push the right child with an increased
//                 // vertical position into the queue
//                 q.push({node->right, line + 1});
//             }
//         }
        
//         // Transfer values from the
//         // map to the result vector
//         for(auto it : mpp){
//             ans.push_back(it.second);
//         }
        
//         return ans;
//     }
// };


//////////BOTTOM VIEW OF BT/////////////////////
// class Solution {
//   public:
//     vector <int> bottomView(Node *root) {
//        // Vector to store the result
//         vector<int> ans;
        
//         // Check if the tree is empty
//         if(root == NULL){
//             return ans;
//         }
        
//         // Map to store the bottom view nodes
//         // based on their vertical positions
//         map<int, int> mpp;
        
//         // Queue for BFS traversal, each
//         // element is a pair containing node
//         // and its vertical position
//         queue<pair<Node*, int>> q;
        
//         // Push the root node with its vertical
//         // position (0) into the queue
//         q.push({root, 0});
        
//         // BFS traversal
//         while(!q.empty()){
//             // Retrieve the node and its vertical
//             // position from the front of the queue
//             auto it = q.front();
//             q.pop();
//             Node* node = it.first;
//             int line = it.second;
            
//             // Update the map with the node's data
//             // for the current vertical position
//             mpp[line] = node->data;
            
//             // Process left child
//             if(node->left != NULL){
//                 // Push the left child with a decreased
//                 // vertical position into the queue
//                 q.push({node->left, line - 1});
//             }
            
//             // Process right child
//             if(node->right != NULL){
//                 // Push the right child with an increased
//                 // vertical position into the queue
//                 q.push({node->right, line + 1});
//             }
//         }
        
//         // Transfer values from the
//         // map to the result vector
//         for(auto it : mpp){
//             ans.push_back(it.second);
//         }
        
//         return ans;
//     }
// };


////////preorder inorder and postorder in single traversals////////////////
// vector<vector<int>> getTreeTraversal(TreeNode *root){
//    vector<int> pre, in, post;

//     // If the tree is empty,
//     // return empty traversals
//     if (root == NULL) {
//         return {};
//     }

//     // Stack to maintain nodes
//     // and their traversal state
//     stack<pair<TreeNode*, int>> st;

//     // Start with the root node
//     // and state 1 (preorder)
//     st.push({root, 1});

//     while (!st.empty()) {
//         auto it = st.top();
//         st.pop();

//         // this is part of pre
//         if (it.second == 1) {
//             // Store the node's data
//             // in the preorder traversal
//             pre.push_back(it.first->data);
//             // Move to state 2
//             // (inorder) for this node
//             it.second = 2;
//             // Push the updated state
//             // back onto the stack
//             st.push(it); 

//             // Push left child onto
//             // the stack for processing
//             if (it.first->left != NULL) {
//                 st.push({it.first->left, 1});
//             }
//         }

//         // this is a part of in
//         else if (it.second == 2) {
//             // Store the node's data
//             // in the inorder traversal
//             in.push_back(it.first->data);
//             // Move to state 3
//             // (postorder) for this node
//             it.second = 3;
//             // Push the updated state
//             // back onto the stack
//             st.push(it); 

//             // Push right child onto
//             // the stack for processing
//             if (it.first->right != NULL) {
//                 st.push({it.first->right, 1});
//             }
//         }

//         // this is part of post
//         else {
//             // Store the node's data
//             // in the postorder traversal
//             post.push_back(it.first->data);
//         }
//     }

//     // Returning the traversals
//     vector<vector<int>> result;
//      result.push_back(in);
//     result.push_back(pre);
//     result.push_back(post);
//     return result;
// }

//vertical order traversal////////////////
// class Solution {
// public:
//     vector<vector<int>> verticalTraversal(TreeNode* root) {
//         map<int,map<int,multiset<int>>> nodes;
//         queue<pair<TreeNode* ,pair<int,int>>>task;
//         task.push({root,{0,0}});

//         while(!task.empty()){
//             auto p=task.front();
//             task.pop();
//             TreeNode* node= p.first;
//             int x= p.second.first , y= p.second.second;
//             nodes[x][y].insert(node->val);
//             if(node->left){
//                 task.push({node->left,{x-1,y+1}});
//             }

//             if(node->right){
//                 task.push({node->right,{x+1,y+1}});
//             }

//         }

//             vector<vector<int>>ans;
//             for (auto p: nodes){
//                 vector<int> col;
//                 for(auto q: p.second){
//                     col.insert(col.end(),q.second.begin(),q.second.end());
//                 }
//                 ans.push_back(col);
//             }
        
//         return ans;
        
//     }
// };


////////ROOT TO LEAF PATHS///////////////
//   void solve(Node* root,vector<vector<int>> &ans,vector<int> &result)
// {
//     if (root == NULL) return;
    
//     result.push_back(root->data);
    
//     if (root->left == NULL && root->right == NULL) {
        
//         ans.push_back(result);
//     } 
//     else {
        
//         solve(root->left, ans, result);
//         solve(root->right, ans, result);
//     }
    
//     result.pop_back();

// }

// class Solution {
//   public:
//     vector<vector<int>> Paths(Node* root) {
        
//         vector<vector<int>> ans;
//         vector<int> result;
        
//         solve(root,ans,result);
        
//         return ans;
        
//     }
// };


////PRINT ROOT TO NODE PATH IN A BINARY TREE///////////////////
// class Solution {
// public:
//     // Function to find the path from the
//     // root to a given node with value 'x'
//     bool getPath(TreeNode* root, vector<int>& arr, int x) {
//         // Base case: If the current
//         // node is null, return false
//         if (!root) {
//             return false;
//         }

//         // Add the current node's
//         // value to the path vector
//         arr.push_back(root->val);

//         // If the current node's value is equal
//         // to the target value 'x', return true
//         if (root->val == x) {
//             return true;
//         }

//         // Recursively search for the target value
//         // 'x' in the left and right subtrees
//         if (getPath(root->left, arr, x)
//             || getPath(root->right, arr, x)) {
//             return true;
//         }

//         // If the target value 'x' is not found
//         // in the current path, backtrack
//         arr.pop_back();
//         return false;
//     }

//     // Function to find and return the path from
//     // the root to a given node with value 'B'
//     vector<int> solve(TreeNode* A, int B) {
//         // Initialize an empty
//         // vector to store the path
//         vector<int> arr;

//         // If the root node is null,
//         // return the empty path vector
//         if (A == NULL) {
//             return arr;
//         }

//         // Call the getPath function to find
//         // the path to the node with value 'B'
//         getPath(A, arr, B);

//         // Return the path vector
//         return arr;
//     }
// };


//////////////maximuym width of bt//////////
// class Solution {
// public:
//     typedef unsigned long long ll;
//     int widthOfBinaryTree(TreeNode* root) {
//         if(!root)   
//             return 0;
//         queue<pair<TreeNode*, ll>> que;
//         que.push({root, 0});
//         ll maxWidth = 0;
        
//         while(!que.empty()) {
//             int n = que.size();
//             ll f = que.front().second;
//             ll l = que.back().second;
//             maxWidth = max(maxWidth, l-f+1);
            
//             while(n--) {
//                 TreeNode* curr = que.front().first;
//                 ll d          = que.front().second;
//                 que.pop();
//                 if(curr->left) {
//                     que.push({curr->left, 2*d+1});
//                 }
//                 if(curr->right) {
//                     que.push({curr->right, 2*d+2});
//                 }
//             }
//         }
//         return maxWidth;
//     }
// };


//////////////LEVEL ORDER TRAVERSAL///////////////////////
// class Solution {
// public:
//     vector<vector<int>> levelOrder(TreeNode* root) {
//          vector<vector<int>> ans; 
//         if (root == nullptr) {
//             // If the tree is empty,
//             // return an empty vector
//             return ans; 
//         }
        
//         // Create a queue to store nodes
//         // for level-order traversal
//         queue<TreeNode*> q; 
//         // Push the root node to the queue
//         q.push(root); 

//         while (!q.empty()) {
//             // Get the size of the current level
//             int size = q.size(); 
//             // Create a vector to store
//             // nodes at the current level
//             vector<int> level; 

//             for (int i = 0; i < size; i++) {
//                 // Get the front node in the queue
//                 TreeNode* node = q.front(); 
//                 // Remove the front node from the queue
//                 q.pop(); 
//                 // Store the node value
//                 // in the current level vector
//                 level.push_back(node->val); 

//                 // Enqueue the child nodes if they exist
//                 if (node->left != nullptr) {
//                     q.push(node->left);
//                 }
//                 if (node->right != nullptr) {
//                     q.push(node->right);
//                 }
//             }
//             // Store the current level
//             // in the answer vector
//             ans.push_back(level); 
//         }
//         // Return the level-order
//         // traversal of the tree
//         return ans; 
    
//     }
// };


///////////////MAX HEIGHT OF TREE (DEPTH)
// class Solution {
// public:
//     int maxDepth(TreeNode* root) {
//         if(root ==NULL){
//             return 0;

//         }
//        int leftHeight = maxDepth(root->left) ;
//        int rightHeight = maxDepth(root->right) ;
//        int Height = max(leftHeight, rightHeight) +1;
//        return Height; 
//     }
// };


//////////////SAME TREES////////////
// class Solution {
// public:
//     bool isSameTree(TreeNode* p, TreeNode* q) {
//          if(p == NULL && q == NULL){
//             return true;
//         }
//         // If only one of the nodes is
//         // NULL, they are not identical
//         if( p== NULL || q==NULL){
//             return false;
//         }
//         // Check if the current nodes
//         // have the same data value
//         // and recursively check their
//         // left and right subtrees
//         return ((p->val == q->val)
//             && isSameTree(p->left, q->left)
//                 && isSameTree(p->right, q->right));
//     }
// };


//check if tree is balanced or not//////////////
// class Solution {
// public:
//     bool isBalanced(TreeNode* root) {
//            return Height(root) != -1;
//     }

//     // Recursive function to calculate
//     // the height of the tree
//     int Height(TreeNode* root) {
//         // Base case: if the current node is NULL,
//         // return 0 (height of an empty tree)
//         if (root == NULL) return 0;

//         // Recursively calculate the
//         // height of the left subtree
//         int leftHeight = Height(root->left);

//         // If the left subtree is unbalanced,
//         // propagate the unbalance status
//         if (leftHeight == -1) 
//             return -1;

//         // Recursively calculate the
//         // height of the right subtree
//         int rightHeight = Height(root->right);

//         // If the right subtree is unbalanced,
//         // propagate the unbalance status
//         if (rightHeight == -1) 
//             return -1;

//         // Check if the difference in height between
//         // left and right subtrees is greater than 1
//         // If it's greater, the tree is unbalanced,
//         // return -1 to propagate the unbalance status
//         if (abs(leftHeight - rightHeight) > 1)  
//             return -1;

//         // Return the maximum height of left and
//         // right subtrees, adding 1 for the current node
//         return max(leftHeight, rightHeight) + 1;
//     }
// };


//////ZIG ZAG TRAVERSAL IN TREE/////////////
// class Solution {
// public:
//     vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
//         vector<vector<int>> result;

//         // Check if the root is NULL,
//         // return an empty result
//         if (root == NULL) {
//             return result;
//         }

//         // Queue to perform
//         // level order traversal
//         queue<TreeNode*> nodesQueue;
//         nodesQueue.push(root);

//         // Flag to determine the direction of
//         // traversal (left to right or right to left)
//         bool leftToRight = true;

//         // Continue traversal until
//         // the queue is empty
//         while (!nodesQueue.empty()) {
//             // Get the number of nodes
//             // at the current level
//             int size = nodesQueue.size();

//             // Vector to store the values
//             // of nodes at the current level
//             vector<int> row(size);

//             // Traverse nodes at
//             // the current level
//             for (int i = 0; i < size; i++) {
//                 // Get the front node
//                 // from the queue
//                 TreeNode* node = nodesQueue.front();
//                 nodesQueue.pop();

//                 // Determine the index to insert the node's
//                 // value based on the traversal direction
//                 int index = leftToRight ? i : (size - 1 - i);

//                 // Insert the node's value at
//                 // the determined index
//                 row[index] = node->val;

//                 // Enqueue the left and right
//                 // children if they exist
//                 if (node->left) {
//                     nodesQueue.push(node->left);
//                 }
//                 if (node->right) {
//                     nodesQueue.push(node->right);
//                 }
//             }

//             // Switch the traversal
//             // direction for the next level
//             leftToRight = !leftToRight;

//             // Add the current level's
//             // values to the result vector
//             result.push_back(row);
//         }

//         // Return the final result of
//         // zigzag level order traversal
//         return result;
//     }
// };

//////construct binary tress from inorder and preorder///////////////
// class Solution {
// public:
//     TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
//          // Create a map to store indices
//         // of elements in the inorder traversal
//         map<int, int> inMap;
        
//         // Populate the map with indices
//         // of elements in the inorder traversal
//         for(int i = 0; i < inorder.size(); i++){
//             inMap[inorder[i]] = i;
//         }
        
//         // Call the private helper function
//         // to recursively build the tree
//         TreeNode* root = buildTree(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1, inMap);
        
//         return root;
//     }

// private:
//     // Recursive helper function to build the tree
//     TreeNode* buildTree(vector<int>& preorder, int preStart, int preEnd, 
//             vector<int>& inorder, int inStart, int inEnd, map<int, int>& inMap){
//                 // Base case: If the start indices 
//                 // exceed the end indices, return NULL
//                 if(preStart > preEnd || inStart > inEnd){
//                     return NULL;
//                 }
                
//                 // Create a new TreeNode with value
//                 // at the current preorder index
//                 TreeNode* root = new TreeNode(preorder[preStart]);
                
//                 // Find the index of the current root
//                 // value in the inorder traversal
//                 int inRoot = inMap[root->val];
                
//                 // Calculate the number of
//                 // elements in the left subtree
//                 int numsLeft = inRoot - inStart;
                
//                 // Recursively build the left subtree
//                 root->left = buildTree(preorder, preStart + 1, preStart + numsLeft, 
//                                 inorder, inStart, inRoot - 1, inMap);
                
//                 // Recursively build the right subtree
//                 root->right = buildTree(preorder, preStart + numsLeft + 1, preEnd, 
//                                 inorder, inRoot + 1, inEnd, inMap);
                
//                 // Return the current root node
//                 return root;
//     }
// };


//////////binary tree from inorder and postorder///////////////////
// class Solution {
// public:
//     TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
//         if(inorder.size()!=postorder.size())
//         return NULL;
//         map<int,int>mp;
//         for(int i=0;i<inorder.size();i++)
//         mp[inorder[i]] = i;
//         return buildTreepostin(inorder,0,inorder.size()-1,postorder,0,postorder.size()-1,mp);
//     }
//     TreeNode* buildTreepostin(vector<int>&inorder,int is,int ie,vector<int>&postorder,int ps,int pe,map<int,int>&mp){
//         if(ps>pe || is>ie)
//         return NULL;
//         TreeNode* root=new TreeNode(postorder[pe]);
//         int inRoot =mp[postorder[pe]];
//         int numsLeft=inRoot - is;
//         root->left=buildTreepostin(inorder,is,inRoot-1,postorder,ps,ps+numsLeft-1,mp);
//         root->right=buildTreepostin(inorder,inRoot+1,ie,postorder,ps+numsLeft,pe-1,mp);
//         return root;
        
//     }
// };

//////////////symmetric tree///////////////////
// class Solution {
// public:
    
//     bool check(TreeNode* l, TreeNode* r) {
//         if(l == NULL && r == NULL)
//             return true;
//         if(l == NULL || r == NULL)
//             return false;
        
//         if(l->val == r->val && check(l->left, r->right) && check(l->right, r->left))
//             return true;
        
//         return false;
//     }
    
//     bool isSymmetric(TreeNode* root) {
//         if(!root)
//             return true;
        
//         return check(root->left, root->right);
//     }
// };

/////////////flatten a binary tree to linked list////////////////
// class Solution {
// public:
//     void flatten(TreeNode* root) {
//          // Initialize a pointer
//         // 'curr' to the root of the tree
//         TreeNode* curr = root;

//         // Iterate until 'curr'
//         // becomes NULL
//         while (curr) {
//             // Check if the current
//             // node has a left child
//             if (curr->left) {
//                 // If yes, find the rightmost
//                 // node in the left subtree
//                 TreeNode* pre = curr->left;
//                 while (pre->right) {
//                     pre = pre->right;
//                 }

//                 // Connect the rightmost node in
//                 // the left subtree to the current
//                //  node's right child
//                 pre->right = curr->right;

//                 // Move the entire left subtree to the
//                 // right child of the current node
//                 curr->right = curr->left;

//                 // Set the left child of
//                 // the current node to NULL
//                 curr->left = NULL;
//             }

//             // Move to the next node
//             // on the right side
//             curr = curr->right;
//         }
//     }
// };


/////////////Cildren sum in a Binary Tree////////////////
// class Solution{
//     public:
//     void solve(Node *root, int &ans){
//         if(ans == 0)
//             return;
//         if(!root)   
//             return;
//         if(!root->left && !root->right)
//             return;
        
//         int left, right;
//         left = right = 0;
        
//         if(root->left)  left = root->left->data;
//         if(root->right) right= root->right->data;
        
//         if(root->data != left+right){
//             ans = 0;
//             return;
//         }
        
//         solve(root->left, ans);
//         solve(root->right, ans);
        
//     }
//     int isSumProperty(Node *root)
//     {
//      // Add your code here
//         int ans = 1;
//         solve(root, ans);
//         return ans;
//     }
// };


/////////Children sum (modified you can do +1 to everynode to validate the property)/////////////////////////
// class Solution {
// public:
//     // Function to change the values of the nodes
//     // based on the sum of its children's values.
//     void changeTree(TreeNode* root) {
//         // Base case: If the current node
//         // is NULL, return and do nothing.
//         if (root == NULL) {
//             return;
//         }

//         // Calculate the sum of the values of
//         // the left and right children, if they exist.
//         int child = 0;
//         if (root->left) {
//             child += root->left->val;
//         }
//         if (root->right) {
//             child += root->right->val;
//         }

//         // Compare the sum of children with
//         // the current node's value and update
//         if (child >= root->val) {
//             root->val = child;
//         } else {
//             // If the sum is smaller, update the
//             // child with the current node's value.
//             if (root->left) {
//                 root->left->val = root->val;
//             } else if (root->right) {
//                 root->right->val = root->val;
//             }
//         }

//         // Recursively call the function
//         // on the left and right children.
//         changeTree(root->left);
//         changeTree(root->right);

//         // Calculate the total sum of the
//         // values of the left and right
//         // children, if they exist.
//         int tot = 0;
//         if (root->left) {
//             tot += root->left->val;
//         }
//         if (root->right) {
//             tot += root->right->val;
//         }

//         // If either left or right child
//         // exists, update the current node's
//         // value with the total sum.
//         if (root->left or root->right) {
//             root->val = tot;
//         }
//     }
// };


/////////SEARCH IN A BINARY SEARCH TREE//////
// class Solution {
// public:
//     TreeNode* searchBST(TreeNode* root, int val) {
//         while(root!=NULL && root->val !=val){
//             root=val <root->val ? root->left:root->right;

//         }
//         return root;
        
//     }
// };

///////construct binary tree from  preodrder traversal//
// class Solution {
// public:
//     TreeNode* bstFromPreorder(vector<int>& preorder) {
//         int i = 0;
//         return build(preorder, i, INT_MAX);
//     }

//     TreeNode* build(vector<int>& preorder, int& i, int bound) {
//         if (i == preorder.size() || preorder[i] > bound)
//             return NULL;
//         TreeNode* root = new TreeNode(preorder[i++]);
//         root->left = build(preorder, i, root->val);
//         root->right = build(preorder, i, bound);
//         return root;
//     }
// };


//////VALIDATE BINARY SEARCH TRESS OR BINARY TREE////////////////////
// class Solution {
// public:
//     bool isValidBST(TreeNode* root) {
//         return isValidBST(root, LONG_MIN, LONG_MAX);
//     }


//     bool isValidBST(TreeNode* root, long minVal, long maxVal) {
//         if (root == NULL) return true;
//         if (root->val >= maxVal || root->val <= minVal) return false;
//         return isValidBST(root->left, minVal, root->val) &&
//                isValidBST(root->right, root->val, maxVal);
//     }
// };


///////lca of BST///////////////////
// class Solution {
// public:
//     TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
//         if(root==NULL)
//             return NULL;
       
//        int curr=root->val;
//        if(curr< p->val && curr < q->val){
//         return lowestCommonAncestor(root->right,p,q);
//        }
//          if(curr > p->val && curr > q->val){
//             return lowestCommonAncestor(root->left,p,q);
//        }
//        return root;
//     }
// };

///////////////////predecor and succesor of bst///////////////////
// class Solution
// {
//     public:
//       Node* inorderPredecessor(Node* root, int key, Node*& pre){
//         pre=nullptr;
//         while(root!=nullptr){
//             if(root->key >= key){
//                 root=root->left;
//             } else{
//                 pre=root;
//                 root=root->right;
//             }
//         }
//         return pre;
//     }
//     Node* inorderSuccessor(Node* root, int key, Node* & suc){
//         suc=nullptr;
//         while(root!=nullptr){
//             if(key>=root->key){
//                 root=root->right;
//             }else{
//                 suc=root;
//                 root=root->left;
//             }
//         }
//         return suc;
//     }
//     void findPreSuc(Node* root, Node*& pre, Node*& suc, int key)
//     {
//         // Your code goes here
//         inorderPredecessor(root, key, pre);
//         inorderSuccessor(root, key, suc);
        
//     }

// };

/////floor in a binary search tree/////////////////

// int floorInBST(TreeNode<int> * root, int X)
// {
//     int floor=-1;
//     while(root){
//         if(root->val==X){
//             floor=root->val;
//             return floor;
//         }
//         if(X>root->val){
//             floor=root->val;
//             root=root->right;
//         }
//         else{
//             root=root->left;
//         }
//     }
//     return floor;
// }


/////////CEIL IN A BST////////////
// int findCeil(BinaryTreeNode<int> *node, int x){
//     int ceil=-1;
//     while(node){
//         if(node->data==x){
//             ceil=node->data;
//             return ceil;
//         }
//         if(x>node->data){
//             node=node->right;
//         }
//         else{
//              ceil=node->data;
//             node=node->left;
//         }
//     }
//     return ceil;
// }


/////////Kth smallest element in a bst/////////////////
// class Solution {
// public:
    
//   // traversal to find Kth smallest element
//     void inorder(TreeNode* node, int& counter, int k, int& kSmallest) {
//         if (!node || counter >= k) return;

//         // Traverse left subtree
//         inorder(node->left, counter, k, kSmallest);

//         // Increment counter after visiting left subtree
//         counter++;

//         // Check if current node is the Kth smallest
//         if (counter == k) {
//             kSmallest = node->val;
//             return;
//         }

//         // Traverse right subtree if
//         // Kth smallest is not found yet
//         inorder(node->right, counter, k, kSmallest);
//     }

// public:
//     int kthSmallest(TreeNode* root, int &k) {
//         int kSmallest = INT_MIN;
//         // Counter to track visited nodes
//         int counter = 0; 

//         // Find Kth smallest element
//         // (perform inorder traversal)
//         inorder(root, counter, k, kSmallest);
        
//         // Reset counter for Kth largest element
//         counter = 0; 

//         return kSmallest;
//     }
//     };


////////KTH LARGEST ELEMENT IN A BST///////////////////
// class Solution {
//   public:
//      int solve(Node* root, int& k){
//         if (!root) {
//             return -1;
//         }
        
        
//         int right = solve(root->right, k);
//         if (right != -1) {
//             return right;
//         }
        
//         k--;
//         if (k == 0) {
//             return root->data;
//         }
        
       
        
//         return solve(root->left, k);
//     }
//     int kthLargest(Node *root, int k) {
//         return solve(root,k);
//     }
// };


//////////KTH SMALLEST ELEMENT////////////////////////
// class Solution {
// public:
//     int kthSmallest(TreeNode* root, int &k) {
//         if(root == NULL){
//             return -1;
//         }
//         int leftAns = kthSmallest(root->left, k);
//         if(leftAns != -1){
//             return leftAns;
//         }
//         k--;
//         if(k == 0){
//             return root->val;
//         }
//         int rightAns = kthSmallest(root->right, k);
//         return rightAns;
        
//     }
// };

//////bst iterator//////////////
// class BSTIterator {

// private:stack<TreeNode *> mystack;
// public:
//     BSTIterator(TreeNode* root) {
//         pushall(root);
//     }
//      bool hasNext() {
//         return !mystack.empty();
//      }
//     int next() {
//         TreeNode* tempnode=mystack.top();
//         mystack.pop();
//         pushall(tempnode->right);
//         return tempnode->val;
//     }
//     private:
//     void pushall(TreeNode* root){
//         for(;root!=NULL;mystack.push(root),root=root->left);
   
//     }
// };


///////////////TWO SUM IV/////////////////////////////
// class Solution {
// public:
// void storeInorder(TreeNode* root, vector<int> & inorder){
//     //basecase
//     if(root== NULL){
//         return;
//     }
//     //lnr
//     storeInorder(root->left, inorder);
//     inorder.push_back(root->val);
//     storeInorder(root->right, inorder);
// }
//     bool findTarget(TreeNode* root, int k) {
//         vector<int> inorder;
//         storeInorder(root, inorder);

//         int start = 0;
//         int end = inorder.size()-1;
//         while(start<end){
//             int sum = inorder[start] + inorder[end];
//             if (sum == k){
//                 return true;
//             }
//             else if(sum > k){
//                 end--;
//             }
//             else if(sum < k){
//                 start++;
//             }
//         }
//         return false;
//     }
// };


////////maximum sum bst in binary tree//////////
// struct Node{
//     int sum, maxnode, minnode;
//     Node(int sum, int maxnode, int minnode){
//         this->sum = sum;
//         this->maxnode = maxnode;
//         this->minnode = minnode;
//     }
// };C

// class Solution {
// public:
//         Node findLargestBST(TreeNode* root, int &ans){
//         if(root->left == NULL && root->right == NULL){
//             ans = max(ans,root->val);
//             return Node(root->val,root->val,root->val);
//         } 
//         if(root->left == NULL){
//             Node right = findLargestBST(root->right,ans);
//             if(root->val <right.minnode){
//                 ans = max(ans,root->val+right.sum);
//                 return Node(root->val+right.sum,right.maxnode,root->val);
//             }
//             return Node(right.sum,INT_MAX,INT_MIN);
//         } 
//         if(root->right == NULL){
//             Node left =  findLargestBST(root->left,ans);
//             if(root->val > left.maxnode){
//                 ans = max(ans,root->val+left.sum);
//                 return Node(root->val+left.sum,root->val,left.minnode);
//             }
//             return Node(left.sum,INT_MAX,INT_MIN);
//         } 

//         Node left = findLargestBST(root->left,ans);
//         Node right = findLargestBST(root->right,ans);
//         if(left.maxnode<root->val && root->val<right.minnode){
//             ans = max(ans, left.sum+root->val+right.sum);
//             return Node(left.sum + root->val + right.sum,
//                         right.maxnode,
//                         left.minnode);
//         }
//         return Node(max(left.sum,right.sum),INT_MAX,INT_MIN);
//     }
//     int maxSumBST(TreeNode* root) {
//         if(root == NULL ) return 0;
//         int ans = 0;
//         findLargestBST(root,ans);     
//         return ans;
//     }
// };


///////largest bst in binary tree(count)/////////////////
// class NodeValue{
//     public:
   
//     int maxNode, minNode , maxSize;
    
//     NodeValue(int minNode,int maxNode,int maxSize){
//         this->maxNode=maxNode;
//         this->minNode=minNode;
//         this->maxSize=maxSize;
//     }
// };
// class Solution{
//     private:
//     NodeValue lbsh(Node* root){
//         if(!root){
//             return NodeValue(INT_MAX,INT_MIN,0);
//         }
//             auto left=lbsh(root->left);
//             auto right=lbsh(root->right);
//             if(left.maxNode <root->data && root->data <right.minNode){
//                 return NodeValue(min(root->data,left.minNode),max(root->data,right.maxNode),
//                 left.maxSize+right.maxSize+1);
//             }
//             return NodeValue(INT_MIN,INT_MAX,max(left.maxSize,right.maxSize));
//         }
        
//     public:
//     int largestBst(Node *root)
//     {
//     return lbsh(root).maxSize;
//     }
// };


///////////serialize and desirailize//////////////
// class Codec {
// public:

//       // Encodes the tree into a single string
//     string serialize(TreeNode* root) {
//         // Check if the tree is empty
//         if (!root) {
//             return "";
//         }

//         // Initialize an empty string
//         // to store the serialized data
//         string s = "";
//         // Use a queue for
//         // level-order traversal
//         queue<TreeNode*> q;
//         // Start with the root node
//         q.push(root);

//         // Perform level-order traversal
//         while (!q.empty()) {
//             // Get the front node in the queue
//             TreeNode* curNode = q.front();
//             q.pop();

//             // Check if the current node is
//             // null and append "#" to the string
//             if (curNode == nullptr) {
//                 s += "#,";
//             } else {
//                 // Append the value of the
//                 // current node to the string
//                 s += to_string(curNode->val) + ",";
//                 // Push the left and right children
//                 // to the queue for further traversal
//                 q.push(curNode->left);
//                 q.push(curNode->right);
//             }
//         }

//         // Return the
//         // serialized string
//         return s;
//     }

//     // Decode the encoded
//     // data to a tree
//     TreeNode* deserialize(string data) {
//         // Check if the
//         // serialized data is empty
//         if (data.empty()) {
//             return nullptr;
//         }

//         // Use a stringstream to
//         // tokenize the serialized data
//         stringstream s(data);
//         string str;
//         // Read the root value
//         // from the serialized data
//         getline(s, str, ',');
//         TreeNode* root = new TreeNode(stoi(str));

//         // Use a queue for 
//         // level-order traversal
//         queue<TreeNode*> q;
//         // Start with the root node
//         q.push(root);

//         // Perform level-order traversal
//         // to reconstruct the tree
//         while (!q.empty()) {
//             // Get the front node in the queue
//             TreeNode* node = q.front();
//             q.pop();

//             // Read the value of the left
//             // child from the serialized data
//             getline(s, str, ',');
//             // If the value is not "#", create a new
//             // left child and push it to the queue
//             if (str != "#") {
//                 TreeNode* leftNode = new TreeNode(stoi(str));
//                 node->left = leftNode;
//                 q.push(leftNode);
//             }

//             // Read the value of the right child
//             // from the serialized data
//             getline(s, str, ',');
//             // If the value is not "#", create a
//             // new right child and push it to the queue
//             if (str != "#") {
//                 TreeNode* rightNode = new TreeNode(stoi(str));
//                 node->right = rightNode;
//                 q.push(rightNode);
//             }
//         }

//         // Return the reconstructed
//         // root of the tree
//         return root;
//     }
// };


//////////INSERT A GIVEN NODE IN A BINARY TREE///////////////
// class Solution {
// public:
//     TreeNode* insertIntoBST(TreeNode* root, int val) {
//         if(root==NULL) return new TreeNode(val);
//         TreeNode* curr =root;
//         while(true){
//             if(curr->val <=val){
//                 if(curr->right!=NULL)
//                 curr=curr->right;
//                 else{
//                     curr->right=new TreeNode(val);
//                     break;
//                 }
//             }
//             else{
//                     if(curr->left!=NULL)
//                     curr=curr->left;
//                     else{
//                         curr->left=new TreeNode(val);
//                         break;
//                     }
//                 }
//             }
//             return root;
//     }
// };

//////////binary search tree ////////////
// class Solution {
//   public:
//     bool isBSTTraversal(vector<int>& arr) {
//       for(int i = 1; i < arr.size(); i++){
//             if(arr[i-1] >= arr[i]) return false;
//         }
//         return true;
//     }
// };

////////////MINIMUM ELEMENTS IN A BST/////////
// class Solution {
//   public:
//     int minValue(Node* root) {
//          if(root==NULL) return -1;
//         // code here
//         Node *temp = root;
//         while(temp->left!=NULL){
//             temp = temp->left;
//         }
//         return temp->data;
//     }

// };


////////SUBTREE OF ANOTHER TREE//////////
// class Solution {
// public:
// bool ans = false;
// bool match(TreeNode * root, TreeNode *subRoot) {
//   if (root && subRoot) {
//     bool a = match(root -> left, subRoot -> left);
//     bool b = match(root -> right, subRoot -> right);

//     if ((root -> val == subRoot -> val) && a && b)
//       return true;
//     else
//       return false;
//   } else if (!root && !subRoot) return true;
//   else return false;
// }
// void inorder(TreeNode * root, TreeNode * subRoot) {
//   if (root) {
//     inorder(root -> left, subRoot);
//     bool x = match(root, subRoot);
//     if (x) ans = 1;
//     inorder(root -> right, subRoot);
//   }
// }

// bool isSubtree(TreeNode * root, TreeNode * subRoot) {
//   inorder(root, subRoot);
//   return ans;
//     }
// };


/////////////////DELETE A NODE IN A bst///////////////
// class Solution {
// public:
//     TreeNode* deleteNode(TreeNode* root, int key) {
//         if(root==NULL){
//             return NULL;
//         }
//         if(root->val==key){
//             return helper(root);
//         }
//         TreeNode *dummy=root;
//         while(root!=NULL){
//             if(root->val > key){
//             if(root->left!=NULL && root->left->val==key){
//                 root->left=helper(root->left);
//                 break;
//             }else{
//                 root=root->left;
//                 }
//                 }
//                 else{
//                     if(root->right!=NULL &&root->right->val==key){
//                         root->right=helper(root->right);
//                         break;
//                         }
//                         else{
//                             root=root->right;
//                         }
//                         }
//                         }
//                         return dummy;
// }
//                         TreeNode *helper(TreeNode * root){
//                             if(root->left==NULL){
//                                 return root->right;
//                             }
//                             else if(root->right==NULL){
//                                 return root->left;
//                             }
//                             TreeNode *rightChild=root->right;
//                             TreeNode *LastRight=findLastRight(root->left);
//                             LastRight->right=rightChild;
//                             return root->left;
//                         }
//                         TreeNode *findLastRight(TreeNode*root){
//                             if(root->right==NULL){
//                                 return root;
//                                 }
//                                 return findLastRight(root->right);

//                             }
//                         };
                

                ////////////RECOVER BINARY SEARCH TREES/////////////////
//                 class Solution {
//     private:
//     TreeNode* middle;
//      TreeNode* prev;
//       TreeNode* first;
//        TreeNode* last;
//        private:
//        void Inorder(TreeNode* root){
//         if(root==NULL)
//         return;
//         Inorder(root->left);
//         if(prev!=NULL && (root->val < prev->val)){
//             if(first==NULL){
//                 first=prev;
//                 middle=root;
//             }
//             else
//             last=root;
//             }
//             prev=root;
//             Inorder(root->right);
//         }
        
// public:
//     void recoverTree(TreeNode* root) {
//         first=middle=last=NULL;
//         prev=new TreeNode(INT_MIN);
//         Inorder(root);
//         if(first && last)
//         swap(first->val,last->val);
//         else if(first && middle)
//         swap(first->val, middle->val);
//     }
// };

////////////populating the next right pointer////////////////////////////////////
// class Solution {
// public:
//     Node* connect(Node* root) {
//         if(root==NULL ||root->left==NULL||root->right==NULL)
//         return root;
//         root->left->next=root->right;
//         if(root->next!=NULL){
//             root->right->next=root->next->left;
//         }
//         connect(root->left);
//         connect(root->right);
//         return root;
//     }
// };



////////RANGE SUM OF BST////////////////////
// class Solution {
// public:
//     int rangeSumBST(TreeNode* root, int low, int high) {
//         if(!root)
//             return 0;
        
//         //Within Range
//         if(root->val >= low && root->val <= high) {
//             return root->val + rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high);
//         }
        
//         //When outside the range (Less than low) - Go right
//         if(root->val < low)
//             return rangeSumBST(root->right, low, high);

//         //When outside the range (Greater than high) - Go left
//         return rangeSumBST(root->left, low, high);
//     }
// };


//////MINIMUM ABSOLUTE DIFFERENCE BST//////////////////
// class Solution {
// public:
    
//     int minDiff = INT_MAX;
    
//     void inOrder(TreeNode* root, TreeNode* &prev) {
        
//         if(root == NULL)
//             return;
        
//         inOrder(root->left, prev);
        
//         if(prev != NULL) {
//             minDiff = min(minDiff, root->val - prev->val);
//         }
        
//         prev = root;
        
//         inOrder(root->right, prev);
        
//     }
    
//     int getMinimumDifference(TreeNode* root) {
//         TreeNode* prev = NULL;
//         inOrder(root, prev);
//         return minDiff;
//     }
// };


//////COUNT NO OF GOOD NODES///////////////////
// class Solution {
// public:
//         void countgoodnodes(TreeNode* root,int &count,int max){
//             if(!root)
//             return;
//             if(root->val >=max){
//                 count++;
//                 max=root->val;
//             }
//             countgoodnodes(root->left,count,max);
//              countgoodnodes(root->right,count,max);
//         }

//         int goodNodes(TreeNode* root) {
//         int count=0;
//         if(!root)
//         return count;
//          countgoodnodes(root,count,root->val);
//         return count; 
//     }
// };

/////////////UNIQUE BINARY TREE REQUIREMENTS/////////////

// class Solution
// {
// public:
//     bool isPossible(int a,int b)
//     {
//         //code here
//         if((a==2 || b==2) &&a!=b) return 1;
//         else return 0;
//     }
// };
 // for unique binary tree we should have inorder and one among post or pre order
//so either one of a or b shd be inorder (a==2 || b==2) && other should be other than inorder a!=b 


/////print all the nodes at a distance of K in Binary tree//////////////
// class Solution{
// void markParents (TreeNode* root, unordered_map<TreeNode*, TreeNode*> &parent_track, TreeNode* target) {
// queue<TreeNode*>queue;
// queue.push(root);
// while(!queue.empty()) {
// TreeNode* current =queue.front();
// queue.pop();
// if(current->left){

// parent_track[current->left]= current;
// queue.push(current->left);
// }
// if(current->right) {
// parent_track[current->right]=current;
// queue.push(current->right);
// }
// }
// }
// public:
// vector<int> distanceK (TreeNode* root, TreeNode* target, int k) {
// unordered_map<TreeNode*, TreeNode*>parent_track; // node->parent
// markParents(root, parent_track, target);
// unordered_map <TreeNode*, bool> visited;
// queue<TreeNode*> queue;
// queue.push(target);
// visited[target] = true;
// int curr_level = 0;
// while(!queue.empty()) { //Second BFS to ga upto K level fros target node and using our hashtable info/
// int size =queue.size();
// if(curr_level++==k) break;
// for(int i=0; i<size; i++) {
// TreeNode* current = queue.front(); queue.pop();

// if(current->left && !visited[current->left]){
//  queue.push(current->left);
// visited[current->left] =true;
// }

//  if(current->right && !visited[current->right]) {
//     queue.push(current->right);
// visited[current->right]=true;
//  }
//  if(parent_track[current] && !visited[parent_track[current]]) {
// queue.push(parent_track[current]); 
//  visited[parent_track [current]] = true;
//  }
// }
// }

// vector<int> result;
// while(!queue.empty()) {
// TreeNode* current= queue.front(); queue.pop();
// result.push_back(current->val);
// }
// return result;
// }
// };



//////////////boundary traversal of binary tree///////////////////////////
//  bool isLeaf(TreeNode<int>* root) {
//         return !root->left && !root->right;
//     }

//     // Function to add the
//     // left boundary of the tree
//     void addLeftBoundary(TreeNode<int>* root, vector<int>& res) {
//         TreeNode<int>* curr = root->left;
//         while (curr) {
//             // If the current node is not a leaf,
//             // add its value to the result
//             if (!isLeaf(curr)) {
//                 res.push_back(curr->data);
//             }
//             // Move to the left child if it exists,
//             // otherwise move to the right child
//             if (curr->left) {
//                 curr = curr->left;
//             } else {
//                 curr = curr->right;
//             }
//         }
//     }

//     // Function to add the
//     // right boundary of the tree
//     void addRightBoundary(TreeNode<int>* root, vector<int>& res) {
//        TreeNode<int>* curr = root->right;
//         vector<int> temp;
//         while (curr) {
//             // If the current node is not a leaf,
//             // add its value to a temporary vector
//             if (!isLeaf(curr)) {
//                 temp.push_back(curr->data);
//             }
//             // Move to the right child if it exists,
//             // otherwise move to the left child
//             if (curr->right) {
//                 curr = curr->right;
//             } else {
//                 curr = curr->left;
//             }
//         }
//         // Reverse and add the values from
//         // the temporary vector to the result
//         for (int i = temp.size() - 1; i >= 0; --i) {
//             res.push_back(temp[i]);
//         }
//     }

//     // Function to add the
//     // leaves of the tree
//     void addLeaves(TreeNode<int>* root, vector<int>& res) {
//         // If the current node is a
//         // leaf, add its value to the result
//         if (isLeaf(root)) {
//             res.push_back(root->data);
//             return;
//         }
//         // Recursively add leaves of
//         // the left and right subtrees
//         if (root->left) {
//             addLeaves(root->left, res);
//         }
//         if (root->right) {
//             addLeaves(root->right, res);
//         }
//     }

//     // Main function to perform the
//     // boundary traversal of the binary tree
//    vector<int> traverseBoundary(TreeNode<int> *root) {
//         vector<int> res;
//         if (!root) {
//             return res;
//         }
//         // If the root is not a leaf,
//         // add its value to the result
//         if (!isLeaf(root)) {
//             res.push_back(root->data);
//         }

//         // Add the left boundary, leaves,
//         // and right boundary in order
//         addLeftBoundary(root, res);
//         addLeaves(root, res);
//         addRightBoundary(root, res);

//         return res;
//     }


///////binary tree pruning ///////////////////
// class Solution {
// public:
//     TreeNode* pruneTree(TreeNode* root) {
//         if(!root)
//             return NULL;
        
//         root->left  = pruneTree(root->left);
//         root->right = pruneTree(root->right);
        
//         if(!root->left && !root->right && root->val == 0)
//             return NULL;
        
//         return root;
//     }
// };

///////////SUM ROOT TO LEAF NODES/////////////////
// class Solution {
// public:
    
//     int find(TreeNode* root, int curr) {
        
//         if(!root)
//             return 0;
        
//         curr = curr*10 + root->val;
        
//         if(root->left == NULL && root->right == NULL) {
//             return curr;
//         }
        
//         int left_num  = find(root->left, curr);
//         int right_num = find(root->right, curr);
        
//         return left_num + right_num;
//     }
    
//     int sumNumbers(TreeNode* root) {
//         return find(root, 0);
//     }
// };

//////////convert sorted array to balanced bst///////////
// class Solution {
// public:
  

//     TreeNode* helper(vector<int>& nums, int start, int end) {
//         if (start > end) return nullptr;
//         int mid = start + (end - start) / 2;
//         TreeNode* root = new TreeNode(nums[mid]);
//         root->left = helper(nums, start, mid - 1);
//         root->right = helper(nums, mid + 1, end);
//         return root;
//     }
//       TreeNode* sortedArrayToBST(vector<int>& nums) {
//         return helper(nums, 0, nums.size() - 1);
//     }

// };


///////count total Nodes(complete tree nodes////////)
// class Solution {
// public:
// int findleftheight(TreeNode *node){
//         int hght=0;
//         while(node){
//             hght++;
//             node=node->left;
//         }
//         return hght;
//         }
//     int findrightheight(TreeNode *node){
//         int hght=0;
//         while(node){
//             hght++;
//             node=node->right;
//         }
//         return hght;
//    }
//     int countNodes(TreeNode* root) {
//         if(root==NULL){
//             return 0;
//         }
//         int lh=findleftheight(root);
//         int rh=findrightheight(root);
//         if(lh==rh)
//         return(1<<lh)-1;
//         return 1+countNodes(root->left)+countNodes(root->right);
//     }
    
    
// };


//////reverse order traversals///////////////
//  class Solution {
// public:
//     vector<vector<int>> levelOrderBottom(TreeNode* root) {
//         if(root == NULL)    return {};
//         vector<vector<int>> ans;
//         queue<TreeNode*> q;
//         q.push(root);

//         while(!q.empty()){
//             int size = q.size();
//             vector<int> s;

//             for(int i=0;i<size;i++){
//                 TreeNode* front = q.front();
//                 q.pop();

//                 s.push_back(front -> val);

//                 if(front -> left != NULL) q.push(front -> left);
//                 if(front -> right != NULL) q.push(front -> right);
//             }

//             ans.push_back(s);
//         }
//         // reverse(ans.begin(), ans.end());
//         //or//////////////////////////////
//         int i=0,j=ans.size()-1;
//         while(i<j){
//             swap(ans[i++], ans[j--]);
//         }
//         ////////////////or////////////
//         return ans;
//     }
// };



/////////Distance bwtween two nodes of tree//////////////
// TreeNode<int>* lca(TreeNode<int> *root, int node1, int node2)

// {

//     if(root==NULL)

//     {

//         return NULL;

//     }

//     if(root->val == node1 || root->val == node2)

//     {

//         return root;

//     }

//     TreeNode<int>*leftside = lca(root->left,node1,node2);

//     TreeNode<int>*rightside = lca(root->right,node1,node2);

//     if(leftside == NULL && rightside!=NULL)

//     {

//         return rightside;

//     }

//     else if(leftside!=NULL && rightside==NULL)

//     {

//         return leftside;

//     }

//     else if(leftside!=NULL && rightside!=NULL)

//     {

//         return root;

//     }

//     else

//     {

//         return NULL;

//     }

// }

// int finddistance(TreeNode<int>*root,int node1,int level)

// {

//     if(root==NULL)

//     {

//         return -1;

//     }

//     if(root->val == node1)

//     {

//         return level;

//     }

//     int left = finddistance(root->left,node1,level+1);

//     if(left == -1)

//     {

//         return finddistance(root->right,node1,level+1);

//     }

//     return left;

// }

// int findDistanceBetweenNodes(TreeNode<int> *root, int node1, int node2)

// {

//     // Write your code here.

//     //finding  lowest ancesator

//     TreeNode<int>* ances = lca(root,node1,node2);

//     //distance between ances and node1

//     int nod1 = finddistance(ances,node1,0);

//     //distance between ances and node2

//     int nod2 = finddistance(ances,node2,0);

//     int ans = nod1+nod2;

//     if(ans<0)

//     {

//         return -1;

//     }

//     return ans;

// }


///////////BINARY TREE PATHS///////////////
// class Solution {
//     private:
//     void findPaths(TreeNode* node, string path, vector<string>& paths) {
//         if (node==NULL) return;
//         if(!path.empty()) {
//             path += "->";
//         }
//         path+=to_string(node->val);
//         // If it's a leaf node, add the path to the list
//        if (node->left == NULL && node->right == NULL){
//             paths.push_back(path);
//         }else{
//             // Otherwise, continue to explore the left and right subtree
//             findPaths(node->left, path, paths);
//             findPaths(node->right, path, paths);
//         }
//     }
// public:
//     vector<string> binaryTreePaths(TreeNode* root) {
//         vector<string> paths;
//         if(root != NULL){
//             findPaths(root, "", paths);
//         }
//         return paths;
//     }
// };

///////////path sum 2//////////////
// class Solution {
// public:
//     void collectPaths(TreeNode* root, int curr, vector<int>& temp, vector<vector<int>>& result) {
//         if(!root)
//             return;
//         temp.push_back(root->val);
//         if(root->left == NULL && root->right == NULL && root->val == curr) {
//             result.push_back(temp);
//         }
        
//         collectPaths(root->left, curr-root->val, temp, result);
//         collectPaths(root->right, curr-root->val, temp, result);
//         temp.pop_back();
//     }
    
//     vector<vector<int>> pathSum(TreeNode* root, int sum) {
//         vector<vector<int>> result;
        
//         vector<int> temp;
//         collectPaths(root, sum, temp, result);
//         return result;
//     }
// };




/////////path sum 3//////////////////
// class Solution {
// public:
//     long long total = 0;

//     void pathSumUtil(TreeNode* root, long long sum, long long curr, map<long long, int>& mp) {
//         if (!root) return;

//         curr += root->val;

//         // Check if the difference exists in the map
//         if (mp.count(curr - sum)) {
//             total += mp[curr - sum];
//         }

//         // Add the current prefix sum to the map
//         mp[curr]++;

//         // Recur for left and right subtrees
//         pathSumUtil(root->left, sum, curr, mp);
//         pathSumUtil(root->right, sum, curr, mp);

//         // Backtrack by decrementing the count of the current prefix sum
//         mp[curr]--;
//     }

//     long long pathSum(TreeNode* root, long long sum) {
//         if (!root) return 0;

//         // Use long long for the map to handle large sums
//         map<long long, int> mp;
//         mp[0] = 1; // Base case for the sum starting from the root

//         pathSumUtil(root, sum, 0, mp);
//         return total;
//     }
// };



//////////////PATH SUM/////////////////////////////////
// class Solution {
// public:
//     bool pathSum(TreeNode* root, int sum, int curr) {
//         if(!root)
//             return false;
        
//         if(!root->left && !root->right)
//             return ((curr+root->val) == sum);
        
//         bool l = pathSum(root->left,  sum, curr+root->val);
//         bool r = pathSum(root->right, sum, curr+root->val);
//         return l||r;
//     }
//     bool hasPathSum(TreeNode* root, int sum) {
//         return pathSum(root, sum, 0);
//     }
// };

///////maximum time to burn a tree////////
// #include<bits/stdc++.h>
// int findMaxDistance(map<BinaryTreeNode<int>*, BinaryTreeNode<int>*> &mpp, Binary TreeNode<int>* target) {
// queue<BinaryTreeNode<int>*> q;
// q.push(target);
// map<BinaryTreeNode<int>*, int> vis;
// vis [target] = 1;
// int maxi = 0;
// while(!q.empty()) {
// int szq.size();
// int fl = 0;
// for(int i = 0;i<sz;i++) {
// auto node q.front();
// q.pop();
// if(node->left && !vis [node->left]) {
// fl = 1;
// vis [node->left] = 1;
// q.push(node->left);
// }
// if(node->right && !vis [node->right]) {
// fl = 1;
// vis [node->right] = 1;
// q.push(node->right);
// }
// if(mpp[node] && !vis [mpp[node]]) {
// fl = 1;
// vis [mpp[node]] = 1;
// q.push(mpp[node]);
// }
// }
// if(fl) maxi++;
// }
// return maxi;
// }
// Binary TreeNode<int>* bfsToMapParents (BinaryTreeNode<int>* root,
// map<BinaryTreeNode<int>*, BinaryTreeNode<int>*> &mpp, int start) {
// queue<BinaryTreeNode<int>*> q;
// q.push(root);
// Binary TreeNode<int>* res;

// while(!q.empty()) {
// Binary TreeNode<int>* node = q.front(); if(node->data = start) res = node;
// q.pop();
// if(node->left) {
// mpp [node->left] = node;
// q.push(node->left);
// }
// if(node->right) {
// mpp[node->right] = node;
// q.push(node->right);
// }
// }
// return res;
// }
// int timeToBurnTree(BinaryTreeNode<int>* root, int start)
// {
// map<BinaryTreeNode<int>*, Binary TreeNode<int>*> mpp;
// Binary TreeNode<int>* target = bfsToMapParents (root, mpp, start);
// int maxi = findMaxDistance (mpp, target);
// return maxi;
// }


//////////minimum time to burn a  node ///////////////(GFG SOLUTION)
// class Solution {
//   public:
  
// unordered_map<Node*, Node*> getAllPArents(Node* root){
//         unordered_map<Node*, Node*> parentOf;
        
//         queue<Node* > q;
//         q.push(root);
        
//         while(!q.empty()){
//             Node* front = q.front();
//             q.pop();
            
//             if(front -> left){
//                 parentOf[front -> left] = front;
//                 q.push(front -> left);
//             }
            
//             if(front -> right){
//                 parentOf[front -> right] = front;
//                 q.push(front -> right);
//             }
//         }
        
//         return parentOf;
//     }
    
//     Node* getTargetNode(Node* root, int target){
//         queue<Node* > q;
//         q.push(root);
        
//         while(!q.empty()){
//             Node* front = q.front();
//             q.pop();
            
//             if(front -> data == target)
//                 return front;
            
//             if(front -> left)
//                 q.push(front -> left);
                
//             if(front -> right)
//                 q.push(front -> right);
//         }
        
//         return NULL;
//     }
  
//     int minTime(Node* root, int target) 
//     {
//         unordered_map<Node*, Node*> parentOf = getAllPArents(root);
        
//         queue<Node* > q;
//         unordered_map<Node*, bool> visited;
        
//         Node* targetNode = getTargetNode(root, target);
        
//         if(targetNode == NULL)
//             return 0;
            
        
//         q.push(targetNode);
//         visited[targetNode] = true;
        
//         int sec = -1;
        
//         while(!q.empty()){
//             int size = q.size();
//             sec++;
            
//             for(int i = 0; i < size; i++){
//                 Node* front = q.front();
//                 q.pop();
                
//                 if(front -> left && !visited[front -> left]){
//                     q.push(front -> left);
//                     visited[front -> left] = true;
//                 }
                
//                 if(front -> right && !visited[front -> right]){
//                     q.push(front -> right);
//                     visited[front -> right] = true;
//                 }
                
//                 if(parentOf[front] && !visited[parentOf[front]]){
//                     q.push(parentOf[front]);
//                     visited[parentOf[front]] = true;
//                 }
                
//             }
//         }
        
//         return sec;
//     }
// };


///////////////cousins in a binary tree 2///////////////////
// class Solution {
// public:
//     TreeNode* replaceValueInTree(TreeNode* root) {
//         if(root == NULL) {
//             return root;
//         }        

//         queue<TreeNode*> que;
//         que.push(root);
//         int levelSum = root->val;

//         while(!que.empty()) {
//             int n = que.size();
//             int nextLevelSum = 0;

//             while(n--) {
//                 TreeNode* curr = que.front();
//                 que.pop();

//                 curr->val = levelSum - curr->val;

//                 int siblingSum = (curr->left != NULL ? curr->left->val : 0);
//                 siblingSum += (curr->right != NULL ? curr->right->val : 0);

//                 if(curr->left) {
//                     nextLevelSum += curr->left->val;
//                     curr->left->val = siblingSum;
//                     que.push(curr->left);
//                 }


//                 if(curr->right) {
//                     nextLevelSum += curr->right->val;
//                     curr->right->val = siblingSum;
//                     que.push(curr->right);
//                 }
//             }

//             levelSum = nextLevelSum;
//         }

//         return root;
//     }
// };


///////find the maximum sum of node values////////////
// class Solution {
// public:
//     typedef long long ll;

//     long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
//         ll  sum        = 0;
//         int count      = 0;
//         int minNukasan = INT_MAX;

//         for (ll num : nums) {

//             if((num^k) > num) {
//                 count++;
//                 sum += (num^k);
//             } else {
//                 sum += num;
//             }

//             minNukasan = min((long long)minNukasan, abs(num - (num ^ k)));
//         }

//         if(count%2 == 0)
//             return sum;

//         return sum - minNukasan;
//     }
// };
