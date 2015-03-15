#line 3617 "figure.nw"
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

#line 1230 "figure.nw"
#include "figure.h"

GINAC_IMPLEMENT_REGISTERED_CLASS_OPT(cycle2D_data, basic,
									 print_func<print_dflt>(&cycle2D_data::do_print))

GINAC_IMPLEMENT_REGISTERED_CLASS_OPT(cycle_relation, basic,
									 print_func<print_dflt>(&cycle_relation::do_print).
print_func<print_tree>(&cycle_relation::do_print_tree))

GINAC_IMPLEMENT_REGISTERED_CLASS_OPT(subfigure, basic,
									 print_func<print_dflt>(&subfigure::do_print))

GINAC_IMPLEMENT_REGISTERED_CLASS_OPT(cycle2D_node, basic,
									 print_func<print_dflt>(&cycle2D_node::do_print).
print_func<print_tree>(&cycle_relation::do_print_tree))

GINAC_IMPLEMENT_REGISTERED_CLASS_OPT(figure, basic,
									 print_func<print_dflt>(&figure::do_print))

#line 1260 "figure.nw"
const ex epsilon=GiNaC::pow(10,-Digits+4);

#line 1264 "figure.nw"
bool is_almost_zero1(const ex & x)
{
	if (is_a<numeric>(x))
		return (ex_to<numeric>(x+epsilon).is_positive() && ex_to<numeric>(epsilon-x).is_positive());
	else
		return x.is_zero();
}

#line 3421 "figure.nw"
ex cycle_orthogonal(const ex & C1, const ex & C2)
{
	return lst((ex)lst(ex_to<cycle2D>(C1).is_orthogonal(ex_to<cycle2D>(C2))));
}

#line 3428 "figure.nw"
ex cycle_f_orthogonal(const ex & C1, const ex & C2)
{
	return lst( (ex)lst(ex_to<cycle2D>(C1).is_f_orthogonal(ex_to<cycle2D>(C2))));
}

#line 3435 "figure.nw"
ex cycle_adifferent(const ex & C1, const ex & C2)
{
	return lst( (ex)lst(cycle2D_data(C1).is_almost_equal(ex_to<basic>(cycle2D_data(C2)),true)? 0: 1));
}


#line 1279 "figure.nw"
cycle2D_data::cycle2D_data() : k(), l(), m()
{
	;
}

#line 1286 "figure.nw"
cycle2D_data::cycle2D_data(const ex & C)
{
	if (is_a<cycle2D>(C)) {
		cycle2D C_new=ex_to<cycle2D>(C).normalize();
		k=C_new.get_k();
		l=C_new.get_l();
		m=C_new.get_m();
	} else if (is_a<cycle2D_data>(C))
		*this=ex_to<cycle2D_data>(C);
	else
		throw(std::invalid_argument("cycle2D_data(): accept only cycle2D or cycle2D_data"
									" as the parameter"));

}

#line 1303 "figure.nw"
cycle2D_data::cycle2D_data(const ex & k1, const ex l1, const ex &m1, bool normalize) : k(k1), l(l1), m(m1)
{
	if (normalize) {
		ex ratio = 0;
		if (!k.is_zero()) // First non-zero coefficient among k, m, l_0, l_1, ... is set to 1
			ratio = k;
		else if (!m.is_zero())
			ratio = m;
		else {
			for (int i=0; i<2; i++)
				if (!l.subs(l.op(1) == i).is_zero()) {
					ratio = l.subs(l.op(1) == i);
					break;
				}
		}

		if (!ratio.is_zero()) {
			k=k/ratio;
			l=indexed((l.op(0)/ratio).evalm().normal(), l.op(1));
			m=(m/ratio).normal();
		}
	}
}

#line 1329 "figure.nw"
return_type_t cycle2D_data::return_type_tinfo() const
{
	return make_return_type_t<cycle2D_data>();
}

#line 1336 "figure.nw"
int cycle2D_data::compare_same_type(const basic &other) const
{
       GINAC_ASSERT(is_a<cycle2D_data>(other));
	   return inherited::compare_same_type(other);
}


#line 1345 "figure.nw"
void cycle2D_data::do_print(const print_dflt & con, unsigned level) const
{
	con.s << "("; \
	k.print(con, level);
	con.s << ", ";
	l.print(con, level);
	con.s << ", ";
	m.print(con, level);
	con.s << ")";
}

#line 1358 "figure.nw"
void cycle2D_data::archive(archive_node &n) const
{
	inherited::archive(n);
	n.add_ex("k-val", k);
	n.add_ex("l-val", l);
	n.add_ex("m-val", m);
}

#line 1368 "figure.nw"
void cycle2D_data::read_archive(const archive_node &n, lst &sym_lst)
{
	inherited::read_archive(n, sym_lst);
	n.find_ex("k-val", k, sym_lst);
	n.find_ex("l-val", l, sym_lst);
	n.find_ex("m-val", m, sym_lst);
}

#line 1378 "figure.nw"
GINAC_BIND_UNARCHIVER(cycle2D_data);

#line 1382 "figure.nw"
ex cycle2D_data::get_cycle2D(const ex & metr) const
{
	return cycle2D(k,l,m,metr);
}

