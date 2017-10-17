#include <vector>
#include <string>
#include <array>
#include <limits>
#include "curve.h"
#include "rand_utils.h"

using namespace std;

void init_r(int dimension,std::vector<int> & r){
    for(int i=0; i< dimension; i++)
      r.push_back(int_uniform_rand(0,1000000));//idk the [M,N]
    return ;
}

void linear_combination(const vector<int> & cur_points, const vector<int> & r,
   int & key,int tablesize){
     //largest prime less than 2^{31}-->2^{31}-1
     int M{std::numeric_limits<int>::max()};//M=2^(31)-1
     int factor{0};
     for(int i=0; i<r.size(); i++)
       factor += (cur_points[i]*r[i])%M;
     factor = factor%M;
     key = factor % tablesize;
     return ;
}

void curve_hashing(const vector<int> & concat_norm_points,vector<int> & r,
    vector<real_curve*> *ht, int tablesize,
    vector<real_curve> & curves,int curve_index){
      int key{};
      linear_combination(concat_norm_points,r,key,tablesize);
      ht[key].push_back(&curves[curve_index]);
      return ;
}

void classic_hash_curves(const vector<vector<norm_curve>> & Lcurves,
  int dimension, vector<vector<vector<real_curve*>>> Lhashtable,int tablesize,
  vector<real_curve> & curves){
    int L{};
    L = Lcurves.size();
    int curve_size{};
    curve_size = Lcurves[0].size();
    vector<int> r{};
    vector<real_curve*> hashtable[tablesize];
    for(int i=0; i<L; i++){
      init_r(dimension,r);
      for(int j=0; j<curve_size; j++){
        curve_hashing(Lcurves[i][j].as_vector(),r,hashtable,tablesize,
        curves,j);
        //linear_combination(,r,key); //used in curve hashing
      }
      r.clear();
      vector<vector<real_curve*>> temp{};
      for(int j=0;j<tablesize;j++){
        temp.push_back(std::move(hashtable[j]));
        hashtable[j].clear();
      }
      Lhashtable.push_back(std::move(temp));
      temp.clear();
    }
    return ;
  }
