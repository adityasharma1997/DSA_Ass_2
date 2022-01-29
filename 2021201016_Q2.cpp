#include<bits/stdc++.h>
using namespace std;

#define prime 31
#define sized 100003

template <class X, class Y>
class unordered_Map{
    public:
    Y v[sized];
    long long int size_value=0;
        class node{
     public:
		X key;
		Y value;
		node *next;
	};
    node *arr[sized];
    unordered_Map(){
        for(int i=0;i<sized;i++){
            arr[i]=NULL;
        }
    }
    long long int hashfunction(X key){
        ostringstream s;
        s << key;
        string t=s.str();
       // string s=to_string(key);
        long long int hash_val=0;
        long long int mul=1;

        //calculating hash value 
        //for xyz= ascii value of x* 31^0 +ascii value of y* 31^1 and so on
        
        for(long int i=0;i<t.size();i++){
            hash_val=hash_val+(mul*t[i]);
            hash_val=hash_val%sized;
            mul=mul*prime;
        }
        return hash_val;
    }

    node* getNode(X key,Y value){
    	node *temp=new node();
    	temp->key=key;
    	temp->value=value;
    	temp->next=NULL;
    	return temp;
    }

    void insert(X key,Y value){
        long long int id =hashfunction(key);
        node *head=arr[id];
        if(head==NULL){
            node *temp=getNode(key,value);
            arr[id]=temp;
            return;
        }
        else{
            while(head->next!=NULL){
                if((head->key==key)&&(head->value==value)){
                    return;
                }
                if(head->key==key){
                    head->value=value;
                    return;
                }
                head=head->next;
            }
            if(head->key==key){
                if(head->value==value){
                    return;
                }    
                else{
                    head->value=value;
                    return;
                }
            }else{
                node *temp=getNode(key,value);
                head->next=temp;
            }
        }
        size_value++;
    }

    void erase(X key){
        long long int id =hashfunction(key);
        node *head=arr[id];
        node *temp=NULL;
        node *prev=NULL;
        if(head==NULL){
            cout<<"no element is present";
          return;
        }
        if(head->key==key){   //1st node
            temp=head;
            head=head->next;
            arr[id]=head;
            delete(temp);
            return;
        }
        while(head->next!=NULL){   //middle node
            if(head->key==key){
                temp=head;
                prev->next=head->next;
                delete(temp);
                return;
            }else{
                prev=head;
                head=head->next;
            }
        }
        if(head->key==key){   //last node
            temp=head;
            prev->next=head->next; //null will be stored
            delete(temp);
        }else{
            cout<<"reach at last but no such key is present";
        }
        size_value--;
        return;
    }

    bool find(X key){
        long long int id =hashfunction(key);
        node *head=arr[id];
        if(head==NULL){
            return false;
        }
        while(head!=NULL){
            if(head->key==key){
                return true;
            }else{
                head=head->next;
            }
        }
        return false;
    }

    Y operator[](X key){
        long long int id =hashfunction(key);
        node *head=arr[id];
        if(head==NULL){
            static Y t2;
            insert(key, t2);
            cout<<t2;
            return t2;
        }
        while(head!=NULL){
            if(head->key==key){
                return head->value;
            }else{
                head=head->next;
            }
        }
    }

    void print(){
        long long int i=0;
        while(i<sized){
            node *temp=arr[i];
            if(temp==NULL){
                i++;
                continue;
            }
            
            while(temp!=NULL){
                cout<<temp->key<<" is the key and it's value is "<<temp->value;
                temp=temp->next;
            }
            cout<<endl;
            i++;
        }
        
    }

    void counting(int k){
        for(long long int i=0;i<sized-k;i++){
            int z=0;
            for(int j=i;j<k;j++){
            node *temp=arr[j];
            
            while(temp!=NULL){
                v[z++]=temp->value;
                temp=temp->next;
              }
              
            }
        
            int count=0;
            for(int x=0;x<z;x++){
                int q=0;
                for(int y=x+1;y<z;y++){
                   if(v[y]==v[x]){
                       q=1;
                       break;
                   } 
                }
                if(q==0){
                    count++;
                }
            }
            cout<<count<<" ";
        }
    }
    
    

};

int main(){
    unordered_Map<string,string>um;
    um.print();
    
    string a,b;
    string k;
    int test;
    cin>>test;
    while(test--){
        int c;
    cin>>c;
    switch(c){
        case 1:
        cin>>a>>b;
        um.insert(a,b);
       // um.print();
        break;
        
        case 2:
        
        cin>>k;
        if(um.find(k)){
            cout<<"true";
        }else{
            cout<<"false";
        }
        cout<<endl;
        break;
        
        case 3:
        
        cin>>k;
        um.erase(k);
        break;
        
        case 4:
        cin>>k;
        cout<<um[k];
        break;
        
        
        // case 5:
        // um.counting(1);
        // break;
        
         }
    }


  

    return 0;
}





