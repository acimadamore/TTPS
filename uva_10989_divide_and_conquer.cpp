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

  // El único vertice mergeado es el inicial
  memset(merged, false, sizeof(merged));
  merged[0] = true; 

  for(int phase=1; phase < n; phase++){
    
    // MINUMUM CUT PHASE - BEGIN

    // Si un vertice no fue mergeado a un tengo que marcar que no pertenece a A e inicializar la distancia desde el inicial
    A[0] = true;
    for(int i=1; i < n; i++){
      if(!merged[i]){
        A[i] = false;
        A_adjacents_weights[i] = map[0][i];
      }
    }
  
    // (V - 1(porque ya tengo [0]) - el numero de mergeados) iteraciones para que A = V
    for(int i=n-phase-1; i >= 0; i--){
  
      z = -1;
  
      // Buscar z tal que no pertenece a A y es el que tiene mas peso adyacente a A
      for(int j=1; j < n; j++)
        if(!A[j] && ( z == -1 || A_adjacents_weights[j] > A_adjacents_weights[z]))
          z = t = j;
  
      // Agregar z a A
      A[z] = true;
  
      // Si no es la última iteracion debo actualizar los pesos de todos los adyacentes a A porque este creció
      // y guardarme en s el z recién agregado a A para hacer la combinación de los dos últimos vertices agregados a A
      // al finalizar todas las iteraciones 
      if(i > 0){
        s = t;
  
        for(int j=1; j < n; j++)
          if(!A[j]) 
            A_adjacents_weights[j] += map[z][j];
      }
    }
  
    // Merge de s y t, los dos ultimos vertices agregados a A y actualización de las aristas de estos
    for(int i=0; i < n; i++){
      map[i][s] += map[t][i];
      map[s][i] += map[t][i];
    }
    merged[t] = true;
    
    // El "cut of the phase" corresponde corresponde al peso de A al último vertice agregado t
    cut_of_the_phase = A_adjacents_weights[t];
    

    // MINUMUM CUT PHASE - END

    // El minimo corte es el menor "cut of the phase" de todas las fases.
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