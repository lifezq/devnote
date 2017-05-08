#include<vector>
#include<list>
#include<deque>
#include<queue>
#include<stack>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<iostream>

using namespace std;

int main(){

    // vector : filo - no sort
    vector<int> v;
    for(int i=0;i<10;i++) v.push_back(i);

    printf("\n\nvector size:%d------------------------------\n",v.size());

    for(int i=0;i<10;i++){
        cout << "vector item:" << v.back() << " front:" << v.front() << endl;
        v.pop_back();
    }

    // list : bothway
    list<int> l;
    for(int i=0;i<10;i++)
    l.push_back(i);

    printf("\n\nlist size:%d------------------------------\n",l.size());
 
    int lfirst = l.front(); // first item 
    l.pop_front();

    l.push_front(100);

    printf("size:%d first:%d second:%d\n",l.size(), lfirst,l.front());

    for(int i=0;i<10;i++){

        cout << "q item:" << l.front() << endl;
        l.pop_front();
    }   


    // deque : bothway
    deque<int> q;
    for(int i=0;i<10;i++)
    q.push_back(i);

    printf("\n\ndeque size:%d------------------------------\n",q.size());

    int first = q.front(); // first item 
    q.pop_front();

    q.push_front(100);

    printf("size:%d first:%d second:%d\n",q.size(), first,q.front());

    for(int i=0;i<10;i++){

        cout << "q item:" << q.front() << endl;
        q.pop_front();
    }

    // queue : fifo
    queue<int> q1;
    for(int i=0;i<10;i++) q1.push(i);// fifo

    printf("\n\nqueue size:%d------------------------------\n",q1.size());
    printf("size:%d front:%d back:%d\n",q1.size(),q1.front(),q1.back());
    q1.pop();
    printf("size:%d front:%d back:%d\n",q1.size(),q1.front(),q1.back());

    // priority_queue : sorted
    priority_queue<int> qpri; // sort: big -> small
    for(int i=0;i<10;i++) 
        qpri.push(i);

    printf("\n\npriority_queue size:%d------------------------------\n",qpri.size());

    cout << "sort:big->small(default):---------------------" << endl;
    for(int i=0;i<10;i++) {
        printf("size:%d top:%d\n",qpri.size(),qpri.top());
        qpri.pop();
    }

    cout << "sort:small->big:---------------------" << endl;
    priority_queue<int, vector<int>, greater<int>> qpri01; // sort: small -> big
    for(int i=0;i<10;i++) 
        qpri01.push(i);

    for(int i=0;i<10;i++) {
        printf("size:%d top:%d\n",qpri01.size(),qpri01.top());
        qpri01.pop();
    }

    // stack : filo
    stack<int> s;
    for(int i=0;i<10;i++) s.push(i);

    printf("\n\nstack size:%d------------------------\n",s.size());
    for(int i=0;i<10;i++){
        cout << "stack item:" << s.top() << endl;
        s.pop();
    }

    // map - sort : less(default) small->big
    map<int,int> m;
    pair<map<int,int>::iterator, bool> insert_ok;
    for(int i=10;i>0;i--){
        insert_ok = m.insert(pair<int, int>(i,i));
        if(!insert_ok.second) cout << "map insert error" << endl;
    }

    printf("\n\nmap size:%d------------------------------\n",m.size());


    // for(int i=0;i<10;i++) cout << "map item:" << m[i] << endl;
    for(map<int,int>::iterator it = m.begin();it!=m.end();it++)
        cout << "map iterator item:" << it->first << "-" << it->second << endl;

    // unordered_map 
    unordered_map<int,int> um;
    pair<unordered_map<int,int>::iterator, bool> um_insert_ok;
    for(int i=10;i>0;i--){
        um_insert_ok = um.insert(pair<int, int>(i,i));
        if(!um_insert_ok.second) cout << "map insert error" << endl;
    }

    printf("\n\nunordered_map size:%d------------------------------\n",um.size());


    for(unordered_map<int,int>::iterator it = um.begin();it!=um.end();it++)
        cout << "unordered_map iterator item:" << it->first << "-" << it->second << endl;


    // multimap 
    multimap<int,int> mm;
    for(int i = 0;i<10;i++){
        for(int j=i;j<10;j++) mm.insert(pair<int,int>(j,i));
    }

    printf("\n\nmultimap size:%d------------------------\n", mm.size());
    multimap<int,int>::iterator p_map;
    pair<multimap<int,int>::iterator, multimap<int,int>::iterator> ret;

    for(p_map=mm.begin();p_map!=mm.end();){
        cout << "multimap item:" << p_map->first << "->";
        ret = mm.equal_range(p_map->first);
        for(p_map=ret.first;p_map!=ret.second;++p_map) cout << p_map->second << ",";

        cout << endl;
    }


    // set 
    set<int> ss; // sort:less
    for(int i=10;i>0;i--) ss.insert(i);
    printf("\n\nset size:%d------------------------\n", ss.size());
    set<int>::iterator siter01 = ss.begin();
    while(siter01!=ss.end()){
        cout << "set item:" << *siter01 << endl;
        siter01++;
    }


    set<char*> sss;
    sss.insert("Hello world!");
    sss.insert("Alpha...");
    sss.insert("Program...");
    set<char*>::iterator siter = sss.begin();
    while(siter!=sss.end()){
        cout << "set item:" << *siter << endl;
        siter++;
    }

    // unordered_set
    unordered_set<int> us;
    for(int i=10;i>0;i--) us.insert(i);
    printf("\n\nunordered_set size:%d------------------------\n", us.size());
    unordered_set<int>::iterator siter02 = us.begin();
    while(siter02!=us.end()){
        cout << "unordered_set item:" << *siter02 << endl;
        siter02++;
    }



    multiset<int> ms;
    for(int i=10;i>0;i--) ms.insert(i);
    for(int i=10;i>0;i--) ms.insert(i);
    printf("\n\nmultiset size:%d------------------------\n", ms.size());
    multiset<int>::iterator msiter = ms.begin();
    while(msiter!=ms.end()){
        cout << "multiset item:" << *msiter << endl;
        msiter++;
    }

    return 0;
}
