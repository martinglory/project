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

#ifndef ____figure__
#define ____figure__

#ifndef ____cyclenode__
#define ____cyclenode__

#define FIGURE_DEBUG true

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <regex>
#include "cycle.h"

#define REAL_LINE_GEN -1
#define INFINITY_GEN -2
#define GHOST_GEN -3
class cycle2D_data : public basic
{
GINAC_DECLARE_REGISTERED_CLASS(cycle2D_data, basic)

protected:
	ex k,
	l,
	m;

public:
	cycle2D_data(const ex & C);
 	cycle2D_data(const ex & k1, const ex l1, const ex &m1, bool normalize=false);
	ex get_cycle2D(const ex & metr) const;
	inline ex get_k() const { return k; }
	inline ex get_l() const { return l; }
	inline ex get_l(size_t i) const { return l.op(0).op(i); }
	inline ex get_m() const { return m;}
	void do_print(const print_dflt & con, unsigned level) const;
	void archive(archive_node &n) const;
	inline ex normalize() const {return cycle2D_data(k,l,m,true);}
	ex num_normalize() const;
	void read_archive(const archive_node &n, lst &sym_lst);
	bool is_equal(const basic & other, bool projectively) const;
	bool is_almost_equal(const basic & other, bool projectively) const;
	cycle2D_data subs(const ex & e, unsigned options=0) const;
	ex subs(const exmap & em, unsigned options=0) const;
        inline bool has(const ex & x) const { return (k.has(x) ||  l.has(x) ||  m.has(x)); }

protected:
	return_type_t return_type_tinfo() const;
};
GINAC_DECLARE_UNARCHIVER(cycle2D_data);


class cycle_relation;

class cycle2D_node : public basic
{
GINAC_DECLARE_REGISTERED_CLASS(cycle2D_node, basic)

protected:
	lst cycles; // List of cycle2D data entries
	int generation;
	lst children; // List of keys to cycle2D_nodes
	lst parents; // List of cycle_relations or a list containing a single subfigure
	string custom_asy; // Custom string fro Asymptote

public:
	cycle2D_node(const ex & C, int g=0);
	cycle2D_node(const ex & C, int g, const lst & par);
	cycle2D_node(const ex & C, int g, const lst & par,  const lst & chil);
	cycle2D_node subs(const ex & e, unsigned options=0) const;
	ex subs(const exmap & m, unsigned options=0) const;

protected:
	inline void add_child(const ex & c) {children.append(c);}

	inline ex get_cycles() const {return cycles;}

	ex get_cycle2D(const ex & metr) const;
	inline ex get_cycle2D_data(int i) const {return cycles.op(i);}

	inline int get_generation() const {return generation;}

	inline lst get_children() const {return children;}

	void set_cycles(const ex & C);

	void append_cycle(const ex & C);
	void append_cycle(const ex & k, const ex & l, const ex & m);

	lst get_parents() const;

	lst get_parent_keys() const ;

	void remove_child(const ex & c);

	inline void set_asy_opt(const string opt)  {custom_asy=opt;}

	void do_print(const print_dflt & con, unsigned level) const;
	void do_print_tree(const print_tree & con, unsigned level) const;
protected:
	return_type_t return_type_tinfo() const;
	void archive(archive_node &n) const;
	void read_archive(const archive_node &n, lst &sym_lst);

friend class cycle_relation;
friend class figure;
};
GINAC_DECLARE_UNARCHIVER(cycle2D_node);

using PCR = std::function<ex(const ex &, const ex &)>;

class cycle_relation  : public basic
{
	GINAC_DECLARE_REGISTERED_CLASS(cycle_relation, basic)
protected:
	ex parkey; // A key to a parent cycle2D_node in figure
	PCR rel; // A pointer to function which produces the relation
	bool use_cycle_metric; // If true uses the cycle space metric, otherwise the point space metric

public:
	cycle_relation(const ex & key, PCR rel, bool cm=true);

protected:
	inline ex get_parkey() const {return parkey;}
	inline PCR get_PCR() const {return rel;}
	inline bool cycle_metric_inuse() const {return use_cycle_metric;}
	ex rel_to_parent(const cycle2D_data & C1, const ex & pmetric, const ex & cmetric,
					 const exhashmap<cycle2D_node> & N) const;
	return_type_t return_type_tinfo() const;
	void do_print(const print_dflt & con, unsigned level) const;
	void do_print_tree(const print_tree & con, unsigned level) const;

