//
// FILE: nfgshow.h -- Declaration of normal form display class
//
// $Id$
//

#ifndef NFGSHOW_H
#define NFGSHOW_H

#include "wx/wx.h"
#include "wx/listctrl.h"
#include "wx/sashwin.h"
#include "wxmisc.h"

#include "nfgdraw.h"
#include "accels.h"

#include "gmisc.h"

#include "nfg.h"
#include "nfgiter.h"
#include "mixedsol.h"
#include "solnlist.h"

#include "efgnfgi.h"

const int idNFG_SOLUTION_LIST = 1900;

class NfgProfileList;
class NfgTable;
class dialogNfgSupportInspect;

typedef SolutionList<MixedSolution> MixedSolutionList;

class NfgPanel;
class NfgToolbar;

class NfgShow : public wxFrame, public EfgNfgInterface {
private:
  Nfg &m_nfg;

  NfgPanel *m_panel;
  NfgToolbar *m_toolbar;
  NfgTable *m_table;
  NfgProfileList *m_solutionTable;

  wxSashWindow *m_panelSashWindow, *m_solutionSashWindow;

  gList<NFSupport *> m_supports;
  NFSupport *m_currentSupport;
  int m_currentSolution;

  int m_rowPlayer, m_colPlayer;
  NormalDrawSettings m_drawSettings;
  gList<Accel> m_accelerators;
  gText m_fileName;


  void MakeMenus(void);
  void UpdateMenus(void);
  gText UniqueSupportName(void) const;
  void AdjustSizes(void);

  // process accelerators
  gArray<AccelEvent> MakeEventNames(void);

  // Menu event handlers
  void OnFileSave(wxCommandEvent &);
  void OnFileOutput(wxCommandEvent &);

  void OnEditLabel(wxCommandEvent &);
  void OnEditPlayers(wxCommandEvent &);
  void OnEditStrategies(wxCommandEvent &);
  void OnEditOutcomeNew(wxCommandEvent &);
  void OnEditOutcomeDelete(wxCommandEvent &);
  void OnEditOutcomeAttach(wxCommandEvent &);
  void OnEditOutcomeDetach(wxCommandEvent &);
  void OnEditOutcomePayoffs(wxCommandEvent &);

  void OnSupportUndominated(wxCommandEvent &);
  void OnSupportNew(wxCommandEvent &);
  void OnSupportEdit(wxCommandEvent &);
  void OnSupportDelete(wxCommandEvent &);
  void OnSupportSelectFromList(wxCommandEvent &);
  void OnSupportSelectPrevious(wxCommandEvent &);
  void OnSupportSelectNext(wxCommandEvent &);

  void OnSolveStandard(wxCommandEvent &);
  void OnSolveCustom(wxCommandEvent &);

  void OnViewSolutions(wxCommandEvent &);
  void OnViewDominance(wxCommandEvent &);
  void OnViewProbabilities(wxCommandEvent &);
  void OnViewValues(wxCommandEvent &);
  void OnViewOutcomes(wxCommandEvent &);
  void OnViewGameInfo(wxCommandEvent &);

  void OnPrefsDisplayColumns(wxCommandEvent &);
  void OnPrefsDisplayDecimals(wxCommandEvent &);
  void OnPrefsFontData(wxCommandEvent &);
  void OnPrefsFontLabels(wxCommandEvent &);
  void OnPrefsColors(wxCommandEvent &);
  void OnPrefsAccels(wxCommandEvent &);
  void OnPrefsSave(wxCommandEvent &);
  void OnPrefsLoad(wxCommandEvent &);

  void OnProfilesNew(wxCommandEvent &);
  void OnProfilesClone(wxCommandEvent &);
  void OnProfilesRename(wxCommandEvent &);
  void OnProfilesEdit(wxCommandEvent &);
  void OnProfilesDelete(wxCommandEvent &);

  // Other event handlers
  void OnCloseWindow(wxCloseEvent &);
  void OnSize(wxSizeEvent &);
  void OnSashDrag(wxSashEvent &);
  void OnSolutionSelected(wxListEvent &);

public:
  NfgShow(Nfg &N, EfgNfgInterface *efg = 0, wxFrame *pframe = 0);
  virtual ~NfgShow();

  gArray<int> GetProfile(void) const;

  NFSupport *CurrentSupport(void) const { return m_currentSupport; }
  int NumSupports(void) const { return m_supports.Length(); }
  
  void OutcomePayoffs(int st1, int st2, bool next = false);
  void UpdateProfile(gArray<int> &profile);
  void SetStrategy(int p_player, int p_strategy);
  void SetProfile(const gArray<int> &);
  void SetPlayers(int p_rowPlayer, int p_colPlayer);
  int GetRowPlayer(void) const { return m_rowPlayer; }
  int GetColPlayer(void) const { return m_colPlayer; }
  
  void ChangeSolution(int sol);

  int CurrentSolution(void) const { return m_currentSolution; }
  const gList<MixedSolution> &Solutions(void) const;

  void SolutionToExtensive(const MixedSolution &mp, bool set = false);

  void SetFileName(const gText &s);
  const gText &Filename(void) const { return m_fileName; }

  const Nfg &Game(void) const { return m_nfg; }  

  bool GameIsDirty(void) const { return m_nfg.IsDirty(); }

  int GetDecimals(void) const { return m_drawSettings.GetDecimals(); }
  void SetDecimals(int p_decimals) { m_drawSettings.SetDecimals(p_decimals); }
  bool OutcomeValues(void) const { return m_drawSettings.OutcomeValues(); }

  int CheckAccelerators(wxKeyEvent &ev);


  DECLARE_EVENT_TABLE()
};


#endif  // NFGSHOW_H