#line 1389 "figure.nw"
bool cycle2D_data::is_equal(const basic & other, bool projectively) const
{
	if (not is_a<cycle2D_data>(other))
		return false;
	const cycle2D_data o = ex_to<cycle2D_data>(other);
	ex factor=0, ofactor=0;

	if (projectively) {
		// Check that coefficients are scalar multiples of other
		if (not ((m*o.get_k()-o.get_m()*k).normal().is_zero()))
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
		if (not ((get_k()-o.get_k()).normal().is_zero()
				 && (get_m()-o.get_m()).normal().is_zero()))
			return false;


#line 1418 "figure.nw"
	for (int i=0; i<2; i++)
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
}

#line 1436 "figure.nw"
bool cycle2D_data::is_almost_equal(const basic & other, bool projectively) const
{
	if (not is_a<cycle2D_data>(other))
		return false;
	const cycle2D_data o = ex_to<cycle2D_data>(other);
	ex factor=0, ofactor=0;

	if (projectively) {
		// Check that coefficients are scalar multiples of other
		if (! (is_almost_zero1(m*o.get_k()-o.get_m()*k)))
			return false;
		// Set up coefficients for proportionality
		if (is_almost_zero1(get_k())) {
			factor=get_m();
			ofactor=o.get_m();
		} else {
			factor=get_k();
			ofactor=o.get_k();
		}

	} else
		// Check the exact equality of coefficients
		if (! (is_almost_zero1((get_k()-o.get_k()))
				 && is_almost_zero1(get_m()-o.get_m())))
			return false;


#line 1465 "figure.nw"
	for (int i=0; i<2; i++)
		if (projectively) {
			// search the the first non-zero coefficient
			if (factor.is_zero()) {
				factor=get_l(i);
				ofactor=o.get_l(i);
			} else
				if (! is_almost_zero1(get_l(i)*ofactor-o.get_l(i)*factor))
					return false;
		} else
			if (! is_almost_zero1(get_l(i)-o.get_l(i)))
				return false;

	return true;
}

#line 1483 "figure.nw"
cycle2D_data cycle2D_data::subs(const ex & e, unsigned options) const
{
	return cycle2D_data(k.subs(e,options),l.subs(e,options),m.subs(e,options),false);
}
#line 1489 "figure.nw"
ex cycle2D_data::subs(const exmap & em, unsigned options) const
{
	return cycle2D_data(k.subs(em,options),l.subs(em,options),m.subs(em,options),false);
}

#line 1496 "figure.nw"
ex cycle2D_data::num_normalize() const
{
	if (! (is_a<numeric>(k) && is_a<numeric>(m)
		   && is_a<numeric>(l.op(0).op(0))  && is_a<numeric>(l.op(0).op(1))))
		return cycle2D_data(k,l,m,true);

	/*	double k1=ex_to<numeric>(k).to_double(),
		m1=ex_to<numeric>(m).to_double(),
		l0=ex_to<numeric>(l.op(0).op(0)).to_double(),
		l1=ex_to<numeric>(l.op(0).op(1)).to_double();
	*/

	numeric k1=ex_to<numeric>(k),
		m1=ex_to<numeric>(m),
		l0=ex_to<numeric>(l.op(0).op(0)),
		l1=ex_to<numeric>(l.op(0).op(1));

	numeric r=max(abs(k1),abs(m1));

	r=max(r,abs(l0));
	r=max(r,abs(l1));

	if (is_almost_zero1(r))
		return cycle2D_data(k,l,m,true);
	k1/=r; k1=(is_almost_zero1(k1)?0:k1);
	m1/=r; m1=(is_almost_zero1(m1)?0:m1);
	l0/=r; l0=(is_almost_zero1(l0)?0:l0);
	l1/=r; l1=(is_almost_zero1(l1)?0:l1);

	return cycle2D_data(k1,indexed(matrix(1, 2, lst(l0,l1)), l.op(1)),m1);
}

#line 1534 "figure.nw"
cycle_relation::cycle_relation() : parkey()
{
  rel = cycle_orthogonal;
  use_cycle_metric = true;
}

#line 1542 "figure.nw"
cycle_relation::cycle_relation(const ex & k, PCR r, bool cm) {
	parkey = k;
	rel = r;
	use_cycle_metric = cm;
}

#line 1550 "figure.nw"
return_type_t cycle_relation::return_type_tinfo() const
{
	return make_return_type_t<cycle_relation>();
}

#line 1557 "figure.nw"
int cycle_relation::compare_same_type(const basic &other) const
{
       GINAC_ASSERT(is_a<cycle_relation>(other));
	   return inherited::compare_same_type(other);
	   /*
  const cycle_relation &o = static_cast<const cycle_relation &>(other);
	if ((parkey == o.parkey) && (&rel == &o.rel))
		return 0;
	else if ((parkey < o.parkey) || (&rel < &o.rel))
		return -1;
	else
	return 1;*/
}

#line 1575 "figure.nw"
void cycle_relation::archive(archive_node &n) const
{
	inherited::archive(n);
	n.add_ex("cr-parkey", parkey);
	n.add_bool("use_cycle_metric", use_cycle_metric);
	ex (*const* ptr)(const ex &, const ex &) = rel.target<ex(*)(const ex&, const ex &)>();
	if (ptr && *ptr == cycle_orthogonal)
		n.add_string("relation", "orthogonal");
	else if (ptr && *ptr == cycle_f_orthogonal)
		n.add_string("relation", "f_orthogonal");
	else if (ptr && *ptr == cycle_different)
		n.add_string("relation", "different");
	else if (ptr && *ptr == cycle_adifferent)
		n.add_string("relation", "adifferent");
	else if (ptr && *ptr == cycle_tangent)
		n.add_string("relation", "tangent");
	else if (ptr && *ptr == cycle_tangent_i)
		n.add_string("relation", "tangent_i");
	else if (ptr && *ptr == cycle_tangent_o)
		n.add_string("relation", "tangent_o");
	else
		throw(std::invalid_argument("cycle_relation::archive(): archiving of this relation is not"
									" implemented"));
}

#line 1602 "figure.nw"
void cycle_relation::read_archive(const archive_node &n, lst &sym_lst)
{
	ex e;
	inherited::read_archive(n, sym_lst);
	n.find_ex("cr-parkey", e, sym_lst);
	if (is_a<symbol>(e))
		parkey=e;
	else
		throw(std::invalid_argument("cycle_relation::read_archive(): read a non-symbol as"
									" a parkey from the archive"));
	n.find_bool("use_cycle_metric", use_cycle_metric);
	string relation;
	n.find_string("relation", relation);
	if (relation == "orthogonal")
		rel = cycle_orthogonal;
	else if (relation == "f_orthogonal")
		rel = cycle_f_orthogonal;
	else if (relation == "different")
		rel = cycle_different;
	else if (relation == "adifferent")
		rel = cycle_adifferent;
	else if (relation == "tangent")
		rel = cycle_tangent;
	else if (relation == "tangent_i")
		rel = cycle_tangent_i;
	else if (relation == "tangent_o")
		rel = cycle_tangent_o;
	else
		throw(std::invalid_argument("cycle_relation::read_archive(): archive contains unknown"
									" relation"));
}

#line 1636 "figure.nw"
GINAC_BIND_UNARCHIVER(cycle_relation);

#line 1640 "figure.nw"
ex cycle_relation::rel_to_parent(const cycle2D_data & C1, const ex & pmetric, const ex & cmetric,
								 const exhashmap<cycle2D_node> & N) const
{
	exhashmap<cycle2D_node> snodes=N;
	lst res,
		cycles=ex_to<lst>(snodes[parkey].get_cycle2D(use_cycle_metric? cmetric : pmetric));

	for (lst::const_iterator it = cycles.begin(); it != cycles.end(); ++it) {
		lst calc=ex_to<lst>(rel(C1.get_cycle2D(use_cycle_metric? cmetric : pmetric), ex_to<cycle2D>(*it)));
		for (lst::const_iterator it1 = calc.begin(); it1 != calc.end(); ++it1)
			res.append(*it1);
	}
	return res;
}

#line 1657 "figure.nw"
void cycle_relation::do_print(const print_dflt & con, unsigned level) const
{
	con.s << parkey << (use_cycle_metric? "|" : "/");
	ex (*const* ptr)(const ex &, const ex &) = rel.target<ex(*)(const ex&, const ex &)>();
	if (ptr && *ptr == cycle_orthogonal)
		con.s << "o";
	else if (ptr && *ptr == cycle_f_orthogonal)
		con.s << "f";
	else if (ptr && *ptr == cycle_different)
		con.s << "d";
	else if (ptr && *ptr == cycle_adifferent)
		con.s << "a";
	else if (ptr && *ptr == cycle_tangent)
		con.s << "t";
	else if (ptr && *ptr == cycle_tangent_i)
		con.s << "ti";
	else if (ptr && *ptr == cycle_tangent_o)
		con.s << "to";
	else
		con.s << "u"; // unknown type of relations
}

#line 1681 "figure.nw"
void cycle_relation::do_print_tree(const print_tree & con, unsigned level) const
{
	//	inherited::do_print_tree(con,level);
	parkey.print(con,level+con.delta_indent);
	//	con.s <<  std::string(level+con.delta_indent, ' ') << (int)rel <<endl;
}

#line 1695 "figure.nw"
subfigure::subfigure() : inherited()
{
}

#line 1701 "figure.nw"
subfigure::subfigure(const ex & F, const ex & l) {
	parlist = ex_to<lst>(l);
	subf = F;
}

#line 1708 "figure.nw"
return_type_t subfigure::return_type_tinfo() const
{
	return make_return_type_t<subfigure>();
}

#line 1715 "figure.nw"
int subfigure::compare_same_type(const basic &other) const
{
       GINAC_ASSERT(is_a<subfigure>(other));
	   return inherited::compare_same_type(other);
}

#line 1726 "figure.nw"
void subfigure::archive(archive_node &n) const
{
	inherited::archive(n);
	n.add_ex("parlist", ex_to<lst>(parlist));
	n.add_ex("subf", ex_to<figure>(subf));
}

#line 1735 "figure.nw"
void subfigure::read_archive(const archive_node &n, lst &sym_lst)
{
	ex e;
	inherited::read_archive(n, sym_lst);
	n.find_ex("parlist", e, sym_lst);
	if (is_a<lst>(e))
		parlist=ex_to<lst>(e);
	else
		throw(std::invalid_argument("subfigure::read_archive(): read a non-lst as a parlist from"
									" the archive"));
	n.find_ex("subf", e, sym_lst);
	if (is_a<figure>(e))
		subf=ex_to<figure>(e);
	else
		throw(std::invalid_argument("subfigure::read_archive(): read a non-figure as a subf from"
									" the archive"));
}

#line 1755 "figure.nw"
GINAC_BIND_UNARCHIVER(subfigure);

#line 1759 "figure.nw"
void subfigure::do_print(const print_dflt & con, unsigned level) const
{
	con.s << "subfig( " ;
        parlist.print(con, level+1);
		//        subf.print(con, level+1);
	con.s << ")" ;
}

#line 1773 "figure.nw"
cycle2D_node::cycle2D_node() 
{
	generation=0;
}

#line 1780 "figure.nw"
cycle2D_node::cycle2D_node(const ex & C, int g) 
{
	generation=g;
	
#line 1788 "figure.nw"
	if (is_a<cycle2D_node>(C)) {
		cycles=ex_to<lst>(ex_to<cycle2D_node>(C).get_cycles());
		generation = ex_to<cycle2D_node>(C).get_generation();
		children = ex_to<cycle2D_node>(C).get_children();
		parents = ex_to<cycle2D_node>(C).get_parents();
	} else
		
#line 1807 "figure.nw"
 	if (is_a<lst>(C)) {
		for (lst::const_iterator it = ex_to<lst>(C).begin(); it != ex_to<lst>(C).end(); ++it)
			if ( is_a<cycle2D_data>(*it) || is_a<cycle2D>(*it))
				cycles.append(cycle2D_data(*it));
			else
				throw(std::invalid_argument("the parameter is list of something which is not"
											" cycle2D_data"));
	} else if (is_a<cycle2D_data>(C)) {
		cycles = lst(C);
	} else if (is_a<cycle2D>(C)) {
		cycles=lst(cycle2D_data(ex_to<cycle2D>(C).get_k(), ex_to<cycle2D>(C).get_l(),
								ex_to<cycle2D>(C).get_m()));
	} else
		throw(std::invalid_argument("the cyle2D parameters must be either cycle2D, cycle2D_data,"
									" cycle2D_node or list of cycle2D_data"));


#line 1784 "figure.nw"
}

#line 1798 "figure.nw"
cycle2D_node::cycle2D_node(const ex & C, int g, const lst & par) 
{
	generation=g;
	
#line 1807 "figure.nw"
 	if (is_a<lst>(C)) {
		for (lst::const_iterator it = ex_to<lst>(C).begin(); it != ex_to<lst>(C).end(); ++it)
			if ( is_a<cycle2D_data>(*it) || is_a<cycle2D>(*it))
				cycles.append(cycle2D_data(*it));
			else
				throw(std::invalid_argument("the parameter is list of something which is not"
											" cycle2D_data"));
	} else if (is_a<cycle2D_data>(C)) {
		cycles = lst(C);
	} else if (is_a<cycle2D>(C)) {
		cycles=lst(cycle2D_data(ex_to<cycle2D>(C).get_k(), ex_to<cycle2D>(C).get_l(),
								ex_to<cycle2D>(C).get_m()));
	} else
		throw(std::invalid_argument("the cyle2D parameters must be either cycle2D, cycle2D_data,"
									" cycle2D_node or list of cycle2D_data"));

#line 1802 "figure.nw"
	
#line 1825 "figure.nw"
	GINAC_ASSERT(is_a<lst>(par));
	parents = ex_to<lst>(par);

#line 1803 "figure.nw"
}

#line 1830 "figure.nw"
cycle2D_node::cycle2D_node(const ex & C, int g, const lst & par, const lst & ch)
{
	generation=g;
	children=ch;
	
#line 1807 "figure.nw"
 	if (is_a<lst>(C)) {
		for (lst::const_iterator it = ex_to<lst>(C).begin(); it != ex_to<lst>(C).end(); ++it)
			if ( is_a<cycle2D_data>(*it) || is_a<cycle2D>(*it))
				cycles.append(cycle2D_data(*it));
			else
				throw(std::invalid_argument("the parameter is list of something which is not"
											" cycle2D_data"));
	} else if (is_a<cycle2D_data>(C)) {
		cycles = lst(C);
	} else if (is_a<cycle2D>(C)) {
		cycles=lst(cycle2D_data(ex_to<cycle2D>(C).get_k(), ex_to<cycle2D>(C).get_l(),
								ex_to<cycle2D>(C).get_m()));
	} else
		throw(std::invalid_argument("the cyle2D parameters must be either cycle2D, cycle2D_data,"
									" cycle2D_node or list of cycle2D_data"));

#line 1835 "figure.nw"
	
#line 1825 "figure.nw"
	GINAC_ASSERT(is_a<lst>(par));
	parents = ex_to<lst>(par);

#line 1836 "figure.nw"
}

#line 1840 "figure.nw"
return_type_t cycle2D_node::return_type_tinfo() const
{
	return make_return_type_t<cycle2D_node>();
}

#line 1847 "figure.nw"
int cycle2D_node::compare_same_type(const basic &other) const
{
       GINAC_ASSERT(is_a<cycle2D_node>(other));
	   return inherited::compare_same_type(other);
}

#line 1855 "figure.nw"
ex cycle2D_node::get_cycle2D(const ex & metr) const
{
	lst res;
	for (lst::const_iterator it = cycles.begin(); it != cycles.end(); ++it)
		res.append(ex_to<cycle2D_data>(*it).get_cycle2D(metr));

	return res;
}

#line 1866 "figure.nw"
void cycle2D_node::set_cycles(const ex & C)
{
	cycles.remove_all();
	
#line 1807 "figure.nw"
 	if (is_a<lst>(C)) {
		for (lst::const_iterator it = ex_to<lst>(C).begin(); it != ex_to<lst>(C).end(); ++it)
			if ( is_a<cycle2D_data>(*it) || is_a<cycle2D>(*it))
				cycles.append(cycle2D_data(*it));
			else
				throw(std::invalid_argument("the parameter is list of something which is not"
											" cycle2D_data"));
	} else if (is_a<cycle2D_data>(C)) {
		cycles = lst(C);
	} else if (is_a<cycle2D>(C)) {
		cycles=lst(cycle2D_data(ex_to<cycle2D>(C).get_k(), ex_to<cycle2D>(C).get_l(),
								ex_to<cycle2D>(C).get_m()));
	} else
		throw(std::invalid_argument("the cyle2D parameters must be either cycle2D, cycle2D_data,"
									" cycle2D_node or list of cycle2D_data"));

#line 1870 "figure.nw"
}

#line 1874 "figure.nw"
void cycle2D_node::append_cycle(const ex & k, const ex & l, const ex & m)
{
	cycles.append(cycle2D_data(k,l,m));
}

#line 1881 "figure.nw"
void cycle2D_node::append_cycle(const ex & C)
{
	if (is_a<cycle2D>(C))
		cycles.append(cycle2D_data(ex_to<cycle2D>(C).get_k(), ex_to<cycle2D>(C).get_l(),
								   ex_to<cycle2D>(C).get_m()));
	else 	if (is_a<cycle2D_data>(C))
		cycles.append(ex_to<cycle2D_data>(C));
	else
		throw(std::invalid_argument("cycle2D_node::append_cycle(const ex &): the parameter must be"
									" either cycle2D or cycle2D_data"));
}

#line 1895 "figure.nw"
lst cycle2D_node::get_parents() const
{
	return parents;
}

#line 1902 "figure.nw"
lst cycle2D_node::get_parent_keys() const
{
	lst pkeys;
	if ( (parents.nops() == 1) && (is_a<subfigure>(parents.op(0)))) {
		pkeys=ex_to<lst>(ex_to<subfigure>(parents.op(0)).get_parlist());
	} else {
		for (lst::const_iterator it = parents.begin(); it != parents.end(); ++it)
			pkeys.append(ex_to<cycle_relation>(*it).get_parkey());
	}
	return pkeys;
}

#line 1916 "figure.nw"
void cycle2D_node::do_print(const print_dflt & con, unsigned level) const
{
	con.s << '{';
	for (lst::const_iterator it = cycles.begin(); it != cycles.end(); ++it) {
		ex_to<cycle2D_data>(*it).do_print(con, level);
		con.s << ", ";
	}
	con.s << generation << '}' << " --> (";
	// list all children
	for (lst::const_iterator it = children.begin(); it != children.end();) {
		con.s << (*it);
		++it;
		if (it != children.end())
			con.s <<",";
	}

	// list all parents
	con.s << ");  <-- (";
        if (generation > 0 || FIGURE_DEBUG)
		for (lst::const_iterator it = parents.begin(); it != parents.end();) {
			if (is_a<cycle_relation>(*it))
				ex_to<cycle_relation>(*it).do_print(con,level);
			else if (is_a<subfigure>(*it))
				ex_to<subfigure>(*it).do_print(con,level);
			++it;
			if (it != parents.end())
				con.s <<",";
	}
	con.s << ")" << endl;
}

#line 1949 "figure.nw"
void cycle2D_node::do_print_tree(const print_tree & con, unsigned level) const
{
	for (lst::const_iterator it = cycles.begin(); it != cycles.end(); ++it)
		it->print(con, level);
	con.s << std::string(level+con.delta_indent, ' ') << "generation: "<< generation << endl;
	con.s << std::string(level+con.delta_indent, ' ') << "children" <<endl;
	children.print(con,level+2*con.delta_indent);
	con.s << std::string(level+con.delta_indent, ' ') << "parents" <<endl;
	parents.print(con,level+2*con.delta_indent);
}

#line 1962 "figure.nw"
void cycle2D_node::remove_child(const ex & other)
{
	lst nchildren;
	for (lst::const_iterator it = children.begin(); it != children.end(); ++it)
	    if (*it != other)
			nchildren.append(*it);
	children=nchildren;
}

#line 1973 "figure.nw"
cycle2D_node cycle2D_node::subs(const ex & e, unsigned options) const
{
	exmap em;
	if (e.info(info_flags::list)) {
		lst l = ex_to<lst>(e);
		for (lst::const_iterator i = l.begin(); i != l.end(); ++i)
			em.insert(std::make_pair(i->op(0), i->op(1)));
	} else if (is_a<relational>(e)) {
		em.insert(std::make_pair(e.op(0), e.op(1)));
	} else
		throw(std::invalid_argument("cycle::subs(): the parameter should be a relational or a lst"));

	return cycle2D_node(cycles.subs(em, options), generation, parents, children);
}

#line 1990 "figure.nw"
ex cycle2D_node::subs(const exmap & em, unsigned options) const
{
	return cycle2D_node(cycles.subs(em, options), generation, parents, children);
}

#line 1997 "figure.nw"
void cycle2D_node::archive(archive_node &n) const
{
	inherited::archive(n);
	n.add_ex("cycles", cycles);
	n.add_unsigned("children_size", children.nops());
	if (children.nops()>0)
		for (lst::const_iterator it = children.begin(); it != children.end(); ++it)
			n.add_ex("chil", *it);

	n.add_unsigned("parent_size", parents.nops());
	if (parents.nops()>0) {
		n.add_bool("has_subfigure", false);
		for (lst::const_iterator it = parents.begin(); it != parents.end(); ++it)
			n.add_ex("par", ex_to<cycle_relation>(*it));
	}

#line 2015 "figure.nw"
	bool neg_generation=(generation<0);
	n.add_bool("neg_generation", neg_generation);
	if (neg_generation)
		n.add_unsigned("abs_generation", -generation);
	else
		n.add_unsigned("abs_generation", generation);
}

#line 2025 "figure.nw"
void cycle2D_node::read_archive(const archive_node &n, lst &sym_lst)
{
	inherited::read_archive(n, sym_lst);
	ex e;
	n.find_ex("cycles", e, sym_lst);
	cycles=ex_to<lst>(e);
	ex ch, par;
	unsigned int c_size;
	n.find_unsigned("children_size", c_size);

	if (c_size>0) {
		archive_node::archive_node_cit first = n.find_first("chil");
		archive_node::archive_node_cit last = n.find_last("chil");
		++last;
		for (archive_node::archive_node_cit i=first; i != last; ++i) {
			ex e;
			n.find_ex_by_loc(i, e, sym_lst);
			children.append(e);
		}
	}

	unsigned int p_size;
	n.find_unsigned("parent_size", p_size);

	if (p_size>0) {
		archive_node::archive_node_cit first = n.find_first("par");
		archive_node::archive_node_cit last = n.find_last("par");
		++last;
		for (archive_node::archive_node_cit i=first; i != last; ++i) {
			ex e;
			n.find_ex_by_loc(i, e, sym_lst);
			parents.append(e);
		}
	}

#line 2062 "figure.nw"
	bool neg_generation;
	n.find_bool("neg_generation", neg_generation);
	unsigned int abs_generation;
	n.find_unsigned("abs_generation", abs_generation);
	if (neg_generation)
		generation = -abs_generation;
	else
		generation = abs_generation;
}

#line 2074 "figure.nw"
GINAC_BIND_UNARCHIVER(cycle2D_node);

#line 2083 "figure.nw"
figure::figure() : inherited(), k(realsymbol("k")), l(realsymbol("l")), n(realsymbol("n")), m(realsymbol("m"))
{
	//	flags &= ~status_flags::expanded;
	infinity=symbol("infty","\\infty");
	real_line=symbol("R","\\mathbf{R}");
	point_metric = clifford_unit(varidx(real_line, 2), indexed(-(new tensdelta)->setflag(status_flags::dynallocated),
								varidx(symbol("i"), 2), varidx(symbol("j"), 2)));
	cycle_metric = clifford_unit(varidx(real_line, 2), indexed(-(new tensdelta)->setflag(status_flags::dynallocated),
								varidx(symbol("ic"), 2), varidx(symbol("jc"), 2)));
	
#line 2098 "figure.nw"
	nodes[infinity] = cycle2D_node(cycle2D_data(numeric(0),indexed(matrix(1, 2, lst(numeric(0),numeric(0))),
																   varidx(infinity, 2)),numeric(1)),INFINITY_GEN);
 
#line 2093 "figure.nw"
	
#line 2103 "figure.nw"
	nodes[real_line] = cycle2D_node(cycle2D_data(numeric(0),indexed(matrix(1, 2, lst(numeric(0),numeric(1))),
																	varidx(real_line, 2)),numeric(0)),REAL_LINE_GEN);

#line 2094 "figure.nw"
}

#line 2108 "figure.nw"
figure::figure(const ex & Mp, const ex & Mc) : inherited(), k(realsymbol("k")), l(realsymbol("l")),
	n(realsymbol("n")), m(realsymbol("m"))
{
//	flags &= ~status_flags::expanded;
	infinity=symbol("infty","\\infty");
	real_line=symbol("R","\\mathbf{R}");
	bool inf_missing=true, R_missing=true;
	
#line 2120 "figure.nw"
if (is_a<clifford>(Mp)) {
	point_metric = clifford_unit(varidx(real_line, 2), ex_to<clifford>(Mp).get_metric());
 } else if (is_a<matrix>(Mp) || is_a<tensor>(Mp)) {
	point_metric = clifford_unit(varidx(real_line, 2), indexed(Mp, varidx(symbol("i"), 2), varidx(symbol("j"), 2)));
 } else if (is_a<indexed>(Mp)) {
	point_metric = clifford_unit(varidx(real_line, 2), Mp);

#line 2132 "figure.nw"
	} else if (is_a<realsymbol>(Mp) || is_a<numeric>(Mp)) {
		point_metric=clifford_unit(varidx(real_line, 2), indexed(diag_matrix(lst(-1,Mp)), varidx(symbol("i"), 2), varidx(symbol("j"), 2)));
	}


#line 2138 "figure.nw"
	else if (is_a<figure>(Mp)) {
		point_metric = ex_to<figure>(Mp).get_point_metric();
		cycle_metric = ex_to<figure>(Mp).get_cycle_metric();
		exhashmap<cycle2D_node> nnodes = ex_to<figure>(Mp).get_nodes();
		for (exhashmap<cycle2D_node>::const_iterator it = nnodes.begin(); it != nnodes.end(); ++it) {
			nodes[it->first]=it->second;
			
#line 2149 "figure.nw"
			if (it->second.get_generation() == REAL_LINE_GEN) {
				real_line = it->first;
				R_missing=false;
			}
			else if (it->second.get_generation() == INFINITY_GEN) {
				infinity = it->first;
				inf_missing=false;
			}

#line 2145 "figure.nw"
			}

#line 2160 "figure.nw"
	} else
			throw(std::invalid_argument("figure::figure(const ex &, const ex &):"
										" the first parameter shall be a figure, "
										" a metric (can be either tensor, matrix,"
										" Clifford unit or indexed by two indices) "
										"a real symbol (to denote the signature of metric) "
										"or a numeric -1, 0, 1 to specify EPH geometries"));
	
#line 2172 "figure.nw"
	if (Mc.is_zero()) {
		cycle_metric = clifford_unit(varidx(real_line, 2), indexed(diag_matrix(
												lst(ex_to<clifford>(point_metric).get_metric(idx(0,2),idx(0,2)),
													-jump_fnct(-ex_to<clifford>(point_metric).get_metric(idx(1,2),idx(1,2))))),
													varidx(symbol("ic"), 2), varidx(symbol("jc"), 2)));

#line 2181 "figure.nw"
	} else if (is_a<clifford>(Mc)) {
		cycle_metric = clifford_unit(varidx(real_line, 2), ex_to<clifford>(Mc).get_metric());
	} else if (is_a<matrix>(Mc) || is_a<tensor>(Mc)) {
		cycle_metric = clifford_unit(varidx(real_line, 2), indexed(Mc, varidx(symbol("ic"), 2),
										varidx(symbol("jc"), 2)));
	} else if (is_a<indexed>(Mc)) {
		cycle_metric = clifford_unit(varidx(real_line, 2), Mc);
	} else if (is_a<realsymbol>(Mc) || is_a<numeric>(Mc)) {
		cycle_metric=clifford_unit(varidx(real_line, 2), indexed(diag_matrix(lst(-1,Mc)),
										varidx(symbol("ic"), 2), varidx(symbol("jc"), 2)));
	}


#line 2195 "figure.nw"
	else
			throw(std::invalid_argument("figure::figure(const ex &, const ex &):"
										" the second parameter"
										" shall be omitted, equal to zero "
										" or be a metric (can be either tensor, matrix,"
										" Clifford unit or indexed by two indices) "
										"a real symbol (to denote the signature of metric) "
										"or a numeric -1, 0, 1 to specify EPH geometries"));

#line 2207 "figure.nw"
	
#line 2212 "figure.nw"
	if (inf_missing)
		
#line 2098 "figure.nw"
	nodes[infinity] = cycle2D_node(cycle2D_data(numeric(0),indexed(matrix(1, 2, lst(numeric(0),numeric(0))),
																   varidx(infinity, 2)),numeric(1)),INFINITY_GEN);
 

#line 2215 "figure.nw"
	if (R_missing)
		
#line 2103 "figure.nw"
	nodes[real_line] = cycle2D_node(cycle2D_data(numeric(0),indexed(matrix(1, 2, lst(numeric(0),numeric(1))),
																	varidx(real_line, 2)),numeric(0)),REAL_LINE_GEN);


#line 2208 "figure.nw"
}

#line 2220 "figure.nw"
figure::figure(const ex & Mp, const ex & Mc, const exhashmap<cycle2D_node> & N):
inherited(), k(realsymbol("k")), l(realsymbol("l")), n(realsymbol("n")), m(realsymbol("m"))
{
//	flags &= ~status_flags::expanded;

	infinity=symbol("infty","\\infty");
	real_line=symbol("R","\\mathbf{R}");
	bool inf_missing=true, R_missing=true;
	if (is_a<clifford>(Mp) && is_a<clifford>(Mc)) {
		point_metric = Mp;
		cycle_metric = Mc;
	} else
		throw(std::invalid_argument("figure::figure(const ex &, const ex &, exhashmap<cycle2D_node>):"
									" the point_metric and cycle_metric should be clifford_unit. "));


#line 2238 "figure.nw"
	for (exhashmap<cycle2D_node>::const_iterator it = N.begin(); it != N.end(); ++it) {
		nodes[it->first]=it->second;
		
#line 2149 "figure.nw"
			if (it->second.get_generation() == REAL_LINE_GEN) {
				real_line = it->first;
				R_missing=false;
			}
			else if (it->second.get_generation() == INFINITY_GEN) {
				infinity = it->first;
				inf_missing=false;
			}

#line 2241 "figure.nw"
	}
	
#line 2212 "figure.nw"
	if (inf_missing)
		
#line 2098 "figure.nw"
	nodes[infinity] = cycle2D_node(cycle2D_data(numeric(0),indexed(matrix(1, 2, lst(numeric(0),numeric(0))),
																   varidx(infinity, 2)),numeric(1)),INFINITY_GEN);
 

#line 2215 "figure.nw"
	if (R_missing)
		
#line 2103 "figure.nw"
	nodes[real_line] = cycle2D_node(cycle2D_data(numeric(0),indexed(matrix(1, 2, lst(numeric(0),numeric(1))),
																	varidx(real_line, 2)),numeric(0)),REAL_LINE_GEN);


#line 2243 "figure.nw"
}

#line 2247 "figure.nw"
figure::figure(const char* file_name, string fig_name) : inherited(), k(realsymbol("k")), l(realsymbol("l")),
	n(realsymbol("n")), m(realsymbol("m"))
{
//	flags &= ~status_flags::expanded;
	infinity=symbol("infty","\\infty");
	real_line=symbol("R","\\mathbf{R}");
	
#line 2271 "figure.nw"
	string fn=file_name;
	size_t found = fn.find(".gar");
	if (found == std::string::npos)
		fn=fn+".gar";

	cout << "use filename: " << fn << endl;

#line 2254 "figure.nw"
	GiNaC::archive A;
	std::ifstream ifs(fn.c_str(),  std::ifstream::in);
	ifs >> A;

	*this=ex_to<figure>(A.unarchive_ex(lst(infinity, real_line), fig_name));

	if (FIGURE_DEBUG) {
		fn="raw-read-"+fn;
		ofstream out1(fn.c_str());
		A.printraw(out1);
		out1.close();
		out1.flush();
	}
}

#line 2281 "figure.nw"
void figure::save(const char* file_name, const char * fig_name)
{
	
#line 2271 "figure.nw"
	string fn=file_name;
	size_t found = fn.find(".gar");
	if (found == std::string::npos)
		fn=fn+".gar";

	cout << "use filename: " << fn << endl;

#line 2284 "figure.nw"
	GiNaC::archive A;
	A.archive_ex(*this, fig_name);
	ofstream out(fn.c_str());
	out << A;
	out.flush();
	out.close();
	if (FIGURE_DEBUG) {
		fn="raw-save-"+fn;
		ofstream out1(fn.c_str());
		A.printraw(out1);
		out1.close();
		out1.flush();
	}
}

#line 2301 "figure.nw"
void figure::set_metric(const ex & Mp, const ex & Mc)
{
	
#line 2120 "figure.nw"
if (is_a<clifford>(Mp)) {
	point_metric = clifford_unit(varidx(real_line, 2), ex_to<clifford>(Mp).get_metric());
 } else if (is_a<matrix>(Mp) || is_a<tensor>(Mp)) {
	point_metric = clifford_unit(varidx(real_line, 2), indexed(Mp, varidx(symbol("i"), 2), varidx(symbol("j"), 2)));
 } else if (is_a<indexed>(Mp)) {
	point_metric = clifford_unit(varidx(real_line, 2), Mp);

#line 2132 "figure.nw"
	} else if (is_a<realsymbol>(Mp) || is_a<numeric>(Mp)) {
		point_metric=clifford_unit(varidx(real_line, 2), indexed(diag_matrix(lst(-1,Mp)), varidx(symbol("i"), 2), varidx(symbol("j"), 2)));
	}

#line 2304 "figure.nw"
	
#line 2172 "figure.nw"
	if (Mc.is_zero()) {
		cycle_metric = clifford_unit(varidx(real_line, 2), indexed(diag_matrix(
												lst(ex_to<clifford>(point_metric).get_metric(idx(0,2),idx(0,2)),
													-jump_fnct(-ex_to<clifford>(point_metric).get_metric(idx(1,2),idx(1,2))))),
													varidx(symbol("ic"), 2), varidx(symbol("jc"), 2)));

#line 2181 "figure.nw"
	} else if (is_a<clifford>(Mc)) {
		cycle_metric = clifford_unit(varidx(real_line, 2), ex_to<clifford>(Mc).get_metric());
	} else if (is_a<matrix>(Mc) || is_a<tensor>(Mc)) {
		cycle_metric = clifford_unit(varidx(real_line, 2), indexed(Mc, varidx(symbol("ic"), 2),
										varidx(symbol("jc"), 2)));
	} else if (is_a<indexed>(Mc)) {
		cycle_metric = clifford_unit(varidx(real_line, 2), Mc);
	} else if (is_a<realsymbol>(Mc) || is_a<numeric>(Mc)) {
		cycle_metric=clifford_unit(varidx(real_line, 2), indexed(diag_matrix(lst(-1,Mc)),
										varidx(symbol("ic"), 2), varidx(symbol("jc"), 2)));
	}

#line 2305 "figure.nw"
	update_figure();
}

#line 2310 "figure.nw"
return_type_t figure::return_type_tinfo() const
{
	return make_return_type_t<figure>();
}

#line 2317 "figure.nw"
int figure::compare_same_type(const basic &other) const
{
       GINAC_ASSERT(is_a<figure>(other));
	   return inherited::compare_same_type(other);
}

#line 2326 "figure.nw"
ex figure::evaluate_cycle(const ex & symbolic, const lst & cond) const
{
	//cerr << "symbolic: "; symbolic.dbgprint();
	//cerr << "condit: "; cond.dbgprint();
	bool first_solution=true, second_solution=false;

#line 2334 "figure.nw"
	lst symbols, lin_cond, nonlin_cond;
	if (is_a<symbol>(ex_to<cycle2D_data>(symbolic).get_m()))
		symbols.append(ex_to<cycle2D_data>(symbolic).get_m());
	for (int i = 0; i < 2; i++) // 2-dim cycles only here
		if (is_a<symbol>(ex_to<cycle2D_data>(symbolic).get_l(i)))
			symbols.append(ex_to<cycle2D_data>(symbolic).get_l(i));
	if (is_a<symbol>(ex_to<cycle2D_data>(symbolic).get_k()))
		symbols.append(ex_to<cycle2D_data>(symbolic).get_k());
	if (symbols.nops() == 0)
		throw(std::invalid_argument("figure::evaluate_cycle(): could not construct the default list of "
								 "parameters"));
	//cerr << "symbols: "; symbols.dbgprint();

#line 2350 "figure.nw"
	lst rhs;
	for (size_t r=0; r<cond.nops(); r++) {
		lst sys;
		const ex eq = (cond.op(r).op(0)-cond.op(r).op(1)).expand(); // lhs-rhs==0
		//cerr << "eq: "; eq.dbgprint();
		ex linpart = eq;
		for (size_t c=0; c<symbols.nops(); c++) {
			const ex co = eq.coeff(ex_to<symbol>(symbols.op(c)),1);
			linpart -= co*symbols.op(c);
			sys.append(co);
		}
		linpart = linpart.expand();
		//cerr << "sys: "; sys.dbgprint();
		//cerr << "linpart: "; linpart.dbgprint();

#line 2367 "figure.nw"
		bool is_linear=true;
		for (size_t i=0; i<symbols.nops(); i++)
			if (sys.has(symbols.op(i)) || linpart.has(symbols.op(i)))
				is_linear = false;
		//cerr << "this equation linear? " << is_linear << endl;

#line 2376 "figure.nw"
		if (is_linear) {
			lin_cond.append(sys);
			rhs.append(linpart);
		} else
			nonlin_cond.append(cond.op(r));
	}
	//cerr << "lin_cond: "; lin_cond.dbgprint();
	//cerr << "nonlin_cond: "; nonlin_cond.dbgprint();


#line 2388 "figure.nw"
	lst subs_lst1, free_vars;
 	if (lin_cond.nops()>0) {
		matrix solution;
		try {
			solution=ex_to<matrix>(lst_to_matrix(lin_cond)).solve(matrix(symbols.nops(),1,symbols),
																  matrix(rhs.nops(),1,rhs));

#line 2398 "figure.nw"
        } catch (const std::runtime_error & e) {
			return lst();
        }
        GINAC_ASSERT(solution.cols()==1);
        GINAC_ASSERT(solution.rows()==symbols.nops());

#line 2407 "figure.nw"
        for (size_t i=0; i<symbols.nops(); i++)
			if (symbols.op(i)==solution(i,0))
				free_vars.append(symbols.op(i));
			else
				subs_lst1.append(symbols.op(i)==solution(i,0));
	}

#line 2417 "figure.nw"
	cycle2D_data C_new, C1_new;
	if (nonlin_cond.nops() == 0) {
		C_new = ex_to<cycle2D_data>(symbolic.subs(subs_lst1)).normalize();
		//cerr << "C_new: "; C_new.dbgprint();
	}

#line 2425 "figure.nw"
		else {
			lst subs_lst2, // The second solution lists for quadratic equations
				nonlin_cond_new;
			subs_lst2=subs_lst1;
			//cerr << "free_vars: "; free_vars.dbgprint();
			//cerr << "subs_lst1: "; subs_lst1.dbgprint();

#line 2435 "figure.nw"
			ex quadratic_eq=nonlin_cond.op(0).subs(subs_lst1, subs_options::algebraic
												   | subs_options::no_pattern);
			ex quadratic=(quadratic_eq.op(0)-quadratic_eq.op(1)).expand().normal();
			//cerr << "quadratic: "; quadratic.dbgprint();
			bool is_quadratic=false;
			exmap flat_var_em, var1_em, var2_em;
			ex flat_var, var1, var2;

#line 2445 "figure.nw"
			for (size_t i=0; i < free_vars.nops(); ++i) {
				ex A=quadratic.coeff(free_vars.op(i),2).normal();
				//cerr << "A: "; A.dbgprint();
				//				if (! is_almost_zero(A.evalf())) {
				if (! A.is_zero()) {
					is_quadratic=true;
					ex B=quadratic.coeff(free_vars.op(i),1),
						C=quadratic.coeff(free_vars.op(i),0);
					ex D=(pow(B,2)-numeric(4)*A*C).normal();
					//cerr << "D: "; D.dbgprint();

#line 2459 "figure.nw"
					if (free_vars.nops()>1) {
						if (i==0) {
							flat_var_em.insert(std::make_pair(free_vars.op(1), numeric(1)));
							flat_var=(free_vars.op(1)==numeric(1));
						} else {
							flat_var_em.insert(std::make_pair(free_vars.op(0), numeric(1)));
							flat_var=(free_vars.op(0)==numeric(1));
						}
					}
					D=D.subs(flat_var_em,subs_options::algebraic | subs_options::no_pattern);
					//cerr << "D: "; D.dbgprint();


#line 2476 "figure.nw"
					if (is_almost_zero1(D.evalf()) || ((! is_almost_zero1(B.evalf())) && is_almost_zero1((A/B).evalf()))) {
						if (is_almost_zero1(D.evalf())) {
							//cerr << "zero determinant" << endl;
							var1=(-B/numeric(2)/A).subs(flat_var_em,subs_options::algebraic
											   | subs_options::no_pattern).normal();
						} else {
							//cerr << "almost linear equation" << endl;
							var1=(-C/B).subs(flat_var_em,subs_options::algebraic
											   | subs_options::no_pattern).normal();
						}
						var1_em.insert(std::make_pair(free_vars.op(i), var1));
						subs_lst1=ex_to<lst>(subs_lst1
											 .subs(var1_em,subs_options::algebraic | subs_options::no_pattern));
						subs_lst1=ex_to<lst>(subs_lst1.append(free_vars.op(i) == var1)
											 .subs(flat_var_em,subs_options::algebraic | subs_options::no_pattern));
						if (free_vars.nops()>1)
							subs_lst1.append(flat_var);
						//cerr << "subs_lst1a: "; subs_lst1.dbgprint();

#line 2497 "figure.nw"
					} else {
						second_solution=true;
						var1=((-B+sqrt(D))/2/A).subs(flat_var_em,subs_options::algebraic
											   | subs_options::no_pattern).normal();
						var1_em.insert(std::make_pair(free_vars.op(i), var1));
						var2=((-B-sqrt(D))/2/A).subs(flat_var_em,subs_options::algebraic
											   | subs_options::no_pattern).normal();
						var2_em.insert(std::make_pair(free_vars.op(i), var2));
						subs_lst1=ex_to<lst>(subs_lst1
											 .subs(var1_em,subs_options::algebraic | subs_options::no_pattern));
						subs_lst1=ex_to<lst>(subs_lst1.append(free_vars.op(i) == var1)
											 .subs(flat_var_em,subs_options::algebraic | subs_options::no_pattern));

#line 2513 "figure.nw"
						if (free_vars.nops()>1)
							subs_lst1.append(flat_var);
						//cerr << "subs_lst1b: "; subs_lst1.dbgprint();
						subs_lst2=ex_to<lst>(subs_lst2
											 .subs(var2_em,subs_options::algebraic | subs_options::no_pattern));
						subs_lst2=ex_to<lst>(subs_lst2.append(free_vars.op(i) == var2)
											 .subs(flat_var_em,subs_options::algebraic | subs_options::no_pattern));
						if (free_vars.nops()>1)
							subs_lst2.append(flat_var);
						//cerr << "subs_lst2b: "; subs_lst2.dbgprint();
					}
					break;
				}
			}

#line 2531 "figure.nw"
			if (! is_quadratic) {
				//cerr << "The equation is not quadratic in a single variable"<<endl;
				//cerr << "free_vars: "; free_vars.dbgprint();
				if (free_vars.nops()>1) {
					//cerr << "Quadratic substituted "; (quadratic.subs(free_vars.op(0)==numeric(1))==0).dbgprint();

#line 2540 "figure.nw"
					int count=0;
					if (quadratic.has(free_vars.op(1))) {
						var1=lsolve(quadratic.subs(free_vars.op(0)==numeric(1))==0, free_vars.op(1));
						var1_em.insert(std::make_pair(free_vars.op(1), var1));
						var1_em.insert(std::make_pair(free_vars.op(0), numeric(1)));
						subs_lst1=ex_to<lst>(subs_lst1
										 .subs(var1_em,subs_options::algebraic | subs_options::no_pattern));
						subs_lst1.append(free_vars.op(1) == var1).append(free_vars.op(0)==numeric(1));

						//cerr << "non-quadratic subs_lst1: "; subs_lst1.dbgprint();
						++count;
					}

#line 2555 "figure.nw"
					if (quadratic.has(free_vars.op(0))) {
						var2=lsolve(quadratic.subs(free_vars.op(1)==numeric(1))==0, free_vars.op(0));
						var2_em.insert(std::make_pair(free_vars.op(0), var2));
						var2_em.insert(std::make_pair(free_vars.op(1), numeric(1)));
						subs_lst2=ex_to<lst>(subs_lst2
										 .subs(var2_em,subs_options::algebraic | subs_options::no_pattern));
						subs_lst2.append(free_vars.op(0) == var2).append(free_vars.op(1)==numeric(1));
						//cerr << "non-quadratic subs_lst2: "; subs_lst2.dbgprint();

#line 2567 "figure.nw"
						if (count==0)
							subs_lst1=subs_lst2;
						++count;
					}
					if (count>1)
						second_solution=true;

#line 2577 "figure.nw"
				} else {
					//cerr << "Quadratic becomes linear: "; quadratic.dbgprint();
					//cerr << "Var: "; free_vars.op(0).dbgprint();
					ex B=quadratic.coeff(free_vars.op(0),1).normal(),
						C=quadratic.coeff(free_vars.op(0),0).normal();
					if (! (quadratic-(B*free_vars.op(0)+C)).normal().is_zero())
						return lst();

#line 2587 "figure.nw"
					var1=(-C/B).normal();
					var1_em.insert(std::make_pair(free_vars.op(0), var1));
					subs_lst1=ex_to<lst>(subs_lst1
										 .subs(var1_em,subs_options::algebraic | subs_options::no_pattern));
					subs_lst1.append(free_vars.op(0) == var1);
					//cerr << "non-quadratic subs_lst1: "; subs_lst1.dbgprint();
				}
			}

#line 2599 "figure.nw"
			lst::const_iterator it1= nonlin_cond.begin();
			++it1;
			//cerr << "Subs list: "; subs_lst1.dbgprint();
			lst subs_f1=ex_to<lst>(subs_lst1.evalf()), subs_f2;
			//cerr << "Subs list float: "; subs_f1.dbgprint();
			if(second_solution)
				subs_f2=ex_to<lst>(subs_lst2.evalf());
			for (; it1 != nonlin_cond.end(); ++it1) {
				first_solution &=is_almost_zero1((it1->op(0)-it1->op(1)).subs(subs_f1,
																	 subs_options::algebraic
																			 | subs_options::no_pattern).evalf());
				if(second_solution)
					second_solution &= is_almost_zero1((it1->op(0)-it1->op(1)).subs(subs_f2,
																		  subs_options::algebraic
																		  | subs_options::no_pattern).evalf());

			}

#line 2619 "figure.nw"
			if (first_solution)
				C_new=symbolic.subs(subs_lst1, subs_options::algebraic
													| subs_options::no_pattern);

			//cerr << "C_new: "; C_new.dbgprint();
			if (second_solution)
				C1_new=symbolic.subs(subs_lst2, subs_options::algebraic
													 | subs_options::no_pattern);
			//cerr << "C1_new: "; C1_new.dbgprint();
		}

#line 2632 "figure.nw"
		lst repl;
 		if (ex_to<cycle2D_data>(C_new).has(ex_to<cycle2D_data>(symbolic).get_k()))
			repl.append(ex_to<cycle2D_data>(symbolic).get_k()==realsymbol());
		if (ex_to<cycle2D_data>(C_new).has(ex_to<cycle2D_data>(symbolic).get_m()))
			repl.append(ex_to<cycle2D_data>(symbolic).get_m()==realsymbol());
		if (ex_to<cycle2D_data>(C_new).has(ex_to<cycle2D_data>(symbolic).get_l().op(0).op(0)))
			repl.append(ex_to<cycle2D_data>(symbolic).get_l().op(0).op(0)==realsymbol());
		if (ex_to<cycle2D_data>(C_new).has(ex_to<cycle2D_data>(symbolic).get_l().op(0).op(1)))
			repl.append(ex_to<cycle2D_data>(symbolic).get_l().op(0).op(1)==realsymbol());


#line 2645 "figure.nw"
	if (repl.nops()>0) {
		if (first_solution)
			C_new=C_new.subs(repl);
		if (second_solution)
			C1_new=C1_new.subs(repl);
	}

	//cerr << endl;

#line 2656 "figure.nw"
	lst res;

	if (first_solution)
		res.append(C_new.num_normalize());
	if (second_solution)
		res.append(C1_new.num_normalize());

	return res;
}

#line 2668 "figure.nw"
ex figure::update_cycle2D_node(const ex & key, const lst & eq_cond, const lst & neq_cond, lst res, unsigned int level)
{
	//cerr << "level: " << level << " "; nodes[key].dbgprint();
	if (level == 0) {// set the iniail symbolic cycle for calculations
		
#line 2735 "figure.nw"
	if ( (nodes[key].get_parents().nops() == 1) && (is_a<subfigure>(nodes[key].get_parents().op(0)))) {
		figure F=ex_to<figure>(ex_to<basic>(ex_to<subfigure>(nodes[key].get_parents().op(0)).get_subf())
							   .clearflag(status_flags::expanded));
		lst parkeys=ex_to<lst>(ex_to<subfigure>(nodes[key].get_parents().op(0)).get_parlist());
		unsigned int var=0;
		char name[12];
		for (lst::const_iterator it = parkeys.begin(); it != parkeys.end(); ++it) {
			sprintf(name, "variable%03d", var);
			F.set_cycle2D(F.get_cycle2D_label(name), nodes[*it].get_cycles());
			++var;
		}
		F.set_metric(point_metric,cycle_metric); // this calls automatic figure re-calculation
		return F.get_cycle2D(F.get_cycle2D_label("result"));

#line 2752 "figure.nw"
	} else
		nodes[key].set_cycles(cycle2D_data(k, indexed(matrix(1, 2, lst(l,n)), varidx(key, 2)), m, false));


#line 2673 "figure.nw"
	}

#line 2677 "figure.nw"
	lst par = nodes[key].get_parents();
	lst::const_iterator it = par.begin();
	for(unsigned int i=0; i<level;++i)
		++it;

	lst new_cond=ex_to<lst>(ex_to<cycle_relation>(*it).rel_to_parent(nodes[key].get_cycles().op(0),
																	 point_metric, cycle_metric, nodes));
	//cerr << "new_cond: "; new_cond.dbgprint();

#line 2688 "figure.nw"
	for (lst::const_iterator it1 = new_cond.begin(); it1 != new_cond.end(); ++it1) {
		lst store_cond=neq_cond;
		lst use_cond=eq_cond;
		lst step_cond=ex_to<lst>(*it1);
		for (lst::const_iterator it2 = step_cond.begin(); it2 != step_cond.end(); ++it2)
			if ((is_a<relational>(*it2) && ex_to<relational>(*it2).info(info_flags::relation_equal)))
				use_cond.append(*it2);	// append the equation
			else
				store_cond.append(*it); // store the pointer to parents producing inequality
		//cerr << "use_cond: "; use_cond.dbgprint();
		//cerr << "store_cond: "; store_cond.dbgprint();
		if(level == par.nops()-1) { //if the last one in the parents list
			lst cnew=ex_to<lst>(evaluate_cycle(nodes[key].get_cycle2D_data(0), use_cond));

#line 2705 "figure.nw"
			//cerr<< "Store cond: "; store_cond.dbgprint();
			//cerr<< "Use cond: "; use_cond.dbgprint();
			for (size_t inew=0; inew< cnew.nops(); ++inew) {
				bool to_add=true;
				for (size_t icon=0; icon< store_cond.nops(); ++icon) {
					lst suits=ex_to<lst>(ex_to<cycle_relation>(store_cond.op(icon))
										 .rel_to_parent(ex_to<cycle2D_data>(cnew.op(inew)), point_metric,
														cycle_metric, nodes));
					//cerr<< "Suit: "; suits.dbgprint();
					for (size_t is=0; is< suits.nops(); ++is)
						for (size_t ic=0; ic< suits.op(is).nops(); ++ic)
							if  (suits.op(is).op(ic).is_zero())
								to_add=false;
				}
				if (to_add)
					res.append(cnew.op(inew));
			}
		//cerr<< "Result: "; res.dbgprint();
		} else
			res=ex_to<lst>(update_cycle2D_node(key, use_cond, store_cond, res, level+1));
	}
	if (level ==0)
		return unique_cycle(res);
	else
		return res;
}

#line 2758 "figure.nw"
void figure::update_figure()
{
	if (info(status_flags::expanded))
		return;
	lst all_child;
	for (exhashmap<cycle2D_node>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		if (ex_to<cycle2D_node>(it->second).get_generation() == 0) {
			if (ex_to<cycle2D_node>(it->second).get_parents().nops() > 0)
				nodes[it->first].set_cycles(ex_to<lst>(update_cycle2D_node(it->first)));

			lst ch=ex_to<cycle2D_node>(it->second).get_children();
			for (lst::const_iterator it1 = ch.begin(); it1 != ch.end(); ++it1)
				all_child.append(*it1);
		}
	all_child.sort();
	all_child.unique();
	update_node_lst(all_child);
}

#line 2779 "figure.nw"
ex figure::get_cycle2D(const ex & key, bool use_point_metric) const
{
	exhashmap<cycle2D_node> snodes=get_nodes();
	return snodes[key].get_cycle2D(use_point_metric?point_metric:cycle_metric);
}


#line 2788 "figure.nw"
void figure::reset_figure()
{
	nodes.clear();
	
#line 2098 "figure.nw"
	nodes[infinity] = cycle2D_node(cycle2D_data(numeric(0),indexed(matrix(1, 2, lst(numeric(0),numeric(0))),
																   varidx(infinity, 2)),numeric(1)),INFINITY_GEN);
 
#line 2792 "figure.nw"
	
#line 2103 "figure.nw"
	nodes[real_line] = cycle2D_node(cycle2D_data(numeric(0),indexed(matrix(1, 2, lst(numeric(0),numeric(1))),
																	varidx(real_line, 2)),numeric(0)),REAL_LINE_GEN);

#line 2793 "figure.nw"
}

#line 2797 "figure.nw"
ex figure::add_point(const ex & x, const ex & y,  string  name, string  TeXname)
{
	
#line 2982 "figure.nw"
	string TeXname_new;
	std::regex e ("([[:alpha:]]+)([[:digit:]]+)");
	std::regex e1 ("([[:alnum:]]+)_([[:alnum:]]+)");
	if (TeXname == "") {
		if (std::regex_match(name, e))
			TeXname_new=std::regex_replace (name,e,"$1_{$2}");
		else if (std::regex_match(name, e1))
			TeXname_new=std::regex_replace (name,e1,"$1_{$2}");
	} else
		TeXname_new=TeXname;

#line 2800 "figure.nw"
	symbol key(name, TeXname_new);
	return add_point(x, y, key);
}

#line 2806 "figure.nw"
ex figure::add_point(const ex & x, const ex & y, const ex & key)
{
	if (not is_a<symbol>(key))
		throw(std::invalid_argument("figure::add_point(const ex &, const ex &, const ex &): the third"
									" argument need to be a point"));
#line 2818 "figure.nw"
	symbol mother(ex_to<symbol>(key).get_name()+"m"),
		father(ex_to<symbol>(key).get_name()+"f");

	nodes[mother]=cycle2D_node(cycle2D_data(numeric(0),indexed(matrix(1, 2, lst(numeric(1),numeric(0))),
															   varidx(mother, 2)),numeric(2)*x),
							   GHOST_GEN, lst(), lst(key));
	nodes[father]=cycle2D_node(cycle2D_data(numeric(0),indexed(matrix(1, 2, lst(numeric(0),numeric(1))),
															   varidx(father, 2)),numeric(2)*y),
							   GHOST_GEN, lst(), lst(key));

#line 2833 "figure.nw"
	nodes[key]=cycle2D_node(cycle2D_data(), 0,
							lst(cycle_relation(mother,cycle_orthogonal),cycle_relation(father,cycle_orthogonal),
								cycle_relation(key,cycle_orthogonal,false),cycle_relation(infinity,cycle_different)));


#line 2839 "figure.nw"
	if (! info(status_flags::expanded))
		nodes[key].set_cycles(ex_to<lst>(update_cycle2D_node(key)));
	if (FIGURE_DEBUG)
		cerr << "Add the point: (" << x << "," << y
			 << ") as the cycle: " << nodes[key] << endl;
	return key;
}

#line 2849 "figure.nw"
ex figure::add_cycle2D(const ex & C, const ex & key)
{
	nodes[key]=cycle2D_node(C);
	if (FIGURE_DEBUG)
		cerr << "Add the cycle: " << nodes[key] << endl;
	return key;
}

#line 2859 "figure.nw"
ex figure::add_cycle2D(const ex & C, string  name, string  TeXname)
{
	
#line 2982 "figure.nw"
	string TeXname_new;
	std::regex e ("([[:alpha:]]+)([[:digit:]]+)");
	std::regex e1 ("([[:alnum:]]+)_([[:alnum:]]+)");
	if (TeXname == "") {
		if (std::regex_match(name, e))
			TeXname_new=std::regex_replace (name,e,"$1_{$2}");
		else if (std::regex_match(name, e1))
			TeXname_new=std::regex_replace (name,e1,"$1_{$2}");
	} else
		TeXname_new=TeXname;

#line 2862 "figure.nw"
	symbol key(name, TeXname_new);
	return add_cycle2D(C, key);
 }

#line 2868 "figure.nw"
void figure::set_cycle2D(const ex & key, const ex & C)
{
    if (nodes.find(key) == nodes.end())
        throw(std::invalid_argument("figure::set_cycle2D(): there is no node wi\
th the key given"));

    if (nodes[key].get_parents().nops() > 0)
        throw(std::invalid_argument("figure::set_cycle2D(): cannot modify data \
of a cycle with parents"));

    nodes[key].set_cycles(C);

    if (FIGURE_DEBUG)
        cerr << "Replace the cycle: " << nodes[key] << endl;
}

#line 2886 "figure.nw"
void figure::move_cycle2D(const ex & key, const ex & C)
{
	if (nodes.find(key) == nodes.end())
		throw(std::invalid_argument("figure::set_cycle2D(): there is no node with the key given"));

	if (nodes[key].get_generation() != 0)
		throw(std::invalid_argument("figure::set_cycle2D(): cannot modify data of a cycle in"
									" non-zero generation"));
#line 2900 "figure.nw"
	if (nodes[key].get_parents().nops() > 0) {
		lst par=nodes[key].get_parent_keys();
		for(lst::const_iterator it = par.begin(); it != par.end(); ++it)
			if (nodes[*it].get_generation() == GHOST_GEN)
				nodes.erase(*it);
			else
				nodes[*it].remove_child(key);
	}
	nodes[key].parents=lst();

#line 2912 "figure.nw"
	nodes[key].set_cycles(C);
	update_node_lst(nodes[key].get_children());

	if (FIGURE_DEBUG)
		cerr << "Replace the cycle: " << nodes[key] << endl;
}

#line 2921 "figure.nw"
ex figure::add_cycle_rel(const lst & rel, const ex & key)
{
	lst cond;
	int gen=0;

	for(lst::const_iterator it = rel.begin(); it != rel.end(); ++it) {
		if (ex_to<cycle_relation>(*it).get_parkey() != key)
			gen=max(gen, nodes[ex_to<cycle_relation>(*it).get_parkey()].get_generation());
		nodes[ex_to<cycle_relation>(*it).get_parkey()].add_child(key);
	}
	nodes[key]=cycle2D_node(cycle2D_data(),gen+1,rel);

#line 2935 "figure.nw"
	if (! info(status_flags::expanded))
		nodes[key].set_cycles(ex_to<lst>(update_cycle2D_node(key)));

	if (FIGURE_DEBUG)
		cerr << "Add the cycle : " << nodes[key] << endl;

	return key;
}

#line 2947 "figure.nw"
ex figure::add_cycle_rel(const lst & rel, string name, string TeXname)
{
	
#line 2982 "figure.nw"
	string TeXname_new;
	std::regex e ("([[:alpha:]]+)([[:digit:]]+)");
	std::regex e1 ("([[:alnum:]]+)_([[:alnum:]]+)");
	if (TeXname == "") {
		if (std::regex_match(name, e))
			TeXname_new=std::regex_replace (name,e,"$1_{$2}");
		else if (std::regex_match(name, e1))
			TeXname_new=std::regex_replace (name,e1,"$1_{$2}");
	} else
		TeXname_new=TeXname;

#line 2950 "figure.nw"
	return add_cycle_rel(rel, symbol(name, TeXname_new));
}

#line 2955 "figure.nw"
ex figure::add_subfigure(const ex & F, const lst & L, const ex & key)
{
	int gen=0;

	for(lst::const_iterator it = L.begin(); it != L.end(); ++it) {
		if (! it->is_equal(key))
			gen=max(gen, nodes[*it].get_generation());
		nodes[*it].add_child(key);
	}
	nodes[key]=cycle2D_node(cycle2D_data(),gen+1,lst(subfigure(F,L)));
	if (! info(status_flags::expanded))
		nodes[key].set_cycles(ex_to<lst>(update_cycle2D_node(key)));

	return key;
}

#line 2974 "figure.nw"
ex figure::add_subfigure(const ex & F, const lst & l, string name, string TeXname)
{
	
#line 2982 "figure.nw"
	string TeXname_new;
	std::regex e ("([[:alpha:]]+)([[:digit:]]+)");
	std::regex e1 ("([[:alnum:]]+)_([[:alnum:]]+)");
	if (TeXname == "") {
		if (std::regex_match(name, e))
			TeXname_new=std::regex_replace (name,e,"$1_{$2}");
		else if (std::regex_match(name, e1))
			TeXname_new=std::regex_replace (name,e1,"$1_{$2}");
	} else
		TeXname_new=TeXname;

#line 2977 "figure.nw"
		return add_subfigure(F, l, symbol(name, TeXname_new));
}

#line 2995 "figure.nw"
void figure::move_point(const ex & key, const ex & x, const ex & y)
{
	if (nodes.find(key) == nodes.end())
		throw(std::invalid_argument("figure::move_point(): there is no node with the key given"));

	if (nodes[key].get_generation() != 0)
		throw(std::invalid_argument("figure::move_point(): cannot modify data of a cycle in"
									" non-zero generation"));

	if (FIGURE_DEBUG)
		cerr << "A cycle is moved : " << nodes[key] << endl;

#line 3010 "figure.nw"
	lst par=nodes[key].get_parent_keys();
	if (par.nops() == 4 ) {
		for(lst::const_iterator it = par.begin(); it != par.end(); ++it) {
			if (ex_to<symbol>(*it).get_name() == (ex_to<symbol>(key).get_name()+"m"))
				nodes[*it].set_cycles(cycle2D_data(numeric(0),indexed(matrix(1, 2, lst(numeric(1),numeric(0))),
																	  varidx(*it, 2)),numeric(2)*x));
			else if (ex_to<symbol>(*it).get_name() == (ex_to<symbol>(key).get_name()+"f"))
				nodes[*it].set_cycles(cycle2D_data(numeric(0),indexed(matrix(1, 2, lst(numeric(0),numeric(1))),
																	  varidx(*it, 2)),numeric(2)*y));
		}

#line 3024 "figure.nw"
	} else if  (par.nops() == 0) {
		lst chil=nodes[key].get_children();
		
#line 2818 "figure.nw"
	symbol mother(ex_to<symbol>(key).get_name()+"m"),
		father(ex_to<symbol>(key).get_name()+"f");

	nodes[mother]=cycle2D_node(cycle2D_data(numeric(0),indexed(matrix(1, 2, lst(numeric(1),numeric(0))),
															   varidx(mother, 2)),numeric(2)*x),
							   GHOST_GEN, lst(), lst(key));
	nodes[father]=cycle2D_node(cycle2D_data(numeric(0),indexed(matrix(1, 2, lst(numeric(0),numeric(1))),
															   varidx(father, 2)),numeric(2)*y),
							   GHOST_GEN, lst(), lst(key));

#line 2833 "figure.nw"
	nodes[key]=cycle2D_node(cycle2D_data(), 0,
							lst(cycle_relation(mother,cycle_orthogonal),cycle_relation(father,cycle_orthogonal),
								cycle_relation(key,cycle_orthogonal,false),cycle_relation(infinity,cycle_different)));

#line 3027 "figure.nw"
		nodes[key].children=chil;
	} else
		throw(std::invalid_argument("figure::move_point(): strange number (neither 0 nor 4) of parents,"
									" which zero-generation node shall have!"));

	if (info(status_flags::expanded))
		return;

	nodes[key].set_cycles(ex_to<lst>(update_cycle2D_node(key)));
	update_node_lst(nodes[key].get_children());

#line 3041 "figure.nw"
	 update_node_lst(nodes[key].get_children());
	 if (FIGURE_DEBUG)
		cerr << "Moved to: (" << x << ", " << y << ")" << endl;
}

#line 3048 "figure.nw"
void figure::update_node_lst(const ex & inlist)
{
	if (info(status_flags::expanded))
		return;

	lst intake=ex_to<lst>(inlist);
	while (intake.nops() !=0) {
		int mingen=nodes[*intake.begin()].get_generation();
		for (lst::const_iterator it = intake.begin(); it != intake.end(); ++it)
			mingen=min(mingen, nodes[*it].get_generation());
		lst current, future;
		for (lst::const_iterator it = intake.begin(); it != intake.end(); ++it)
			if (nodes[*it].get_generation() == mingen)
				current.append(*it);
			else
				future.append(*it);
#line 3066 "figure.nw"
		for (lst::const_iterator it = current.begin(); it != current.end(); ++it) {
			nodes[*it].set_cycles(ex_to<lst>(update_cycle2D_node(*it)));
			//			lst nchild=nodes[*it].get_children_except(*it);
			lst nchild=nodes[*it].get_children();
			for (lst::const_iterator it1 = nchild.begin(); it1 != nchild.end(); ++it1)
				future.append(*it1);
		}
#line 3075 "figure.nw"
		intake=future;
                intake.sort();
		intake.unique();
	}
}
#line 3082 "figure.nw"
ex figure::get_cycle2D_label(string name) const
{
	for (exhashmap<cycle2D_node>::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
		if (ex_to<symbol>(it->first).get_name() == name)
			return it->first;

	return 0;
}

#line 3094 "figure.nw"
void figure::remove_cycle2D_node(const ex & key)
{
	lst  branches=nodes[key].get_children();
	for (lst::const_iterator it = branches.begin(); it != branches.end(); ++it)
		remove_cycle2D_node(*it);

#line 3102 "figure.nw"
	lst  par = nodes[key].get_parent_keys();
	for (lst::const_iterator it = par.begin(); it != par.end(); ++it) {

#line 3109 "figure.nw"
		if (nodes[*it].get_generation() == GHOST_GEN)
			nodes.erase(*it);
		else
			nodes[*it].remove_child(key);
	}

#line 3117 "figure.nw"
	//remove the cycle2D_node c from the figure
	nodes.erase(key);
	if (FIGURE_DEBUG)
		cerr << "A cycle is removed :" << key << endl ;
}

#line 3125 "figure.nw"
void figure::asy_draw(ostream & ost, ostream & err, const string picture,
					  const ex & xmin, const ex & xmax, const ex & ymin, const ex & ymax,
					  asy_style style, label_string lstring, bool with_realline,
					  bool with_header, int points_per_arc) const
{
	stringstream labels;
	string dots;
	std::regex re("dot\\(");

	for (exhashmap<cycle2D_node>::const_iterator it = nodes.begin(); it != nodes.end(); ++it) {
		lst cycles=ex_to<lst>(it->second.get_cycle2D(point_metric));
		for (lst::const_iterator it1 = cycles.begin(); it1 != cycles.end(); ++it1)
			try {
				if ( (it->second.get_generation() > REAL_LINE_GEN) ||
					 ((it->second.get_generation() == REAL_LINE_GEN) && with_realline)) {
					ost << "// label: " << (it->first) << endl;

#line 3144 "figure.nw"
				lst colours;
				string asy_opt;
				if (it->second.custom_asy=="") {
					asy_opt=style(it->first, (*it1), colours);
				} else
					asy_opt=it->second.custom_asy;

#line 3153 "figure.nw"
				stringstream sstr;
				ex_to<cycle2D>(*it1).asy_draw(sstr, picture, xmin, xmax,
											 ymin, ymax, colours, asy_opt, with_header, points_per_arc);

#line 3160 "figure.nw"
			if (FIGURE_DEBUG && is_almost_zero1(ex_to<cycle2D>(*it1).det())
				&& ex_to<clifford>(point_metric).get_metric(idx(1,2),idx(1,2)).is_zero()) {
				double x=ex_to<numeric>(ex_to<cycle2D>(*it1).center(cycle_metric).op(0)
										.evalf()).to_double(),
					y=ex_to<numeric>(ex_to<cycle2D>(*it1).center(cycle_metric).op(1)
										.evalf()).to_double();
				if ( xmin <= x && x<=xmax && ymin <= y && y<=ymax)
					sstr << "dot((" << ex_to<cycle2D>(*it1).center(cycle_metric).op(0).evalf()
						 << "," << ex_to<cycle2D>(*it1).center(cycle_metric).op(1).evalf()
						 << "), black+3pt);" << endl;
			}

#line 3174 "figure.nw"
				if (std::regex_search(sstr.str(), re))
					dots+=sstr.str();
				else
					ost << sstr.str();


#line 3182 "figure.nw"
				labels << lstring(it->first, (*it1), sstr.str());
				}
			} catch (exception &p) {
				err << it->first <<": " << it->second;
			}
	}
	//cerr << "Dots: " << dots;
	ost << dots
		<< labels.str();
}

#line 3195 "figure.nw"
void figure::do_print(const print_dflt & con, unsigned level) const {
	for (exhashmap<cycle2D_node>::const_iterator it = nodes.begin(); it != nodes.end(); ++it) {
		if (it->second.get_generation() > GHOST_GEN  || FIGURE_DEBUG)
			con.s << it->first <<": " << it->second ;
	}
}

#line 3204 "figure.nw"
ex figure::op(size_t i) const
{
 GINAC_ASSERT(i<nops());
	switch(i) {
	case 0:
		return real_line;
	case 1:
		return infinity;
	case 2:
		return point_metric;
	case 3:
		return cycle_metric;
	default:
		throw(std::invalid_argument("figure::op(): requested operand out of the range (3)"));
	}
}

#line 3223 "figure.nw"
figure figure::subs(const ex & e, unsigned options) const
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

	exhashmap<cycle2D_node> snodes;
	for (exhashmap<cycle2D_node>::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
		snodes[it->first]=ex_to<cycle2D_node>(it->second.subs(m, options));

	return figure(point_metric.subs(m, options), cycle_metric.subs(m, options), snodes);
}

#line 3244 "figure.nw"
void figure::archive(archive_node &an) const
{
	inherited::archive(an);
	an.add_ex("real_line", real_line);
	an.add_ex("infinity", infinity);
	an.add_ex("point_metric", ex_to<clifford>(point_metric));
	an.add_ex("cycle_metric", ex_to<clifford>(cycle_metric));

#line 3254 "figure.nw"
	lst keys, cnodes;
	for (exhashmap<cycle2D_node>::const_iterator it = nodes.begin(); it != nodes.end(); ++it) {
		keys.append(it->first);
		cnodes.append(it->second);
	}
	an.add_ex("keys", keys);
	an.add_ex("cnodes", cnodes);
}

#line 3265 "figure.nw"
void figure::read_archive(const archive_node &an, lst &sym_lst)
{
	inherited::read_archive(an, sym_lst);
	ex e;
	an.find_ex("point_metric", e, sym_lst);
	point_metric=ex_to<clifford>(e);
	an.find_ex("cycle_metric", e, sym_lst);
	cycle_metric=ex_to<clifford>(e);
	lst all_sym=sym_lst;
	ex keys, cnodes;
	an.find_ex("real_line", real_line, sym_lst);
	all_sym.append(real_line);
	an.find_ex("infinity", infinity, sym_lst);
	all_sym.append(infinity);

#line 3282 "figure.nw"
	//an.find_ex("keys", keys, all_sym);
	an.find_ex("keys", keys, sym_lst);
	for (lst::const_iterator it = ex_to<lst>(keys).begin(); it != ex_to<lst>(keys).end(); ++it)
		all_sym.append(*it);
	all_sym.sort();
	all_sym.unique();
	an.find_ex("cnodes", cnodes, all_sym);
	lst::const_iterator it1 = ex_to<lst>(cnodes).begin();
	nodes.clear();
	for (lst::const_iterator it = ex_to<lst>(keys).begin(); it != ex_to<lst>(keys).end(); ++it) {
		nodes[*it]=*it1;
		++it1;
	}
}

#line 3299 "figure.nw"
GINAC_BIND_UNARCHIVER(figure);

#line 3303 "figure.nw"
bool figure::info(unsigned inf) const
{
	switch (inf) {
	case status_flags::expanded:
		return (inf & flags);
	}
	return inherited::info(inf);
}


#line 3315 "figure.nw"
string asy_cycle_color(const ex & label, const ex & C, lst & color)
{
	string asy_options="";
	if (is_almost_zero1(ex_to<cycle2D>(C).det())) {// point
		color=lst(0.5,0,0);
		asy_options="dotted";
	} else if (is_almost_zero1(ex_to<cycle2D>(C).get_k())) // straight line
		color=lst(0,0.5,0);
	else  // a proper circle-hyperbola-parabola
		color=lst(0,0,0.5);

	return asy_options;
}

#line 3331 "figure.nw"
string label_pos(const ex & label, const ex & C, const string draw_str) {
	stringstream sstr;
	sstr << latex << label;

	string name=ex_to<symbol>(label).get_name(), new_TeXname;

	if (sstr.str() == name) {
		string TeXname;
		
#line 2982 "figure.nw"
	string TeXname_new;
	std::regex e ("([[:alpha:]]+)([[:digit:]]+)");
	std::regex e1 ("([[:alnum:]]+)_([[:alnum:]]+)");
	if (TeXname == "") {
		if (std::regex_match(name, e))
			TeXname_new=std::regex_replace (name,e,"$1_{$2}");
		else if (std::regex_match(name, e1))
			TeXname_new=std::regex_replace (name,e1,"$1_{$2}");
	} else
		TeXname_new=TeXname;

#line 3340 "figure.nw"
		if (TeXname_new =="")
			new_TeXname=name;
		else
			new_TeXname=TeXname_new;
	} else
		new_TeXname=sstr.str();

	std::regex e("([.\\n\\r\\s]*)(dot|draw)\\(([\\w]*,)?((?:\\(.+?\\)|\\{.+?\\}|[^-,0-9\\.])+),([.\\n\\r]*)");
	std::regex e1("symbolLaTeXname");

	if (std::regex_search(draw_str, e)) {
			string labelstr=std::regex_replace (draw_str, e,
								"label($3\"$symbolLaTeXname$\",point($4,0.1),SE);\n",
								std::regex_constants::format_no_copy | std::regex_constants::format_first_only);
			return std::regex_replace (labelstr, e1, new_TeXname);
	} else
		return "";
}

#line 3361 "figure.nw"
void figure::asy_write(int size, const ex & xmin, const ex & xmax, const ex & ymin, const ex & ymax,
					  string name, string format,
					  asy_style style, label_string lstring, bool with_realline,
					  bool with_header, int points_per_arc) const
{
	char buffer [L_tmpnam];
	tmpnam (buffer);
	ofstream out(buffer);
	out << "size(" << size << ");" << endl;
	asy_draw(out, cerr, "", xmin, xmax, ymin, ymax,
			 style, lstring, with_realline, with_header, points_per_arc);
	if (name == "")
		out << "shipout();" << endl;
	else
		out << "shipout(\"" << name << "\");" << endl;
	out.flush();
	out.close();
	char command[L_tmpnam+120];
	strcpy(command, "asy -V -f ");
	strcat(command, format.c_str());
	strcat(command, " ");
	strcat(command, buffer);
	char * pcommand=command;
	system(pcommand);
	remove(buffer);
}

#line 3390 "figure.nw"
ex figure::check_rel(const ex & key1, const ex & key2, PCR rel, bool use_cycle_metric) const
{
	exhashmap<cycle2D_node> snodes=nodes;
	lst res,
		cycles1=ex_to<lst>(ex_to<cycle2D_node>(snodes[key1])
						   .get_cycle2D(use_cycle_metric? cycle_metric : point_metric)),
		cycles2=ex_to<lst>(ex_to<cycle2D_node>(snodes[key2])
						   .get_cycle2D(use_cycle_metric? cycle_metric : point_metric));

	for (lst::const_iterator it1 = cycles1.begin(); it1 != cycles1.end(); ++it1)
		for (lst::const_iterator it2 = cycles2.begin(); it2 != cycles2.end(); ++it2) {
			lst calc=ex_to<lst>(rel(ex_to<cycle2D>(*it1),ex_to<cycle2D>(*it2)));
			for (lst::const_iterator itr = calc.begin(); itr != calc.end(); ++itr) {

#line 3407 "figure.nw"
				ex e=(itr->op(0)).normal();
				if (is_a<relational>(e))
					res.append(e);
				else
					res.append(e==0);
			}
		}

	return res;
}
#line 3447 "figure.nw"
bool is_almost_equal(const ex & A, const ex & B)
{
	if ((not is_a<cycle2D>(A)) || (not is_a<cycle2D>(B)))
		return false;

	const cycle2D C1 = ex_to<cycle2D>(A),
        C2 = ex_to<cycle2D>(B);
	ex factor=0, ofactor=0;

	// Check that coefficients are scalar multiples of C2
	if (not is_almost_zero1((C1.get_m()*C2.get_k()-C2.get_m()*C1.get_k()).normal()))
		return false;
	// Set up coefficients for proportionality
	if (C1.get_k().normal().is_zero()) {
		factor=C1.get_m();
		ofactor=C2.get_m();
	} else {
		factor=C1.get_k();
		ofactor=C2.get_k();
	}

#line 3470 "figure.nw"
	for (int i=0; i<2; i++)
		// search the the first non-zero coefficient
		if (factor.is_zero()) {
			factor=C1.get_l(i);
			ofactor=C2.get_l(i);
		} else
			if (! is_almost_zero1((C1.get_l(i)*ofactor-C2.get_l(i)*factor).normal()))
				return false;
	return true;
}

#line 3488 "figure.nw"
ex check_tangent(const ex & C1, const ex & C2)
{
	return lst( (ex)lst(pow(ex_to<cycle2D>(C1).cycle_product(ex_to<cycle2D>(C2)),2)
					-ex_to<cycle2D>(C1).cycle_product(ex_to<cycle2D>(C1))
					 *ex_to<cycle2D>(C2).cycle_product(ex_to<cycle2D>(C2)) == 0));
}

#line 3502 "figure.nw"
ex cycle_tangent(const ex & C1, const ex & C2)
{
	return lst( (ex)lst(ex_to<cycle2D>(C1).cycle_product(ex_to<cycle2D>(C1))+numeric(1)==0,
				   ex_to<cycle2D>(C1).cycle_product(ex_to<cycle2D>(C2))
				   -sqrt(-ex_to<cycle2D>(C2).cycle_product(ex_to<cycle2D>(C2)))==0),
			   lst(ex_to<cycle2D>(C1).cycle_product(ex_to<cycle2D>(C1))+numeric(1)==0,
				   ex_to<cycle2D>(C1).cycle_product(ex_to<cycle2D>(C2))
				   +sqrt(-ex_to<cycle2D>(C2).cycle_product(ex_to<cycle2D>(C2)))==0));
}

#line 3514 "figure.nw"
ex cycle_tangent_o(const ex & C1, const ex & C2)
{
	return lst((ex)lst(ex_to<cycle2D>(C1).cycle_product(ex_to<cycle2D>(C1))+numeric(1)==0,
				   ex_to<cycle2D>(C1).cycle_product(ex_to<cycle2D>(C2))
					   -sqrt(-ex_to<cycle2D>(C2).cycle_product(ex_to<cycle2D>(C2)))==0));
}

#line 3523 "figure.nw"
ex cycle_tangent_i(const ex & C1, const ex & C2)
{
	return lst((ex)lst(ex_to<cycle2D>(C1).cycle_product(ex_to<cycle2D>(C1))+numeric(1)==0,
				   ex_to<cycle2D>(C1).cycle_product(ex_to<cycle2D>(C2))
					   +sqrt(-ex_to<cycle2D>(C2).cycle_product(ex_to<cycle2D>(C2)))==0));
}

#line 3532 "figure.nw"
ex cycle_different(const ex & C1, const ex & C2)
{
	return lst( (ex)lst(ex_to<cycle2D>(C1).is_equal(ex_to<basic>(C2), true)? 0: 1));
}

#line 3539 "figure.nw"
ex midpoint_constructor()
{
 	figure SF=ex_to<figure>((new figure)->setflag(status_flags::expanded));

	ex v1=SF.add_cycle2D(cycle2D_data(),"variable000");
	ex v2=SF.add_cycle2D(cycle2D_data(),"variable001");
	ex v3=SF.add_cycle2D(cycle2D_data(),"variable002");

#line 3549 "figure.nw"
	ex v4=SF.add_cycle_rel(lst(cycle_relation(v1,cycle_orthogonal),
							   cycle_relation(v2,cycle_orthogonal),
							   cycle_relation(v3,cycle_orthogonal)),
						   "v4");

#line 3556 "figure.nw"
	ex v5=SF.add_cycle_rel(lst(cycle_relation(v1,cycle_orthogonal),
							   cycle_relation(v2,cycle_orthogonal),
							   cycle_relation(v4,cycle_orthogonal)),
						   "v5");

#line 3563 "figure.nw"
	ex v6=SF.add_cycle_rel(lst(cycle_relation(v3,cycle_orthogonal),
							   cycle_relation(v4,cycle_orthogonal),
							   cycle_relation(v5,cycle_orthogonal)),
						   "v6");

#line 3570 "figure.nw"
	ex r=symbol("result");
	SF.add_cycle_rel(lst(cycle_relation(v4,cycle_orthogonal),
						   cycle_relation(v6,cycle_orthogonal),
						   cycle_relation(r,cycle_orthogonal,false),
						   cycle_relation(v3,cycle_adifferent)),
					   r);

	return SF;
}


#line 3584 "figure.nw"
ex unique_cycle(const ex & L)
{
	if(is_a<lst>(L) && (L.nops() > 1) ) {
		lst res;
		lst::const_iterator it = ex_to<lst>(L).begin();
		if (is_a<cycle2D_data>(*it)) {
			res.append(*it);
			++it;
			for (; it != ex_to<lst>(L).end(); ++it) {
				bool is_new=true;
				if (! is_a<cycle2D_data>(*it))
					break; // a non-cycle detected, get out

				for (lst::const_iterator it1 = res.begin(); it1 != res.end(); ++it1)
					if (ex_to<cycle2D_data>(*it).is_almost_equal(ex_to<basic>(*it1),true)) {
						is_new=false; // is a duplicate
						break;
					}
				if (is_new)
					res.append(*it);
			}
			if (it == ex_to<lst>(L).end()) // all are processed, no non-cycle is detected
				return res;
		}
	}
	return L;
}


