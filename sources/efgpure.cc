//
// FILE: efgpure.cc -- Find all pure strategy Nash equilibria
//
// $Id$
//

#include "efgpure.h"

#include "glist.h"
#include "efg.h"
#include "efgiter.h"
#include "efgciter.h"
#include "behavsol.h"

int FindPureNash(const EFSupport &p_support,
		 gList<BehavSolution> &p_solutions)
{
  int index;
  EfgContIter citer(p_support);
  gPVector<gNumber> probs(p_support.Game().NumInfosets());

  do  {
    int flag = 1;
    citer.GetProfile().InfosetProbs(probs);

    EfgIter eiter(citer);

    for (int pl = 1; flag && pl <= p_support.Game().NumPlayers(); pl++)  {
      gNumber current = citer.Payoff(pl);
      for (int iset = 1; flag && iset <= p_support.Game().Players()[pl]->NumInfosets();
	         iset++)  {
      	if (probs(pl, iset) == gNumber(0))   continue;
	      Infoset *s = p_support.Game().Players()[pl]->Infosets()[iset];
       	for (int act = 1; act <= s->NumActions(); act++)  {
	  eiter.Next(pl, iset);
	  if (eiter.Payoff(pl) > current)  {
	    flag = 0;
	    break;
	  }
      	}
      }
    }

    if (flag)  {
      BehavProfile<double> temp(p_support);
      // zero out all the entries, since any equilibria are pure
      ((gVector<double> &) temp).operator=(0);
      const PureBehavProfile<gNumber> &profile = citer.GetProfile();
      for (int pl = 1; pl <= p_support.Game().NumPlayers(); pl++)  {
	for (int iset = 1; iset <= p_support.Game().Players()[pl]->NumInfosets();
	     iset++)
	  temp(pl, iset, profile.GetAction(p_support.Game().Players()[pl]->Infosets()[iset])->GetNumber()) = 1;
      }

      index = p_solutions.Append(BehavSolution(temp, EfgAlg_PURENASH));
      p_solutions[index].SetIsNash(triTRUE);
    }
  }  while (citer.NextContingency());

  return p_solutions.Length();
}


int EnumPure(const EFSupport &p_support,
	     gList<BehavSolution> &p_solutions, double &p_time)
{
  EfgPSNEBySubgame module(p_support);
  module.Solve();
  p_time = module.Time();
  p_solutions = module.GetSolutions();
  return 1;
}

int EfgPSNEBySubgame::SolveSubgame(const Efg &/*E*/, const EFSupport &sup,
				   gList<BehavSolution> &solns)
{
  FindPureNash(sup, solns);

  return 0;
}

EfgPSNEBySubgame::EfgPSNEBySubgame(const EFSupport &S, int max)
  : SubgameSolver(S, max)
{ }

EfgPSNEBySubgame::~EfgPSNEBySubgame()   { }

