// range heap example
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main () {
  int myints[] = {10,20,30,5,15};
  vector<int> v(myints,myints+5);
  vector<int>::iterator it;

  cout << "before heap" << endl;
  for (unsigned i=0; i<v.size(); i++) cout << " " << v[i];
  cout << endl;
  make_heap (v.begin(),v.end());
  cout << "initial max heap   : " << v.front() << endl;
  cout << "after heap" << endl;
  for (unsigned i=0; i<v.size(); i++) cout << " " << v[i];
  cout << endl;

  cout << "max heap before pop : " << v.front() << " " << v.back() << endl;
  for (unsigned i=0; i<v.size(); i++) cout << " " << v[i];
  cout << endl;
  pop_heap (v.begin(),v.end()); 
  cout << "max heap after pop_heap : " << v.front() << " " << v.back() << endl;
  for (unsigned i=0; i<v.size(); i++) cout << " " << v[i];
  cout << endl;
  v.pop_back();
  cout << "max heap after pop_back : " << v.front() << " " << v.back() << endl;
  for (unsigned i=0; i<v.size(); i++) cout << " " << v[i];
  cout << endl;

  cout << "max heap before push: " << v.front() << " " << v.back() << endl;
  for (unsigned i=0; i<v.size(); i++) cout << " " << v[i];
  cout << endl;
  v.push_back(99); 
  cout << "max heap after push_back: " << v.front() << " " << v.back() << endl;
  for (unsigned i=0; i<v.size(); i++) cout << " " << v[i];
  cout << endl;
  push_heap (v.begin(),v.end());
  cout << "max heap after push_heap: " << v.front() << " " << v.back() << endl;
  for (unsigned i=0; i<v.size(); i++) cout << " " << v[i];
  cout << endl;

  sort_heap (v.begin(),v.end());

  cout << "final sorted range :";
  for (unsigned i=0; i<v.size(); i++) cout << " " << v[i];

  cout << endl;

  return 0;
}
