#line 4495 "cycle.nw"
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

#line 2787 "cycle.nw"
#include <cycle.h>
#define PRINT_CYCLE  c.s << "("; \
 k.print(c, level); \
 c.s << ", "; \
 l.print(c, level); \
 c.s << ", "; \
 m.print(c, level); \
 c.s << ")";

 GINAC_IMPLEMENT_REGISTERED_CLASS_OPT(cycle, basic,
           print_func<print_dflt>(&cycle::do_print).
									  //           print_func<print_python>(&cycle::do_print_python).
           print_func<print_latex>(&cycle::do_print_latex))

 GINAC_IMPLEMENT_REGISTERED_CLASS(cycle2D, cycle)
//,    print_func<print_dflt>(&cycle2D::do_print)


#if GINAC_VERSION_ATLEAST(1,5)
return_type_t cycle::return_type_tinfo() const
{
	if (is_a<numeric>(get_dim()))
		switch (ex_to<numeric>(get_dim()).to_int()) {
		case 2:
			return make_return_type_t<cycle2D>();
		default:
		return make_return_type_t<cycle>();
		}
	else
		return make_return_type_t<cycle>();
}
#endif
cycle::cycle() : unit(), k(), l(), m()
{
#if GINAC_VERSION_ATLEAST(1,5)
#else
 tinfo_key = &cycle::tinfo_static;
#endif
}

#line 2833 "cycle.nw"
cycle::cycle(const ex & k1, const ex & l1, const ex & m1, const ex & metr) // Main constructor
 : k(k1), m(m1)
{
	ex D, metric;

#line 2841 "cycle.nw"
	  if (is_a<indexed>(l1.simplify_indexed())) {
		  l = ex_to<indexed>(l1.simplify_indexed());
		  if (ex_to<indexed>(l).get_indices().size() == 1) {
			  D = ex_to<varidx>(ex_to<indexed>(l).get_indices()[0]).get_dim();
		  } else
			  throw(std::invalid_argument("cycle::cycle(): the second parameter should be an indexed object"
										  "with one varindex"));
	  } else if (is_a<matrix>(l1) && (min(ex_to<matrix>(l1).rows(), ex_to<matrix>(l1).cols()) ==1)) {
		  D = max(ex_to<matrix>(l1).rows(), ex_to<matrix>(l1).cols());
		  l = indexed(l1, varidx((new symbol)->setflag(status_flags::dynallocated), D));
	  } else if (l1.info(info_flags::list) && (l1.nops() > 0)) {
		  D = l1.nops();
		  l = indexed(matrix(1, l1.nops(), ex_to<lst>(l1)), varidx((new symbol)->setflag(status_flags::dynallocated), D));

#line 2858 "cycle.nw"
	} else if (not l1.simplify_indexed().is_zero()) {
		  throw(std::invalid_argument("cycle::cycle(): the second parameter should be an indexed object, "
									  "matrix or list"));
	  }

#line 2866 "cycle.nw"
	if (is_a<clifford>(metr)) {
		if (D.is_zero())
			D = ex_to<varidx>(metr.op(1)).get_dim();
		unit = clifford_unit(varidx(0, D), ex_to<clifford>(metr).get_metric());
	} else {
		if (D.is_zero()) {
			if (is_a<indexed>(metr))
				D = ex_to<varidx>(metr.op(1)).get_dim();
			else if (is_a<matrix>(metr))
				D = ex_to<matrix>(metr).rows();
			else {
				exvector indices = metr.get_free_indices();
				if (indices.size() == 2)
					D = ex_to<varidx>(indices[0]).get_dim();
			}
		}

#line 2885 "cycle.nw"
	if (D.is_zero())
		throw(std::invalid_argument("cycle::cycle(): the metric should be either tensor, "
									"matrix, Clifford unit or indexed by two indices. "
									"Otherwise supply the through the second parameter."));

unit = clifford_unit(varidx(0, D), metr);
	}
#line 2895 "cycle.nw"
/*	if (l1.is_zero()) {
		if (not D.is_zero()) {
			l = indexed(0, varidx((new symbol)->setflag(status_flags::dynallocated), D));
		}
		else
			throw(std::invalid_argument("cycle::cycle(): the second argument is zero and the metric  "
										"does not tell the dimensionality of space"));
										}*/
#if GINAC_VERSION_ATLEAST(1,5)
#else
 
#line 2911 "cycle.nw"
if (is_a<numeric>(D))
	switch (ex_to<numeric>(D).to_int()) {
	case 2:
		tinfo_key = &cycle2D::tinfo_static;
		break;
	default:
		tinfo_key = &cycle::tinfo_static;
		break;
	}
else
	tinfo_key = &cycle::tinfo_static;


#line 2906 "cycle.nw"
#endif
}

#line 2931 "cycle.nw"
cycle::cycle(const lst & l, const ex & metr, const ex & r_squared, const ex & e, const ex & sign)
{
	symbol m_temp;
	cycle C(numeric(1), l, m_temp, metr);
	(*this) = C.subject_to(lst(C.radius_sq(e, sign) == r_squared), lst(m_temp));
}

#line 2941 "cycle.nw"
cycle::cycle(const cycle & C, const ex & metr)
{
 (*this) = metr.is_zero()? C : cycle(C.get_k(), C.get_l(), C.get_m(), metr);
}

#line 2949 "cycle.nw"
cycle::cycle(const matrix & M, const ex & metr, const ex & e, const ex & sign)
{
	if (not (M.rows() == 2 && M.cols() == 2 && (M.op(0)+M.op(3)).normal().is_zero()))
		throw(std::invalid_argument("cycle::cycle(): the second argument should be square 2x2 matrix "
									"with M(1,1)=-M(2,2)"));

	
#line 3020 "cycle.nw"
ex e1, D;
if (e.is_zero()) {
	ex metr1;
	if (is_a<matrix>(metr)) {
		D = ex_to<matrix>(metr).cols();
		metr1 = metr;
	} else if (is_a<clifford>(metr)) {
		D = ex_to<varidx>(metr.op(1)).get_dim();
		metr1 = ex_to<clifford>(metr).get_metric();
	} else if (is_a<indexed>(metr)) {
		D = ex_to<varidx>(ex_to<indexed>(metr).get_indices()[0]).get_dim();
		metr1 = metr;
	} else
		throw(std::invalid_argument("Could not determine the dimensionality of point space "
									"from the supplied metric or Clifford unit"));
	
	e1 = clifford_unit(varidx((new symbol)->setflag(status_flags::dynallocated), D), metr1);
} else {
	e1 = e;
	D = ex_to<varidx>(e.op(1)).get_dim();
 }

#line 2956 "cycle.nw"
	varidx i0((new symbol)->setflag(status_flags::dynallocated), D),
	i1((new symbol)->setflag(status_flags::dynallocated), D, true);

#line 2962 "cycle.nw"
if (sign.is_zero()) {
	try {
		(*this) = cycle(remove_dirac_ONE(M.op(2)), clifford_to_lst(M.op(0), e1), remove_dirac_ONE(M.op(1)), metr);
	} catch  (std::exception &p) {
		(*this) = cycle(numeric(1), clifford_to_lst(M.op(0)*clifford_inverse(M.op(2)), e1),
						canonicalize_clifford(M.op(1)*clifford_inverse(M.op(2))), metr);
	}
} else {
	ex sign_m, conv;
	sign_m = sign.evalm();

#line 2975 "cycle.nw"
	if (is_a<tensor>(sign_m))
		conv = indexed(ex_to<tensor>(sign_m), i0, i1);
	else if (is_a<clifford>(sign_m)) {
		if (ex_to<varidx>(sign_m.op(1)).get_dim() == D)
			conv = ex_to<clifford>(sign_m).get_metric(i0, i1);
		else
			throw(std::invalid_argument("cycle::cycle(): the sign should be a Clifford unit with "
										"the dimensionality matching to the second parameter"));
	} else if (is_a<indexed>(sign_m)) {
		exvector ind = ex_to<indexed>(sign_m).get_indices();
		if ((ind.size() == 2) && (ex_to<varidx>(ind[0]).get_dim() == D) && (ex_to<varidx>(ind[1]).get_dim() == D))
			conv = sign_m.subs(lst(ind[0] == i0, ind[1] == i1));
		else
			throw(std::invalid_argument("cycle::cycle(): the sign should be an indexed object with two "
										"indices and their dimensionality matching to the second parameter"));

#line 2993 "cycle.nw"
	} else if (is_a<matrix>(sign_m)) {
		if ((ex_to<matrix>(sign_m).cols() == D) && (ex_to<matrix>(sign_m).rows() == D))
			conv = indexed(ex_to<matrix>(sign_m), i0, i1);
		else
			throw(std::invalid_argument("cycle::cycle(): the sign should be a square matrix with the "
										"dimensionality matching to the second parameter"));
	} else
		throw(std::invalid_argument("cycle::cycle(): the sign should be either tensor, indexed, matrix "
									"or Clifford unit"));

#line 3006 "cycle.nw"
	try {
		(*this) = cycle(remove_dirac_ONE(M.op(2)), indexed(matrix(1, ex_to<numeric>(D).to_int(),
																   clifford_to_lst(M.op(0), e1)), i0.toggle_variance())*conv, remove_dirac_ONE(M.op(1)), metr);
	} catch  (std::exception &p) {
		(*this) = cycle(numeric(1), indexed(matrix(1, ex_to<numeric>(D).to_int(), clifford_to_lst(M.op(0)
																								  *clifford_inverse(M.op(2)), e1)), i0.toggle_variance())*conv,
						canonicalize_clifford(M.op(1)*clifford_inverse(M.op(2))), metr);
	}
}
}

