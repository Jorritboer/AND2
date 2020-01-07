#include <iostream>
#include <limits.h>
#include <vector>
#include <map>
#include <algorithm>
#define NIL 0
#define INF INT_MAX

using namespace std;

int hopcroftKarp(vector<vector<int>> actresses) {
  vector<int> pairActresses(actresses.size());
  vector<int> pairActors(actresses.size());
  vector<int> dist(actresses.size());
  for (int i = 0; i < actresses.size(); i++){
    pairActors[i] = NIL;
    pairActresses[i] = NIL;
  }
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
  for (int i = 0; i < actresses.size(); i++){
    cout << "Actress " << i << ": ";
    for (int j = 0; j < actresses[i].size(); j++) {
      cout << actresses[i][j];
    }
    cout << endl;
  }
  hopcroftKarp(actresses);
  return 0;
}