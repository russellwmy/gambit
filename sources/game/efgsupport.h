//
// $Source$
// $Date$
// $Revision$
//
// DESCRIPTION:
// Interface to supports for extensive forms
//
// This file is part of Gambit
// Copyright (c) 2002, The Gambit Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//

#ifndef EFGSUPPORT_H
#define EFGSUPPORT_H

#include "base/gstatus.h"
#include "game.h"

class gbtGameActionSet;

//
// We are in the process of migrating supports so they act like
// "views" on a game -- they should support (no pun intended) all the
// usual members of the underlying game (such as NumPlayers()) as well
// as extra editing features to show/hide actions
// 
// This will eventually derive from gbtGame, providing the usual
// extensive form operations
//
class gbtEfgSupport {
protected:
  gbtText m_label;
  gbtGame m_efg;
  gbtArray<gbtGameActionSet *> m_players;

  // The following members were added from a derived class.
  // The proper factoring of these features is uncertain...
  gbtArray<gbtList<bool> >         is_infoset_active;
  gbtArray<gbtList<gbtList<bool> > > is_nonterminal_node_active;

  void InitializeActiveListsToAllActive();
  void InitializeActiveListsToAllInactive();
  void InitializeActiveLists();

  bool infoset_has_active_nodes(const int pl, const int iset) const;
  bool infoset_has_active_nodes(const gbtGameInfoset &) const;
  void activate_this_and_lower_nodes(const gbtGameNode &);
  void deactivate_this_and_lower_nodes(const gbtGameNode &);

  void activate(const gbtGameNode &);
  void deactivate(const gbtGameNode &);
  void activate(const gbtGameInfoset &);
  void deactivate(const gbtGameInfoset &);

  void deactivate_this_and_lower_nodes_returning_deactivated_infosets(
                                                 const gbtGameNode &,
						 gbtList<gbtGameInfoset> *);
public:
  gbtEfgSupport(const gbtGame &);
  gbtEfgSupport(const gbtEfgSupport &);
  virtual ~gbtEfgSupport();
  gbtEfgSupport &operator=(const gbtEfgSupport &);

  bool operator==(const gbtEfgSupport &) const;
  bool operator!=(const gbtEfgSupport &) const;

  gbtGame GetTree(void) const { return m_efg; }

  gbtText GetLabel(void) const { return m_label; }
  void SetLabel(const gbtText &p_label) { m_label = p_label; }

  int NumActions(int pl, int iset) const;
  int NumActions(const gbtGameInfoset &) const;
  gbtPVector<int> NumActions(void) const;
  int NumDegreesOfFreedom(void) const;

  // Checks to see that every infoset in the support has at least one
  // action in it.
  bool HasActiveActionAt(const gbtGameInfoset &) const;
  bool HasActiveActionsAtAllInfosets(void) const;

  bool Contains(const gbtGameAction &) const;
  bool Contains(int pl, int iset, int act) const;
  int GetIndex(const gbtGameAction &) const;
  gbtGameAction GetAction(const gbtGameInfoset &, int index) const;
  gbtGameAction GetAction(int pl, int iset, int index) const;

  // Action editing functions
  void AddAction(const gbtGameAction &);
  bool RemoveAction(const gbtGameAction &);

  // Number of Sequences for the player
  int NumSequences(int pl) const;
  int TotalNumSequences(void) const;

  // Reachable Nodes and Information Sets
  gbtList<gbtGameNode> ReachableNonterminalNodes(const gbtGameNode &) const;
  gbtList<gbtGameNode> ReachableNonterminalNodes(const gbtGameNode &,
					      const gbtGameAction &) const;
  gbtList<gbtGameInfoset> ReachableInfosets(const gbtGameNode &) const;
  gbtList<gbtGameInfoset> ReachableInfosets(const gbtGameNode &,
					 const gbtGameAction &) const;
  gbtList<gbtGameInfoset> ReachableInfosets(const gbtGamePlayer &) const;

  bool AlwaysReaches(const gbtGameInfoset &) const;
  bool AlwaysReachesFrom(const gbtGameInfoset &, const gbtGameNode &) const;
  bool MayReach(const gbtGameNode &) const;
  bool MayReach(const gbtGameInfoset &) const;

  bool Dominates(const gbtGameAction &, const gbtGameAction &,
		 bool strong, bool conditional) const;
  bool IsDominated(const gbtGameAction &,
		   bool strong, bool conditional) const;
  gbtEfgSupport Undominated(bool strong, bool conditional,
			    const gbtArray<int> &players,
			    gbtOutput &, // tracefile 
			    gbtStatus &status) const;


  // The following are just echoed from the base game.  In the future,
  // derivation from gbtGame will handle these.
  gbtText GetComment(void) const { return m_efg->GetComment(); }
  void SetComment(const gbtText &p_comment) { m_efg->SetComment(p_comment); }
  bool IsConstSum(void) const { return m_efg->IsConstSum(); }
  int NumPlayers(void) const { return m_efg->NumPlayers(); }
  gbtGamePlayer GetChance(void) const { return m_efg->GetChance(); }
  gbtGamePlayer GetPlayer(int pl) const { return m_efg->GetPlayer(pl); }
  int NumOutcomes(void) const { return m_efg->NumOutcomes(); }
  gbtArray<int> NumInfosets(void) const { return m_efg->NumInfosets(); }
  gbtPVector<int> NumMembers(void) const { return m_efg->NumMembers(); }
  int NumNodes(void) const { return m_efg->NumNodes(); }
  int NumPlayerInfosets(void) const { return m_efg->NumPlayerInfosets(); }
  gbtGameNode GetRoot(void) const { return m_efg->GetRoot(); }
  gbtNumber MaxPayoff(void) const { return m_efg->MaxPayoff(); }
  gbtNumber MinPayoff(void) const { return m_efg->MinPayoff(); }
  bool IsPerfectRecall(void) const { return m_efg->IsPerfectRecall(); }

  void Dump(gbtOutput &) const;

  // The subsequent members were merged from a derived class.

  // Find the reachable nodes at an infoset
  gbtList<gbtGameNode> ReachableNodesInInfoset(const gbtGameInfoset &) const;

  bool HasActiveActionsAtActiveInfosets(void);
  bool HasActiveActionsAtActiveInfosetsAndNoOthers(void);

  bool InfosetIsActive(const gbtGameInfoset &) const;

  bool RemoveActionReturningDeletedInfosets(const gbtGameAction &,
					    gbtList<gbtGameInfoset> *);
  // Information
  bool InfosetIsActive(const int pl, const int iset) const;
  int  NumActiveNodes(const int pl, const int iset) const;
  int  NumActiveNodes(const gbtGameInfoset &) const;
  bool NodeIsActive(const int pl, const int iset, const int node) const;
  bool NodeIsActive(const gbtGameNode &) const;

  gbtList<gbtGameNode> ReachableNonterminalNodes() const;
};

gbtOutput &operator<<(gbtOutput &f, const gbtEfgSupport &);

#endif  // EFGSUPPORT_H