#line 3048 "cycle.nw"
ex cycle::op(size_t i) const
{
 GINAC_ASSERT(i<nops());

 switch (i) {
 case 0:
  return k;
 case 1:
  return l;
 case 2:
  return m;
 case 3:
  return unit;
 default:
  throw(std::invalid_argument("cycle::op(): requested operand out of the range (4)"));
 }
}

#line 3068 "cycle.nw"
ex & cycle::let_op(size_t i)
{
 GINAC_ASSERT(i<nops());

 ensure_if_modifiable();
 switch (i) {
 case 0:
  return k;
 case 1:
  return l;
 case 2:
  return m;
 case 3:
  return unit;
 default:
  throw(std::invalid_argument("cycle::let_op(): requested operand out of the range (4)"));
 }
}

#line 3089 "cycle.nw"
cycle cycle::subs(const ex & e, unsigned options) const
{
 exmap m;
 if (e.info(info_flags::list)) {
  lst l = ex_to<lst>(e);
  for (lst::const_iterator i = l.begin(); i != l.end(); ++i)
   m.insert(std::make_pair(i->op(0), i->op(1)));
 } else if (is_a<relational>(e)) {
  m.insert(std::make_pair(e.op(0), e.op(1)));
 } else
  throw(std::invalid_argument("cycle::subs(): the parameter should be a relational or a lst"));

 return ex_to<cycle>(inherited::subs(m, options));
}


#line 3113 "cycle.nw"
void cycle::archive(archive_node &n) const
{
	inherited::archive(n);
	n.add_ex("k-param", k);
	n.add_ex("l-param", l);
	n.add_ex("m-param", m);
	n.add_ex("unit", unit);
}

#line 3124 "cycle.nw"
void cycle::read_archive(const archive_node &n, lst &sym_lst) 
{
	inherited::read_archive(n, sym_lst);
	n.find_ex("k-param", k, sym_lst);
	n.find_ex("l-param", l, sym_lst);
	n.find_ex("m-param", m, sym_lst);
	n.find_ex("unit", unit, sym_lst);
}
GINAC_BIND_UNARCHIVER(cycle);


//const char *cycle::get_class_name() { return "cycle"; }

#line 3139 "cycle.nw"
int cycle::compare_same_type(const basic &other) const
{
       GINAC_ASSERT(is_a<cycle>(other));
	   return inherited::compare_same_type(other);
/*
	const cycle &o = static_cast<const cycle &>(other);
	if ((unit == o.unit) && (l*o.get_k() - o.get_l()*k).is_zero() && (m*o.get_k() - o.get_m()*k).is_zero())
		return 0;
	else if ((unit < o.unit)
			 || (l*o.get_k() < o.get_l()*k) || (m*o.get_k() < o.get_m()*k))
		return -1;
	else
		return 1;*/
}

#line 3156 "cycle.nw"
bool cycle::is_equal(const basic & other, bool projectively) const
{
	if (not is_a<cycle>(other))
		return false;
	const cycle o = ex_to<cycle>(other);
	ex factor=0, ofactor=0;

	if (projectively) {
		// Check that coefficients are scalar multiples of other 
		if (not (unit.is_equal(o.unit) && (m*o.get_k()-o.get_m()*k).normal().is_zero()))
			return false;
		// Set up coefficients for proportionality
		if (get_k().normal().is_zero()) {
			factor=get_m();
			ofactor=o.get_m();
		} else {
			factor=get_k();
			ofactor=o.get_k();
		}
			
	} else
		// Check the exact equality of coefficients
		if (not (unit.is_equal(o.unit) && (get_k()-o.get_k()).normal().is_zero()
				 && (get_m()-o.get_m()).normal().is_zero()))
			return false;


#line 3185 "cycle.nw"
	if (is_a<numeric>(get_dim())) {
		int D = ex_to<numeric>(get_dim()).to_int();
		if (! (is_a<numeric>(o.get_dim()) && D ==ex_to<numeric>(o.get_dim()).to_int()))
			return false;
		
		for (int i=0; i<D; i++)
			if (projectively) {
				// search the the first non-zero coefficient 
				if (factor.is_zero()) {
					factor=get_l(i);
					ofactor=o.get_l(i);
				} else
					if (! (get_l(i)*ofactor-o.get_l(i)*factor).normal().is_zero())
						return false;
			} else 
				if (! (get_l(i)-o.get_l(i)).normal().is_zero())
					return false;
		
		return true;
	} else
		return (l*ofactor-o.get_l()*factor).normal().is_zero();
}

#line 3212 "cycle.nw"
ex cycle::the_same_as(const basic & other) const
{
 if (! (is_a<cycle>(other) && (get_dim() == ex_to<cycle>(other).get_dim())))
  return lst(1==0);
 ex f=1, f1=1;
 lst res;

#line 3221 "cycle.nw"
 if (not k.is_zero()) {
  f = k;
  f1 = ex_to<cycle>(other).get_k();
  res.append(f1*m ==f*ex_to<cycle>(other).get_m());

#line 3228 "cycle.nw"
 } else if (not m.is_zero()) {
  f = m;
  f1 = ex_to<cycle>(other).get_m();
 }

#line 3235 "cycle.nw"
 if (ex_to<varidx>(unit.op(1)).is_numeric()) {
  int D = ex_to<numeric>(get_dim()).to_int();
  for (int i=0; i < D; ++i)
   res.append(f1*get_l(i)==f*ex_to<cycle>(other).get_l(i));
 } else
  res.append(f1*l==f*ex_to<cycle>(other).get_l());
 return res;
}


#line 3247 "cycle.nw"
bool cycle::is_zero() const
{
 return (k.is_zero() && l.is_zero() && m.is_zero());
}

#line 3254 "cycle.nw"
void cycle::do_print(const print_dflt & c, unsigned level) const
{
 PRINT_CYCLE
}

/*void cycle::do_print_python(const print_dflt & c, unsigned level) const
{
 PRINT_CYCLE
 }*/

void cycle::do_print_latex(const print_latex & c, unsigned level) const
{
 PRINT_CYCLE
}

