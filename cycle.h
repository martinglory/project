// The library to operate cycles in non-Euclidean geometry
//
//  Copyright (C) 2004-2014 Vladimir V. Kisil
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <stdexcept>
#include <ostream>
#include <sstream>
 using namespace std;

#include <ginac/ginac.h>
 using namespace GiNaC;

#define GINAC_VERSION_ATLEAST( major, minor) \
        (GINACLIB_MAJOR_VERSION > major \
        || (GINACLIB_MAJOR_VERSION == major && GINACLIB_MINOR_VERSION >= minor))

#define CYCLELIB_MAJOR_VERSION 1
#define CYCLELIB_MINOR_VERSION 2

/** Check of equality of two expression and report the string */
DECLARE_FUNCTION_1P(jump_fnct)

const string equality(const ex & E);
inline const string equality(const ex & E1, const ex & E2) { return equality(E1-E2);}
inline const string equality(const ex & E, const ex & solns1, const ex & solns2)
{ ex e = E; return equality(e.subs(solns1), e.subs(solns2));}

/** Return the string describing the case (elliptic, parabolic or hyperbolic)  */
const string eph_case(const numeric & sign);

/** Return even (real) part of a Clifford number */
ex scalar_part(const ex & e);

///** Return odd part of a Clifford number */
//inline ex clifford_part(const ex & e) { return normal(canonicalize_clifford(e - clifford_bar(e)))/numeric(2);}

/** Produces a Clifford matrix form of element of SL2 */
matrix sl2_clifford(const ex & a, const ex & b, const ex & c, const ex & d, const ex & e, bool not_inverse=true);

matrix sl2_clifford(const ex & M, const ex & e, bool not_inverse=true);


/** The class holding cycles kx^2-2<l,x>+m=0 */
class cycle : public basic
{
 GINAC_DECLARE_REGISTERED_CLASS(cycle, basic)

 public:
 cycle(const ex & k, const ex & l, const ex & m,
    const ex & metr = -(new tensdelta)->setflag(status_flags::dynallocated));
 cycle(const lst & l,
    const ex & metr = -(new tensdelta)->setflag(status_flags::dynallocated),
    const ex & r_squared = 0, const ex & e = 0,
    const ex & sign = (new tensdelta)->setflag(status_flags::dynallocated));
  
 cycle(const cycle & C, const ex & metr);

 cycle(const matrix & M, const ex & metr, const ex & e = 0, const ex & sign = 0);

 #if GINAC_VERSION_ATLEAST(1,5)
  void archive(archive_node &n) const;
  void read_archive(const archive_node &n, lst &sym_lst);
  return_type_t return_type_tinfo() const;
 #endif

 ex real_part() const;
 ex imag_part() const;

 protected:
  void do_print(const print_dflt & c, unsigned level) const;
 // void do_print_python(const print_dflt & c, unsigned level) const;
  void do_print_dflt(const print_dflt & c, unsigned level) const;
  void do_print_latex(const print_latex & c, unsigned level) const;

 public:
  virtual inline ex get_dim() const { return ex_to<varidx>(unit.op(1)).get_dim(); }
  virtual inline ex get_metric() const { return ex_to<clifford>(unit).get_metric(); }
  virtual inline ex get_metric(const ex &i0, const ex &i1) const
       { return ex_to<clifford>(unit).get_metric(i0, i1); }
  virtual inline ex get_k() const { return k; }
 inline ex get_l() const { return l; }
 inline ex get_l(const ex & i) const
 { return (l.is_zero()?0:l.subs(l.op(1) == i, subs_options::no_pattern)); }
 inline ex get_m() const {return m;}
 inline ex get_unit() const {return unit;}
 size_t nops() const {return 4;}
 ex op(size_t i) const;
 ex & let_op(size_t i);
 bool is_equal(const basic & other, bool projectively = true) const;
 bool is_zero() const;
 cycle subs(const ex & e, unsigned options = 0) const;
 inline cycle normal() const
  { return cycle(k.normal(), l.normal(), m.normal(), unit.normal());}
 inline cycle expand() const { return cycle(k.expand(), l.expand(), m.expand(), unit);}
 ex the_same_as(const basic & other) const;

