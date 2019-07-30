// Copyright [2019] <Kai Xiang Yong>
#ifndef ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
#define ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_

#include <math.h>

#include <exception>
#include <iostream>
#include <istream>
#include <list>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept { return what_.c_str(); }

 private:
  std::string what_;
};

class EuclideanVector {
 public:
  // --------------- Constructor ---------------
  explicit EuclideanVector(int i);
  EuclideanVector(int i, double magnitude);
  // Iterator Constructor
  EuclideanVector(std::vector<double>::const_iterator start,
                  std::vector<double>::const_iterator end);
  // Copy Constructor
  EuclideanVector(const EuclideanVector&);
  // Move Constructor
  EuclideanVector(EuclideanVector&&) noexcept;

  // --------------- Operations ---------------
  // Move Assignment
  EuclideanVector& operator=(const EuclideanVector&);
  // Copy Assignment
  EuclideanVector& operator=(EuclideanVector&&) noexcept;
  // Subscript
  double& operator[](int);
  double operator[](int i) const;
  // Addition
  EuclideanVector& operator+=(const EuclideanVector&);
  // Subtraction
  EuclideanVector& operator-=(const EuclideanVector&);
  // Multiplication
  EuclideanVector& operator*=(double);
  // Division
  EuclideanVector& operator/=(double);
  // Vector Type Conversion
  explicit operator std::vector<double>();
  // List Type Conversion
  explicit operator std::list<double>();
  // --------------- Method ---------------

  double at(int) const;
  double& at(int);
  int GetNumDimensions();
  int GetNumDimensions() const;
  double GetEuclideanNorm();
  EuclideanVector CreateUnitVector();

  // --------------- Friends ---------------
  friend bool operator==(const EuclideanVector&, const EuclideanVector&);
  friend bool operator!=(const EuclideanVector&, const EuclideanVector&);
  using ev = EuclideanVector;
  friend ev operator+(const ev&, const ev&);
  friend ev operator-(const ev&, const ev&);
  friend double operator*(const ev&, const ev&);
  friend ev operator*(const ev&, double);
  friend ev operator/(const ev&, double);

  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);

 private:
  std::unique_ptr<double[]> magnitudes_;
  int size_;
};

#endif  // ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