#line 3274 "cycle.nw"
cycle cycle::add(const cycle & rh) const
{
	if (get_dim() != rh.get_dim())
		throw(std::invalid_argument("cycle::add(): cannot add two cycles from diferent dimensions"));

	ex ln=indexed(((get_l().is_zero()?0:get_l().op(0))+(rh.get_l().is_zero()?0:rh.get_l().op(0))).evalm(), 
				  varidx((new symbol)->setflag(status_flags::dynallocated), get_dim()));
	return cycle(get_k()+rh.get_k(), ln, get_m()+rh.get_m(), get_metric());
}
cycle cycle::sub(const cycle & rh) const
{
	if (get_dim() != rh.get_dim())
		throw(std::invalid_argument("cycle::add(): cannot subtract two cycles from diferent dimensions"));

	ex ln=indexed(((get_l().is_zero()?0:get_l().op(0))-(rh.get_l().is_zero()?0:rh.get_l().op(0))).evalm(), 
				  varidx((new symbol)->setflag(status_flags::dynallocated), get_dim()));
	return cycle(get_k()-rh.get_k(), ln, get_m()-rh.get_m(), get_metric());
}
cycle cycle::exmul(const ex & rh) const
{
	return cycle(get_k()*rh, indexed(get_l().is_zero() ? 0 : (get_l().op(0)*rh).evalm(), 
									 varidx((new symbol)->setflag(status_flags::dynallocated), get_dim())),
				 get_m()*rh, get_metric());
}
cycle cycle::div(const ex & rh) const
{
	return exmul(pow(rh, numeric(-1)));
}

#line 3305 "cycle.nw"
const cycle operator+(const cycle & lh, const cycle & rh)
{
 return lh.add(rh);
}
const cycle operator-(const cycle & lh, const cycle & rh)
{
 return lh.sub(rh);
}
const cycle operator*(const cycle & lh, const ex & rh)
{
 return lh.exmul(rh);
}
const cycle operator*(const ex & lh, const cycle & rh)
{
 return rh.exmul(lh);
}
const cycle operator/(const cycle & lh, const ex & rh)
{
 return lh.div(rh);
}
const ex operator*(const cycle & lh, const cycle & rh)
{
 return lh.mul(rh);
}

#line 3332 "cycle.nw"
const cycle2D operator+(const cycle2D & lh, const cycle2D & rh)
{
 return ex_to<cycle2D>(lh.add(rh));
}
const cycle2D operator-(const cycle2D & lh, const cycle2D & rh)
{
 return ex_to<cycle2D>(lh.sub(rh));
}
const cycle2D operator*(const cycle2D & lh, const ex & rh)
{
 return ex_to<cycle2D>(lh.exmul(rh));
}
const cycle2D operator*(const ex & lh, const cycle2D & rh)
{
 return ex_to<cycle2D>(rh.exmul(lh));
}
const cycle2D operator/(const cycle2D & lh, const ex & rh)
{
 return ex_to<cycle2D>(lh.div(rh));
}
const ex operator*(const cycle2D & lh, const cycle2D & rh)
{
 return ex_to<cycle2D>(lh.mul(rh));
}

#line 3365 "cycle.nw"
cycle cycle::normalize(const ex & k_new, const ex & e) const
{
	ex ratio = 0;
	if (k_new.is_zero()) // Make the determinant equal 1
		ratio = sqrt(radius_sq(e));
	else { // First non-zero coefficient among k, m, l_0, l_1, ... is set to k_new
		if (!k.is_zero())
			ratio = k/k_new;
		else if (!m.is_zero())
			ratio = m/k_new;
		else {
			int D = ex_to<numeric>(get_dim()).to_int();
			for (int i=0; i<D; i++)
				if (!l.subs(l.op(1) == i).is_zero()) {
					ratio = l.subs(l.op(1) == i)/k_new;
					break;
				}
		}
	}
	if (ratio.is_zero()) // No normalisation is possible
		return (*this);
	
	return cycle(k/ratio, indexed((l.op(0)/ratio).evalm().normal(), l.op(1)), (m/ratio).normal(), get_metric());
}

#line 3392 "cycle.nw"
cycle cycle::normalize_det(const ex & e, const ex & sign) const
{
	ex d = det(e, sign);
	return (d.is_zero()? *this: normalize(k/sqrt(d), e));
}


#line 3402 "cycle.nw"
ex cycle::center(const ex & metr, bool return_matrix) const
{
	if (is_a<numeric>(get_dim())) {
		ex e1, D = get_dim();
		if (metr.is_zero())
			e1 = unit;
		else {
			if (is_a<clifford>(metr))
				e1 = clifford_unit(varidx(0, D), ex_to<clifford>(metr).get_metric());
			else
				try {
					e1 = clifford_unit(varidx(0, D), metr);
				} catch (exception &p) {
					throw(std::invalid_argument("cycle::center(): supplied metric"
												" is not suitable for Clifford unit"));
				}
		}
		
#line 3426 "cycle.nw"
		lst c;
		for(int i=0; i<D; i++)
			if (k.is_zero())
				c.append(get_l(i));
			else
				//c.append(jump_fnct(-ex_to<clifford>(e1).get_metric(varidx(i, D), varidx(i, D)))*get_l(i)/k);
				c.append(-ex_to<clifford>(e1).get_metric(varidx(i, D), varidx(i, D))*get_l(i)/k);
		return (return_matrix? (ex)matrix(ex_to<numeric>(D).to_int(), 1, c) : (ex)c);
	} else {
		return l/k;
	}
}

#line 3449 "cycle.nw"
cycle cycle::subject_to(const ex & condition, const ex & vars) const
{
 lst vars1;
 if (vars.info(info_flags::list) &&(vars.nops() != 0))
   vars1 = ex_to<lst>(vars);
 else if (is_a<symbol>(vars))
   vars1 = lst(vars);
 else if ((vars == 0) || (vars.nops() == 0)) {
  if (is_a<symbol>(m))
   vars1.append(m);
  if (is_a<numeric>(get_dim()))
   for (int i = 0; i < ex_to<numeric>(get_dim()).to_double(); i++)
    if (is_a<symbol>(get_l(i)))
     vars1.append(get_l(i));
  if (is_a<symbol>(k))
   vars1.append(k);
  if (vars1.nops() == 0)
   throw(std::invalid_argument("cycle::subject_to(): could not construct the default list of "
          "parameters"));
 } else
  throw(std::invalid_argument("cycle::subject_to(): second parameter should be a list of symbols"
         " or a single symbol"));

 return subs(lsolve(condition.info(info_flags::relation_equal)? lst(condition) : condition,
        vars1), subs_options::algebraic | subs_options::no_pattern);
}


