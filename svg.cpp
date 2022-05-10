/// \file svg.cpp
/// \brief SVG output for solutions to the Peaceful Queens problem.

#include <fstream>
#include <string>
#include <cmath>

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

/// \brief Make file name from array.
///
/// Concatenate the elements of an array into a string for use as a file name.
/// \param A An array.
/// \param n The number of elements in the array.
/// \return File name string.

std::string GetFileName(size_t A[], size_t n){
  std::string s; //for file name

  for(size_t i=0; i<n; i++) //for each array entry
    s += std::to_string(A[i]); //concatenate into string

  return s; //file name
} //GetFileName

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

/// \brief Output the queens stored in an array.
///
/// Output the SVG tags for queens stored in an array to an output stream.
/// \param ostream An output stream, assumed to be opened.
/// \param A An array containing the solution.
/// \param w Width of a chessboard square in pixels.
/// \param n Width and height of the chessboard in squares.

void SVGQueens(std::ofstream& ostream, size_t A[], size_t w, size_t n){
  const size_t delta = w/2; //half the width of a square

  for(size_t i=0; i<n; i++)
    SVGCircle(ostream, i*w + delta, A[i]*w + delta);
} //SVGSquare

/// \brief Output a solution to the Peaceful Queens problem in SVG format.
///
/// Output the SVG tags for a solution to the Peaceful Queens problem.
/// \param A An array containing the solution.
/// \param n The number of elements in the array.

void ExportToSVG(size_t A[], size_t n){
  const size_t w = 32; //width and height of chessboard squares in pixels

  std::ofstream ostream(GetFileName(A, n) + ".svg"); 

  SVGHeader(ostream, w*(n + 1));
  SVGStyle(ostream, (int)std::round(0.35f*w));
  SVGChessboard(ostream, w, n);
  SVGQueens(ostream, A, w, n);
  
  ostream << "</svg>" << std::endl;
} //ExportToSVG
