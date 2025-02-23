namespace gcdst{
    template <class Comparable, class ValueType>  
    struct skiplist_node{
        skiplist_node * right;
        skiplist_node * down;
        Comparable key;
        ValueType value;

    };

    template<class Comparable, class ValueType>
    class skiplist{
    private:
        using node = skiplist_node<Comparable, ValueType>;
        node * header;
        vector<node *> levels;

    public:
        skiplist() : levels(32){}

        //deepcopy
        skiplist(const skiplist & other){

        }

        //move_copy
        skiplist(skiplist && other){

        }

        void operator=(const skiplist & other){

        }

        void operator=(skiplist && other){

        }

        ValueType find(Comparable key){
            
        }

        void insert(Comparable key, ValueType val){

        }

        void remove(Comparable key){

        }
    }
    
}