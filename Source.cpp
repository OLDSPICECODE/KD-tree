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

Node* insertRec(Node* root, vector<int> point, unsigned depth){
    if (root == NULL)
        return newNode(point);

    unsigned cd = depth % point.size();

    if (point[cd] < (root->point[cd]))
        root->left = insertRec(root->left, point, depth + 1);
    else
        root->right = insertRec(root->right, point, depth + 1);

    return root;
}

Node* insert(Node* root, vector<int> point){
    return insertRec(root, point, 0);
}

bool arePointsSame(vector<int> point1, vector<int> point2){
    for (int i = 0; i < point1.size(); ++i)
        if (point1[i] != point2[i])
            return false;

    return true;
}

Node* minNode(Node* x, Node* y, Node* z, int d){
    Node* res = x;
    if (y != NULL && y->point[d] < res->point[d])
        res = y;
    if (z != NULL && z->point[d] < res->point[d])
        res = z;
    return res;
}

Node* findMinRec(Node* root, int d, unsigned depth){
    if (root == NULL)
        return NULL;

    unsigned cd = depth % root->point.size();

    if (cd == d){
        if (root->left == NULL)
            return root;
        return findMinRec(root->left, d, depth + 1);
    }

    return minNode(root, findMinRec(root->left, d, depth + 1), findMinRec(root->right, d, depth + 1), d);
}

Node* findMin(Node* root, int d){
    return findMinRec(root, d, 0);
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