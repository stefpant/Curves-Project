#include <vector>
#include <string>
#include <limits>
#include <iostream>

#include "curve.h"
#include "rand_utils.h"
#include "classic_hash.h"
#include "lsh.h"
#include "entry.h"

using namespace std;

void init_r(int dimension, vector<int> & r){
    for(int i=0; i< dimension; i++)
      r.push_back(int_uniform_rand(0,1000000));//the selected [M,N] was random
    return ;
}

void linear_combination(const vector<int> & cur_points, const vector<int> & r,
  int & key,int tablesize){

  //largest prime less than 2^{31}-->2^{31}-1
  int M{std::numeric_limits<int>::max()};//M=2^(31)-1
  int factor{0};
  for(size_t i=0; i<cur_points.size(); i++)
    factor += (cur_points[i]*r[i])%M;
  key = (factor % tablesize + tablesize) % tablesize;
}

void hash_curves(const vector<vector<norm_curve>> & Lcurves,
  int dimension, vector<vector<vector<entry>>> & Lhashtable,
  int tablesize, vector<real_curve*> & pcurves,
  vector<real_curve> & normalized_curves, string hash, int kvec, int w){

  size_t L{Lcurves.size()};
  size_t curve_size{Lcurves[0].size()};
  vector<int> r{};


  for(size_t i=0; i<L; i++){
    vector<entry> hashtable[tablesize];

		if(hash=="classic"){
      init_r(dimension, r);
	    for(size_t j=0; j<curve_size; j++)
	      classic_curve_hashing(Lcurves[i][j].as_vector(),r, hashtable,
	      	tablesize, pcurves, j, normalized_curves);
	      //after calling the above function we inserted in hashtable
	      //the curve[j] as an entry
  	 }
		else if(hash=="probabilistic"){
      init_r(kvec, r);
      vector<hash_f> hs;
      vector<int> g;
      make_hashes(hs, w, dimension, kvec);
      make_g(hs, g);
		  for(size_t j=0; j<curve_size; j++)
        lsh_curve_hashing(Lcurves[i][j].as_vector(),r, hashtable,
        	tablesize, pcurves, j, normalized_curves, g, hs);
        //same here like before after calling this function
    }

    r.clear();
    vector<vector<entry>> temp{};

    for(int j=0;j<tablesize;j++){
      temp.push_back(std::move(hashtable[j]));
      hashtable[j].clear();
    }
    Lhashtable.push_back(std::move(temp));
    temp.clear();
  }
}

void print_hashtable(vector<vector<entry>> & ht,
  int tablesize){

  for(size_t i=0; i<ht.size();i++){
    cout <<"key = "<<i<<": ";
    for(size_t j=0;j<ht[i].size();j++)
      cout << "-->"<<ht[i][j].rcurve->get_id()<<" ";
    cout << endl;
  }
  return ;
}
