#include<iostream>
#include<climits>

using namespace std;

class xyz{
public:
	pair <int,int> p;
	xyz(){
		p.first=10;
		p.second=20;
	}
	xyz(int a){
		p.first=a;
		p.second=40;
	}
	xyz(int a,int b){
		p.first=a;
		p.second=b;
	}
	bool operator <(xyz A){
		if(p.first < A.p.first ){
			return true;
		}
		else if(p.first == A.p.first && p.second < A.p.second){
			return true;
		}
		return false;
	}
	bool operator >(xyz A){
		if(p.first > A.p.first ){
			return true;
		}
		else if(p.first == A.p.first && p.second > A.p.second){
			return true;
		}
		return false;
	}
	bool operator ==(xyz A){
		if(p.first == A.p.first && p.second == A.p.second){
		    return true;
		}
		return false;
	}
	bool operator <=(xyz A){
		if(p.first < A.p.first ){
			return true;
		}
		else if(p.first == A.p.first && p.second < A.p.second){
			return true;
		}
		else if (p.first == A.p.first && p.second == A.p.second){
			return true;
		}
		return false;
	}
	bool operator >=(xyz A){
		if(p.first > A.p.first ){
			return true;
		}
		else if(p.first == A.p.first && p.second > A.p.second){
			return true;
		}
		else if (p.first == A.p.first && p.second == A.p.second){
			return true;
		}
		return false;
	}

};

template <class T>
class AVL{
    public:
       struct node{
        T value;
        struct node *left;
        struct node *right;
        int height;
        int sizeofRST; //size of right subtree
        int sizeofLST; //size of left subtree
       };
       typedef struct node node;
       node *root=NULL;
    	//int SIZE=0;

       node* makenode(T val){
           node *temp=(node*)malloc(sizeof(node));
           temp->value=val;
           temp->left=NULL;
           temp->right=NULL;
           temp->height=1;
           temp->sizeofLST=0;
           temp->sizeofRST=0;

           return temp;
       }

       int height_of_tree(node *root){
           int h=0;
           if(root!=NULL){
               h=max(height_of_tree(root->left),height_of_tree(root->right));
               h++;
           }
            return h;
       }

       int height_of_node(node *root){
           if(root==NULL){
               return 0;
           }
           return root->height;
       }

       int balance_factor(node *root){
           if(root==NULL){
               return 0;
           }
           int lef=height_of_node(root->left);
           int rig=height_of_node(root->right);
           return lef-rig;
       }

       void change_in_subtree(node *root){
            int l=0;
            if(root->left!=NULL){
                l=root->left->sizeofLST+root->left->sizeofRST;
                l++;
            }
            root->sizeofLST=l;
            int r=0;
            if(root->right!=NULL){
                r=root->right->sizeofLST+root->right->sizeofRST;
                r++;
            }
            root->sizeofRST=r;

       }

       node* LL_rotation(node *root){
           node *temp_r=root->left;
           node *temp=root->left->right;
           root->left=temp;
            temp_r->right=root;
            root->height=max(height_of_node(root->left),height_of_node(root->right));
            root->height+=1;
            temp_r->height=max(height_of_node(temp_r->right),height_of_node(temp_r->left));
            temp_r->height+=1;
            change_in_subtree(root);
            change_in_subtree(temp_r);
            return temp_r;
       }

       node* RR_rotation(node *root){
           node *temp_r=root->right;
           node *temp=root->right->left;
           root->right=temp;
           temp_r->left=root;
          root->height=max(height_of_node(root->left),height_of_node(root->right));
            root->height+=1;
            temp_r->height=max(height_of_node(temp_r->right),height_of_node(temp_r->left));
            temp_r->height+=1;
            change_in_subtree(root);
            change_in_subtree(temp_r);
            return temp_r;
       }

       node* LR_rotation(node *root){
           node *temp=root->left;
           root->left=RR_rotation(temp);
           return LL_rotation(root);
       }
        node* RL_rotation(node *root){
            node *temp=root->right;
            root->right=LL_rotation(temp);
            return RR_rotation(root);
        }

