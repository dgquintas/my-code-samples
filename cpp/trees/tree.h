#include <iostream>
#include <vector>

template<typename K, typename V>
    class Node {
        public: 
            Node(K key, V value)
                : _key(key), _value(value) {}

            K key() const { return _key; }
            V value() const { return _value; }

            K& key() { return _key; }
            V& value() { return _value; }

            friend std::ostream& operator<<(std::ostream& out, Node<K,V>& n){
                out << "Node(" << n.key() << ", " << n.value() << ")";
                return out;
            }

        private:
            K _key;
            V _value;
    };


template<typename K, typename V>
    class Tree {
        public:
            Tree() 
                : _root(NULL), _left(NULL), _right(NULL) {};

            Tree<K,V>* left(){ return this->_left; }
            Tree<K,V>* right() { return this->_right; }

            void add(const K& key, const V& value);
            V& search(const K& key) const;
            std::vector<V> sorted() const;
        private:
            Node<K,V>* _root; 
            Tree<K,V>* _left;
            Tree<K,V>* _right;

    };


template<typename K, typename V>
    void Tree<K,V>::add(const K& key, const V& value){
        // is it the first element?
        if( ! _root ){
            _root = new Node<K,V>(key, value);
            return;
        }

        Tree<K,V>* dst = NULL;
        if( key < _root->key() ){
            if( !_left ){
                _left = new Tree<K,V>();
            }
            dst = _left;
        }
        else {
            if( !_right){
                _right = new Tree<K,V>();
            }
            dst = _right;
        }
        dst->add(key, value);
        return;
    }


template<typename K, typename V>
    V& Tree<K,V>::search(const K& key) const {
        if( !_root ){
            //XXX
    }

template<typename K, typename V>
    std::vector<V> Tree<K,V>::sorted() const {
    }


