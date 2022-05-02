#include<iostream>
#include<vector>

using namespace std;

struct Node
{
    vector<int> point;
    Node* left, * right;
};


struct Node* newNode(vector<int> arr)
{
    struct Node* temp = new Node;

    temp->point = arr;

    temp->left = temp->right = NULL;
    return temp;
}

Node* insertRec(Node* root, vector<int> point, unsigned depth)
{
    // Tree is empty?
    if (root == NULL)
        return newNode(point);

    // Calculate current dimension (cd) of comparison
    unsigned cd = depth % point.size();

    // Compare the new point with root on current dimension 'cd'
    // and decide the left or right subtree
    if (point[cd] < (root->point[cd]))
        root->left = insertRec(root->left, point, depth + 1);
    else
        root->right = insertRec(root->right, point, depth + 1);

    return root;
}

// Function to insert a new point with given point in
// KD Tree and return new root. It mainly uses above recursive
// function "insertRec()"
Node* insert(Node* root, vector<int> point)
{
    return insertRec(root, point, 0);
}

// A utility method to determine if two Points are same
// in K Dimensional space
bool arePointsSame(vector<int> point1, vector<int> point2)
{
    // Compare individual pointinate values
    for (int i = 0; i < point1.size(); ++i)
        if (point1[i] != point2[i])
            return false;

    return true;
}

Node* minNode(Node* x, Node* y, Node* z, int d)
{
    Node* res = x;
    if (y != NULL && y->point[d] < res->point[d])
        res = y;
    if (z != NULL && z->point[d] < res->point[d])
        res = z;
    return res;
}

// Recursively finds minimum of d'th dimension in KD tree
// The parameter depth is used to determine current axis.
Node* findMinRec(Node* root, int d, unsigned depth)
{
    // Base cases
    if (root == NULL)
        return NULL;

    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned cd = depth % root->point.size();

    // Compare point with root with respect to cd (Current dimension)
    if (cd == d)
    {
        if (root->left == NULL)
            return root;
        return findMinRec(root->left, d, depth + 1);
    }

    // If current dimension is different then minimum can be anywhere
    // in this subtree
    return minNode(root,
        findMinRec(root->left, d, depth + 1),
        findMinRec(root->right, d, depth + 1), d);
}

// A wrapper over findMinRec(). Returns minimum of d'th dimension
Node* findMin(Node* root, int d)
{
    // Pass current level or depth as 0
    return findMinRec(root, d, 0);
}

void copyPoint(vector<int> &p1, vector<int> &p2){
    p1 = p2;
}

Node* deleteNodeRec(Node* root, vector<int> point, int depth){
    if (root == NULL)
        return NULL;

    int cd = depth % point.size();

    if (arePointsSame(root->point, point)){
        if (root->right != NULL){
            Node* min = findMin(root->right, cd);

            root->point = min->point;

            root->right = deleteNodeRec(root->right, min->point, depth + 1);
        }
        else if (root->left != NULL){
            Node* min = findMin(root->left, cd);
            root->point = min->point;
            root->right = deleteNodeRec(root->left, min->point, depth + 1);
        }
        else{
            delete root;
            return NULL;
        }
        return root;
    }

    if (point[cd] < root->point[cd])
        root->left = deleteNodeRec(root->left, point, depth + 1);
    else
        root->right = deleteNodeRec(root->right, point, depth + 1);
    return root;
}


Node* deleteNode(Node* root, vector<int> point){
    return deleteNodeRec(root, point, 0);
}

bool searchRec(Node* root, vector<int> point, unsigned depth){
    if (root == NULL)
        return false;
    if (arePointsSame(root->point, point))
        return true;

    unsigned cd = depth % point.size();

    if (point[cd] < root->point[cd])
        return searchRec(root->left, point, depth + 1);

    return searchRec(root->right, point, depth + 1);
}

bool search(Node* root, vector<int> point){
    return searchRec(root, point, 0);
}

int main(){
    struct Node* root = NULL;
    vector<vector<int>> points = {{30, 40},{5, 25}, {70, 70},{10, 12}, {50, 30}, {35, 45} };

    for (int i = 0; i < points.size(); i++)
        root = insert(root, points[i]);

    vector<int> point1 = { 5, 25 };
    (search(root, point1)) ? cout << "Found\n" : cout << "Not Found\n";

    vector<int> point2 = { 12, 19 };
    (search(root, point2)) ? cout << "Found\n" : cout << "Not Found\n";

    root = deleteNode(root, points[0]);

    cout << "Root after deletion of (30, 40)\n";
    cout << root->point[0] << ", " << root->point[1] << endl;

    return 0;
}