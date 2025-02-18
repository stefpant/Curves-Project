#ifndef RANGE_ASSIGN_H
#define RANGE_ASSIGN_H

#include <vector>
#include <string>

#include "assign_entry.h"

//returns the min distance between centroids
double find_R0(const std::vector<real_curve*> & centroids,std::string dist);

//takes all remaining curves from entries
void collect_remaining_objects(std::vector<assign_entry> & entries,
  std::vector<real_curve*> & rem_curves);

//checks in centroids buckets to assign the curves
void range_assign(std::vector<real_curve*> & centroids,
  std::vector<std::vector<std::vector<assign_entry*>>> &Lht,
   double R, std::vector<std::vector<int>> & keys, std::string dist);

//here assigns the curves
double search_in_entries(std::vector<assign_entry> & entries,
  std::vector<std::vector<std::vector<assign_entry*>>> &Lht,
  std::vector<std::vector<int>> & keys, int & flag,
  std::vector<std::vector<real_curve*>> & assigned_objects);

double assign_by_range_search(std::vector<real_curve*> & centroids,
  std::vector<std::vector<std::vector<assign_entry*>>> Lht,
  std::vector<assign_entry> & entries,
  std::vector<std::vector<int>> & keys, std::string dist,
  std::vector<std::vector<real_curve*>> & assigned_objects);

#endif