#line 3486 "cycle.nw"
matrix cycle::to_matrix(const ex & e, const ex & sign) const
{
	ex one, es, conv, D = get_dim();
	varidx i0((new symbol)->setflag(status_flags::dynallocated), D),
		i1((new symbol)->setflag(status_flags::dynallocated), D, true);
	if (e.is_zero()) {
		one = dirac_ONE();
		es = clifford_unit(i1.toggle_variance(), get_metric());
	} else if (is_a<clifford>(e)) {
		one = dirac_ONE(ex_to<clifford>(e).get_representation_label());
		es = e.subs(e.op(1) == i1.toggle_variance());
	} else if (is_a<tensor>(e) || is_a<indexed>(e) || is_a<matrix>(e)) {
		one = dirac_ONE();
		es = clifford_unit(i1.toggle_variance(), e);
	} else
		throw(std::invalid_argument("cycle::to_matrix(): expect a clifford number, matrix, tensor or "
									"indexed as the first parameter"));

#line 3506 "cycle.nw"
	ex sign_m = sign.evalm();

if (is_a<tensor>(sign_m))
	conv = indexed(ex_to<tensor>(sign_m), i0, i1);
else if (is_a<clifford>(sign_m)) {
	if (ex_to<varidx>(sign_m.op(1)).get_dim() == D)
		conv = ex_to<clifford>(sign_m).get_metric(i0, i1);
	else
		throw(std::invalid_argument("cycle::to_matrix(): the sign should be a Clifford unit with the "
									"dimensionality matching to the second parameter"));
} else if (is_a<indexed>(sign_m)) {
	exvector ind = ex_to<indexed>(sign_m).get_indices();
	if ((ind.size() == 2) && (ex_to<varidx>(ind[0]).get_dim() == D) && (ex_to<varidx>(ind[1]).get_dim() == D))
		conv = sign_m.subs(lst(ind[0] == i0, ind[1] == i1));
	else
		throw(std::invalid_argument("cycle::to_matrix(): the sign should be an indexed object with two "
									"indices and their dimensionality matching to the second parameter"));
} else if (is_a<matrix>(sign_m)) {
	if ((ex_to<matrix>(sign_m).cols() == D) && (ex_to<matrix>(sign_m).rows() == D))
		conv = indexed(ex_to<matrix>(sign_m), i0, i1);
	else
		throw(std::invalid_argument("cycle::to_matrix(): the sign should be a square matrix with the "
									"dimensionality matching to the second parameter"));
} else
	throw(std::invalid_argument("cycle::to_matrix(): the sign should be either tensor, indexed, "
								"matrix or Clifford unit"));

#line 3535 "cycle.nw"
	ex a00 = expand_dummy_sum(l.subs(ex_to<indexed>(l).get_indices()[0] == i0.toggle_variance()) * conv * es);

return matrix(2, 2, lst(a00, m * one, k * one, -a00));
}

#line 3547 "cycle.nw"
ex cycle::val(const ex & y) const
{
	ex y0, D = get_dim();
	varidx i0, i1;
	if (is_a<indexed>(y)) {
		i0 = ex_to<varidx>(ex_to<indexed>(y).get_indices()[0]);
		if ((ex_to<indexed>(y).get_indices().size() == 1) && (i0.get_dim() == D)) {
			y0 = ex_to<indexed>(y);
			i1 = varidx((new symbol)->setflag(status_flags::dynallocated), D);
		} else
			throw(std::invalid_argument("cycle::val(): the second parameter should be a indexed object with "
										"one varindex"));
	} else if (y.info(info_flags::list) && (y.nops() == D)) {
		i0 = varidx((new symbol)->setflag(status_flags::dynallocated), D);
		i1 = varidx((new symbol)->setflag(status_flags::dynallocated), D);
		y0 = indexed(matrix(1, y.nops(), ex_to<lst>(y)), i0);
	} else if (is_a<matrix>(y) && (min(ex_to<matrix>(y).rows(), ex_to<matrix>(y).cols()) ==1)
			   && (D == max(ex_to<matrix>(y).rows(), ex_to<matrix>(y).cols()))) {
		i0 = varidx((new symbol)->setflag(status_flags::dynallocated), D);
		i1 = varidx((new symbol)->setflag(status_flags::dynallocated), D);
		y0 = indexed(y, i0);
	} else
		throw(std::invalid_argument("cycle::val(): the second parameter should be a indexed object, "
									"matrix or list"));
	
	return expand_dummy_sum(-k*y0*y0.subs(i0 == i1)*get_metric(i0.toggle_variance(), i1.toggle_variance())
							- 2* l*y0.subs(i0 == ex_to<varidx>(ex_to<indexed>(l).get_indices()[0]).toggle_variance()) +m);
}

#line 3589 "cycle.nw"
ex cycle::det(const ex & e, const ex & sign, const ex & k_norm) const
{
	return remove_dirac_ONE((k_norm.is_zero()?*this:normalize(k_norm)).to_matrix(e, sign).determinant());
}


#line 3598 "cycle.nw"
ex cycle::mul(const ex & C, const ex & e, const ex & sign, const ex & sign1) const
{
	if (is_a<cycle>(C)) {
		return canonicalize_clifford(to_matrix(e, sign).mul(
										 ex_to<cycle>(C).to_matrix(e==0?get_unit():e, sign1.is_zero()?sign:sign1)));
	} else if (is_a<matrix>(C) && (ex_to<matrix>(C).rows() == 2)  && (ex_to<matrix>(C).cols() == 2)) {
		return canonicalize_clifford(to_matrix(e, sign).mul(ex_to<matrix>(C)));
	} else
		throw(std::invalid_argument("cycle::mul(): cannot multiply a cycle by anything but a cycle "
									"or 2x2 matrix"));
}

#line 3621 "cycle.nw"
cycle cycle::matrix_similarity(const ex & M, const ex & e, const ex & sign, bool not_inverse, const ex & sign_inv) const
{
	if (not (is_a<matrix>(M) && ex_to<matrix>(M).rows()==2 && ex_to<matrix>(M).cols()==2))
		throw(std::invalid_argument("cycle::matrix_similarity(): the first parameter sgould be a 2x2 matrix"));
	return matrix_similarity(M.op(0), M.op(1), M.op(2), M.op(3), e, sign, not_inverse, sign_inv);
}

#line 3631 "cycle.nw"
cycle cycle::matrix_similarity(const ex & a, const ex & b, const ex & c, const ex & d, const ex & e,
          const ex & sign, bool not_inverse, const ex & sign_inv) const
{
	matrix R=ex_to<matrix>(canonicalize_clifford(matrix(2,2,not_inverse?lst(a, b, c, d):lst(clifford_star(d), -clifford_star(b), -clifford_star(c), clifford_star(a)))
												 .mul(ex_to<matrix>(mul(matrix(2,2,not_inverse?lst(clifford_star(d), -clifford_star(b), -clifford_star(c), clifford_star(a)):lst(a, b, c, d)), e, sign)))
												 .evalm()).normal());

#line 3642 "cycle.nw"
 return cycle(matrix(2,2,lst((R.op(0)-R.op(3))/2,R.op(1),R.op(2),(-R.op(0)+R.op(3))/2)), get_metric(), e, sign_inv);
}

#line 3648 "cycle.nw"
cycle cycle::sl2_similarity(const ex & a, const ex & b, const ex & c, const ex & d, const ex & e, 
							const ex & sign, bool not_inverse, const ex & sign_inv) const
{
//	ex sign_inv=is_a<matrix>(sign)?pow(sign,-1):sign;
	relational sl2_rel = (c*b == (d*a-1));

#line 3657 "cycle.nw"
	ex det=(a*d-b*c).eval();
	if (is_a<numeric>(det) && (ex_to<numeric>(det).evalf() !=1)) 
		sl2_rel = (c*b==c*b);

#line 3663 "cycle.nw"
	matrix R=ex_to<matrix>(canonicalize_clifford(
							   sl2_clifford(a, b, c, d, e.is_zero()?unit:e, not_inverse)
							   .mul(ex_to<matrix>(mul(sl2_clifford(a, b, c, d, e.is_zero()?unit:e, !not_inverse), e, sign_inv)))
							   .evalm().subs(sl2_rel, subs_options::algebraic | subs_options::no_pattern)).normal());

#line 3670 "cycle.nw"
	return cycle(matrix(2,2,lst((R.op(0)-R.op(3))/2,R.op(1),R.op(2),(-R.op(0)+R.op(3))/2)), get_metric(), e, sign);
}

#line 3675 "cycle.nw"
cycle cycle::sl2_similarity(const ex & M, const ex & e, const ex & sign, bool not_inverse, const ex & sign_inv) const
{
	if (is_a<matrix>(M) || M.info(info_flags::list))
		return sl2_similarity(M.op(0), M.op(1), M.op(2), M.op(3), e, sign, not_inverse, sign_inv);
	else
		throw(std::invalid_argument("sl2_clifford(): expect a list or matrix as the first parameter"));
}

#line 3688 "cycle.nw"
cycle cycle::cycle_similarity(const cycle & C, const ex & e, const ex & sign, const ex & sign1, const ex & sign_inv) const
{
//	ex sign_inv=is_a<matrix>(sign)?pow(sign,-1):sign;
 return cycle(ex_to<matrix>(canonicalize_clifford(C.mul(mul(C, e, sign, sign1.is_zero()?sign:sign1), e.is_zero()?get_metric():e, sign1.is_zero()?sign:sign1))), get_metric(), e, sign_inv);
}

