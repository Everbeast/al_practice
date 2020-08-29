//
// Created by ChanChill on 2020-08-29.
//

//https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/

//前序遍历 ====================================
class Codec {
public:
    string step = ",";
    string  null_node = "null";

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res = "";
        serialize(root, res);
        return res;
    }

    void serialize(TreeNode* root, string& res){
        if(root == NULL){
            res += null_node + step;
            return;
        }
        res += to_string(root->val) + step;
        serialize(root->left, res);
        serialize(root->right,res);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        queue<string> nodes;
        int l, r= -1;
        for(int i = 0; i< data.size(); i++){
            if(data[i] == ','){
                l = r + 1;
                r = i;
                nodes.push(data.substr(l, r - l));
            }
        }
        return deserialize(nodes);
    }

    TreeNode* deserialize(queue<string>& nodes){
        if(nodes.size() == 0) return NULL;
        string first = nodes.front();
        nodes.pop();

        if(first == "null"){
            return NULL;
        }
        TreeNode* root = new TreeNode(stoi(first));
        root->left = deserialize(nodes);
        root->right = deserialize(nodes);
        return root;
    }
};



//后序遍历法 ==========================================
class Codec {
public:
    string step = ",";
    string  null_node = "null";

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res = "";
        serialize(root, res);
        return res;
    }

    void serialize(TreeNode* root, string& res){
        if(root == NULL){
            res += null_node + step;
            return;
        }

        serialize(root->left, res);             //后序遍历 先遍历
        serialize(root->right,res);             //先遍历

        res += to_string(root->val) + step;     //  再操作

    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string> nodes;
        int l, r= -1;
        for(int i = 0; i< data.size(); i++){
            if(data[i] == ','){
                l = r + 1;
                r = i;
                nodes.push_back(data.substr(l, r - l));
            }
        }
        return deserialize(nodes);
    }

    TreeNode* deserialize(vector<string>& nodes){
        if(nodes.size() == 0) return NULL;


        string last = nodes.back();
        nodes.pop_back();

        if(last == "null"){
            return NULL;
        }

        TreeNode* root = new TreeNode(stoi(last));  //解码处 从后开始解码
        root->right = deserialize(nodes);           //先构建右子树
        root->left = deserialize(nodes);
        return root;
    }
};


//层遍历法 ========================================
class Codec {
public:
    string step = ",";
    string  null_node = "null";

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res = "";
        serialize(root, res);
        return res;
    }

    void serialize(TreeNode* root, string& res){
        queue<TreeNode*> que;
        que.push(root);
        while(!que.empty()){
            TreeNode* cur = que.front();
            que.pop();
            if(cur == NULL){
                res += null_node + step;
                continue;
            }
            res += to_string(cur->val) + step;
            que.push(cur->left);
            que.push(cur->right);
        }
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string> nodes;
        int l, r= -1;
        for(int i = 0; i< data.size(); i++){
            if(data[i] == ','){
                l = r + 1;
                r = i;
                nodes.push_back(data.substr(l, r - l));
            }
        }
        return deserialize(nodes);
    }

    TreeNode* deserialize(vector<string>& nodes){
        if(nodes.empty()) return NULL;
        TreeNode* root = new TreeNode(stoi(nodes[0]));

        queue<TreeNode*> que;
        que.push(root);
        for(int i = 1; i < nodes.size();){
            TreeNode* parent = que.front();
            que.pop();

            if(nodes[i] != "null"){
                parent->left = new TreeNode(stoi(nodes[i]));
                que.push(parent->left);
            }
            else{
                parent->left = NULL;
            }
            i++;

            if(nodes[i] != "null"){
                parent->right = new TreeNode(stoi(nodes[i]));
                que.push(parent->right);
            }
            else{
                parent->right = NULL;
            }
            i++;
        }
        return root;
    }
};