#include <string>
#include <vector>
#include <limits>
#include <iostream>
#include "minmax.h"
#include "curve.h"
#include "update.h"
#include "distance_ops.h"

using namespace std;

int find_second_best(real_curve * tempC, int y,
  vector<real_curve*> & centroids, string dist){

  double min_dist{std::numeric_limits<int>::max()},min_dist2;
  int index{-1};
  for(unsigned int i=0; i<centroids.size(); i++){
    if((int)i==y || centroids[i]==nullptr) continue;//don't check it's real centroid
    find_distance(tempC->get_points(), centroids[i]->get_points(),
      dist, min_dist2);
    if(min_dist>min_dist2){
      min_dist = min_dist2;
      index = i;
    }
  }
  return index;
}

void compute_silhuette(vector<real_curve *> & centroids,
  vector<vector<real_curve *>> & assignment, string dist,
  vector<double> & Si, double & Stotal){

  Si.clear();
  if(centroids.size()==1){
    Si.push_back(1);//in case we have one cluster silhuette=1
    return ;
  }
  Stotal = 0.0;
  double objA, objB, clusterS;
  int sec_best;
  for(unsigned int i=0; i<centroids.size(); i++){
    clusterS = 0.0;
    if(centroids[i]==nullptr){Si.push_back(clusterS); continue;cout << "B"<<endl;}
    for(unsigned int j=0; j<assignment[i].size(); j++){
      objA = compute_objective(assignment[i][j], assignment[i], dist)/assignment[i].size();//a(i)
      sec_best = find_second_best(assignment[i][j], i, centroids, dist);
      if(sec_best != -1){
        objB = compute_objective(assignment[i][j], assignment[sec_best], dist)/assignment[sec_best].size();//b(i)
        clusterS += (objB - objA)/MYmax(objA,objB);//s(i)
      }
      else 
        clusterS += 1;      
    }
    clusterS=clusterS/assignment[i].size();//normalized in [-1,1]
    Si.push_back(clusterS);
    Stotal += clusterS;
  }
  Stotal = Stotal/centroids.size();//also normalized in [-1,1]
}
