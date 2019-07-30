// Copyright [2019] <Kai Xiang Yong>
#include "assignments/ev/euclidean_vector.h"

// #include "euclidean_vector.h"

#include <algorithm>
#include <utility>

/**
 * --------------------------------- Constructors ---------------------------------
 */

/**
 * Given dimension, initialize vector with dimension given input
 * @param size Dimension
 */
EuclideanVector::EuclideanVector(int size) : size_{size} {
  magnitudes_ = std::make_unique<double[]>(size_);
}

/**
 * Given dimension and magnitude, initialise vector with all dimension has same the magnitude
 * @param size Dimension of the vector
 * @param magnitude Magnitude
 */
EuclideanVector::EuclideanVector(int size, double magnitude) : size_{size} {
  magnitudes_ = std::make_unique<double[]>(size_);
  std::fill_n(magnitudes_.get(), size_, magnitude);
}

/**
 * Iterator Constructor
 * @param start Start iterator
 * @param end End iterator
 */
EuclideanVector::EuclideanVector(std::vector<double>::const_iterator start,
                                 std::vector<double>::const_iterator end) {
  std::vector<double> list;
  int size = 0;
  for (auto p = start; p != end; p++) {
    list.push_back(*p);
    size++;
  }
  size_ = size;
  magnitudes_ = std::make_unique<double[]>(size_);

  int i = 0;
  for (const auto& item : list) {
    magnitudes_[i] = item;
    i++;
  }
}

/**
 * Copy Constructor
 * @param a Euclidean Vector to copy to
 */
EuclideanVector::EuclideanVector(const EuclideanVector& a) : size_{a.size_} {
  magnitudes_ = std::make_unique<double[]>(size_);
  for (int i = 0; i < size_; i++) {
    magnitudes_[i] = a.magnitudes_[i];
  }
}

/**
 * Move Constructor
 * @param a Euclidean Vector to move to
 */
EuclideanVector::EuclideanVector(EuclideanVector&& a) noexcept
  : magnitudes_{std::move(a.magnitudes_)}, size_{a.size_} {
  a.size_ = 0;
}

/**
 * --------------------------------- Operations ---------------------------------
 */

/**
 * Copy Assignment =
 * @param a Vector to Copy
 * @return Pointer to this vector
 */
EuclideanVector& EuclideanVector::operator=(const EuclideanVector& a) {
  size_ = a.size_;
  // Deep Copy
  magnitudes_.reset();
  magnitudes_ = std::make_unique<double[]>(size_);
  std::vector<double> vector;
  for (int i = 0; i < size_; i++) {
    magnitudes_[i] = a[i];
  }
  return *this;
}

/**
 * Move Assignment
 * @param a Vector to Move
 * @return Pointer to this vector
 */
EuclideanVector& EuclideanVector::operator=(EuclideanVector&& a) noexcept {
  magnitudes_ = std::move(a.magnitudes_);
  size_ = a.size_;
  a.size_ = 0;
  return *this;
}

/**
 * Subscript for write
 * @param n nth dimension
 * @return A reference to nth dimension
 */
double& EuclideanVector::operator[](int n) {
  return magnitudes_[n];
}

/**
 * Subscript for read
 * @param n nth dimension
 * @return The value of nth dimension
 */
double EuclideanVector::operator[](int n) const {
  return magnitudes_[n];
}

/**
 * Addition
 * @param a Another Vector to add on
 * @return Reference to this vector
 */
EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& a) {
  int numDimensions = this->GetNumDimensions();
  if (a.size_ != numDimensions) {
    std::stringstream ss;
    ss << "Dimensions of LHS(" << this->GetNumDimensions();
    ss << ") and RHS(" << a.GetNumDimensions() << ") do not match\n";
    throw EuclideanVectorError{ss.str()};
  }
  for (int i = 0; i < numDimensions; i++) {
    magnitudes_[i] += a[i];
  }
  return *this;
}

/**
 * Subtraction
 * @param a Another Vector to subtract from
 * @return Referene to this vector
 */
EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& a) {
  int numDimensions = this->GetNumDimensions();
  if (a.size_ != numDimensions) {
    std::stringstream ss;
    ss << "Dimensions of LHS(" << this->GetNumDimensions();
    ss << ") and RHS(" << a.GetNumDimensions() << ") do not match\n";
    throw EuclideanVectorError{ss.str()};
  }
  for (int i = 0; i < numDimensions; i++) {
    magnitudes_[i] += a[i];
  }
  return *this;
}

// Multiplication
/**
 * Multiplication
 * @param m Multiplier
 * @return Reference to this vector
 */
EuclideanVector& EuclideanVector::operator*=(const double m) {
  for (int i = 0; i < this->GetNumDimensions(); i++) {
    this->magnitudes_[i] *= m;
  }
  return *this;
}

/**
 * Division
 * @param d Divider
 * @return Reference to this vector
 */
EuclideanVector& EuclideanVector::operator/=(const double d) {
  if (d == 0) {
    throw EuclideanVectorError{"Invalid vector division by 0\n"};
  }
  for (int i = 0; i < this->GetNumDimensions(); i++) {
    this->magnitudes_[i] /= d;
  }
  return *this;
}

/**
 * Vector Type Conversion
 * @return A vector with values of dimensions
 */
EuclideanVector::operator std::vector<double>() {
  std::vector<double> vector;
  vector.reserve(size_);
  for (int i = 0; i < this->GetNumDimensions(); i++) {
    vector.push_back(magnitudes_[i]);
  }
  return vector;
}

/**
 * List Type Conversion
 * @return A list with values of dimensions
 */
EuclideanVector::operator std::list<double>() {
  std::list<double> list;
  for (int i = 0; i < this->GetNumDimensions(); i++) {
    list.push_back(magnitudes_[i]);
  }
  return list;
}

/**
 * --------------------------------- Methods ---------------------------------
 */

/**
 * At
 * @param n nth value
 * @return Value of nth dimension
 */
double EuclideanVector::at(int n) const {
  if (n < 0 || n >= this->size_) {
    std::stringstream ss;
    ss << "Index " << n << " is not valid for this EuclideanVector object\n";
    throw EuclideanVectorError{ss.str()};
  }
  return magnitudes_[n];
}

/**
 * At
 * @param n nth value
 * @return Reference to nth dimension
 */
double& EuclideanVector::at(int n) {
  if (n < 0 || n >= this->GetNumDimensions()) {
    std::stringstream ss;
    ss << "Index " << n << " is not valid for this EuclideanVector object\n";
    throw EuclideanVectorError{ss.str()};
  }
  return this->operator[](n);
}

/**
 * Get number of dimension
 * @return Number of Dimension
 */
int EuclideanVector::GetNumDimensions() {
  return size_;
}

int EuclideanVector::GetNumDimensions() const {
  return size_;
}

/**
 * Get Euclidean Norm
 * @return Value of Euclidean Norm
 */
double EuclideanVector::GetEuclideanNorm() {
  if (this->GetNumDimensions() == 0) {
    std::string s = "EuclideanVector with no dimensions does not have a norm\n";
    throw EuclideanVectorError{s};
  }
  double norm = 0;
  for (int i = 0; i < this->GetNumDimensions(); i++) {
    norm += magnitudes_[i] * magnitudes_[i];
  }
  return sqrt(norm);
}

/**
 * Create a Unit Vector
 * @return Unit Vector
 */
EuclideanVector EuclideanVector::CreateUnitVector() {
  if (this->GetNumDimensions() == 0) {
    std::string s = "EuclideanVector with no dimensions does not have a norm\n";
    throw EuclideanVectorError{s};
  }
  double norm = this->GetEuclideanNorm();
  if (norm == 0) {
    std::stringstream ss;
    ss << "EuclideanVector with euclidean normal";
    ss << " of 0 does not have a unit vector\n";
    throw EuclideanVectorError{ss.str()};
  }
  return *this / norm;
}

/**
 * --------------------------------- Friends ---------------------------------
 */

