/*++
  Copyright (c) 2015 Microsoft Corporation

  Module Name:

  lackr.h

Abstract:


Author:

Mikolas Janota

Revision History:
--*/
#ifndef LACKR_H_
#define LACKR_H_

#include "ackermannization/ackr_info.h"
#include "ackermannization/ackr_helper.h"
#include "ast/rewriter/th_rewriter.h"
#include "util/cooperate.h"
#include "ast/bv_decl_plugin.h"
#include "util/lbool.h"
#include "model/model.h"
#include "solver/solver.h"
#include "util/util.h"
#include "tactic/tactic_exception.h"
#include "tactic/goal.h"

struct lackr_stats {
  lackr_stats() : m_it(0), m_ackrs_sz(0) {}
  void reset() { m_it = m_ackrs_sz = 0; }
  unsigned    m_it;       // number of lazy iterations
  unsigned    m_ackrs_sz; // number of congruence constraints
};

/** \brief
  A class to encode or directly solve problems with uninterpreted functions via ackermannization.
  Currently, solving is supported only for QF_UFBV.
 **/
class lackr {
  public:
    lackr(ast_manager& m, params_ref p, lackr_stats& st,
        expr_ref_vector& formulas, solver * uffree_solver);
    ~lackr();
    void updt_params(params_ref const & _p);

    /** \brief
     * Solve the formula that the class was initialized with.
     **/
    lbool operator() ();


    /** \brief
      Converts function occurrences to constants and encodes all congruence ackermann lemmas.

      This procedure guarantees a equisatisfiability with the input formula and it has a worst-case quadratic blowup.
      Before ackermannization an upper bound on congruence lemmas is computed and tested against \p lemmas_upper_bound.
      If this bound is exceeded, the function returns false, it returns true otherwise.
     **/
    bool mk_ackermann(/*out*/goal_ref& g, double lemmas_upper_bound);

    //
    // getters
    //
    inline ackr_info_ref get_info() { return m_info; }
    inline model_ref get_model() { return m_model; }

    //
    //  timeout mechanism
    //
    void checkpoint() {
      if (m_m.canceled()) {
        throw tactic_exception(TACTIC_CANCELED_MSG);
      }
      cooperate("lackr");
    }
  private:
    typedef ackr_helper::fun2terms_map fun2terms_map;
    typedef ackr_helper::app_set       app_set;
    ast_manager&                         m_m;
    params_ref                           m_p;
    expr_ref_vector                      m_formulas;
    expr_ref_vector                      m_abstr;
    fun2terms_map                        m_fun2terms;
    ackr_info_ref                        m_info;
    solver*                              m_sat;
    ackr_helper                          m_ackr_helper;
    th_rewriter                          m_simp;
    expr_ref_vector                      m_ackrs;
    model_ref                            m_model;
    bool                                 m_eager;
    lackr_stats&                         m_st;
    bool                                 m_is_init;

    bool init();
    lbool eager();
    lbool lazy();

    //
    // Introduce congruence ackermann lemma for the two given terms.
    //
    bool ackr(app * const t1, app * const t2);

    //
    // Introduce the ackermann lemma for each pair of terms.
    //
    void eager_enc();

    void abstract();

    void push_abstraction();

    void add_term(app* a);

    //
    // Collect all uninterpreted terms, skipping 0-arity.
    //
    bool collect_terms();
};
#endif /* LACKR_H_ */
