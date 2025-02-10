#include <iostream>

namespace gcdst{
template<class Comparable=int, class ValueType=int>
struct rbtree_node{
    rbtree_node * parent;
    rbtree_node * left;
    rbtree_node * right;

    Comparable key;
    ValueType val;
    unsigned char color; //0->black, 1->right
};

template<class Comparable=int, class ValueType=int>
class rbtree{
private:
    using Node = rbtree_node<Comparable, ValueType>;
    Node * _root;
    Node * _nil;
public:
    rbtree(){}
    rbtree(rbtree & other){ // deep copy, O(n)
        _nil = new Node();
        this->_nil->color = 0;
        dfs_for_deepcopy(_root, other._root, _nil, other._nil);
    }

    rbtree(rbtree && other){ // move constructor, O(1)
        delete _root;
        _root = other._root;
        other._root = nullptr;
    }

    ~rbtree(){  //O(n)
        dfs_for_delete(_root);
        delete _nil;
    }

    Node * root(){return _root;}
    void setRoot(Node *rt){this->_root = rt;}
    Node * nil() {return _nil;}

    void insert(Comparable key, ValueType value){
        Node * z = new Node({_nil, _nil, _nil, key, value, 1});  //red
        insert(z);
    }

    ValueType find(Comparable key){
        Node * ret = find_node(key);
        if(ret != _nil) return ret->val;
        ValueType v;
        return v;  //here we should throw an exception
    }

    ValueType operator[] (Comparable key){
        return find(key);
    }

    void remove(Comparable key){
        Node * target = find_node(key);
        if(target == _nil) return;
        delete_node(target);
    }

private:
    void dfs_for_delete(Node * rt){
        //in-tranverse
        if(rt->left != _nil) dfs_for_delete(rt->left);
        if(rt->right != _nil) dfs_for_delete(rt->right);
        delete rt;
    }

    Node dfs_for_deepcopy(Node *rt, \
       Node * other_rt, Node * pre, Node * other_rt__nil){
        rt = new Node();
        rt->key = other_rt->key;
        rt->val = other_rt->value;
        rt->parent = pre;

        if(other_rt->left != other_rt__nil) rt->left = dfs_for_deepcopy(rt->left, other_rt->left, rt, other_rt__nil);
        else rt->left = this->_nil;

        if(other_rt->right != other_rt__nil) rt->right = dfs_for_deepcopy(rt->right, other_rt->right, rt, other_rt__nil);
        else rt->right = this->_nil;      

        return rt;  
    }

