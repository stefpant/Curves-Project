#ifndef CURVE_H
#define CURVE_H

#include <vector>
#include <string>

class curve{
  std::string id;
  int dimension;
  //every point is a dimension-vector of coordinates
public:
  curve(int dim = 0);
  curve(const curve & c_curve);
  curve& operator=(const curve &);
  curve(curve && m_curve);
  curve& operator=(curve &&);
  virtual ~curve();
  void set_id(std::string r_id);
  std::string get_id() const;
  void set_dimension(int dim);
  int get_dimension() const;
  virtual void print() = 0;

};

//real_curve and norm_curve are symmetrical with double and int coordinates
class real_curve : public curve {
  std::vector<std::vector<double>> points;

public:
  real_curve(int dim = 0);
  real_curve(const real_curve &);
  real_curve& operator=(const real_curve &);
  real_curve(real_curve &&);
  real_curve& operator=(real_curve &&);
  virtual ~real_curve();
  void set_point(std::vector<double> & point);
  //we introduce a move push back
  void set_point(std::vector<double> && point);
  const std::vector<std::vector<double>> & get_points() const;
  const std::vector<double> as_vector() const;
  void print();
};

class norm_curve : public curve {
  std::vector<std::vector<int>> points;

public:
  norm_curve(int dim = 0);
  void set_point(std::vector<int> & point);
  //we introduce a move push back
  void set_point(std::vector<int> && point);
  const std::vector<std::vector<int>> & get_points() const;
  const std::vector<int> as_vector() const;
  void print();
};

class segment : public real_curve{
  std::string way_id;

public:
  segment(int dim=0);
  void set_way(std::string && w_id);
  std::string get_way();
};

#endif
