/// \file backtrack.cpp
/// \brief Backtrack for solutions to the Peaceful Queens problem.

#include <iostream>
#include <fstream>
#include <string>

// MIT License
//
// Copyright (c) 2022 Ian Parberry
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

#if defined(_MSC_VER) //Windows Visual Studio 
  #include <windows.h>
#else //g++, *nix
  #include <time.h>
#endif

void ExportToSVG(size_t[], size_t); //defined in svg.cpp

/// Get CPU time for this process in milliseconds. It's annoying that
/// `std::chron` has no cross-platform support for this.
/// \return User CPU time in milliseconds.

const uint64_t CPUTime(){
#if defined(_MSC_VER) //Windows Visual Studio 
  uint64_t llCNS = 0; //for CPU time in centinanoseconds

  HANDLE hProcess = //handle to this process
    OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, GetCurrentProcessId()); 

  if(hProcess != nullptr){ //handle is valid
    FILETIME ftCreation, ftExit, ftKernel; //unused
    FILETIME ftUser; //this one we want 

    if(GetProcessTimes(hProcess, &ftCreation, &ftExit, &ftKernel, &ftUser))
      llCNS = *((uint64_t*)&ftUser);  //get time values
    
    CloseHandle(hProcess); //close the process handle
  } //if

  return uint64_t(llCNS)/10000; 
#else //g++, *nix
  return uint64_t(1000.0*(double)(clock())/CLOCKS_PER_SEC);
#endif
} //CPUTime

/// \brief Print an array.
///
/// Output to the console the elements of an array.
/// \param A An array.
/// \param n The number of elements in the array.

void print(size_t A[], size_t n){
  for(size_t i=0; i<n-1; i++) //all but last entry
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

void initialize(size_t A[], bool b[], bool d[], size_t n){
  for(size_t i=0; i<n; i++)
    A[i] = i;
  
  for(size_t i=0; i<2*n-1; i++)
    b[i] = d[i] = true;
} //initialize

/// \brief Process a solution to the Peaceful Queens problem.
///
/// Process a solution to the Peaceful Queens problem.
/// \param A The solution in permutation form.
/// \param n The number of elements in the solution array.
/// \param count [in, out] Running count of number of solutions found.

void process(size_t A[], size_t n, uint64_t& count){
  count++; //one more solution
  //print(A, n); //print to console
  //ExportToSVG(A, n); //export as SVG file
} //process

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
/// \param m Previous array element.
/// \param n The number of elements in the solution array.
/// \param count [in, out] Running count of number of solutions found.

void queen(size_t A[], bool b[], bool d[], size_t m, size_t n, uint64_t& count){
  if(m == 0) //base of recursion
    process(A, n, count); //process new solution

  else{ //recursive part
    for(int i=0; i<m; i++){
      const size_t j = m - 1; //largest index to swap in permutation
      const size_t k = j - i; //smallest index to swap in permutation
      const size_t dx = A[k] + j; //diagonal index
      const size_t bx = A[k] - m + n; //back-diagonal index

      if(b[bx] && d[dx]){ //diagonal & back-diagonal unused
        std::swap(A[j], A[k]); //permute

        b[bx] = d[dx] = false; //mark back-diagonal and diagonal used
        queen(A, b, d, j, n, count); //recurse on smaller array
        b[bx] = d[dx] = true; //mark back-diagonal and diagonal unused

        std::swap(A[j], A[k]); //unpermute
      } //if
    } //for
  } //else
} //queen

/// \brief Backtrack for Peaceful Queens.
///
/// Backtrack for Peaceful Queens. Set up space for the arrays, initialize
/// the counter, and call the recursive backtracking function which sets the
/// counter to the number of solutions found. Report the number of solutions to
/// the console and delete the arrays.
/// \param n Width and height of the chessboard in squares.

uint64_t queen(size_t n){
  size_t* A = new size_t[n]; //solution array
  const size_t m = 2*n - 1; //size of diagonal and back-diagonal arrays
  bool* b = new bool[m]; //back-diagonal array
  bool* d = new bool[m]; //diagonal array

  uint64_t nCount = 0; //for number of solutions
  initialize(A, b, d, n); //initialize arrays
  queen(A, b, d, n, n, nCount); //here's where the work gets done

  //clean up and exit

  delete [] A;
  delete [] b;
  delete [] d;

  return nCount;
} //queen

/// \brief Main.
///
/// Backtrack for solutions to the Peaceful Queens problem.
/// \return 0

int main(){
  const size_t n = 11; //board size
  const uint64_t nCount = queen(n); //backtrack for peaceful queens
  
  std::cout << std::endl << nCount << " solutions found" << std::endl; //report
  std::cout << CPUTime()/1000.0f << " seconds CPU time" << std::endl; //CPU time

  return 0; //what could possibly go wrong?
} //main
