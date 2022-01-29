#include <iostream>
using namespace std;

template <typename T>

class Deque{
    public:
    int size=0;
    int cap=10000;
    int head=-1;
    int tail=-1;
    T *arr;
        void deque(){
            size=0;
            arr=new T[cap];
        }

         void deque(int n, T x){
			cap=n*2;
			size=n;
			arr=new T[cap];
			head=0;
            tail=n-1;
            for(int i=0;i<n;i++){
                arr[i]=x;
            }
		}

        void push_back(T x){
            if(size==0){
                head=0;
                tail=0;
                arr[tail]=x;
            }
            if(size!=cap){
                tail=(tail+1)%cap;
                arr[tail]=x;
            }else{
                int prev=cap;
                T *temp=new T[2*cap];
                int k=0;
                for(int i=head;k<size;k++){
                    temp[k]=arr[i];
                    i=(i+1)%prev;
                }
                cap=cap*2;
                head=0;
                tail=size-1;
                delete(arr);
                arr=temp;
                tail++;
                arr[tail]=x;
            }
            size++;
        }


        void push_front(T x){
            if(size==0){
                head=0;
                tail=0;
                arr[head]=x;
            }
            if(size!=cap){
                head=(head-1+cap)%cap;
                arr[head]=x;
            }else{
                int prev=cap;
                T *temp=new T[2*cap];
                int k=0;
                for(int i=head;k<size;k++){
                    temp[k]=arr[i];
                    i=(i+1)%prev;
                }
                cap=cap*2;
                tail=size-1;
                head=cap-1;
                delete(arr);
                arr=temp;
                arr[head]=x;
            }
            size++;
        }

        T pop_back(){
            if(size!=0){
                string result=arr[tail];
                tail=(tail-1+cap)%cap;
                size--;
                if(size==0){
                    head=-1;
                    tail=-1;
                }
                return result;

            }
            cout<<"nothing to be printed as size is already zero";
            exit(0);
        }

        T pop_front(){
            if(size!=0){
                string result=arr[head];
                head=(head+1)%cap;
                size--;
                if(size==0){
                    head=-1;
                    tail=-1;
                }
                return result;
            }
            cout<<"nothing to be printed as size is already zero";
            exit(0);
        }

        T front(){
            if(size!=0){
                return arr[head];
            }
            cout<<"no element is there";
            exit(0);
        }

        T back(){
            if(size!=0){
                return arr[tail];
            }
            cout<<"no element is there";
            exit(0);
        }

        bool empty(){
            if(size==0){
                return true;
            }
            return false;
        }

        int sized(){
            return size;
        }


        void resize(int x, T d){
            if(x<size){
                int extra=size-x;
                while(extra>0){
                    pop_back();
                    extra--;
                }
            }else if(x>size){
                int lesser=x-size;
                while(lesser>0){
                    push_back(d);
                    lesser--;
                }
            }
            size=x;
        }

        void clear(){
            size=0;
            head=-1;
            tail=-1;
            delete[] arr;
            cap=1000;
            arr= new T[cap];
        }

        T operator[](int n){
            if(n<=size){
                int res=(head+n-1)%cap;
             return arr[res];
                
            }
            
            cout<<"not in bound";
            exit(0);
        }
        void print(){
            if(size!=0){
                int k=0;
                for(int i=head;k<size;k++){
                    cout<<arr[i]<<" ";
                    i=(i+1)%cap;
                }
            }else{
                cout<<"size is zero";
            }
        }


};

int main(){
   
   Deque<string> dq;
    string x;
    int n;
    // dq.deque(5,x);
    // dq.print();
    
   
    int a;
    string b;
    cin>>a>>b;
    dq.deque(a,b);
    dq.print();
    cout<<endl;
    cout<<dq.sized();
    //dq.clear();
   // cout<<dq.empty();
     int c;
     cin>>c;
    int t;
    string newt;
    int find;
   
        switch(c){
            case 1:dq.deque();  //blank deque case

            dq.print();
            break;
            
            case 2:cin>>n>>x;   //deque with size n case
            dq.deque(n,x);
            dq.print();
            cout<<endl;
            cout<<dq.sized();
            break;
            
            case 3:cin>>x;    //push_back case
            dq.push_back(x);
            dq.print();
            cout<<endl;
            cout<<dq.sized();
            break;
            
            case 4:cin>>x;   //push_front case
            cout<<endl;
            dq.push_front(x);
            dq.print();
            cout<<endl;
            cout<<dq.sized();
            //  cin>>find;
            //  cout<<dq[find];
            dq.clear();
            cout<<dq.empty();
            // dq.clear();
            // dq.print();
            // cout<<dq.sized();
            // cout<<endl;
            // cout<<dq.front();
            // cout<<endl;
             //cout<<dq.back();
           
            
            
            break;
            
            case 5:
            cout<<dq.pop_front();  //pop front
            cout<<endl;
            cout<<dq.sized();
            break;
            
            case 6:
            cout<<dq.pop_back();  //pop back
            cout<<endl;
            cout<<dq.sized();
            break;
            
          case 7:
          cout<<dq.empty();    //empty case of deque
           break;
           
            case 8:
            cout<<dq.front();
            break;
            
        case 9:
        cout<<dq.back();
        break;
        
         case 10:   //resize function
         cin>>t>>newt;
            cout<<endl;
            dq.resize(t,newt);
            dq.print();
            break;
            
            case 11:
            dq.clear();
            break;
        
        
        case 12:
        cin>>find;
            cout<<dq[find];
            break;
        
        
        }
        return 0;
   
   
}