    void left_rotate(Node *x){
        //             x                                        y
        //  alpha              y             -->           x       gamma
        //               beta    gamma              alpha      bata
        Node* y = x->right;
        x->right = y->left;
        if(y->left != _nil) y->left->parent = x;

        y->parent = x->parent;
        if(y->parent == _nil) _root = y;
        else if(x == x->parent->left) y->parent->left = y;
        else y->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void right_rotate(Node *y){
        //             x                                        y
        //  alpha              y             -->           x       gamma
        //               beta    gamma              alpha      bata
        Node * x = y->left;
        y->left = x->right;
        if(x->right != _nil) x->right->parent = y;

        x->parent = y->parent;
        if(y->parent == _nil) _root = x;
        else if(y == y->parent->left) x->parent->left = x;
        else x->parent->right = x;

        x->right = y;
        y->parent  = x;
    }

    void insert(Node *z){
        Node* target = _root;
        if(target == _nil){ //z is the first node in the tree;
            z->parent = _nil;
            z->color = 0;
            _root = z;
            return;
        }
        Node* target_p = _nil;
        while(target != _nil){
            target_p = target;
            if(z->key <= target->key) target = target->left;  //actually, if equal, we have to throw an exception
            else{  //z > target
                target = target->right;
            }
        } 

        //insert z as a child of target_p.
        z->parent = target_p;
        if(z->key <= target_p->key) target_p->right = z;
        else target_p->left = z;

        this->rbtree_insert_fixup(z); //z should be adjust because z is red and may break some rules
    }

    void rbtree_insert_fixup(Node *z){
        //check z's parent, if its color is red, we have to adjust using the color of z's uncle 
        //or z is the _root, it is much more easy.
        Node * y = z->parent;
        while (y->color == 1){   //before adjust, if z->parent->color == 1, z->parent can not be the _root.
            Node * uncle = nullptr;
            if(y == y->parent->left) uncle = y->parent->right;
            else uncle = y->parent->left;

            if(uncle->color == 1){
                y->color = 0;
                uncle->color = 0;
                y->parent->color = 1;
                z = y->parent;
                y = z->parent;
            }
            else{
                //Step 1. check if rotation of z and z'parent is needed
                //Step 2. change colors of y and y->parent
                //Step 3. rotate the parent of (z, z->parent(origin)) and grandparent
                
                if(z == y->left && y == y->parent->left){
                    //no self-rotation, change the color of y and y'parent, right_rotate(y->parent)
                    y->color = 0;
                    y->parent->color = 1;
                    right_rotate(y->parent);
                }

                else if(z == y->right && y == y->parent->right){
                    // no self-rotation, change the color of y and y'parent, left_rotation(y->parent)
                    y->color = 0;
                    y->parent->color = 1;
                    left_rotate(y->parent);
                }

                else if(z == y->right && y == y->parent->left){
                    // left_rotate(y), change the color of z and z'parent, right_rotate(z->parent)
                    z->color = 0;
                    y->parent->color = 1;
                    left_rotate(y);
                    right_rotate(z->parent);
                    y = z;
                    z = y->left;
                }

                else { //that is: z == y->left && y = y->parent->right
                    z->color = 0;
                    y->parent->color = 1;
                    right_rotate(y);
                    left_rotate(z->parent);
                    y = z;
                    z = y->left;
                }
            }
        }
        //z is fixup as a _root
        if(y == _nil){
            z->color = 0;
            _root = z;
        }
    }

    Node * find_node(Comparable key){
        Node * z = _root;
        while(z != _nil){
            if(z->key == key) return z;
            else if(z->key < key) z = z->right;
            else z = z->left;
        } 
        return z;  //here we should throw an exception
    }

    Node * find_predecessor(Node * replaced){
        // find the predecessor(the last num that less than repalced->val)
        Node * ret = replaced->left;
        while(1){
            if(ret->right == _nil) break; 
            ret = ret->right;
        }
        return ret;
    }

    inline void swap_node(Node * a, Node * b){
        std::swap(a->key, b->key);
        std::swap(a->val, b->val);
    }

    Node * find_successor(Node * replaced){
        Node * ret = replaced->right;
        while(1){
            if(ret->left == _nil) break;;
            ret = ret->left;
        }
        return ret;
    }

    void delete_node(Node * z){
        if(z == _root){
            delete _root;
            _root = _nil;
            return;
        }

        //there are 3 cases, divided by the num of children
        if(z->right != _nil && z->left != _nil){  // 2 children
            //swap it with its predecessor or successor
            Node* pre = find_predecessor(z);
            this->swap_node(z, pre);  //now the value and key are in z, and the pre is what should be delete, and it has 0 or 1 child
            delete_node(pre);            
        }
        else if(z->left != _nil){ // 1 child
            //the child must be a red node, because if not the blackheight will no equal
            if(z == z->parent->left) z->parent->left = z->left;
            else z->parent->right = z->left;
            z->left->parent = z->parent;
            z->left->color = 0; // turn the red node to black
            delete z;
        }
        else if(z->right != _nil){  // 1 child
            if(z == z->parent->left) z->parent->left = z->right;
            else z->parent->right = z->right;
            z->right->parent = z->parent;
            z->right->color = 0;
            delete z;
        }
        else{  // 0 child
            if(z->color == 0) rbtree_delete_fixup(z);
            if(z == z->parent->left) z->parent->left = _nil;
            else z->parent->right = _nil;
            delete z;
        }
    }

    void rbtree_delete_fixup(Node * z){
        Node * y = nullptr;  //y is the sibling of the z, and it must exist.
        if(z == z->parent->left) y = z->parent->right;
        else y = z->parent->left;

        if(y->color == 1){ //y is red, then it must have to black node, and y->p is also black
            if(y == y->parent->left){
                y->color = 0;
                y->right->color = 1;
                right_rotate(y->parent);
            } else { // y == y->parent->right
                y->color = 0;
                y->left->color = 1;
                left_rotate(y->parent);
            }
        }
        else if(y->parent->color == 1){
            if(y->left != _nil && y->right != _nil){
                y->color = 1;
                y->parent->color = 0;
                if(y == y->parent->left){
                    y->left->color = 0;
                    right_rotate(y->parent);
                } else { //y is y_p's right childs 
                    y->right->color = 0;
                    left_rotate(y->parent);
                }
            }
            else if(y->left != _nil){
                if(y == y->parent->left) right_rotate(y->parent);
                else {  // y == y->parent->right
                    y->parent->color = 0;
                    right_rotate(y);
                    left_rotate(y->parent->parent);
                }
            } 
            else if(y->right != _nil){
                if(y == y->parent->left) {
                    y->parent->color = 0;
                    left_rotate(y);
                    right_rotate(y->parent->parent);
                }
                else left_rotate(y->parent);
            } 
            else { // y has no child
                y->color = 1;
                y->parent->color = 0;
            }
        }
        else{  //y->parent->color == 0
            if(y->left != _nil && y->right != _nil){
                if(y == y->parent->left){
                    y->left->color = 0;
                    right_rotate(y->parent);
                } else { //y == y->parent->right
                    y->right->color = 0;
                    left_rotate(y->parent);
                }
            }
            else if(y->left != _nil){
                y->left->color = 0;
                if(y == y->parent->left) left_rotate(y->parent);
                else { //y == y->parent->right
                    left_rotate(y);
                    right_rotate(y->parent->parent);
                }
            }
            else if(y->right != _nil){
                y->right->color = 0;
                if(y == y->parent->left){
                    right_rotate(y);
                    left_rotate(y->parent->parent);
                } else right_rotate(y->parent);
            }
            else{
                y->color = 1;
                rbtree_delete_fixup(y->parent);
            }

        }
    }

};
}


using namespace std;
int main(){
    gcdst::rbtree tree;
    tree.insert(10, 100);
    cout << tree.find(10) << endl;
    return 0;
}

