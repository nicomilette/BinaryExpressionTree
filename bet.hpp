
template <typename T>
BET<T>::BET(){
    root = nullptr;
}

template <typename T>
BET<T>::BET( const BET & rhs ) : root{nullptr}
{
    root = clone( rhs.root );
}

template <typename T>
typename BET<T>::BinaryNode * BET<T>::clone( BinaryNode *t ) const
{
    if( t == nullptr ) return nullptr;
    else return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
}

template <typename T>
BET<T>::~BET() { makeEmpty(root); }

template <typename T>
BET<T>::BET(const list<T> & postfix) { buildFromPostfix(postfix); }

template <typename T>
void BET<T>::makeEmpty( BinaryNode * & t)
{
    if( t != nullptr )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = nullptr;
}

template <typename T>
int BET<T>::leaves() { return leaves(root); } 
template <typename T>
int BET<T>::depth() { return depth(root) - 1; }
template <typename T>
int BET<T>::breadth( ) { return breadth(root); } 
template <typename T>
size_t BET<T>::size() { return size(root); } 

template <typename T>
bool BET<T>::empty() { return root == nullptr; }

template <typename T>
void BET<T>::printInfixExpression() { 
    printInfixExpression(root);
    cout << endl;     
} 
template <typename T>
void BET<T>::printPostfixExpression() { 
    printPostfixExpression(root);
    cout << endl;
}

template <typename T>
typename BET<T>::BET & BET<T>::operator=(const BET & rhs){
    if (this != &rhs) {
            makeEmpty(root); 
            root = clone(rhs.root); 
        }
        return *this;
}

template <typename T>
int BET<T>::depth(BinaryNode* &t){
    if (t == nullptr) return 0; 
    else {
        int Ldepth = depth(t->left); 
        int Rdepth = depth(t->right); 
        return max(Ldepth, Rdepth) + 1; 
    }
}

template <typename T>
int BET<T>::breadth(BinaryNode* &t){
   if (t == nullptr) return 0;
    queue<BinaryNode*> q;
    q.push(t);
    int breadth = 0;
    while (!q.empty()) {
        int level_size = q.size();
        breadth = max(breadth, level_size);
        for (int i = 0; i < level_size; i++) {
            BinaryNode* current = q.front();
            q.pop();
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }
    return breadth;
}

template <typename T>
int BET<T>::leaves (BinaryNode *t){
    if (t == nullptr) return 0; 
    else if (t->left == nullptr && t->right == nullptr) return 1; 
    else return leaves(t->left) + leaves(t->right); 
} 

template <typename T>
size_t BET<T>::size(BinaryNode *t){
    if (t == nullptr) return 0;
    else return 1 + size(t->left) + size(t->right); 
}

//todo

template <typename T>
bool BET<T>::buildFromPostfix(const list<T> & postfix){
    stack<BinaryNode *> nodeStack;
    for (const auto& token : postfix) {
        BinaryNode *node = new BinaryNode(token, nullptr, nullptr);
        if (isOperand(token)) {
            nodeStack.push(node);
        } else if (isOperator(token)) {
            if (nodeStack.size() < 2) {
                makeEmpty(node);
                return false;
            }
            node->right = nodeStack.top();
            nodeStack.pop();
            node->left = nodeStack.top();
            nodeStack.pop();
            nodeStack.push(node);
        } else {
            makeEmpty(node);
            return false;
        }
    }
    if (nodeStack.size() != 1) {
        makeEmpty(nodeStack.top());
        return false;
    }
    root = nodeStack.top();
    nodeStack.pop();
    return true;

}

template <typename T>
void BET<T>::printInfixExpression(BinaryNode *n){
    if(n != nullptr){
        bool needParentheses = false;

        if (n->left != nullptr && n->left->element.isOperator()) needParentheses = true;
        if (needParentheses) cout << "( ";
        
        printInfixExpression(n->left);
        if (needParentheses) cout << ") ";
        if (n->right != nullptr && n->right->element.isOperator()) needParentheses = true;
        else needParentheses = false;
        cout << n->element << " ";
        if (needParentheses) cout << "( ";
        
        printInfixExpression(n->right);
        if (needParentheses) cout << ") ";       
    }
}
template <typename T>
void BET<T>::printPostfixExpression(BinaryNode *n){
    if (n != nullptr) {
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        cout << n->element << " ";
    }
    
}

template <typename T>
bool isOperator(T in){
    if(in.getType() >=4 && in.getType() <= 7) return true;
    else return false;
}

template <typename T>
bool isOperand(T in){
    return !(isOperator(in));
}

