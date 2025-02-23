#include <vector>
namespace gcdst{
    
    template<class Comparable, class ValueType>
    class skiplist{
    private:
        typedef struct skiplist_node{
            std::vector<skiplist_node *> forward;
            Comparable key;
            ValueType value;
            skiplist_node(int max_level, Comparable _key, ValueType _value):\
                key(_key), value(_value), forward(max_level, nullptr){}
            skiplist_node(int max_level = 32):forward(max_level, nullptr){}
            int level(){return forward.size();}
        } Node;

        Node * header;  //a sentinal whose val should be the minimum;
        int cur_level;
        int max_level;

    public:
        skiplist() = delete;
        explicit skiplist(int _max_level = 32): header(new Node(_max_level)), cur_level(0), max_level(_max_level){}
        //deepcopy
        skiplist(const skiplist & other) = delete; //waiting for completion

        //move_copy
        skiplist(skiplist && other){
            header = other.header;
            other.header = nullptr;
            cur_level = std::move(other.cur_level);
            max_level = std::move(other.max_level);
        }

        void operator=(const skiplist & other) = delete; //waiting for completion

        void operator=(skiplist && other) = delete; //waiting for completion

        ValueType find(Comparable key){
            if(cur_level == 0 || header->forward[0]->key > key) throw ("Key " + to_string(key) + "is not exist");  //we can not find that key
            const Node * cur = header;
            for(int i = cur_level - 1; i >= 0; --i){
                while(cur->forward[i] && cur->forward[i]->key < key) cur = cur->forward[i];
            }
            if(cur && cur->key == key) return cur->value;
            throw ("Key " + to_string(key) + "is not exist");
        }

        ValueType operator[](Comparable key){
            return find(key);
        }

        std::vector<ValueType> & find(Comparable range_left, Comparable range_right){
            return {};
        }

        bool isExist(Comparable key){
            if(cur_level == 0 || header->forward[0]->key > key) return false;  //we can not find that key
            const Node * cur = header;
            for(int i = cur_level - 1; i >= 0; --i){
                while(cur->forward[i] && cur->forward[i]->key < key) cur = cur->forward[i];
            }
            if(cur && cur->key == key) return true;
            return false;;
        }

        void insert(Comparable key, ValueType val){
            std::vector<Node *> updates(max_level, header);
            const Node * cur = header;
            for(int i = cur_level - 1; i >= 0; --i){
                while(cur->forward[i] && cur->forward[i]->key < key) cur = cur->forward[i];
                updates[i] = cur;
            } 

            int new_node_level = randomLevel();
            Node * new_node = new Node(new_node_level, key, val);
            for(int i = 0;i < new_node_level; ++i){
                new_node->forward[i] = updates[i]->forward[i];
                updates[i]->forward[i] = new_node;
            }
            cur_level = max(cur_level, new_node_level);
        }

        void remove(Comparable key){
            std::vector<Node *> updates(max_level, header);
            const Node * cur = header;
            for(int i = cur_level - 1;i >= 0; --i){
                while(cur->forward[i] && cur->forward[i]->key < key) cur = cur->forward[i];
                updates[i] = cur;
            }

            if(!cur->forward[0] || cur->forward[0] > key) return; // no node with that key
            //the node to be deleted is cur->forward[0]
            cur = cur->forward[0]; 
            for(int i = 0;i < cur_level; ++i){
                if(updates[i]->forward[i] != cur) break;  //no need to continue deleting.
                updates[i]->forward[i] = cur->forward[i];
            }

            delete cur;  //delete this node
            if(cur_level > 1 && !header[cur_level - 1]) cur_level -= 1;
        }

    private:
        inline int randomLevel(){
            int ans = 1;
            while((rand() % 2) == 0 && ans < max_level) ++ans;
            return ans;
        }
    };
}