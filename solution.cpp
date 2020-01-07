#include <iostream>
#include <vector>
#include <map>
#include <limits.h>
#include <algorithm>
using namespace std;
#define NIL 0
#define INF INT_MAX 

bool DFS(int actress, vector<vector<int>>& actresses, vector<int>& pairActresses, vector<int>& pairActors, vector<int>& dist) {
  if (actress == NIL) {
    return true;
  }
  for (int i = 0; i < actresses[actress].size(); i++) {
    int actor = actresses[actress][i]; 
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
  vector<int> pairActresses, pairActors = {};
  for (int i = 0; i < actresses.size(); i++) {
    pairActresses.push_back(NIL);
    pairActors.push_back(NIL);
  }
  int matching = 0;
  vector<int> dist(actresses.size());
  while (BFS(actresses, pairActresses, pairActors, dist)) {
    for (int actress = 1; actress < actresses.size(); actress++) {
      if (pairActresses[actress] == NIL && DFS(actress, actresses, pairActresses, pairActors, dist)) {
        matching++;
      }
    }

  }
  return matching;
}

void input(vector<vector<int>>& U) {
  U.push_back({});
  int nrActors, nrMovies;
  cin >> nrActors >> nrMovies;
  map<string, int> actresses, actors;// map of names to indexes
  string actress;
  for (int i = 1; i < nrActors + 1; i++) {
    cin >> actress;
    actresses[actress] = i;
    U.push_back({});
  }
  string actor;
  for (int i = 1; i < nrActors + 1; i++) {
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
  int m = HopcroftKarp(actresses);
  if (m == actresses.size() - 1 ) {
    cout << "Mark" << endl;
  } else {
    cout << "Veronique" << endl;
  }
  return 0;
}