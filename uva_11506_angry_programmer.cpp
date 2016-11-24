// Angry Programmer: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2501
#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <vector>

using namespace std;

typedef vector<int> vi;

#define INF 1e9
#define MAX_MACHINES 200

int network[MAX_MACHINES][MAX_MACHINES], p[MAX_MACHINES], m, w, total_vertex, boss_m, server_m;
vector<vi> AdjList;
bool visited[MAX_MACHINES];


int augment_path(int v, int min_flux){

  if(v != boss_m)
  {
    min_flux = augment_path(p[v], min(min_flux, network[p[v]][v]));

    network[v][p[v]] += min_flux;
    network[p[v]][v] -= min_flux;
  } 
  
  return min_flux;
}

int edmond_karp() {
  int max_flow = 0, u, v;
  while (true) {

    memset(p, -1, sizeof(p));

    for(int i=1;i < total_vertex;i++) visited[i] = false;
    visited[boss_m] = true;

    queue<int> q;
    q.push(boss_m);

    while (!q.empty()){
      u = q.front();
      q.pop();

      if (u == server_m) break;

      for (int i = 0; i < (int) AdjList[u].size(); i++) {
        v = AdjList[u][i];
  
        if (network[u][v] > 0 && !visited[v]) {
          visited[v] = true;
          q.push(v);
          p[v] = u;
        } 
      }
    }

    if(u != server_m) break;

    max_flow += augment_path(server_m, INF);
  }

  return max_flow;
}

void add_machine(int id_m, int cost){
  int sm = id_m + id_m - 1;
  int tm = sm + 1;

  network[sm][tm] = cost;
  AdjList[sm].push_back(tm);
  AdjList[tm].push_back(sm);
}

void add_wire(int id_m1, int id_m2, int cost){
  int su, tu, sv, tv;

  if(id_m1 != boss_m && id_m1 != m-1)
  {
    su = id_m1 + id_m1-1;
    tu = su + 1;
  }
  else
  {
    (id_m1 == boss_m) ? (su = tu = boss_m) : (su = tu = server_m);
  }

  if(id_m2 != boss_m && id_m2 != m-1)
  {
    sv = id_m2 + id_m2 -1;
    tv = sv + 1;
  }
  else
  {
    (id_m2 == boss_m) ? (sv = tv = boss_m) : (sv = tv = server_m);
  }

  AdjList[tu].push_back(sv);
  AdjList[sv].push_back(tu);
  network[tu][sv] = cost;
  
  AdjList[tv].push_back(su);
  AdjList[su].push_back(tv);
  network[tv][su] = cost;
}

int main(){
  int id_m, id_m1, id_m2, cost;

  while(true){

    scanf("%d %d", &m, &w);

    if(m == 0 && w == 0) break;

    total_vertex = m*2-2;

    boss_m   = 0;
    server_m = total_vertex - 1;

    memset(network, 0, sizeof(network));
    AdjList.assign(total_vertex, vi());

    for(int i=0; i < m-2; i++){
      scanf("%d %d", &id_m, &cost);
      add_machine(--id_m, cost);
    }

    for(int i=0; i < w; i++){
      scanf("%d %d %d", &id_m1, &id_m2, &cost);
      add_wire(--id_m1, --id_m2, cost);
    }

    printf("%d\n", edmond_karp());
  }


  return 0;
}