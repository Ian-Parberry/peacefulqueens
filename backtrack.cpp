/// \file backtrack.cpp
/// \brief Solving the Peaceful Queens problem.

#include <iostream>
#include <fstream>
#include <string>

//////////////////////////////////////////////////////////////////////////////
// Helper functions.

/// \brief Make file name from array.
///
/// Concatenate the elements of an array into a string for use as a file name.
/// \param A An array.
/// \param n The number of elements in the array.

std::string GetFileName(size_t A[], size_t n){
  std::string s; //for file name

  for(size_t i=0; i<n; i++) //for each array entry
    s += std::to_string(A[i]); //concatenate into string

  return s; //file name
} //GetFileName

/// Output to the console the elements of an array.
/// \param A An array.
/// \param n The number of elements in the array.

void print(size_t A[], size_t n){
  for(size_t i=0; i<n-1; i++) //all but last entry
    std::cout << A[i] << " "; //space between each one

  std::cout << A[n - 1] << std::endl; //last entry, no space
} //print

//////////////////////////////////////////////////////////////////////////////
// Output to an SVG file.

/// \brief Output an SVG header.
///
/// Output the SVG tags for an SVG header to an output stream.
/// \param ostream An output stream, assumed to be opened.
/// \param w Width and height of the image.

void SVGHeader(std::ofstream& ostream, size_t w){
  ostream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
  ostream << "<svg width=\"" << w <<  "\" height=\"" << w << "\" " <<
    "viewBox=\"-4 -4 " << w << " " << w << "\" " << 
    "xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;
} //SVGHeader

/// \brief Output an SVG style.
///
/// Output the SVG style tags for this project to an output stream.
/// \param ostream An output stream, assumed to be opened.
/// \param r Radius for circles.

void SVGStyle(std::ofstream& ostream, size_t r){
  ostream << "<style>" << std::endl;
  ostream << "circle{stroke:black;stroke-width:1;fill:darkgray;r:" <<
    r << "}" << std::endl;
  ostream << "</style>" << std::endl;
} //SVGStyle

/// \brief Output an SVG line.
///
/// Output the SVG tag for a line to an output stream.
/// \param ostream An output stream, assumed to be opened.
/// \param x1 X-coordinate of first end of line.
/// \param y1 Y-coordinate of first end of line.
/// \param x2 X-coordinate of second end of line.
/// \param y2 Y-coordinate of second end of line.

void SVGLine(std::ofstream& ostream, size_t x1, size_t y1, size_t x2, size_t y2){
  ostream << "<line x1=\"" << x1 << "\" y1=\"" << y1 <<
    "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\"/>" << std::endl;
} //SVGLine

/// \brief Output an SVG circle.
///
/// Output the SVG tag for a circle to an output stream.
/// \param ostream An output stream, assumed to be opened.
/// \param cx X-coordinate of the center of the circle.
/// \param cy Y-coordinate of the center of the circle.

void SVGCircle(std::ofstream& ostream, size_t cx, size_t cy){
  ostream << "<circle cx=\"" << cx << "\" cy=\"" << cy << "\"/>" << std::endl;
} //SVGCircle

/// \brief Output an SVG square.
///
/// Output the SVG tag for a square to an output stream.
/// \param ostream An output stream, assumed to be opened.
/// \param x X-coordinate of the center of the square.
/// \param y Y-coordinate of the center of the square.
/// \param w Width and height of the square.

void SVGSquare(std::ofstream& ostream, size_t x, size_t y, size_t w){
  ostream << "<rect x=\"" << x << "\" y=\"" << y <<
    "\" width=\"" << w << "\" height=\"" << w << "\"/>" << std::endl;
} //SVGSquare

/// \brief Output a chessboard in SVG format.
///
/// Output the SVG style tags for a chessboard.
/// \param ostream An output stream, assumed to be opened.
/// \param w Width of a chessboard square in pixels.
/// \param n Width and height of the chessboard in squares.

void SVGChessboard(std::ofstream& ostream, size_t w, size_t n){  
  ostream << "<rect width=\"" << w*n << "\" height=\"" << w*n << 
    "\" fill=\"none\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;

  for(size_t i=0; i<n; i++)
    for(size_t j=0; j<n; j++)
      if((i&1) ^ (j&1))
        SVGSquare(ostream, i*w, j*w, w);
} //SVGChessboard

/// \brief Output a solution to the Peaceful Queens problem in SVG format.
///
/// Output the SVG tags for a solution to the Peaceful Queens problem.
/// \param A An array containing the solution.
/// \param n The number of elements in the array.

void ExportToSVG(size_t A[], size_t n){
  const size_t w = 32; //width and height of chessboard squares in pixels

  //open SVG file and output header information and style tag

  std::ofstream ostream(GetFileName(A, n) + ".svg"); 

  SVGHeader(ostream, w*(n + 1));
  SVGStyle(ostream, (size_t)std::round(0.35f*w));

  //output chessboard

  SVGChessboard(ostream, w, n);

  //output circles to represent queens

  const size_t delta = w/2; //half the width of a square

  for(size_t i=0; i<n; i++)
    SVGCircle(ostream, i*w + delta, A[i]*w + delta);
  
  ostream << "</svg>" << std::endl;
} //ExportToSVG

//////////////////////////////////////////////////////////////////////////////
// Backtracking for peaceful queens.

/// \brief Initialize.
///
/// Initialize ready for bactracking.
/// \param A An array for the solution.
/// \param b Back-diagonal flags.
/// \param d Diagonal flags.
/// \param n The number of elements in the solution array.

void initialize(size_t A[], bool b[], bool d[], size_t n){
  for(size_t i=0; i<n; i++)
    A[i] = i;
  
  for(size_t i=0; i<2*n-1; i++)
    b[i] = d[i] = true;
} //initialize

/// \brief Backtrack for Peaceful Queens.
///
/// Backtrack for Peaceful Queens.
/// \param A An array for the solution.
/// \param b Back-diagonal flags.
/// \param d Diagonal flags.
/// \param m Current array element.
/// \param n The number of elements in the solution array.
/// \param count [in, out] Running count of number of solutions found.

void queen(size_t A[], bool b[], bool d[], size_t m, size_t n, size_t& count){
  if(m == 0){ //base of recursion
    print(A, n); //print to console
    ExportToSVG(A, n); //export as SVG file
    count++; //one more solution
  } //if
  
  else //recursive part
    for(int i=(int)m-1; i>=0; i--)
      if(b[A[i] + m - 1] && d[A[i] + n - m]){ //diagonal & back-diagonal unused
        std::swap(A[m], A[i]); //permute

        const size_t j = A[m] + m - 1; //back-diagonal index
        const size_t k = A[m] + n - m; //diagonal index

        b[j] = d[k] = false; //mark back-diagonal and diagonal used
        queen(A, b, d, m - 1, n, count); //recurse on smaller array
        b[j] = d[k] = true; //mark back-diagonal and diagonal unused

        std::swap(A[m], A[i]); //unpermute
      } //if
} //queen

/// \brief Backtrack for Peaceful Queens.
///
/// Backtrack for Peaceful Queens.
/// \param n Width and height of the chessboard in squares.

void queen(size_t n){
  size_t* A = new size_t[n]; //solution array
  bool* b = new bool[2*n - 1]; //back-diagonal array
  bool* d = new bool[2*n - 1]; //diagonal array

  size_t count = 0; //for number of solutions
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
  const size_t n = 6; //board size
  queen(n); //backtrack for peaceful queens

  return 0; //what could possibly go wrong?
} //main