 public:
 cycle normalize(const ex & k_new = numeric(1), const ex & e = 0) const;
 cycle normalize_det(const ex & e = 0,
   const ex & sign = (new tensdelta)->setflag(status_flags::dynallocated)) const;
 virtual ex center(const ex & metr = 0, bool return_matrix = false) const;
 virtual ex val(const ex & y) const;
 inline ex passing(const ex & y) const {return  val(y).numer().normal() == 0;}
 cycle subject_to(const ex & condition, const ex & vars = 0) const;
 virtual matrix to_matrix(const ex & e = 0,
      const ex & sign = (new tensdelta)->setflag(status_flags::dynallocated)) const;
 virtual ex det(const ex & e = 0,
   const ex & sign = (new tensdelta)->setflag(status_flags::dynallocated),
   const ex & k_norm = 0) const;
 virtual inline ex radius_sq(const ex & e = 0,
 					const ex & sign = (new tensdelta)->setflag(status_flags::dynallocated)) const
 	{ return this->det(e, sign, numeric(1));}
 virtual ex mul(const ex & C, const ex & e = 0,
      const ex & sign = (new tensdelta)->setflag(status_flags::dynallocated),
      const ex & sign1 =0) const;
 virtual cycle sl2_similarity(const ex & a, const ex & b, const ex & c, const ex & d,
 	const ex & e = 0,
 	const ex & sign = (new tensdelta)->setflag(status_flags::dynallocated),
 	bool not_inverse=true,
 	const ex & sign_inv = (new tensdelta)->setflag(status_flags::dynallocated)) const;
 virtual cycle sl2_similarity(const ex & M, const ex & e = 0,
       const ex & sign = (new tensdelta)->setflag(status_flags::dynallocated),
 	bool not_inverse=true,
       const ex & sign_inv = (new tensdelta)->setflag(status_flags::dynallocated)) const;
 virtual cycle matrix_similarity(const ex & M, const ex & e = 0,
       const ex & sign = (new tensdelta)->setflag(status_flags::dynallocated),
 	bool not_inverse=true,
       const ex & sign_inv = (new tensdelta)->setflag(status_flags::dynallocated)) const;
 virtual cycle matrix_similarity(const ex & a, const ex & b, const ex & c, const ex & d,
       const ex & e = 0,
       const ex & sign = (new tensdelta)->setflag(status_flags::dynallocated),
       bool not_inverse=true,
       const ex & sign_inv = (new tensdelta)->setflag(status_flags::dynallocated)) const;

 virtual cycle cycle_similarity(const cycle & C, const ex & e = 0,
         const ex & sign = (new tensdelta)->setflag(status_flags::dynallocated),
         const ex & sign1 = 0,
       const ex & sign_inv = (new tensdelta)->setflag(status_flags::dynallocated)) const;
 virtual inline ex moebius_map(const ex & P, const ex & e = 0,
        const ex & sign = (new tensdelta)->setflag(status_flags::dynallocated)) const
 {return clifford_moebius_map(to_matrix(e, sign), P, (e.is_zero()?get_metric():e));}
 virtual inline ex cycle_product(const cycle & C, const ex & e = 0,
 		const ex & sign = (new tensdelta)->setflag(status_flags::dynallocated)) const
 {return scalar_part(ex_to<matrix>(mul(C, e, sign)).trace());}
 virtual inline ex is_orthogonal(const cycle & C, const ex & e = 0,
    const ex & sign = (new tensdelta)->setflag(status_flags::dynallocated)) const
     {return (cycle_product(C, e, sign) == 0);}
 ex is_f_orthogonal(const cycle & C, const ex & e = 0,
 				   const ex & sign = (new tensdelta)->setflag(status_flags::dynallocated),
 				   const ex & sign1 = (new tensdelta)->setflag(status_flags::dynallocated),
 				   const ex & sign_inv = (new tensdelta)->setflag(status_flags::dynallocated)) const;
  inline ex is_linear() const {return (k == 0);}
  inline ex is_normalized() const {return (k == 1);}
 virtual cycle add(const cycle & rh) const;
 virtual cycle sub(const cycle & rh) const;
 virtual cycle exmul(const ex & rh) const;
 virtual cycle div(const ex & rh) const;

protected:
 ex unit; // A Clifford unit to store the dimensionality and metric of the point space
 ex k;
 ex l;
 ex m;
};
 GINAC_DECLARE_UNARCHIVER(cycle);

 const cycle operator+(const cycle & lh, const cycle & rh);
 const cycle operator-(const cycle & lh, const cycle & rh);
 const cycle operator*(const cycle & lh, const ex & rh);
 const cycle operator*(const ex & lh, const cycle & rh);
 const cycle operator/(const cycle & lh, const ex & rh);
 const ex operator*(const cycle & lh, const cycle & rh);


