
#pragma one
#include <stack>
#include <iostream>

namespace ariel
{

  
    template <typename T>
    class BinaryTree
    {
    
        class Node
        {
            friend class BinaryTree;
            T value;
            Node *left;
            Node *right;
            Node *parent;

        public:
         
            Node(T val) : value(val), right(nullptr), left(nullptr), parent(nullptr){};
            bool operator==(Node t)
            {
                return value == t->value && left == t->left &&
                       right == t.right && parent == t->parent;
            }

            ~Node() {
                delete left;
                delete right;
                 delete parent;
            }
        };


        Node *root;
        enum SearchForm
        {
            preorder,  postorder, inorder
         
        };
        //----------------- Iterator --------------//

        class Iterator
        {
            Node *curr;
            SearchForm orderp;
            std::stack<Node *> stack;

        public:
            // constrctor
            Iterator() : curr(nullptr){};
            Iterator(const SearchForm order, Node *node=nullptr) : curr(node) ,orderp(order)
            {
                toStack(node);
                if (!stack.empty())  {  curr = stack.top();
             stack.pop(); }
            }


            void toStack(Node *node)
            { 
                if (node == nullptr) {  return;  }

                if (orderp == inorder){

                    toStack(node->right);
                    stack.push(node);
                    toStack(node->left);
                }
            
                if(orderp==postorder)  {
                    stack.push(node);
                    toStack(node->right);
                    toStack(node->left);
                }
                  if (orderp == preorder){
                    toStack(node->right);
                    toStack(node->left);
                    stack.push(node);
                }
            }
            //++i
            Iterator &operator++()
            {
                if (stack.empty())
                {
                    curr = nullptr;
                }
                else
                {
                    curr = stack.top();
                    stack.pop();
                }

                return *this;
            }
            //i++
            Iterator operator++(int){

                Iterator tmp = *this;
                if (stack.empty())  {    curr = nullptr; }
                else
                {
                    curr = stack.top();
                    stack.pop();
                              }
                return tmp;
                }
                   T *operator->() const
            {
                return &(curr->value);
            }

            T &operator*() const
            {
                return curr->value;
            }

         
            bool operator==(const Iterator &other) const
            {
      
                return curr == other.curr;
            }

            bool operator!=(const Iterator &other) const
            {
                return !(*this == other);
            }
        };




    public:
        BinaryTree<T>() : root(nullptr)
        {

        };
       ~BinaryTree() {  }
      

           void create_copy(Node * source , Node * dest) {
        if(dest->left) {
            source->left = new Node(dest->left->value);
            create_copy(source->left,dest->left);
        }
         if(dest->right) {
            source->right = new Node(dest->right->value);
            create_copy(source->right,dest->right);
        }
    }

    
             BinaryTree & operator = (const BinaryTree & from) {
     
        		if (this == &from){
				return *this;
			}
			if (root != nullptr){
				delete root;
			}
			if (from.root != nullptr){
				root = new Node{from.root->value};
				create_copy(root, from.root);
			}
			return *this;
    }
        
        
         friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &tree)
        {
            return os;
        }


    
            BinaryTree(const BinaryTree & from) {
        root = new Node(from.root->value);
        create_copy(root,from.root);
    }
    

      
     
          BinaryTree<T> &add_root(const T &val){
            if(this->root == nullptr){
                Node *r = new Node{val};
                this->root = r;
                return *this;
            }
            this->root->value = val;
            return *this;}

  
                Node *found_node(Node *root,const T &val){
            if(root == nullptr) return nullptr;
            if(root->value == val){return root;}
            Node *ans = found_node(root->left,val);
            if(ans != nullptr) return ans;
            return found_node(root->right,val); 
        }

     
            BinaryTree & add_left(const T & parent , const T & child) {
        if(!root) {throw std::invalid_argument{" tree is empty"};}
        // find the parent of the candiate child
        Node* found = found_node(root,parent);
        if (!found) {throw std::invalid_argument{" parent not found"};}
        if (found->left == nullptr) {found->left = new Node(child); return *this;}
        found->left->value=child;
        return *this;
    }

   
            BinaryTree & add_right(const T & parent , const T & child) {
       if(!root) {throw std::invalid_argument{" tree is empty"};}
        // find the parent of the candiate child
        Node* found = found_node(root,parent);
        if (!found) {throw std::invalid_argument{" parent not found"};}
        if (found->right == nullptr) {found->right = new Node(child); return *this;}
        found->right->value=child;
        return *this;
    }

        Iterator begin()
        {
            return Iterator{inorder,root};
        };
        Iterator end()
        {
            return Iterator{inorder,nullptr};
        };
        Iterator begin_preorder()
        {
            return Iterator{preorder,root};
        }
        Iterator end_preorder()
        {

            return Iterator{preorder,nullptr};
        }
           Iterator begin_inorder()
        {
            return Iterator{inorder, root};
        }
    
        Iterator end_inorder()
        {

            return Iterator{inorder, nullptr};
        }
          Iterator begin_postorder()
        {
            return Iterator{ postorder, root};
        }
     
        Iterator end_postorder()
        {
            return Iterator{ postorder, nullptr};
        }
      
    };
}