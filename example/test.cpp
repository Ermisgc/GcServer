#include <iostream>

template<class Comparable, class ValueType>
struct rbtree_node{
    rbtree_node * parent;
    rbtree_node * left;
    rbtree_node * right;

    Comparable key;
    ValueType val;
    unsigned char color;
};

template<class Comparable, class ValueType>
class rbtree{
private:
    rbtree_node<Comparable, ValueType> *root;
    rbtree_node<Comparable, ValueType> * nil;
public:
    rbtree(){}
    rbtree(rbtree & other){ // deep copy
        
    }

    rbtree(rbtree && other){ // move constructor
        delete root;
        root = other.root;
        other.root = nullptr;
    }

    ~rbtree(){
        dfs_for_delete(root);
        delete nil;
    }

    rbtree_node<Comparable, ValueType> * root(){return root;}
    void setRoot(rbtree_node<Comparable, ValueType> *rt){this->root = rt;}
    rbtree_node<Comparable, ValueType> * nil() {return nil;}

private:
    void dfs_for_delete(rbtree_node<Comparable, ValueType> * rt){
        //in-tranverse
        if(rt->left != nil) dfs_for_delete(rt->left);
        if(rt->right != nil) dfs_for_delete(rt->right);
        delete rt;
    }

    void dfs_for_deepcopy(rbtree_node<Comparable, ValueType> *rt){

    }

    void left_rotate(rbtree_node<Comparable, ValueType> *x){
        //             x                                        y
        //  alpha              y             -->           x       gamma
        //               beta    gamma              alpha      bata
        rbtree_node<Comparable, ValueType>* y = x->right;
        x->right = y->left;
        if(y->left != nil) y->left->parent = x;

        y->parent = x->parent;
        if(y->parent == nil) root = y;
        else if(x == x->parent->left) y = y->parent->left;
        else y = y->parent->right;

        y->left = x;
        x->parent = y;
    }

    void right_rotate(rbtree_node<Comparable, ValueType> *y){
        //             x                                        y
        //  alpha              y             -->           x       gamma
        //               beta    gamma              alpha      bata
        rbtree_node<Comparable, ValueType> * x = y->left;
        y->left = x->right;
    }
};
