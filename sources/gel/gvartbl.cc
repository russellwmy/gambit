//
// FILE: gvartbl.cc -- Implementation of variable lookup table
//
// $Id$
//

#include "gvartbl.h"

gelVariableTable::gelVariableTable(void)
{ }

void gelVariableTable::Define(const gText &name, const gelType type)
{
  if (!IsDefined(name))    {
    switch (type)    {
    case gelNUMBER:
      m_NumberNames.Append(name);
      m_NumberValues.Append(gNestedList<gNumber>());
      break;
    case gelBOOLEAN:
	    m_BooleanNames.Append(name);
      m_BooleanValues.Append(gNestedList<gTriState>());
      break;
    case gelTEXT:
      m_TextNames.Append(name);
      m_TextValues.Append(gNestedList<gText>());
      break;
    case gelEFG:
      m_EfgNames.Append(name);
      m_EfgValues.Append(gNestedList<Efg *>());
      break;
    case gelNODE:
      m_NodeNames.Append(name);
      m_NodeValues.Append(gNestedList<Node *>());
      break;
    case gelACTION:
      m_ActionNames.Append(name);
      m_ActionValues.Append(gNestedList<Action *>());
      break;
    case gelINFOSET:
      m_InfosetNames.Append(name);
      m_InfosetValues.Append(gNestedList<Infoset *>());
      break;
    case gelEFPLAYER:
      m_EFPlayerNames.Append(name);
      m_EFPlayerValues.Append(gNestedList<EFPlayer *>());
      break;
    case gelEFOUTCOME:
      m_EFOutcomeNames.Append(name);
      m_EFOutcomeValues.Append(gNestedList<EFOutcome *>());
      break;
    case gelNFG:
      m_NfgNames.Append(name);
      m_NfgValues.Append(gNestedList<Nfg *>());
      break;
    case gelSTRATEGY:
      m_StrategyNames.Append(name);
      m_StrategyValues.Append(gNestedList<Strategy *>());
      break;
    case gelNFPLAYER:
      m_NFPlayerNames.Append(name);
      m_NFPlayerValues.Append(gNestedList<NFPlayer *>());
      break;
    case gelNFOUTCOME:
      m_NFOutcomeNames.Append(name);
      m_NFOutcomeValues.Append(gNestedList<NFOutcome *>());
      break;
    default:
      assert(0);
    }
  }
}

bool gelVariableTable::IsDefined(const gText &name) const
{
  return m_NumberNames.Contains(name) || m_BooleanNames.Contains(name) ||
         m_TextNames.Contains(name) || m_EfgNames.Contains(name) ||
         m_NodeNames.Contains(name) || m_ActionNames.Contains(name) ||
         m_EFPlayerNames.Contains(name) || m_EFOutcomeNames.Contains(name) ||
         m_InfosetNames.Contains(name) || m_NfgNames.Contains(name) ||
         m_StrategyNames.Contains(name) || m_NFPlayerNames.Contains(name) ||
         m_NFOutcomeNames.Contains(name);
}

gelType gelVariableTable::Type(const gText &name) const
{
  if (m_NumberNames.Contains(name))
    return gelNUMBER;
  else if (m_BooleanNames.Contains(name))
    return gelBOOLEAN;
  else if (m_TextNames.Contains(name))
    return gelTEXT;
  else if (m_EfgNames.Contains(name))
    return gelEFG;
  else if (m_NodeNames.Contains(name))
    return gelNODE;
  else if (m_ActionNames.Contains(name))
    return gelACTION;
  else if (m_InfosetNames.Contains(name))
    return gelINFOSET;
  else if (m_EFPlayerNames.Contains(name))
    return gelEFPLAYER;
  else if (m_EFOutcomeNames.Contains(name))
    return gelEFOUTCOME;
  else if (m_NfgNames.Contains(name))
    return gelNFG;
  else if (m_StrategyNames.Contains(name))
    return gelSTRATEGY;
  else if (m_NFPlayerNames.Contains(name))
    return gelNFPLAYER;
  else if (m_NFOutcomeNames.Contains(name))
    return gelNFOUTCOME;

  assert(0);
  return gelBOOLEAN;
}

void gelVariableTable::Value(const gText &name,
                             gNestedList<gNumber> &value) const
{
  if (m_NumberNames.Contains(name))
    value = m_NumberValues[m_NumberNames.Find(name)];
  else
    assert(0);
}

void gelVariableTable::Value(const gText &name,
			                       gNestedList<gTriState> &value) const
{
  if (m_BooleanNames.Contains(name))
    value = m_BooleanValues[m_BooleanNames.Find(name)];
  else
    assert(0);
}

void gelVariableTable::Value(const gText &name,
			                       gNestedList<gText> &value) const
{
  if (m_TextNames.Contains(name))
    value = m_TextValues[m_TextNames.Find(name)];
  else
    assert(0);
}

void gelVariableTable::Value(const gText &name,
                             gNestedList<Efg *> &value) const
{
  if (m_EfgNames.Contains(name))
    value = m_EfgValues[m_EfgNames.Find(name)];
  else
    assert(0);
}

void gelVariableTable::Value(const gText &name,
                             gNestedList<Node *> &value) const
{
  if (m_NodeNames.Contains(name))
    value = m_NodeValues[m_NodeNames.Find(name)];
  else
    assert(0);
}

void gelVariableTable::Value(const gText &name,
                             gNestedList<Action *> &value) const
{
  if (m_ActionNames.Contains(name))
    value = m_ActionValues[m_ActionNames.Find(name)];
  else
    assert(0);
}