/**
 * Equal
 * @param a 1st vector
 * @param b 2nd vector
 * @return True if 1st vector is equal to 2nd, False otherwise
 */
bool operator==(const EuclideanVector& a, const EuclideanVector& b) {
  if (a.size_ != b.size_)
    return false;
  for (int i = 0; i < a.size_; i++) {
    if (a.at(i) != b.at(i))
      return false;
  }
  return true;
}

/**
 * Not Equal
 * @param a 1st vector
 * @param b 2nd vector
 * @return True if 1st vector is not equal to 2nd, False otherwise
 */
bool operator!=(const EuclideanVector& a, const EuclideanVector& b) {
  return !operator==(a, b);
}

/**
 * Addition
 * @param a 1st vector
 * @param b 2nd vector
 * @return New vector with values of 1st vector plus 2nd vector
 */
EuclideanVector operator+(const EuclideanVector& a, const EuclideanVector& b) {
  if (a.size_ != b.size_) {
    std::stringstream ss;
    ss << "Dimensions of LHS(" << a.GetNumDimensions();
    ss << ") and RHS(" << b.GetNumDimensions() << ") do not match\n";
    throw EuclideanVectorError{ss.str()};
  }
  std::vector<double> vector;
  vector.reserve(a.size_);
  for (int i = 0; i < a.size_; i++) {
    vector.push_back(a[i] + b[i]);
  }
  return EuclideanVector(vector.begin(), vector.end());
}

/**
 * Subtraction
 * @param a 1st vector
 * @param b 2nd vector
 * @return New vector with values of 1st vector minus 2nd vector
 */
EuclideanVector operator-(const EuclideanVector& a, const EuclideanVector& b) {
  if (a.size_ != b.size_) {
    std::stringstream ss;
    ss << "Dimensions of LHS(" << a.GetNumDimensions();
    ss << ") and RHS(" << b.GetNumDimensions() << ") do not match\n";
    throw EuclideanVectorError{ss.str()};
  }
  std::vector<double> vector;
  vector.reserve(a.size_);
  for (int i = 0; i < a.size_; i++) {
    vector.push_back(a[i] - b[i]);
  }
  return EuclideanVector(vector.begin(), vector.end());
}

/**
 * Multiplication
 * @param a 1st vector
 * @param b 2nd vector
 * @return Dot Product of two vectors
 */
double operator*(const EuclideanVector& a, const EuclideanVector& b) {
  if (a.size_ != b.size_) {
    std::stringstream ss;
    ss << "Dimensions of LHS(" << a.GetNumDimensions();
    ss << ") and RHS(" << b.GetNumDimensions() << ") do not match\n";
    throw EuclideanVectorError{ss.str()};
  }
  double sum = 0;
  for (int i = 0; i < a.size_; i++) {
    sum += a[i] * b[i];
  }
  return sum;
}

/**
 * Multiplication
 * @param a vector
 * @param m multiplier
 * @return New vector with values multiplied by the multiplier
 */
EuclideanVector operator*(const EuclideanVector& a, double m) {
  std::vector<double> vector;
  vector.reserve(a.size_);
  for (int i = 0; i < a.size_; i++) {
    vector.push_back(a[i] * m);
  }
  return EuclideanVector(vector.begin(), vector.end());
}

/**
 * Division
 * @param a vector
 * @param d diveder
 * @return New vector with values divided by divider
 */
EuclideanVector operator/(const EuclideanVector& a, double d) {
  if (d == 0) {
    throw EuclideanVectorError{"Invalid vector division by 0\n"};
  }
  std::vector<double> vector;
  vector.reserve(a.size_);
  for (int i = 0; i < a.size_; i++) {
    vector.push_back(a[i] / d);
  }
  return EuclideanVector(vector.begin(), vector.end());
}

/**
 * Output Stream
 * @param os osstream
 * @param v vector
 * @return output stream with magnitude in each dimension of the Euclidean Vector
 */
std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) {
  os << "[";
  for (int i = 0; i < v.size_; i++) {
    os << v[i];
    if (i != v.size_ - 1) {
      os << " ";
    }
  }
  os << "]";
  return os;
}