        void archive(archive_node &n) const;
        void read_archive(const archive_node &n, lst &sym_lst);

friend class cycle2D_node;
friend class figure;
};
GINAC_DECLARE_UNARCHIVER(cycle_relation);

ex cycle_orthogonal(const ex & C1, const ex & C2);
ex cycle_f_orthogonal(const ex & C1, const ex & C2);
ex check_tangent(const ex & C1, const ex & C2);
ex cycle_different(const ex & C1, const ex & C2);
ex cycle_adifferent(const ex & C1, const ex & C2);

ex cycle_tangent(const ex & C1, const ex & C2);
ex cycle_tangent_i(const ex & C1, const ex & C2);
ex cycle_tangent_o(const ex & C1, const ex & C2);
inline cycle_relation is_orthogonal(const ex & key, bool cm=true)
					{return cycle_relation(key, cycle_orthogonal, cm);}
inline cycle_relation is_f_orthogonal(const ex & key, bool cm=true)
					{return cycle_relation(key, cycle_f_orthogonal, cm);}
inline cycle_relation is_different(const ex & key, bool cm=true)
					{return cycle_relation(key, cycle_different, cm);}
inline cycle_relation is_adifferent(const ex & key, bool cm=true)
					{return cycle_relation(key, cycle_adifferent, cm);}
inline cycle_relation is_tangent(const ex & key, bool cm=true)
					{return cycle_relation(key, cycle_tangent, cm);}
inline cycle_relation is_tangent_i(const ex & key, bool cm=true)
					{return cycle_relation(key, cycle_tangent_i, cm);}
inline cycle_relation is_tangent_o(const ex & key, bool cm=true)
					{return cycle_relation(key, cycle_tangent_o, cm);}

ex metric_e = clifford_unit(varidx(symbol("i"), 2), indexed(diag_matrix(lst(-1,-1)), varidx(symbol("j"), 2), varidx(symbol("k"), 2)));
ex metric_p = clifford_unit(varidx(symbol("i"), 2), indexed(diag_matrix(lst(-1,0)), varidx(symbol("j"), 2), varidx(symbol("k"), 2)));
ex metric_h = clifford_unit(varidx(symbol("i"), 2), indexed(diag_matrix(lst(-1,1)), varidx(symbol("j"), 2), varidx(symbol("k"), 2)));
inline ex cycle_orthogonal_e(const ex & C1, const ex & C2) {
	return lst((ex)lst(ex_to<cycle2D>(C1).is_orthogonal(ex_to<cycle2D>(C2), metric_e)));}

inline ex cycle_orthogonal_p(const ex & C1, const ex & C2) {
	return lst((ex)lst(ex_to<cycle2D>(C1).is_orthogonal(ex_to<cycle2D>(C2), metric_p)));}

inline ex cycle_orthogonal_h(const ex & C1, const ex & C2) {
	return lst((ex)lst(ex_to<cycle2D>(C1).is_orthogonal(ex_to<cycle2D>(C2), metric_h)));}
#endif /* defined(____cycle2D_node__) */

using asy_style=std::function<string(const ex &, const ex &, lst &)>;
//typedef string (*asy_style)(const ex &, const ex &, lst &);
inline string no_color(const ex & label, const ex & C, lst & color) {color=lst(0,0,0); return "";}
string asy_cycle_color(const ex & label, const ex & C, lst & color);
asy_style default_asy=asy_cycle_color;

using label_string=std::function<string(const ex &, const ex &, const string)>;
//typedef string (*label_string)(const ex &, const ex &, const string);
string label_pos(const ex & label, const ex & C, const string draw_str);
inline string no_label(const ex & label, const ex & C, const string draw_str) {return "";}
//label_string default_label=*no_label;
label_string default_label=label_pos;

