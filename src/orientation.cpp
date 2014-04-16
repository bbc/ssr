/******************************************************************************
 * Copyright © 2012-2014 Institut für Nachrichtentechnik, Universität Rostock *
 * Copyright © 2006-2012 Quality & Usability Lab,                             *
 *                       Telekom Innovation Laboratories, TU Berlin           *
 * Copyright © 2014 British Broadcasting Corporation                         *
 *                                                                            *
 * This file is part of the SoundScape Renderer (SSR).                        *
 *                                                                            *
 * The SSR is free software:  you can redistribute it and/or modify it  under *
 * the terms of the  GNU  General  Public  License  as published by the  Free *
 * Software Foundation, either version 3 of the License,  or (at your option) *
 * any later version.                                                         *
 *                                                                            *
 * The SSR is distributed in the hope that it will be useful, but WITHOUT ANY *
 * WARRANTY;  without even the implied warranty of MERCHANTABILITY or FITNESS *
 * FOR A PARTICULAR PURPOSE.                                                  *
 * See the GNU General Public License for more details.                       *
 *                                                                            *
 * You should  have received a copy  of the GNU General Public License  along *
 * with this program.  If not, see <http://www.gnu.org/licenses/>.            *
 *                                                                            *
 * The SSR is a tool  for  real-time  spatial audio reproduction  providing a *
 * variety of rendering algorithms.                                           *
 *                                                                            *
 * http://spatialaudio.net/ssr                           ssr@spatialaudio.net *
 ******************************************************************************/

/// @file
/// %Orientation class and helper function(s) (implementation).

#include <ostream>

#include "orientation.h"
#include "position.h"
#include "apf/math.h" // cos(), sin(), acos()
#include "ssr_global.h"

/** ctor.
 * @param azimuth azimuth (in degrees)
 * @param elevation elevation (in degrees)
 */
Orientation::Orientation(const float azimuth, const float elevation) :
  azimuth(azimuth),
  elevation(elevation)
{}

/** - operator.
 * @return difference of Orientations
 **/
Orientation operator-(const Orientation& lhs, const Orientation& rhs)
{
  return Orientation(lhs.azimuth - rhs.azimuth, lhs.elevation - rhs.elevation);
}

/** + operator.
 **/
Orientation operator+(const Orientation& lhs, const Orientation& rhs)
{
  return Orientation(lhs.azimuth + rhs.azimuth, lhs.elevation + rhs.elevation);
}

/** += operator.
 * @param other addend.
 * @return sum of Orientations
 **/
Orientation& Orientation::operator+=(const Orientation& other)
{
  azimuth += other.azimuth;
  elevation += other.elevation;
  return *this;
}

/** -= operator.
 * @param other minuend.
 * @return difference of Orientations
 **/
Orientation& Orientation::operator-=(const Orientation& other)
{
  azimuth -= other.azimuth;
  elevation -= other.elevation;
  return *this;
}

/** convert the orientation given by the orientation angles (yaw,pitch) to a
 * Position unit-length look vector.
 * @return Position with the corresponding unit-length 3D look vector
 * @warning this is not really a position, just a vector (maybe reconsider?)
 **/
Position Orientation::look_vector() const
{
  // angles phi and theta in radians!
  float phi = apf::math::deg2rad(azimuth);
  float theta = apf::math::deg2rad(elevation);
  return Position(cos(theta) * cos(phi), cos(theta) * sin(phi), sin(theta));
}

/** ._
 * @param yaw yaw rotation angle in degrees.
 * @param pitch pitch rotation angle in degrees.
 * @return the resulting orientation
 **/
Orientation& Orientation::rotate(float yaw, float pitch)
{
  this->azimuth += yaw;
  this->elevation += pitch;
  return *this;
}

Orientation& Orientation::rotate(const Orientation& rotation)
{
  return this->rotate(rotation.azimuth, rotation.elevation);
}

/** _.
 * @param a One orientation
 * @param b Another orientation
 * @return Angle between the two orientations in radians. If the angle of @a b
 * is bigger than the angle of @a a, the result is negative.
 **/
float angle(const Orientation& a, const Orientation& b)
{
  // angle between two vectors is arccos(dot product / mag*mag)
  Position a_vec = a.look_vector();
  Position b_vec = b.look_vector();
  float inner_product = a_vec.x * b_vec.x + a_vec.y * b_vec.y + a_vec.z * b_vec.z;
  return acos(inner_product / (a_vec.length() * b_vec.length()));
  // or
  // return angle(a.look_vector(), b.look_vector()); // see Position.h
}

/// output stream operator (<<)
std::ostream& operator<<(std::ostream& stream, const Orientation& orientation)
{
  stream << "azimuth = " << orientation.azimuth << ", elevation = " << orientation.elevation;
  return stream;
}

// Settings for Vim (http://www.vim.org/), please do not remove:
// vim:softtabstop=2:shiftwidth=2:expandtab:textwidth=80:cindent
// vim:fdm=expr:foldexpr=getline(v\:lnum)=~'/\\*\\*'&&getline(v\:lnum)!~'\\*\\*/'?'a1'\:getline(v\:lnum)=~'\\*\\*/'&&getline(v\:lnum)!~'/\\*\\*'?'s1'\:'='
