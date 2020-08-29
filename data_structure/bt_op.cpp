//
// Created by ChanChill on 2020-08-29.
//



struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


//判断是否新相同的二叉树
//https://leetcode-cn.com/problems/same-tree
bool isSameTree(TreeNode* p, TreeNode* q) {
    if(p == nullptr && q == nullptr) return true;
    if(p == nullptr || q == nullptr) return false;
    if(p->val != q->val) return false;
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

//删除某节点
//https://leetcode-cn.com/problems/delete-node-in-a-bst
TreeNode* deleteNode(TreeNode* root, int key) {
    if(root == NULL) return NULL;
    if(root->val == key){
        if(root->left == NULL) return root->right;
        if(root->right == NULL) return root->left;
        TreeNode* minNode = getMinNode(root->right); //找右子树的最小节点
        root->val = minNode->val;
        root->right = deleteNode(root->right, minNode->val);
    }
    else if(root->val > key){
        root->left = deleteNode(root->left, key);
    }
    else{
        root->right = deleteNode(root->right, key);
    }
    return root;
}

TreeNode* getMinNode(TreeNode* root){
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}


//插入
//https://leetcode-cn.com/problems/insert-into-a-binary-search-tree/
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if(root == nullptr) return new TreeNode(val);
    if(root->val > val){
        root->left = insertIntoBST(root->left, val);
    }
    if(root->val < val){
        root->right = insertIntoBST(root->right, val);
    }
    return root;
}

//查找
//https://leetcode-cn.com/problems/search-in-a-binary-search-tree/
TreeNode* searchBST(TreeNode* root, int val) {
    if(root == nullptr) return root;
    if(root->val == val) return root;
    if(root->val > val) return searchBST(root->left, val);
    if(root->val < val) return searchBST(root->right, val);
    return root;
}

//验证是否二叉查找树
//https://leetcode-cn.com/problems/validate-binary-search-tree/
bool isValidBST(TreeNode* root) {
    return isValidBST(root, NULL, NULL);
}

bool isValidBST(TreeNode* root, TreeNode* max, TreeNode* min){
    if(root == NULL) return true;
    if(max != NULL && root->val >= max->val) return false;
    if(min != NULL && root->val <= min->val) return false;
    return isValidBST(root->left, root, min) && isValidBST(root->right, max, root);
}




