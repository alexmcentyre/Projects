#ifndef MATRIX_H
#define MATRIX_H
 
#include <initializer_list>
#include <iostream>
 
using namespace std;
 
typedef unsigned int uint;
typedef initializer_list<initializer_list<double>> i_list;
 
class Matrix{
 private:

  double** matrix;
  //acts as a 2d array to store values in the matrix
  uint rows, cols;
  //stores the number of rows and columns in the matrix
 
 public: 

  /*
    This is a constructor for Matrix that creates a matrix
    with a specific number of rows and columns. The values are
    set to zero by default.

    Parameters: number of rows, number of columns
   */
   Matrix(uint rows, uint cols);

   /*
     This is a constructor for Matrix that creates a matrix
     with values given by the user in an initializer list.

     Parameters: initializer list to store in a new matrix
    */
   Matrix(const i_list & list);

   /*
     This is a constructor for Matrix that creates a matrix
     that is identical to another specific matrix.

     Parameters: matrix that should be copied
    */
   Matrix(const Matrix & m);

   /*
     This is a destructor for matrix objects. This is automatically
     called for each creation of a matrix to prevent memory leaks. 
    */
   ~Matrix();
 
   /*
     This function adds a double to a matrix and returns the
     resulting matrix.

     Parameters: double to add to matrix
    */
  Matrix add(double s) const;

  /*
    This function adds two matrices together and returns the
    resulting matrix.

    Parameters: matrix that will be added
   */
  Matrix add(const Matrix & m) const;

  /*
    This function overloads the + operator to add a double to
    a matrix and return the resulting matrix.

    Parameters: double to add to matrix
   */
  Matrix operator+(double s) const;

  /*
    This function overloads the + operator to add a matrix to
    another matrix and return the resulting matrix.

    Parameters: matrix that will be added
   */
  Matrix operator+(const Matrix & m) const;

  /*
    This function subtracts a double from a matrix and returns
    the resulting matrix.
    
    Parameters: double to subtract from matrix
   */
  Matrix subtract(double s) const;

  /*
    This function subtracts a matrix from another matrix and
    returns the resulting matrix.

    Parameters: matrix that will be subtracted
   */
  Matrix subtract(const Matrix & m) const;

  /*
    This function overloads the - operator to subtract a double
    from a matrix and return the resulting matrix;

    Parameters: double to subtract from matrix
   */
  Matrix operator-(double s) const;

  /*
    This function overloads the - operator to subtract a matrix
    from another matrix and returns the resulting matrix.

    Parameter: matrix that will be subtracted
   */
  Matrix operator-(const Matrix & m) const;

  /*
    This function multiplies a matrix by a double and returns
    the resulting matrix.

    Parameters: double to multiply by
   */
  Matrix multiply(double s) const;

  /*
    This function multiplies a matrix by another matrix and
    returns the resulting matrix.

    Parameters: matrix to multiply by
   */
  Matrix multiply(const Matrix & m) const;

  /*
    This function overloads the * operator to multiply a matrix
    by a double and returns the resulting matrix.

    Parameters: double to multiply by
   */
  Matrix operator*(double s) const;

  /*
    This function overloads the * operator to multiply a matrix
    by another matrix and returns the resulting matrix.

    Parameters: matrix to multiply by
   */
  Matrix operator*(const Matrix & m) const;

  /*
    This function divides a matrix by a double and returns the
    resulting matrix.

    Parameters: double to divide by
   */
  Matrix divide(double s) const;

  /*
    This function overloads the / operator to divide a matrix by
    a double and returns the resulting matrix.

    Parameters: double to divide by
   */
  Matrix operator/(double s) const;

  /*
    This function transposes of a matrix and returns the
    resulting matrix.
   */
  Matrix t() const;
 
  /*
    This function returns the number of rows in the matrix
    it is called for.
   */
  const uint numRows() const;

  /*
    This function returns the number of cols in the matrix
    it is called for.
   */
  const uint numCols() const;
 
  /*
    This function returns the value at a specific point in
    a matrix.

    Parameters: row and column of the value
   */
  double & at(uint row, uint col);

  /*
    This function is simply a constant version of the one
    above (return is also constant).

    Parameters: row and column of the value
   */
  const double & at (uint row, uint col) const;

  /*
    This function prints the contents of a matrix in a format
    that makes sense
   */
  void print();

  /*
    This function overloads the = operator to accept a matrix
    for assignment. It returns a matrix.

    Parameters: matrix
   */
  Matrix & operator=(const Matrix & m);

  /*
    This function overloads the = operator to accept an
    initializer list for assignment. It returns a matrix.

    Parameters: initializer list
   */
  Matrix & operator=(const i_list & list);

  /*
    This function overloads the - operator to negate a matrix. It
    then returns the negated matrix.
   */
  Matrix operator-();

  /*
    This function overloads the () operator to return a specific
    value in a matrix based on the provided row and column.

    Parameters: specific row and column
   */
  double & operator()(uint row, uint col);

  /*
    This function is a constant version of the one above with a
    constant return type.

    Parameters: specific row and column
   */
  const double & operator()(uint row, uint col) const;

};// Matrix



/*
  This function overloads the << operator to recognize a matrix
  and be able to print out its contents in correct format.
  
  Parameters: ostream and matrix to be added to the stream
 */
ostream & operator<<(ostream & o, const Matrix & m);

/*
  This function overloads the + operator to act identical to
  the add function but to allow a double to be the left side
  operand. It returns the result matrix.

  Parameters: matrix to add to and double to add
 */
Matrix operator+(double s, Matrix & m);

/*
  This function overloads the - operator to act identical to
  the subtract function but to allow a double to be the left side
  operand. It returns the result matrix.

  Parameters: matrix to subtract from and double to subtract
 */
Matrix operator-(double s, Matrix & m);

/*
  This function overloads the * operator to act identical to
  the multiply function but to allow a double to be the left side
  operand. It returns the result matrix.

  Parameters: matrix to multiply and double to multiply
 */
Matrix operator*(double s, Matrix & m);

/*
  This function overloads the / operator to act identical to
  the divide function but to allow a double to be the left side
  operand. It returns the result matrix.

  Parameters: double to divide by and matrix to divide from
 */
Matrix operator/(double s, Matrix & m);
                                                                                
#endif