#line 3696 "cycle.nw"
ex cycle::is_f_orthogonal(const cycle & C, const ex & e, const ex & sign, const ex & sign1, const ex & sign_inv) const
{
	return (cycle(ex_to<matrix>(canonicalize_clifford(this->mul(C.mul(*this, e, sign, sign1.is_zero()?sign:sign1), e, sign1.is_zero()?sign:sign1))), get_metric(), e, sign_inv).get_l(get_dim()-1).normal() == 0);
//	return (C.cycle_similarity(*this, e, sign, sign1).get_l(get_dim()-1).normal() == 0);
}

#line 3709 "cycle.nw"
cycle2D::cycle2D() : inherited()
{
#if GINAC_VERSION_ATLEAST(1,5)
#else
 tinfo_key = &cycle2D::tinfo_static;
#endif
}

#line 3719 "cycle.nw"
cycle2D::cycle2D(const ex & k1, const ex & l1, const ex & m1, const ex & metr)
 : inherited(k1, l1, m1, metr)
{
 if (get_dim() != 2)
  throw(std::invalid_argument("cycle2D::cycle2D(): class cycle2D is defined in two dimensions"));
#if GINAC_VERSION_ATLEAST(1,5)
#else
 tinfo_key = &cycle2D::tinfo_static;
#endif
}

#line 3732 "cycle.nw"
cycle2D::cycle2D(const lst & l, const ex & r_squared, const ex & metr, const ex & e, const ex & sign)
 : inherited(l, r_squared, metr, e, sign)
{
 if (get_dim() != 2)
  throw(std::invalid_argument("cycle2D::cycle2D(): class cycle2D is defined in two dimensions"));
#if GINAC_VERSION_ATLEAST(1,5)
#else
 tinfo_key = &cycle2D::tinfo_static;
#endif
}

#line 3745 "cycle.nw"
cycle2D::cycle2D(const matrix & M, const ex & metr, const ex & e, const ex & sign)
 : inherited(M, metr, e, sign)
{
 if (get_dim() != 2)
  throw(std::invalid_argument("cycle2D::cycle2D(): class cycle2D is defined in two dimensions"));
#if GINAC_VERSION_ATLEAST(1,5)
#else
 tinfo_key = &cycle2D::tinfo_static;
#endif
}

#line 3758 "cycle.nw"
cycle2D::cycle2D(const cycle & C, const ex & metr)
{
 (*this) = cycle2D(C.get_k(), C.get_l(), C.get_m(), (metr.is_zero()? C.get_metric(): metr));
}

#line 3765 "cycle.nw"
void cycle2D::archive(archive_node &n) const
{
	inherited::archive(n);
}

//cycle2D::cycle2D(const archive_node &n, lst &sym_lst) : inherited(n, sym_lst) {; }

void cycle2D::read_archive(const archive_node &n, lst &sym_lst)
{
	inherited::read_archive(n, sym_lst);
}
GINAC_BIND_UNARCHIVER(cycle2D);

int cycle2D::compare_same_type(const basic &other) const
{
       GINAC_ASSERT(is_a<cycle2D>(other));
	return inherited::compare_same_type(other);
}

//const char *cycle2D::get_class_name() { return "cycle2D"; }

#line 3797 "cycle.nw"
ex cycle2D::focus(const ex & e, bool return_matrix) const
{
	lst f=lst(//jump_fnct(-get_metric(varidx(0, 2), varidx(0, 2)))*
		get_l(0)/k,
		(-det(e)/(2*get_l(1)*k)).normal());
	return (return_matrix? (ex)matrix(2, 1, f) : (ex)f);
}

#line 3807 "cycle.nw"
lst cycle2D::roots(const ex & y, bool first) const
{
 ex D = get_dim();
 lst k_sign = lst(-k*get_metric(varidx(0, D), varidx(0, D)), -k*get_metric(varidx(1, D), varidx(1, D)));
 int i0 = (first?0:1), i1 = (first?1:0);
 ex c = k_sign.op(i1)*pow(y, 2) - numeric(2)*get_l(i1)*y+m;
 if (k_sign.op(i0).is_zero())
  return (get_l(i0).is_zero() ? lst() : lst(c/get_l(i0)/numeric(2)));
 else {
  ex disc = sqrt(pow(get_l(i0), 2) - k_sign.op(i0)*c);
  return lst((get_l(i0)-disc)/k_sign.op(i0), (get_l(i0)+disc)/k_sign.op(i0));
 }
}

#line 3823 "cycle.nw"
lst cycle2D::line_intersect(const ex & a, const ex & b) const
{
 ex D = get_dim();
 ex pm = -k*get_metric(varidx(1, D), varidx(1, D));
 return cycle2D(k*(numeric(1)+pm*pow(a,2)).normal(), lst((get_l(0)+get_l(1)*a-pm*a*b).normal(), 0), (m-2*get_l(1)*b+pm*pow(b,2)).normal()).roots();
}

#line 3836 "cycle.nw"
inline ex max(const ex &a, const ex &b) {return ex_to<numeric>((a-b).evalf()).is_positive()?a:b;}
inline ex min(const ex &a, const ex &b) {return ex_to<numeric>((a-b).evalf()).is_positive()?b:a;}

#line 3841 "cycle.nw"
#define PAIR(X, Y)  ex_to<numeric>((X).evalf()).to_double() << "," << \
   ex_to<numeric>((Y).evalf()).to_double()
#define DRAW_ARC(X, S)   u = ex_to<numeric>((X).evalf()).to_double(); \
    v = ex_to<numeric>(roots(X, !not_swapped).op(zero_or_one).evalf()).to_double(); \
    du = dir*(-k_d*signv*v+lv);    \
    dv = dir*(k_d*signu*u-lu);        \
    if (not_swapped)            \
     ost << S <<  u << "," << v << "){" << du << "," << dv << "}"; \
    else                \
     ost << S <<  v << "," << u << "){" << (sign == 0? dv : -dv) << "," << (sign == 0? du : -du) << "}";

#line 3854 "cycle.nw"
bool is_almost_zero(const ex & x)
{
	if (is_a<numeric>(x))
		return (abs(ex_to<numeric>(x).to_double()) < 0.0000000001);
	else
		return x.is_zero();
}

#line 3864 "cycle.nw"
bool is_almost_negative(const ex & x)
{
	if (is_a<numeric>(x))
		return (ex_to<numeric>(x.evalf()).to_double() < 0.0000000001);
	else
		return x.is_zero();
}

