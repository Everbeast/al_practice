//
// Created by ChanChill on 2020-08-29.
//
//https://leetcode-cn.com/problems/count-complete-tree-nodes/

 //普通二叉树
 int countNodes(TreeNode* root) {
     if(root == NULL) return 0;
     return 1 + countNodes(root->left) + countNodes(root->right);
 }


//满二叉树
 int countNodes(TreeNode* root){
     int h = 0;
     while(root){
         root = root->left;
         h++;
     }
     return (int)pow(2, h) - 1
 }

//完全二叉树
int countNodes(TreeNode* root){
    TreeNode* l_node = root;
    TreeNode* r_node = root;
    int lh = 0, rh = 0;
    while(l_node){
        lh++;
        l_node = l_node->left;
    }

    while(r_node){
        rh++;
        r_node = r_node->right;
    }
    if(lh == rh){
        return (int)pow(2, lh) - 1;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}