class cycle2D : public cycle
{
 GINAC_DECLARE_REGISTERED_CLASS(cycle2D, cycle)

 public:
 	cycle2D(const ex & k1, const ex & l1, const ex & m1,
 			const ex & metr = -unit_matrix(2));
 cycle2D(const lst & l, const ex & metr = -unit_matrix(2), const ex & r_squared =0,
   const ex & e =0, const ex & sign = unit_matrix(2));

 cycle2D(const matrix & M, const ex & metr, const ex & e = 0, const ex & sign = 0);


 cycle2D(const cycle & C, const ex & metr = 0);

 public:
 virtual inline ex hdet(const ex & e = 0,
   const ex & sign = (new tensdelta)->setflag(status_flags::dynallocated),
   const ex & k_norm = 0) const
   {return -det(e, sign, k_norm);}
  ex focus(const ex & e = diag_matrix(lst(-1, 1)), bool return_matrix = false) const;
  inline ex focal_length() const {return (get_l(1)/2/k);} // focal length of the cycle
  lst roots(const ex & y = 0, bool first = true) const;
  lst line_intersect(const ex & a, const ex & b) const;
  void metapost_draw(ostream & ost, const ex & xmin = -5, const ex & xmax = 5,
      const ex & ymin = -5, const ex & ymax = 5, const lst & color = lst(),
      const string more_options = "",
      bool with_header = true, int points_per_arc = 0, bool asymptote = false,
      const string picture = "", bool only_path=false, bool is_continuation=false) const;
 inline void asy_draw(ostream & ost, const string picture,
       const ex & xmin = -5, const ex & xmax = 5,
       const ex & ymin = -5, const ex & ymax = 5, const lst & color = lst(),
       const string more_options = "",
       bool with_header = true, int points_per_arc = 0) const
 { metapost_draw(ost, xmin, xmax, ymin, ymax, color, more_options, with_header,
     points_per_arc, true, picture); }

 inline void asy_draw(ostream & ost = std::cout,
       const ex & xmin = -5, const ex & xmax = 5,
       const ex & ymin = -5, const ex & ymax = 5, const lst & color = lst(),
       const string more_options = "",
       bool with_header = true, int points_per_arc = 0) const
 { metapost_draw(ost, xmin, xmax, ymin, ymax, color, more_options, with_header,
     points_per_arc, true); }
 inline void asy_path(ostream & ost = std::cout,
       const ex & xmin = -5, const ex & xmax = 5,
       const ex & ymin = -5, const ex & ymax = 5,
       int points_per_arc = 0, bool is_continuation = false) const
 { metapost_draw(ost, xmin, xmax, ymin, ymax, lst(), "", false,
    points_per_arc, true, "", true, is_continuation); }
 inline cycle2D subs(const ex & e, unsigned options = 0) const {
  return ex_to<cycle2D>(inherited::subs(e, options)); }
 inline cycle2D normalize(const ex & k_new = numeric(1), const ex & e = 0) const {
  return ex_to<cycle2D>(inherited::normalize(k_new, e)); }
 inline cycle2D normalize_det(const ex & e = 0) const {
  return ex_to<cycle2D>(inherited::normalize_det(e)); }
 inline cycle2D normal() const { return cycle2D(k.normal(), l.normal(), m.normal(), unit.normal());}
 inline cycle2D expand() const { return cycle2D(k.expand(), l.expand(), m.expand(), unit);}
 inline cycle2D subject_to(const ex & condition, const ex & vars = 0) const {
  return ex_to<cycle2D>(inherited::subject_to(condition, vars)); }

 // cycle2D(const archive_node &n, lst &sym_lst);
  void archive(archive_node &n) const;
  // ex unarchive(const archive_node &n, lst &sym_lst);
  void read_archive(const archive_node &n, lst &sym_lst);

 ex real_part() const;
 ex imag_part() const;

};
GINAC_DECLARE_UNARCHIVER(cycle2D);

 const cycle2D operator+(const cycle2D & lh, const cycle2D & rh);
 const cycle2D operator-(const cycle2D & lh, const cycle2D & rh);
 const cycle2D operator*(const cycle2D & lh, const ex & rh);
 const cycle2D operator*(const ex & lh, const cycle2D & rh);
 const cycle2D operator/(const cycle2D & lh, const ex & rh);
 const ex operator*(const cycle2D & lh, const cycle2D & rh);