void gelVariableTable::Value(const gText &name,
                             gNestedList<Infoset *> &value) const
{
  if (m_InfosetNames.Contains(name))
    value = m_InfosetValues[m_InfosetNames.Find(name)];
  else
    assert(0);
}

void gelVariableTable::Value(const gText &name,
                             gNestedList<EFPlayer *> &value) const
{
  if (m_EFPlayerNames.Contains(name))
    value = m_EFPlayerValues[m_EFPlayerNames.Find(name)];
  else
    assert(0);
}

void gelVariableTable::Value(const gText &name,
                             gNestedList<EFOutcome *> &value) const
{
  if (m_EFOutcomeNames.Contains(name))
    value = m_EFOutcomeValues[m_EFOutcomeNames.Find(name)];
  else
    assert(0);
}

void gelVariableTable::Value(const gText &name,
                             gNestedList<Nfg *> &value) const
{
  if (m_NfgNames.Contains(name))
    value = m_NfgValues[m_NfgNames.Find(name)];
  else
    assert(0);
}

void gelVariableTable::Value(const gText &name,
                             gNestedList<Strategy *> &value) const
{
  if (m_StrategyNames.Contains(name))
    value = m_StrategyValues[m_StrategyNames.Find(name)];
  else
    assert(0);
}

void gelVariableTable::Value(const gText &name,
                             gNestedList<NFPlayer *> &value) const
{
  if (m_NFPlayerNames.Contains(name))
    value = m_NFPlayerValues[m_NFPlayerNames.Find(name)];
  else
    assert(0);
}

void gelVariableTable::Value(const gText &name,
                             gNestedList<NFOutcome *> &value) const
{
  if (m_NFOutcomeNames.Contains(name))
    value = m_NFOutcomeValues[m_NFOutcomeNames.Find(name)];
  else
    assert(0);
}

void gelVariableTable::SetValue(const gText &name,
			                          const gNestedList<gNumber> &value)
{
  assert(m_NumberNames.Contains(name));
  m_NumberValues[m_NumberNames.Find(name)] = value;
}

void gelVariableTable::SetValue(const gText &name,
			                          const gNestedList<gTriState> &value)
{
  assert(m_BooleanNames.Contains(name));
  m_BooleanValues[m_BooleanNames.Find(name)] = value;
}

void gelVariableTable::SetValue(const gText &name,
			                          const gNestedList<gText> &value)
{
  assert(m_TextNames.Contains(name));
  m_TextValues[m_TextNames.Find(name)] = value;
}

void gelVariableTable::SetValue(const gText &name,
                                const gNestedList<Efg *> &value)
{
  assert(m_EfgNames.Contains(name));
  m_EfgValues[m_EfgNames.Find(name)] = value;
}

void gelVariableTable::SetValue(const gText &name,
                                const gNestedList<Node *> &value)
{
  assert(m_NodeNames.Contains(name));
  m_NodeValues[m_NodeNames.Find(name)] = value;
}

void gelVariableTable::SetValue(const gText &name,
                                const gNestedList<Action *> &value)
{
  assert(m_ActionNames.Contains(name));
  m_ActionValues[m_ActionNames.Find(name)] = value;
}

void gelVariableTable::SetValue(const gText &name,
                                const gNestedList<Infoset *> &value)
{
  assert(m_InfosetNames.Contains(name));
  m_InfosetValues[m_InfosetNames.Find(name)] = value;
}

void gelVariableTable::SetValue(const gText &name,
                                const gNestedList<EFPlayer *> &value)
{
  assert(m_EFPlayerNames.Contains(name));
  m_EFPlayerValues[m_EFPlayerNames.Find(name)] = value;
}

void gelVariableTable::SetValue(const gText &name,
                                const gNestedList<EFOutcome *> &value)
{
  assert(m_EFOutcomeNames.Contains(name));
  m_EFOutcomeValues[m_EFOutcomeNames.Find(name)] = value;
}

void gelVariableTable::SetValue(const gText &name,
                                const gNestedList<Nfg *> &value)
{
  assert(m_NfgNames.Contains(name));
  m_NfgValues[m_NfgNames.Find(name)] = value;
}

void gelVariableTable::SetValue(const gText &name,
                                const gNestedList<Strategy *> &value)
{
  assert(m_StrategyNames.Contains(name));
  m_StrategyValues[m_StrategyNames.Find(name)] = value;
}

void gelVariableTable::SetValue(const gText &name,
                                const gNestedList<NFPlayer *> &value)
{
  assert(m_NFPlayerNames.Contains(name));
  m_NFPlayerValues[m_NFPlayerNames.Find(name)] = value;
}

void gelVariableTable::SetValue(const gText &name,
                                const gNestedList<NFOutcome *> &value)
{
  assert(m_NFOutcomeNames.Contains(name));
  m_NFOutcomeValues[m_NFOutcomeNames.Find(name)] = value;
}


#include "glist.imp"

template class gList<gText>;
template class gList<gNumber>;
template class gList<gTriState>;

template class gList< gNestedList<gText> >;
template class gList< gNestedList<gNumber> >;
template class gList< gNestedList<gTriState> >;

template gOutput &operator<<( gOutput&, const gList<gText>& );
template gOutput &operator<<( gOutput&, const gList<gNumber>& );
template gOutput &operator<<( gOutput&, const gList<gTriState>& );
