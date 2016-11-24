#include <cstdio>
#include <cstring>
#include <climits>


using namespace std;

#define MAX_N 200

int map[MAX_N][MAX_N], A_adjacents_weights[MAX_N];
bool A[MAX_N], merged[MAX_N];

int stoer_wagner_it(int n){
  int best_min_cut = INT_MAX;
  int cut_of_the_phase, s, t, z;

  // ninguno esta mergeado salvo el inicial
  memset(merged, false, sizeof(merged));
  merged[0] = true; 

  for(int phase=1; phase < n; phase++){
    // MINUMUM CUT PHASE 
    // si no fue mergeado tengo que marcarlo como false en A e iniciar los pesos adyacentes
    A[0] = true;
    for(int i=1; i < n; i++){
      if(!merged[i]){
        A[i] = false;
        A_adjacents_weights[i] = map[0][i];
      }
    }
  
    // Necesito (V - 1(porque ya tengo [0])- el numero de mergeados) iteraciones para que A = V
    for(int i=n-phase-1; i >= 0; i--){
  
      z = -1;
  
      //busco z
      for(int j=1; j < n; j++)
        if(!A[j] && ( z == -1 || A_adjacents_weights[j] > A_adjacents_weights[z]))
          z = t = j;
  
      //agrego z a A
      A[z] = true;
  
      // actualizo los pesos adyacentes a A porque este crecio y me guardo el anterior, solo tiene sentido sino es el ultimo
      if(i > 0){
        s = t;
  
        for(int j=1; j < n; j++)
          if(!A[j]) 
            A_adjacents_weights[j] += map[z][j];
      }
    }
  
    // Termino todo tengo que mergear s y t
    for(int i=0; i < n; i++){
      map[i][s] += map[t][i];
      map[s][i] += map[t][i];
    }
    merged[t] = true;
    cut_of_the_phase = A_adjacents_weights[t];
    // MINUMUM CUT PHASE END


    if(best_min_cut > cut_of_the_phase){
      best_min_cut = cut_of_the_phase;
    }
  }

  return best_min_cut;
}

int main(){
  int total_cases, n, m, city_1, city_2, bombing_cost;

  scanf("%d", &total_cases);

  for(int ccase = 1; ccase <= total_cases; ccase++){

    memset(map, 0, sizeof(map));

    scanf("%d %d", &n, &m);

    for(int i=0; i < m; i++){
      scanf("%d %d %d", &city_1, &city_2, &bombing_cost);

      city_1--;
      city_2--;

      map[city_1][city_2] += bombing_cost;
      map[city_2][city_1] += bombing_cost;
    }

    printf("Case #%d: %d\n", ccase, stoer_wagner_it(n));
  }

  return 0;
}