#line 3874 "cycle.nw"
void cycle2D::metapost_draw(ostream & ost, const ex & xmin, const ex & xmax, const ex & ymin, const ex & ymax,
 const lst & color, const string more_options, bool with_header,
 int points_per_arc, bool asymptote, const string picture, bool only_path,
 bool is_continuation) const
{
 ex D = get_dim();
 ostringstream draw_start, draw_options;
 string already_drawn =(is_continuation? "^^(" : "(" ); // Was any arc already drawn?
 draw_start << "draw" << (asymptote ? "(" : " ") << picture << (picture.size()==0? "" : ",") << "(";
 ios_base::fmtflags keep_flags = ost.flags(); // Keep stream's flags to be restored on the exit
 draw_options.flags(keep_flags); // Synchronise flags between the streams
 draw_options.precision(ost.precision()); // Synchronise flags between the streams

#line 3890 "cycle.nw"
 ost << fixed;
 draw_options << fixed;
 if (color.nops() == 3) {
  if (asymptote)
   draw_options  << ",rgb("
       << ex_to<numeric>(color.op(0)).to_double() << ","
       << ex_to<numeric>(color.op(1)).to_double() <<","
       << ex_to<numeric>(color.op(2)).to_double() << ")";
  else
   draw_options  << showpos << " withcolor "
       << ex_to<numeric>(color.op(0)).to_double() << "*red"
       << ex_to<numeric>(color.op(1)).to_double() <<"*green"
       << ex_to<numeric>(color.op(2)).to_double() << "*blue ";
 }
 if (more_options != "") {
	 if (color.nops() == 3)
		 draw_options << "+";
	 else
		 draw_options << ",";
	 draw_options << more_options;
 }
 draw_options << (asymptote ? ");" : ";") << endl;

#line 3916 "cycle.nw"
 if (with_header)
  ost << (asymptote ? "// Asymptote" : "% Metapost") << " data in [" << xmin << ","
   << xmax << "]x[" << ymin << ","
   << ymax << "] for " << (ex)passing(lst(symbol("u"), symbol("v")));

 if (k.is_zero() && l.subs(l.op(1) == 0).is_zero() && l.subs(l.op(1) == 1).is_zero() && \
m.is_zero()) {
  ost << " zero cycle, (whole plane) " << endl;
  ost.flags(keep_flags);
  return;
 }

#line 3932 "cycle.nw"
	ex xc = center().op(0).evalf(), yc = center().op(1).evalf(); // the center of cycle
double sign0 = ex_to<numeric>(-get_metric(varidx(0, D), varidx(0, D)).evalf()).to_double(),
	sign1 = ex_to<numeric>(-get_metric(varidx(1, D), varidx(1, D)).evalf()).to_double(),
	sign = sign0 * sign1;
double determinant = ex_to<numeric>(radius_sq().evalf()).to_double();
 double epsilon=0.0000000001;
 bool not_swapped = (sign>0 || sign1==0 || ((sign <0) && (determinant < epsilon)));
double signu = (not_swapped?sign0:sign1), signv = (not_swapped?sign1:sign0);
int iu = (not_swapped?0:1), iv = (not_swapped?1:0);
ex umin =  (not_swapped ? xmin : ymin), umax =  (not_swapped ? xmax : ymax),
	vmin =  (not_swapped ? ymin:  xmin), vmax =  (not_swapped ? ymax : xmax),
	uc =  (not_swapped ? xc:  yc), vc =  (not_swapped ? yc : xc);
lst b_roots = roots(vmin, not_swapped), t_roots = roots(vmax, not_swapped);

#line 3964 "cycle.nw"
if (b_roots.nops() != 2) { // a linear object
	if (get_k().is_zero() && get_l(0).is_zero() && get_l(1).is_zero()) {
		if (with_header)
			ost << " the zero-radius cycle at infinity" << endl;
		return;
	}
	if (with_header)
		ost << " (straight line)" << endl;
	ex u1, u2, v1, v2;
	if (b_roots.nops() == 1){ // a "non-horisontal" line
		u1 = max(min(b_roots.op(0), umax), umin);
		u2 = min(max(t_roots.op(0), umin), umax);
	} else { // a "horisontal" line
		u1 = umin;
		u2 = umax;
	}

#line 3983 "cycle.nw"
if (get_l(iv).is_zero()) { // a vertical line
	if (ex_to<numeric>((b_roots.op(0)- umin).evalf()).is_positive()
		&& ex_to<numeric>((umax-b_roots.op(0)).evalf()).is_positive()) {
		v1 =  vmin;
		v2 =  vmax;
	} else { // out of scope
		ost.flags(keep_flags);
		return;
	}

#line 3995 "cycle.nw"
} else {
	v1 = roots(u1, !not_swapped).op(0);
	v2 = roots(u2, !not_swapped).op(0);
	if ((max(v1, v2) > vmax) || (min(v1, v2) < vmin)) {
		ost.flags(keep_flags);
		return; //out of scope
	}
}

#line 4006 "cycle.nw"
ost <<  (only_path ? already_drawn : draw_start.str()) << PAIR(not_swapped ? u1: v1, not_swapped ? v1: u1)
	<< ")--(" << PAIR(not_swapped ? u2: v2, not_swapped ? v2: u2) << ")"
																	 << (only_path ? "" : draw_options.str());
already_drawn="^^(";
if (with_header)
	ost << endl;
ost.flags(keep_flags);
return;
}

#line 4019 "cycle.nw"
ex left[2] = {max(min(uc, umax), umin),
			  max(min(uc, umax), umin)},
    right[2] = {max(min(uc, umax), umin),
        max(min(uc, umax), umin)};
//if (!ex_to<numeric>((k*signu).evalf()).is_positive()) { // rearrange to have minimum value first
//}
if (ex_to<numeric>(b_roots.op(0).evalf()).is_real()) {
	if (ex_to<numeric>((b_roots.op(0)-b_roots.op(1)).evalf()).is_positive())
		b_roots = lst(b_roots.op(1), b_roots.op(0)); // rearrange to have minimum value first
	left[0] = min(max(b_roots.op(0), umin), umax);
	right[0] = max(min(b_roots.op(1), umax), umin);
}
if (ex_to<numeric>(t_roots.op(0).evalf()).is_real()) {
	if (ex_to<numeric>((t_roots.op(0)-t_roots.op(1)).evalf()).is_positive())
		t_roots = lst(t_roots.op(1), t_roots.op(0)); // rearrange to have minimum value first
	left[1] = min(max(t_roots.op(0), umin), umax);
	right[1] = max(min(t_roots.op(1), umax), umin);
}

#line 3952 "cycle.nw"
	if (sign > 0) { // elliptic metric
		
#line 4043 "cycle.nw"
if (determinant > epsilon) {
 ex r = sqrt(radius_sq()), u[2][4], v[2][4];
 if (with_header)
  ost << " /circle of radius " << r  << endl;

#line 4050 "cycle.nw"
 if (ex_to<numeric>((vc-vmax).evalf()).is_positive()) {
  u[0][2] = left[1]; u[0][3] = right[1];
  u[1][2] = left[0]; u[1][3] = right[0];
  u[0][0] = u[1][0] = uc;
  u[0][1] = u[1][1] = uc;

#line 4058 "cycle.nw"
 } else if (ex_to<numeric>((vc-vmin).evalf()).is_positive()) {
  u[0][0] = left[1]; u[0][1] = right[1]; u[0][2] = right[0]; u[0][3] = left[0];
  if (ex_to<numeric>((uc-r-umin).evalf()).is_positive())
   u[1][0] = u[1][3] = uc-r;
  else
   u[1][0] = u[1][3] = umin;

  if (ex_to<numeric>((umax-uc-r).evalf()).is_positive())
   u[1][1] = u[1][2] = uc+r;
  else
   u[1][1] = u[1][2] = umax;

#line 4072 "cycle.nw"
 } else {
  u[0][0] = left[1]; u[0][1] = right[1];
  u[1][0] = left[0]; u[1][1] = right[0];
  u[0][2] = u[1][2] = uc;
  u[0][3] = u[1][3] = uc;
 }


#line 4083 "cycle.nw"
 lst y_roots;
 for (int j=0; j<2; j++)
  for (int i=0; i<4; i++)
   if ((u[j][i]-uc).evalf().is_zero()) // Touch the horizontal boundary?
    v[j][i] = (i==0 || i ==1? vc+r : vc-r);
   else if ((u[j][i]-uc-r).evalf().is_zero() || (u[j][i]-uc+r).evalf().is_zero()) // Touch the vertical boundary?
    v[j][i] = vc;
   else {
    y_roots = roots(u[j][i], false);
    if (ex_to<numeric>(y_roots.op(0).evalf()).is_real()) { // does circle intersect the boundary?
     if (i<2)
      v[j][i] = min(max(y_roots.op(0), y_roots.op(1)), vmax);
     else
      v[j][i] = max(min(y_roots.op(0), y_roots.op(1)), vmin);
    } else
     v[j][i] = vc;
   }

#line 4105 "cycle.nw"
 for (int i=0; i<4; i++) {// actual drawing of four arcs
  int s = (i==0 || i ==2? -1:1);
  if ((u[0][i] != u[1][i]) || (v[0][i] != v[1][i])) {// do not draw empty arc
   ost << "  " << (only_path ? already_drawn : draw_start.str()) << PAIR(u[0][i], v[0][i]) << "){" << PAIR(s*(v[0][i]-vc), s*(uc-u[0][i]))
    << (asymptote ? "}::{" : "}...{")
//   << (asymptote ? "}.. tension atleast 1.5 ..{" : "}...{") // temporary fix
    << PAIR(s*(v[1][i]-vc), s*(uc-u[1][i])) << "}(" << PAIR(u[1][i], v[1][i]) << ")"
    << (only_path ? "" : draw_options.str());
   already_drawn="^^(";
  }
 }

#line 4120 "cycle.nw"
} else if (is_almost_zero(radius_sq())) {
	if (with_header)
		ost << " /circle of zero-radius" << endl;
	
#line 4127 "cycle.nw"
	double U=ex_to<numeric>(uc.evalf()).to_double();
	double V=ex_to<numeric>(vc.evalf()).to_double();
	if ((umin <=U) && (umax>=U) && (vmin<=V) && (vmax>=V)) {
		ost << (asymptote ? (only_path ? already_drawn : "dot(") : "draw " ) << picture << (picture.size()==0? "" : ",")
			<< (only_path ? "" : "(")
			<< PAIR(uc, vc) << ")" << (only_path ? "" : draw_options.str());
	already_drawn="^^(";

#line 4137 "cycle.nw"
	} else
		if (with_header)
			ost << "// the vertex is out of range" << endl;


#line 4143 "cycle.nw"
} else
	if (with_header)
		ost << " /circle of imaginary radius--not drawing" << endl;

#line 3954 "cycle.nw"
			} else { // parabolic or hyperbolic  metric
		
#line 4150 "cycle.nw"
double u, v, du, dv, k_d = ex_to<numeric>(k.evalf()).to_double(),
                 lu = ex_to<numeric>(get_l(iu).evalf()).to_double(),
                 lv = ex_to<numeric>(get_l(iv).evalf()).to_double();

bool change_branch = (sign != 0); // either to do a swap of branches
int zero_or_one = (sign == 0 || k_d*signv > 0 ? 0 : 1); // for parabola and positive k take first

if (sign == 0) {
 
#line 4167 "cycle.nw"
if (sign0 == 0 && get_l(0).is_zero()) {
	if (with_header)
		ost << " /parabola degenerated into two horizontal lines" << endl;
	cycle2D(0, lst(0, 1), 2*b_roots.op(0), get_metric()).metapost_draw(ost, xmin, xmax, ymin, ymax, color, more_options,
																	   false, 0, asymptote, picture, only_path, is_continuation);
	cycle2D(0, lst(0, 1), 2*b_roots.op(1), get_metric()).metapost_draw(ost, xmin, xmax, ymin, ymax, color, more_options,
																	   false, 0, asymptote, picture, only_path, true);
	if (with_header)
		ost << endl;
	ost.flags(keep_flags);
	return;

#line 4181 "cycle.nw"
} else if (sign1 == 0 && get_l(1).is_zero()) {
	if (with_header)
		ost << " /parabola degenerated into two vertical lines" << endl;
	cycle2D(0, lst(1, 0), 2*b_roots.op(0), get_metric()).metapost_draw(ost, xmin, xmax, ymin, ymax, color, more_options,
																	   false, 0, asymptote, picture, only_path, is_continuation);
	cycle2D(0, lst(1, 0), 2*b_roots.op(1), get_metric()).metapost_draw(ost, xmin, xmax, ymin, ymax, color, more_options,
																	   false, 0, asymptote, picture, only_path, true);
	if (with_header)
		ost << endl;
	ost.flags(keep_flags);
	return;
}


#line 4198 "cycle.nw"
if (with_header)
	ost << " /parabola" << endl;
 if (ex_to<numeric>((right[0]-left[0]).evalf()).is_positive() && ex_to<numeric>((right[1]-left[1]).evalf()).is_positive()) {
	if (k_d*(signu*lv+signv*lu) > 0) { //rearrange intervals
		ex e = left[1]; left[1] = right[0]; right[0] = left[0]; left[0] =e;
	} else {
		ex e = left[1]; left[1] = right[1]; right[1] = right[0]; right[0] =e;
	}
 }

#line 4217 "cycle.nw"
for (int i =0; i < 2; i++) {
	if (ex_to<numeric>((right[i]-left[i]).evalf()).is_positive()) { // a proper branch of a parabola
		ex cp[8];
		if (not_swapped) {
			cp[0] = left[i];
			cp[1] = val(lst(cp[0],0))/2/get_l(1);
			cp[6] = right[i];
			cp[7] = val(lst(cp[6],0))/2/get_l(1);
			cp[2] = numeric(2,3)*cp[0]+numeric(1,3)*cp[6];
			cp[3] = (numeric(1,6)*cp[0]*cp[0]*k + numeric(1,3)*cp[0]*cp[6]*k
					 - numeric(2,3)*cp[0]*get_l(0)- numeric(1,3)*get_l(0)*cp[6]+m/2)/get_l(1);
			cp[4] = numeric(1,3)*cp[0]+numeric(2,3)*cp[6];
			cp[5] = (numeric(1,3)*cp[0]*k*cp[6]-numeric(1,3)*cp[0]*get_l(0)
					 -numeric(2,3)*get_l(0)*cp[6]+numeric(1,6)*k*cp[6]*cp[6]+m/2)/get_l(1);

#line 4234 "cycle.nw"
  } else {
			cp[1] = left[i];
			cp[0] = val(lst(0,cp[1]))/2/get_l(0);
			cp[7] = right[i];
			cp[6] = val(lst(0,cp[7]))/2/get_l(0);
			cp[3] = numeric(2,3)*cp[1]+numeric(1,3)*cp[7];
			cp[2] = (numeric(1,6)*cp[1]*cp[1]*k + numeric(1,3)*cp[1]*cp[7]*k
					 - numeric(2,3)*cp[1]*get_l(1)- numeric(1,3)*get_l(1)*cp[7]+m/2)/get_l(0);
			cp[5] = numeric(1,3)*cp[1]+numeric(2,3)*cp[7];
			cp[4] = (numeric(1,3)*cp[1]*k*cp[7]-numeric(1,3)*cp[1]*get_l(1)
					 -numeric(2,3)*get_l(1)*cp[7]+numeric(1,6)*k*cp[7]*cp[7]+m/2)/get_l(0);
  }

#line 4249 "cycle.nw"
	ost <<  (only_path ? already_drawn : draw_start.str()) << PAIR(cp[0], cp[1]) << ") .. controls (";
if (asymptote)
	ost <<  PAIR(cp[2], cp[3]) << ") and (" <<  PAIR(cp[4], cp[5]) << ") .. (";
else
	ost <<  "(" << PAIR(cp[2], cp[3]) << ")) and ((" <<  PAIR(cp[4], cp[5]) << ")) .. (";
ost <<  PAIR(cp[6], cp[7]) << ")" << (only_path ? "" : draw_options.str());
already_drawn="^^(";
	}
}

#line 4159 "cycle.nw"
} else {
 
#line 4262 "cycle.nw"
if (abs(determinant)<epsilon) {
	if (with_header)
		ost << " / a light cone at (" << xc << "," << yc <<")" << endl;
	cycle2D(0, lst(1, 1), 2*(uc+vc), get_metric()).metapost_draw(ost, xmin, xmax, ymin, ymax, color, more_options,
																 false, 0, asymptote, picture, only_path, is_continuation);
	cycle2D(0, lst(1, -1), 2*(uc-vc), get_metric()).metapost_draw(ost, xmin, xmax, ymin, ymax, color, more_options,
																  false, 0, asymptote, picture, only_path, true);

#line 4272 "cycle.nw"
   
#line 4127 "cycle.nw"
	double U=ex_to<numeric>(uc.evalf()).to_double();
	double V=ex_to<numeric>(vc.evalf()).to_double();
	if ((umin <=U) && (umax>=U) && (vmin<=V) && (vmax>=V)) {
		ost << (asymptote ? (only_path ? already_drawn : "dot(") : "draw " ) << picture << (picture.size()==0? "" : ",")
			<< (only_path ? "" : "(")
			<< PAIR(uc, vc) << ")" << (only_path ? "" : draw_options.str());
	already_drawn="^^(";

#line 4137 "cycle.nw"
	} else
		if (with_header)
			ost << "// the vertex is out of range" << endl;

#line 4273 "cycle.nw"
	if (with_header)
		ost << endl;
	ost.flags(keep_flags);
	return;

#line 4280 "cycle.nw"
} else {
 if (with_header)
  ost << " /hyperbola" << endl;
 if (ex_to<numeric>((vmin-vc).evalf()).is_positive()) {
  ex e = left[1]; left[1] = right[0]; right[0] = left[0]; left[0] =e;
  change_branch = false;
  zero_or_one = (k_d*signv > 0 ? 1 : 0);
 }
 if (ex_to<numeric>((vc-vmax).evalf()).is_positive()) {
  ex e = left[1]; left[1] = right[1]; right[1] = right[0]; right[0] =e;
  change_branch = false;
  zero_or_one = (k_d*signv > 0 ? 0 : 1);
 }
}

#line 4297 "cycle.nw"
int points = (points_per_arc == 0? 7 : points_per_arc);
for (int i =0; i < 2; i++) {
	double dir = ex_to<numeric>(csgn(signv*(2*zero_or_one-1))).to_double(); //direction of the tangent vectors
	// double dir = ((sign == 0? lv : signv*(2*zero_or_one-1))<0?-1:1); direction of the tangent vectors (second alternative)
	if (ex_to<numeric>((right[i]-left[i]).evalf()).is_positive()) { // a proper branch of the hyperbola
		ex f_left=asinh((left[i]-uc)/sqrt(abs(determinant))),
			f_right=asinh((right[i]-uc)/sqrt(abs(determinant)));
		DRAW_ARC(sinh(f_left)*sqrt(abs(determinant))+uc, (only_path ? already_drawn : draw_start.str()));
		for (int j=1; j<points; j++) {
			DRAW_ARC(sinh(f_left*(1.0-j/(points-1.0))+f_right*j/(points-1.0))*sqrt(abs(determinant))+uc,
					 (asymptote ? "::(" : "...(") );
		}
		ost << (only_path ? "" : draw_options.str());
		already_drawn="^^(";
	}
	if (change_branch)
		zero_or_one = 1 - zero_or_one; // make a swap for the next branch of hyperbola
 }

#line 4161 "cycle.nw"
}

#line 3956 "cycle.nw"
			}
ost << endl;
ost.flags(keep_flags);
return;
}