        node* insert_into(node *root,T key){
            if(root==NULL){
                node *temp=makenode(key);
                return temp;
            }
            else if(((root->value)>key) || ((root->value)==key)){
                root->left=insert_into(root->left,key);
            }else if((root->value)<key){
                root->right=insert_into(root->right,key);
            }
            //as new node is inserted we have to update the height of root
            int left_height=0;
            if(root->left!=NULL){
                left_height=root->left->height;
            }
            int right_height=0;
            if(root->right!=NULL){
                right_height=root->right->height;
            }
            int x=max(left_height,right_height); //height of that root
            root->height=x+1;
            int bf=balance_factor(root);
            if(bf>1){
                if(root->left){
                    if((root->left->value)>key){
                       return LL_rotation(root);
                    }else if((root->left->value)<key){
                       return LR_rotation(root);
                    }
                }
            }else if(bf<-1){
                if(root->right){
                    if((root->right->value)<key){
                       return RR_rotation(root);
                    }else if((root->right->value)>key){
                       return RL_rotation(root);
                    }
                }
            }
            change_in_subtree(root);
            return root;
        }

        node* insert(T key){
            node *temp=insert_into(root,key);
            return temp; 
        }

        node* successor(node *root){
            if(root->left==NULL)
                return root;
            if(root->left->value < root->value)
                return successor(root->left);
        }

        node* delete_from(node *root,T key){
            if(root==NULL){
                return root;
            }
            if(root->value > key){
                root->left=delete_from(root->left,key);
            }
            else if(root->value <key){
                root->right=delete_from(root->right,key);
            }
            else {
                if((root->left==NULL)&&(root->right==NULL)){
                    delete(root);     //it is a case of leaf
                    return NULL;
                }else if((root->left==NULL) || (root->right==NULL)){
                    if(root->left!=NULL){
                        node *temp=root->left;   //it is a case when it has only one child
                        delete(root);
                        return temp;
                    }else{
                        node *temp=root->right;
                        delete(root);
                        return temp;
                    }
                }
                else{
                    
                    node *temp=successor(root->right);
                    root->value=temp->value;
                    root->right=delete_from(root->right,temp->value);
                }
            }

            if(root==NULL){
               return root;
            }
            int left_height=0;
            if(root->left!=NULL){
                left_height=root->left->height;
            }
            int right_height=0;
            if(root->right!=NULL){
                right_height=root->right->height;
            }
            int x=max(left_height,right_height); //height of that root
            root->height=x+1;
            int bf=balance_factor(root);
            if(bf>1){
                    int left_bf=balance_factor(root->left);
                    if(left_bf>=0){
                       return LL_rotation(root);
                    }else if(left_bf<0){
                       return LR_rotation(root);
                    }
            }
            else if(bf<-1){
                int right_bf=balance_factor(root->right);
                if(right_bf>0){
                    return RL_rotation(root);
                }else if(right_bf<=0){
                    return RR_rotation(root);
                }
            }

        change_in_subtree(root);
        return root;

        }

        void deleted(T key){
            node *temp=delete_from(root,key);
            return;
        }

        bool search_value(node *root,T key){
            if(root==NULL){
                return false;
            }
            if(root->value==key){
                return true;
            }else if((root->value)>key){
                return search_value(root->left,key);
            }
            return search_value(root->right,key);
        }

        bool search(T key){
            bool ans=search_value(root,key);
            return ans;
        }

        void lower_bound_val(node *root,T key,node *&temp){
            if(root==NULL){
                    return;
            }
            if(root->value >=key){
                temp=root;
                lower_bound_val(root->left,key,temp);
            }else{
                lower_bound_val(root->right,key,temp);
            }
        
        }

        void lower_bound(T key){
            node *temp=NULL;
            lower_bound_val(root,key,temp);
            if(temp){
                cout<<temp->value;
            }else{
                cout<<"does not exist";
                exit(0);
            }

        }

        void upper_bound_val(node *root,T key,node *&temp){
            if(root==NULL){
                return;
            }
            if(root->value > key){
                temp=root;
                upper_bound_val(root->left,key,temp);
            }else{
                upper_bound_val(root->right,key,temp);
            }
        }

         void upper_bound(T key){
            node *temp=NULL;
            upper_bound_val(root,key,temp);
            if(temp){
                cout<<temp->value;
            }

        }

