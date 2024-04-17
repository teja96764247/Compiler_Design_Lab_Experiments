#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

// Node structure for syntax tree
struct Node {
    char data;
    Node* left;
    Node* right;
};

// Function to create a new node
Node* createNode(char data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

// Function to traverse syntax tree and perform arithmetic operations
int evaluateSyntaxTree(Node* root) {
    if (root == nullptr)
        return 0;
    if (isdigit(root->data))
        return root->data - '0'; // Convert char to integer

    int leftValue = evaluateSyntaxTree(root->left);
    int rightValue = evaluateSyntaxTree(root->right);

    switch (root->data) {
        case '+': return leftValue + rightValue;
        case '-': return leftValue - rightValue;
        case '*': return leftValue * rightValue;
        case '/': return leftValue / rightValue;
    }
    return 0;
}
// Function to build syntax tree from postfix expression
Node* buildSyntaxTree(const string& postfix) {
    stack<Node*> stack;

    for (char c : postfix) {
        Node* newNode = createNode(c);
        if (isdigit(c)) {
            stack.push(newNode);
        } else {
            newNode->right = stack.top();
            stack.pop();
            newNode->left = stack.top();
            stack.pop();
            stack.push(newNode);
        }
    }
    return stack.top();
}

int main() {
    string postfixExpression = "23*5+";
    Node* root = buildSyntaxTree(postfixExpression);

    cout << "Postfix expression: " << postfixExpression << endl;
    cout << "Result of evaluation: " << evaluateSyntaxTree(root) << endl;

    return 0;
}