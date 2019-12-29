#include <iostream>
#include <vector>
#include <map>
using namespace std;
#define NIL 0
#define INF 100000 // practically infinite in this case because maximum of 1000 movies.

/*
G = U ∪ V ∪ {NIL}
 where U and V are partition of graph and NIL is a special null vertex


function Hopcroft–Karp is
    for each u in U do
        Pair_U[u] := NIL
    for each v in V do
        Pair_V[v] := NIL
    matching := 0
    while BFS() = true do
        for each u in U do
            if Pair_U[u] = NIL then
                if DFS(u) = true then
                    matching := matching + 1
    return matching

function BFS() is
    for each u in U do
        if Pair_U[u] = NIL then
            Dist[u] := 0
            Enqueue(Q, u)
        else
            Dist[u] := ∞
    Dist[NIL] := ∞
    while Empty(Q) = false do
        u := Dequeue(Q)
        if Dist[u] < Dist[NIL] then
            for each v in Adj[u] do
                if Dist[Pair_V[v]] = ∞ then
                    Dist[Pair_V[v]] := Dist[u] + 1
                    Enqueue(Q, Pair_V[v])
    return Dist[NIL] ≠ ∞

function DFS(u) is
    if u ≠ NIL then
        for each v in Adj[u] do
            if Dist[Pair_V[v]] = Dist[u] + 1 then
                if DFS(Pair_V[v]) = true then
                    Pair_V[v] := u
                    Pair_U[u] := v
                    return true
        Dist[u] := ∞
        return false
    return true
    */

bool DFS(int actress, vector<vector<int>>& actresses, vector<int>& pairActresses, vector<int>& pairActors, vector<int>& dist) {
  if (actress == NIL) {
    return true;
  }
  for (int i = 0; i < actresses[actress].size(); i++) {
    int actor = actresses[actress][i]; 
    // cout << "For actress " << actress << ", checking actor " << actor << endl;
    if (dist[pairActors[actor]] == dist[actress] + 1) {
      if (DFS(pairActors[actor], actresses, pairActresses, pairActors, dist)) {
        pairActors[actor] = actress;
        pairActresses[actress] = actor;
        return true;
      }
    }
  }
  dist[actress] = INF;
  return false;
}

bool BFS(vector<vector<int>>& actresses, vector<int>& pairActresses, vector<int>& pairActors, vector<int>& dist) {
  vector<int> queue;
  for (int actress = 1; actress < actresses.size(); actress++){
    if (pairActresses[actress] == NIL) { // meaning this actress doesn't yet have a match
      dist[actress] = 0;
      queue.push_back(actress);
    } else {
      dist[actress] = INF; 
    }
  }
  dist[NIL] = INF;
  while(!queue.empty()) {
    int actress = queue.front();
    queue.erase(queue.begin());
    if (dist[actress] < dist[NIL]) {
      for (int i = 0; i < actresses[actress].size(); i++) {
        int actor = actresses[actress][i];
        if (dist[pairActors[actor]] == INF) {
          dist[pairActors[actor]] = dist[actress] + 1;
          queue.push_back(pairActors[actor]);
        }
      }
    }
  }
  return dist[NIL] != INF;
}
int HopcroftKarp(vector<vector<int>> actresses) {
  vector<int> empty = {};
  actresses.insert(actresses.begin(), empty);
  vector<int> pairActresses, pairActors = {};
  for (int i = 0; i < actresses.size(); i++) {
    pairActresses.push_back(NIL);
    pairActors.push_back(NIL);
  }
  int matching = 0;
  vector<int> dist(actresses.size());
  while (BFS(actresses, pairActresses, pairActors, dist)) {
    // for (int i = 0; i < dist.size(); i++ ) {
    //   cout << "i: " << i << ", dist: " << dist[i] << ", pairActresses[i]:" << pairActresses[i] << ", pairActors[i]: " << pairActors[i] << ", dist[i]: " << dist[i] << endl;
    // }
    for (int actress = 1; actress < actresses.size(); actress++) {
      if (pairActresses[actress] == NIL && DFS(actress, actresses, pairActresses, pairActors, dist)) {
        matching++;
      }
    }

  }
  return matching;
}

void input(vector<vector<int>>& U) {
  int nrActors, nrMovies;
  cin >> nrActors >> nrMovies;
  map<string, int> actresses, actors;// map of names to indexes
  string actress;
  for (int i = 0; i < nrActors; i++) {
    cin >> actress;
    actresses[actress] = i;
    U.push_back({});
  }
  string actor;
  for (int i = 0; i < nrActors; i++) {
    cin >> actor;
    actors[actor] = i;
  }
  for (int m = 0; m < nrMovies; m++) {
    string movie;
    cin >> movie;
    int s;
    cin >> s;
    vector<int> actorsInMovie;
    vector<int> actressesInMovie;
    for (int n = 0; n < s; n++) {
      string name;
      cin >> name;
      map<string,int>::iterator ac = actresses.find(name);
      if (ac != actresses.end()) {
        actressesInMovie.push_back(ac -> second);
      } else {
        actorsInMovie.push_back(actors[name]);
      }
    }
    for (int i = 0; i < actressesInMovie.size(); i++) {
      int actress = actressesInMovie[i];
      for (int j = 0; j < actorsInMovie.size(); j++) {
        int actor = actorsInMovie[j];
        if (find(U[actress].begin(), U[actress].end(), actor) == U[actress].end()) {
          U[actress].push_back(actor);
        }
      }
    }
  }
}

int main(int argc, char const *argv[]) {
  vector<vector<int>> actresses;
  input(actresses);
  int max = actresses.size();
  int m = HopcroftKarp(actresses);
  // cout << "Matching: " << m << ", max: " << max << endl;
  if (m == max ) {
    cout << "Mark" << endl;
  } else {
    cout << "Veronique" << endl;
  }
  return 0;
}