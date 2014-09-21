#include <iostream>
#include "avltree.h"
using namespace std;
int main(){
  avltree<int> avlt;
  avltree<int>::node *avltn=0;
  int c=1,n;
  cout<<"\nEnter:\n1 to add\n2 to delete\n3 to print\n0 to exit\n\n";
  while(c!=0){
    cout<<"\n#>";
    cin>>c;cout<<endl;
    if(c==1){
      cout<<"New:\n";cin>>n;
      avlt.insert(n);
    }else if(c==2){
      cout<<"Remove:\n";cin>>n;
      avltn=avlt.find(n);
      if(!avltn){
        cout<<n<<" not found!\n";
        continue;
      }
      avlt.remove(avltn);
      cout<<"Removed "<<n<<"!\n";
    }else if(c==3){
      avlt.print();
    }
  }
  cout<<"You chose to exit.\n";
  return 0;
}
