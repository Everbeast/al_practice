//
// Created by ChanChill on 2020-08-29.
//
//最近的公共父节点
//为后序遍历，应该从下面往上推来想/
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root == NULL) return NULL;
    if(root == p || root == q) return root;

    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    //情况1 p q 都在以root为根的树中  则left 和 right 一定是p q（base case 可以看出）
    if(left != NULL && right !=NULL){
        return root;
    }

    //情况2 p q都不在root为根的树中
    if(left == NULL && right == NULL){
        return NULL;
    }

    //只有一个存在于以root为根的树中
    return left == NULL ? right : left;
}
