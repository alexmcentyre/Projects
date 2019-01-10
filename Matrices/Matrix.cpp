
#include "Matrix.h"
#include <iostream>

using namespace std;

//main constructor (values set to 0)
Matrix::Matrix(uint rows, uint cols){
  matrix = new double* [rows];
  for(uint i = 0; i < rows; ++i){
    matrix[i] = new double [cols];
  }//for
  Matrix::rows = rows;
  Matrix::cols = cols;
}//Matrix

//initializer list constructor
Matrix::Matrix(const i_list& list){
  rows = list.size();
  cols = (*(list.begin())).size();
  matrix = new double* [rows];
  for(uint i = 0; i < rows; ++i){
    matrix[i] = new double [cols];
  }//for
  for(uint a = 0; a < rows; ++a){
    for(uint b = 0; b < cols; ++b){
      matrix[a][b] = *((*(list.begin() + a)).begin() + b);
    }//for
  }//for
}//Matrix

//copy constructor
Matrix::Matrix(const Matrix& m){
  matrix = new double* [m.rows];
  for(uint i = 0; i < m.rows; ++i){
    matrix[i] = new double [m.cols];
  }//for
  Matrix::rows = m.rows;
  Matrix::cols = m.cols;
  for(uint i = 0; i < rows; ++i){
    for(uint j = 0; j < cols; ++j){
      matrix[i][j] = m.matrix[i][j];
    }//for
  }//for
}//Matrix

//destructor
Matrix::~Matrix(){
  for(uint i = 0; i < rows; ++i){
    delete[] matrix[i];
  }//for
  delete[] matrix;
}//~Matrix
////////////////////////////////////////////////////////////////////////////////////

//adds s to each value in a matrix
Matrix Matrix::add(double s) const{
  Matrix temp(*this);
  for(uint i = 0; i < rows; ++i){
    for(uint j = 0; j < cols; ++j){
      temp.matrix[i][j] += s;
    }//for
  }//for
  return temp;
}//add

//adds corresponding values of two matrices
Matrix Matrix::add(const Matrix& m) const{
  Matrix temp(*this);
  for(uint i = 0; i < rows; ++i){
    for(uint j = 0; j < cols; ++j){
      temp.matrix[i][j] += m.matrix[i][j];
    }//for                                                                               
  }//for                                                                                 
  return temp;
}//add

Matrix Matrix::operator+(double s) const{
  return (*this).add(s);
}//+

Matrix Matrix::operator+(const Matrix& m) const{
  return (*this).add(m);
}//+
///////////////////////////////////////////////////////////////////////////////////

//subtracts s from each value in a matrix
Matrix Matrix::subtract(double s) const{
  Matrix temp(*this);
  for(uint i = 0; i < rows; ++i){
    for(uint j = 0; j < cols; ++j){
      temp.matrix[i][j] -= s;
    }//for
  }//for
  return temp;
}//subtract

//subtracts values of one matrix from corresponding values in another
Matrix Matrix::subtract(const Matrix& m) const{
  Matrix temp(*this);
  for(uint i = 0; i < rows; ++i){
    for(uint j = 0; j < cols; ++j){
      temp.matrix[i][j] -= m.matrix[i][j];
    }//for
  }//for
  return temp;
}//subtract

Matrix Matrix::operator-(double s) const{
  return (*this).subtract(s);
}//-

Matrix Matrix::operator-(const Matrix& m) const{
  return (*this).subtract(m);
}//-
////////////////////////////////////////////////////////////////////////////////

//multiplies each value in a matrix by s
Matrix Matrix::multiply(double s) const{
  Matrix temp(*this);
  for(uint i = 0; i < rows; ++i){
    for(uint j = 0; j < cols; ++j){
      temp.matrix[i][j] *= s;
    }//for
  } //for
  return temp;
}//multiply

//these loops use counter variables to keep track of indexes in scalar multiplication
Matrix Matrix::multiply(const Matrix& m) const{
  Matrix temp((*this).rows, m.numCols());
  uint a = 0;
  while(a < rows){
    for(uint b = 0; b < cols; ++b){
      for(uint c = 0; c < cols; ++c){
	temp.matrix[a][b] = temp.matrix[a][b] + (((*this).matrix[a][c]) * (m.matrix[c][b]));
      }//for a
    }//for b
    ++a;
  } //while
  return temp;
}//multiply

Matrix Matrix::operator*(double s) const{
  return (*this).multiply(s);
}//*

//divides each value in the matrix by s
Matrix Matrix::divide(double s) const{
  Matrix temp(*this);
  for(uint i = 0; i < rows; ++i){
    for(uint j = 0; j < cols; ++j){
      temp.matrix[i][j] /= s;
    }//for
  }//for
  return temp;
}//divide

Matrix Matrix::operator/(double s) const{
  return (*this).divide(s);
}// /


Matrix Matrix::t() const{
  Matrix temp(cols, rows);
  for(uint i = 0; i < cols; ++i){
    for(uint j = 0; j < rows; ++j){
      temp.matrix[i][j] = (*this).matrix[j][i];
    }//for
  }//for
  return temp;
}//t
//////////////////////////////////////////////////////////////////////////////

const uint Matrix::numRows() const{
  return Matrix::rows;
}//numRows

const uint Matrix::numCols() const{
  return Matrix::cols;
}//numCols

double& Matrix::at(uint row, uint col){ 
 return matrix[row][col];
}//at

const double& Matrix:: at(uint row, uint col) const{
 return matrix[row][col];
}//at
////////////////////////////////////////////////////////////////////////////////

//loop is used to assign each value in the matrix
Matrix & Matrix::operator=(const Matrix & m){
  for(uint i = 0; i < rows; ++i){
    for(uint j = 0; j < cols; ++j){
      (*this).matrix[i][j] = m.matrix[i][j];
    }//for
  }//for
  return *this;
}//=

//loop is used to assign each value in the initializer list to a matrix
Matrix & Matrix::operator=(const i_list & list){
  for(uint a = 0; a < rows; ++a){
    for(uint b = 0; b < cols; ++b){
      (*this).matrix[a][b] = *((*(list.begin() + a)).begin() + b);
    }//for
  }//for 
  return *this;
}//=

//loop is used to print each value with reasonable format
void Matrix::print(){
  for(uint i = 0; i < rows; ++i){
    for(uint j = 0; j < cols; ++j){
      cout << matrix[i][j] << " ";
    }//for
    cout << endl;
  }//for
}//print

Matrix operator+(double s, Matrix & m){
  return m.add(s);
}//+

Matrix operator-(double s, Matrix & m){
  return m.subtract(s);
}//-

Matrix operator*(double s, Matrix & m){
  return m.multiply(s);
}//*

Matrix operator/(double s, Matrix & m){
  return m.divide(s);
}// /

//loop is used to negate each individual value
Matrix Matrix::operator-(){
  Matrix temp(*this);
  for(uint i = 0; i < rows; ++i){
    for(uint j = 0; j < cols; ++j){
      temp.matrix[i][j] = -(temp.matrix[i][j]);
    }//for
  }//for
  return temp;
}//-

//loop is used to have correct format in what will be printed
ostream & operator<<(ostream & o, const Matrix & m){
  for(uint i = 0; i < m.numRows(); ++i){
    for(uint j = 0; j < m.numCols(); ++j){
      o << m.at(i,j);
      o << " ";
    }//for
    o << endl;
  }//for
  return o;
}//<<*/

double & Matrix::operator()(uint row, uint col){
  return matrix[row][col];
}//()

const double & Matrix::operator()(uint row, uint col) const{
  return matrix[row][col];
}//()
