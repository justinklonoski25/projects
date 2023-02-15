#include <iostream>
#include <stack>
using namespace std;

// Definition of a binary tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Recursive function to check if two binary trees are identical
bool isIdenticalRecursive(TreeNode* p, TreeNode* q) {
    if (p == NULL && q == NULL) {
        return true;
    } else if (p == NULL || q == NULL) {
        return false;
    } else if (p->val != q->val) {
        return false;
    } else {
        return isIdenticalRecursive(p->left, q->left) && isIdenticalRecursive(p->right, q->right);
    }
}

// Iterative function to check if two binary trees are identical
bool isIdenticalIterative(TreeNode* p, TreeNode* q) {
    stack<TreeNode*> stackP, stackQ;
    stackP.push(p);
    stackQ.push(q);

    while (!stackP.empty() && !stackQ.empty()) {
        TreeNode* currP = stackP.top();
        stackP.pop();
        TreeNode* currQ = stackQ.top();
        stackQ.pop();

        if (currP == NULL && currQ == NULL) {
            continue;
        } else if (currP == NULL || currQ == NULL) {
            return false;
        } else if (currP->val != currQ->val) {
            return false;
        } else {
            stackP.push(currP->left);
            stackP.push(currP->right);
            stackQ.push(currQ->left);
            stackQ.push(currQ->right);
        }
    }

    return stackP.empty() && stackQ.empty();
}

// Function to create a binary tree from an array
TreeNode* createTree(int arr[], int n, int i) {
    if (i >= n || arr[i] == -1) {
        return NULL;
    }
    TreeNode* root = new TreeNode(arr[i]);
    root->left = createTree(arr, n, 2*i+1);
    root->right = createTree(arr, n, 2*i+2);
    return root;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5, -1, -1};
    int arr2[] = {1, 2, 3, 4, 5, -1, -1};
    TreeNode* tree1 = createTree(arr1, 7, 0);
    TreeNode* tree2 = createTree(arr2, 7, 0);

    // Recursive approach
    bool identical1 = isIdenticalRecursive(tree1, tree2);
    cout << "The trees are " << (identical1 ? "" : "not ") << "identical (recursive)." << endl;

    // Iterative approach
    bool identical2 = isIdenticalIterative(tree1, tree2);
    cout << "The trees are " << (identical2 ? "" : "not ") << "identical (iterative)." << endl;

    return 0;
}