#line 4327 "cycle.nw"
//////////
// Jump function
//////////

static ex jump_fnct_evalf(const ex & arg)
{
 if (is_exactly_a<numeric>(arg)) {
  if ((ex_to<numeric>(arg).is_real() && ex_to<numeric>(arg).is_positive()) || ex_to<numeric>(arg).is_zero())
   return numeric(1);
  else
   return numeric(-1);
 }

 return jump_fnct(arg).hold();
}

#line 4345 "cycle.nw"
static ex jump_fnct_eval(const ex & arg)
{
 if (is_exactly_a<numeric>(arg)) {
  if ((ex_to<numeric>(arg).is_real() && ex_to<numeric>(arg).is_positive()) || ex_to<numeric>(arg).is_zero())
   return numeric(1);
  else
   return numeric(-1);
 } else if (is_exactly_a<mul>(arg) &&
      is_exactly_a<numeric>(arg.op(arg.nops()-1))) {
  numeric oc = ex_to<numeric>(arg.op(arg.nops()-1));
  if (oc.is_real()) {
   if (oc > 0)
    // jump_fnct(42*x) -> jump_fnct(x)
    return jump_fnct(arg/oc).hold();
   else
    // jump_fnct(-42*x) -> jump_fnct(-x)
    return jump_fnct(-arg/oc).hold();
  }
 }
 return jump_fnct(arg).hold();
}

