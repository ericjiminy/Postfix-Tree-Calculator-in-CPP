// Eric Chun - jc2ppp - 10/5/20 - TreeCalc.cpp
// TreeCalc.cpp:  CS 2150 Tree Calculator method implementations

#include "TreeCalc.h"
#include <iostream>
#include <string>

using namespace std;

// Constructor
TreeCalc::TreeCalc() {
}

// Destructor - frees memory
TreeCalc::~TreeCalc() {
  if (!expressionStack.empty()){
    cleanTree(expressionStack.top());
  }
}

// Deletes tree/frees memory
void TreeCalc::cleanTree(TreeNode* tree) {
  if (tree != NULL){
    cleanTree(tree->left);
    cleanTree(tree->right);
    delete tree;
  }
}

// Gets data from user
// DO NOT MODIFY
void TreeCalc::readInput() {
  string response;
  cout << "Enter elements one by one in postfix notation" << endl
       << "Any non-numeric or non-operator character,"
       << " e.g. #, will terminate input" << endl;
  cout << "Enter first element: ";
  cin >> response;
  //while input is legal
  while (isdigit(response[0]) || response[0] == '/' || response[0] == '*'
	 || response[0] == '-' || response[0] == '+') {
    insert(response);
    cout << "Enter next element: ";
    cin >> response;
  }
}

bool isOperator(const string& val){
  return val == "+" || val == "-" || val == "*" || val == "/";
}

// Puts value in tree stack
void TreeCalc::insert(const string& val) {
  if (!isOperator(val)) {
    TreeNode* tree = new TreeNode(val);
    expressionStack.push(tree);
  } else {
    TreeNode* tree = new TreeNode(val);
    tree->right = expressionStack.top();
    expressionStack.pop();
    tree->left = expressionStack.top();
    expressionStack.pop();
    expressionStack.push(tree);
  }
}

// Prints data in prefix form
void TreeCalc::printPrefix(TreeNode* tree) const {
  // print the tree in prefix format
  if (tree != NULL){
    cout << tree->value << " ";
    printPrefix(tree->left);
    printPrefix(tree->right);
  }
}

// Prints data in infix form
void TreeCalc::printInfix(TreeNode* tree) const {
  // print tree in infix format with appropriate parentheses
  if (tree != NULL){
    if (isOperator(tree->value)){
      cout << "(";
    }
    printInfix(tree->left);
    if (isOperator(tree->value)) cout << " ";
    cout << tree->value;
    if (isOperator(tree->value)) cout << " ";
    printInfix(tree->right);
    if (isOperator(tree->value)){
      cout << ")";
    }
  }
}

//Prints data in postfix form
void TreeCalc::printPostfix(TreeNode* tree) const {
  // print the tree in postfix form
  if (tree != NULL){
    printPostfix(tree->left);
    printPostfix(tree->right);
    cout << tree->value << " ";
  }
}

// Prints tree in all 3 (post, in, pre) forms
// DO NOT MODIFY
void TreeCalc::printOutput() const {
  if (expressionStack.size() != 0 && expressionStack.top() != NULL) {
    TreeNode* tree = expressionStack.top();
    cout << "Expression tree in postfix expression: ";
    printPostfix(tree);
    cout << endl;

    cout << "Expression tree in infix expression: ";
    printInfix(tree);
    cout << endl;

    cout << "Expression tree in prefix expression: ";
    printPrefix(tree);
    cout << endl;
  } else {
    cout << "Size is 0." << endl;
  }
}

// Evaluates tree, returns value
// private calculate() method
int TreeCalc::calculate(TreeNode* tree) const {
  // Traverse the tree and calculates the result
  if (tree != NULL){
    if (!isOperator(tree->value)){
      return std::stoi(tree->value);
    } else {
      int a = calculate(tree->left);
      int b = calculate(tree->right);
      if (tree->value == "+") return a + b;
      if (tree->value == "-") return a - b;
      if (tree->value == "*") return a * b;
      if (tree->value == "/") return a / b;
    }
  }
  return 0;
}

//Calls calculate, sets the stack back to a blank stack
// public calculate() method. Hides private data from user
int TreeCalc::calculate() {
  // call private calculate method here
  int x = calculate(expressionStack.top());
  cleanTree(expressionStack.top());
  while (!expressionStack.empty()){
    expressionStack.pop();
  }
  return x;
}