class figure : public basic
{
GINAC_DECLARE_REGISTERED_CLASS(figure, basic)

public:
	ex real_line, // the key for the real line
        infinity; // the key for cycle at infinity
protected:
	ex point_metric; // The metric of the point space encoded as a clifford_unit object
        ex cycle_metric; // The metric of the cycle space encoded as a clifford_unit object
        exhashmap<cycle2D_node> nodes; // List of cycle2D_node, exhashmap<cycle2D_node> object
        ex k, l, n, m; // realsymbols for symbolic calculations

protected:
	//update all children of cycle2D_node c (when c is changed)
ex update_cycle2D_node(const ex & key, const lst & eq_cond=lst(),
						   const lst & neq_cond=lst(), lst res=lst(), unsigned int level=0);
void set_cycle2D(const ex & key, const ex & C);
ex evaluate_cycle(const ex & symbolic, const lst & cond) const;

public:
	inline ex get_cycle2D_node(const ex & k) {return nodes[k];}
	inline ex get_real_line() const {return real_line;}
	inline ex get_infinity() const {return infinity;}

		figure(const ex & Mp, const ex & Mc=0);
		void set_metric(const ex & Mp, const ex & Mc=0);
		figure(const ex & Mp, const ex & Mc, const exhashmap<cycle2D_node> & N);
		void reset_figure();
		ex add_point(const ex & x, const ex & y, string  name, string  TeXname="");
		ex add_point(const ex & x, const ex & y, const ex & key);
		ex add_cycle2D(const ex & C, string  name, string  TeXname="");
		ex add_cycle2D(const ex & C, const ex & key);
		ex add_cycle_rel(const lst & rel, string name, string TeXname="");
		ex add_cycle_rel(const lst & rel, const ex & key);
		ex add_subfigure(const ex & F, const lst & L, string name, string TeXname="");
		ex add_subfigure(const ex & F, const lst & L, const ex & key);
		void move_point(const ex & key, const ex & x, const ex & y);
		void move_cycle2D(const ex & key, const ex & C);
		void remove_cycle2D_node(const ex & key);
		ex get_cycle2D_label(string name) const;
		ex check_rel(const ex & key1, const ex & key2, PCR rel, bool use_cycle_metric=true) const;
		void asy_draw(ostream & ost =std::cout, ostream & err=std::cerr, const string picture="",
					  const ex & xmin = -5, const ex & xmax = 5,
					  const ex & ymin = -5, const ex & ymax = 5,
					  asy_style style=default_asy, label_string lstring=default_label,
					  bool with_realline=true, bool with_header = true, int points_per_arc = 0) const;
		void asy_write(int size=300, const ex & xmin = -5, const ex & xmax = 5,
					  const ex & ymin = -5, const ex & ymax = 5,
					  string name="figure-view-tmp", string format="eps",
					  asy_style style=default_asy, label_string lstring=default_label,
					  bool with_realline=true, bool with_header = true, int points_per_arc = 0) const;
		inline void set_asy_style(const ex & key, string opt) {nodes[key].set_asy_opt(opt);}
		void save(const char* file_name, const char* fig_name="myfig");
		figure(const char* file_name, string fig_name="myfig");
			inline ex get_point_metric() const {return point_metric;}
		        inline ex get_cycle_metric() const {return cycle_metric;}
			inline exhashmap<cycle2D_node> get_nodes() const {return nodes;}

			ex get_cycle2D(const ex & k, bool use_point_metric=true) const;
			inline size_t nops() const {return 4;}
			ex op(size_t i) const;
			figure subs(const ex & e, unsigned options=0) const;
			void archive(archive_node &n) const;
			void read_archive(const archive_node &n, lst &sym_lst);
			bool info(unsigned inf) const;



protected:
	void do_print(const print_dflt & con, unsigned level) const;
	return_type_t return_type_tinfo() const;

	void update_node_lst(const ex & inlist);

	void update_figure();

};
GINAC_DECLARE_UNARCHIVER(figure);

class subfigure  : public basic
{
	GINAC_DECLARE_REGISTERED_CLASS(subfigure, basic)
protected:
	ex subf; // A figure to be inserted
	lst parlist; // A list of key to a parent cycle2D_node in figure
public:
	subfigure(const ex & F, const ex & L);

protected:
	inline ex get_parlist() const {return parlist;}
	inline ex get_subf() const {return subf;}
	return_type_t return_type_tinfo() const;
	void do_print(const print_dflt & con, unsigned level) const;
	void do_print_tree(const print_tree & con, unsigned level) const;

        void archive(archive_node &n) const;
        void read_archive(const archive_node &n, lst &sym_lst);

friend class cycle2D_node;
friend class figure;
};
GINAC_DECLARE_UNARCHIVER(subfigure);


ex midpoint_constructor();
ex unique_cycle(const ex & L);
#endif /* defined(____figure__) */