#line 4369 "cycle.nw"
static ex jump_fnct_conjugate(const ex & arg)
{
 return jump_fnct(arg);
}

#line 4376 "cycle.nw"
static ex jump_fnct_power(const ex & arg, const ex & exp)
{
 if (is_a<numeric>(exp) && ex_to<numeric>(exp).is_integer()) {
  if (ex_to<numeric>(exp).is_even())
   return numeric(1);
  else
   return jump_fnct(arg);
 }
 if (is_a<numeric>(exp) && ex_to<numeric>(-exp).is_positive())
  return ex_to<basic>(pow(jump_fnct(arg), -exp)).hold();
 return ex_to<basic>(pow(jump_fnct(arg), exp)).hold();
}

#line 4391 "cycle.nw"
static void jump_fnct_print_dflt_text(const ex & x, const print_context & c)
{
 c.s << "H("; x.print(c); c.s << ")";
}

static void jump_fnct_print_latex(const ex & x, const print_context & c)
{
 c.s << "\\chi("; x.print(c); c.s << ")";
}

#line 4403 "cycle.nw"
REGISTER_FUNCTION(jump_fnct, eval_func(jump_fnct_eval).
      evalf_func(jump_fnct_evalf).
      latex_name("\\chi").
      //text_name("H").
      print_func<print_dflt>(jump_fnct_print_dflt_text).
      print_func<print_latex>(jump_fnct_print_latex).
      //derivative_func(2*delta).
      power_func(jump_fnct_power).
      conjugate_func(jump_fnct_conjugate));

#line 4415 "cycle.nw"
const string equality(const ex & E)
{
 if (normal(E).is_zero())
  return "-equal-";
 else
  return "DIFFERENT!!!";
}

#line 4425 "cycle.nw"
const string eph_case(const numeric & sign)
{
 if (numeric(sign-(-1)).is_zero())
  return "Elliptic case (sign = -1)";
 if (numeric(sign).is_zero())
  return "Parabolic case (sign = 0)";
 if (numeric(sign-1).is_zero())
  return "Hyperbolic case (sign = 1)";
 return "Unknown case!!!!";
}

#line 4439 "cycle.nw"
matrix sl2_clifford(const ex & a, const ex & b, const ex & c, const ex & d, const ex & e, bool not_inverse)
{
 if (is_a<clifford>(e)) {
  ex e0 = e.subs(e.op(1) == 0);
  ex one = dirac_ONE(ex_to<clifford>(e).get_representation_label());
  if (not_inverse)
   return matrix(2, 2,
        lst(a * one, b * e0,
         c * pow(e0, 3), d * one));
  else
   return matrix(2, 2,
        lst(d * one, -b * e0,
         -c * pow(e0, 3), a * one));
 } else
  throw(std::invalid_argument("sl2_clifford(): expect a clifford numeber as a parameter"));
}

#line 4458 "cycle.nw"
ex scalar_part(const ex & e) {
	ex given=canonicalize_clifford(e.expand()), 
		out=0, term;
	if (is_a<add>(given)){
		for (size_t i=0; i<given.nops(); i++) { 
			try {
				term=remove_dirac_ONE(given.op(i));
			} catch (exception &p) {
				term=0;
			}
			out+=term;
		}
		return out.normal();
	} else{
		try {
			return remove_dirac_ONE(given);
		} catch (exception &p) {
			return 0;
		}
	}
}

#line 4482 "cycle.nw"
matrix sl2_clifford(const ex & M, const ex & e, bool not_inverse)
{
 if (is_a<matrix>(M) || M.info(info_flags::list))
  return sl2_clifford(M.op(0), M.op(1), M.op(2), M.op(3), e, not_inverse);
 else
  throw(std::invalid_argument("sl2_clifford(): expect a list or matrix as the first parameter"));
}