        void count_occur(node *root,T key,int &occ){
            if(root==NULL){
                return;
            }
            if(key<=root->value){
                if(key==root->value){
                     occ++;
                }
                count_occur(root->left,key,occ);
            }else if(key>root->value){
                count_occur(root->right,key,occ);
            }
        }

        int count(T key){
            bool ans=search(key);
            if(!ans){
                return 0;
            }
            int occ=0;
            count_occur(root,key,occ);

            return occ;

        }

        node* kthLargest_val(node *root,int &k){
            if(root==NULL){
                return root;
            }
            if(k==0){
                return root;
            }
            int sidhe=root->sizeofRST;
            if(k-1==sidhe){
                return root;
            }
            if(k<=sidhe){
                return kthLargest_val(root->right,k);
            }
            k=k-1-sidhe;
                return kthLargest_val(root->left,k);
            
        }

        T kthLargest(int k){
            node *temp=kthLargest_val(root,k);
             if(temp!=NULL){
                return temp->value;
            }else{
                cout<<"not exist";
                exit(0);
            }
        }

        void closest_value(node *root,T key,T &min_diference,T &answer){
            if(root==NULL){
                    return;
            }
            if(key==root->value){
                answer=root->value;
                return;
            }
            int sh=abs((root->value)-key);
            if(sh<min_diference){
                min_diference=sh;
                answer=root->value;
            }

            if(key > root->value){
                closest_value(root->right,key,min_diference,answer);
            }else{
                closest_value(root->left,key,min_diference,answer);
            }
        }

        T closest(T key){
            T min_diference=INT_MAX;
            T answer;
            closest_value(root,key,min_diference,answer);
            return answer;
        }

        void count_lesser(node *root,T first,int &total_time){
            if(root!=NULL){
                count_lesser(root->left,first,total_time);
                if(root->value<=first){
                    total_time++;
                }
                count_lesser(root->right,first,total_time);
            }
        }


        int count_in_range(T first,T second){
            bool first_mila=search(first);
            bool second_mila=search(second);
            int count_first=0;
            count_lesser(root,first,count_first);
            int count_second=0;
            count_lesser(root,second,count_second);
            int itne_h_range=count_second-count_first;
            if(first_mila==true && second_mila==true){
                itne_h_range++;
            }
            if(first_mila==true && second_mila==false){
                itne_h_range++;
            }
            return itne_h_range;

        }
        
        void inorder(node *root){
	    if(root){
			inorder(root->left);
			
			cout<<root->value<<" ";
			inorder(root->right);
		}
	}
	void preorder(node* root){
	    if(root){
	        cout<<root->value<<" ";
	        preorder(root->left);
	        preorder(root->right);
	    }
	}
    
};


int main(){
    
    AVL<int> tree;
    int a,b,c;
    cin>>a>>b>>c;
    tree.root=tree.insert(a);
    tree.root=tree.insert(b);
    tree.root=tree.insert(c);
    cin>>a>>b>>c;
    tree.root=tree.insert(a);
    tree.root=tree.insert(b);
    tree.root=tree.insert(c);
    cin>>a>>b>>c;
    tree.root=tree.insert(a);
    tree.root=tree.insert(b);
    tree.root=tree.insert(c);
    cin>>a>>b>>c;
    tree.root=tree.insert(a);
    tree.root=tree.insert(b);
    tree.root=tree.insert(c);
    tree.inorder(tree.root);
    cout<<endl;
    int k,l,h;
    int t;
    cin>>t;
    
    
    switch(t){
        case 1:cin>>a;
        tree.root=tree.insert(a);
        tree.inorder(tree.root);
        break;
        
        case 2:cin>>k;
        while(tree.search(k)){
            tree.deleted(k);
        }
        tree.inorder(tree.root);
        break;
        
        case 3:cin>>k;
        cout<<tree.search(k);
        break;
        
        case 4:cin>>k;
        cout<<tree.count(k);
        break;
        
        case 5:cin>>k;
        tree.lower_bound(k);
        break;
        
        case 6:cin>>k;
        tree.upper_bound(k);
        break;
        
        case 7:cin>>l>>h;
        cout<<tree.count_in_range(l,h);
        break;
        
        case 8:cin>>k;
        cout<<tree.kthLargest(k);
        break;
        
        case 9:cin>>k;
        cout<<tree.closest(k);
        break;
        
    }
    return 0;
}
