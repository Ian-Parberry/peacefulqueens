/// \file backtrack.cpp
/// \brief Backtrack for solutions to the Peaceful Queens problem.

#include <iostream>
#include <fstream>
#include <string>

// MIT License
//
// Copyright (c) 2020 Ian Parberry
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

void ExportToSVG(int[], int);

/// \brief Print an array.
///
/// Output to the console the elements of an array.
/// \param A An array.
/// \param n The number of elements in the array.

void print(int A[], int n){
  for(int i=0; i<n-1; i++) //all but last entry
    std::cout << A[i] << " "; //space between each one

  std::cout << A[n - 1] << std::endl; //last entry, no space
} //print

/// \brief Initialize.
///
/// Initialize the arrays ready for backtracking.
/// \param A [out] An array for the solution.
/// \param b [out] Back-diagonal flags.
/// \param d [out] Diagonal flags.
/// \param n The number of elements in the solution array.

void initialize(int A[], bool b[], bool d[], int n){
  for(int i=0; i<n; i++)
    A[i] = i;
  
  for(int i=0; i<2*n-1; i++)
    b[i] = d[i] = true;
} //initialize

/// \brief Backtrack for Peaceful Queens.
///
/// Recursively backtrack for the Peaceful Queens problem. Exhaustively search
/// through permutations to avoid row and column conflicts, pruning using a
/// pair of arrays to detect diagonal and back-diagonal conflicts. Keep track
/// of the number of solutions found. Print solutions to the console and save
/// them to files in SVG (Scalable Vector Graphics) format.
/// \param A [in, out] An array for the solution.
/// \param b [in, out] Back-diagonal flags.
/// \param d [in, out] Diagonal flags.
/// \param m Current array element.
/// \param n The number of elements in the solution array.
/// \param count [in, out] Running count of number of solutions found.

void queen(int A[], bool b[], bool d[], int m, int n, int& count){
  if(m < 0){ //base of recursion
    count++; //one more solution
    print(A, n); //print to console
    ExportToSVG(A, n); //export as SVG file
  } //if
  
  else //recursive part
    for(int i=m; i>=0; i--){
      const int j = A[i] - m + n - 1; //back-diagonal index
      const int k = A[i] + m; //diagonal index

      if(b[j] && d[k]){ //diagonal & back-diagonal unused
        std::swap(A[m], A[i]); //permute

        b[j] = d[k] = false; //mark back-diagonal and diagonal used
        queen(A, b, d, m - 1, n, count); //recurse on smaller array
        b[j] = d[k] = true; //mark back-diagonal and diagonal unused

        std::swap(A[m], A[i]); //unpermute
      } //if
    } //for
} //queen

/// \brief Backtrack for Peaceful Queens.
///
/// Backtrack for Peaceful Queens. Set up space for the arrays, initialize
/// the counter, and call the recursive backtracking function which sets the
/// counter to the number of solutions found. Report the number of solutions to
/// the console and delete the arrays.
/// \param n Width and height of the chessboard in squares.

void queen(int n){
  int* A = new int[n]; //solution array
  bool* b = new bool[2*n - 1LL]; //back-diagonal array
  bool* d = new bool[2*n - 1LL]; //diagonal array

  int count = 0; //for number of solutions
  initialize(A, b, d, n); //initialize arrays
  queen(A, b, d, n - 1, n, count); //here's where the work gets done
  std::cout <<  std::endl<< count << " solutions found" << std::endl; //report

  //clean up and exit

  delete [] A;
  delete [] b;
  delete [] d;
} //queen

/// \brief Main.
///
/// Backtrack for solutions to the Peaceful Queens problem.
/// \return 0

int main(){
  const int n = 4; //board size
  queen(n); //backtrack for peaceful queens

  return 0; //what could possibly go wrong?
} //main
