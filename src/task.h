////////////////////////////////////////////////////////////////////////////////
// task - a command line task list manager.
//
// Copyright 2006 - 2009, Paul Beckingham.
// All rights reserved.
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, write to the
//
//     Free Software Foundation, Inc.,
//     51 Franklin Street, Fifth Floor,
//     Boston, MA
//     02110-1301
//     USA
//
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <map>
#include <sys/types.h>
#include "Config.h"
#include "Table.h"
#include "Date.h"
#include "color.h"
#include "TDB.h"
#include "T.h"
#include "../auto.h"

#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif

#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

#define foreach(i, c)                                              \
for (typeof (c) *foreach_p = & (c);                                \
     foreach_p;                                                    \
     foreach_p = 0)                                                \
  for (typeof (foreach_p->begin()) i = foreach_p->begin();         \
       i != foreach_p->end();                                      \
       ++i)

// parse.cpp
void parse (std::vector <std::string>&, std::string&, T&, Config&);
bool validPriority (const std::string&);
bool validDate (std::string&, Config&);
void loadCustomReports (Config&);
bool isCustomReport (const std::string&);
void allCustomReports (std::vector <std::string>&);

// task.cpp
void gatherNextTasks (const TDB&, T&, Config&, std::vector <T>&, std::vector <int>&);
void nag (TDB&, T&, Config&);
int getDueState (const std::string&);
void handleRecurrence (TDB&, std::vector <T>&);
bool generateDueDates (T&, std::vector <Date>&);
Date getNextRecurrence (Date&, std::string&);
void updateRecurrenceMask (TDB&, std::vector <T>&, T&);
void onChangeCallback ();
std::string runTaskCommand (int, char**, TDB&, Config&, bool gc = true, bool shadow = true);
std::string runTaskCommand (std::vector <std::string>&, TDB&, Config&, bool gc = false, bool shadow = false);

// command.cpp
void handleAdd (TDB&, T&, Config&);
void handleExport (TDB&, T&, Config&);
void handleDone (TDB&, T&, Config&);
void handleModify (TDB&, T&, Config&);
std::string handleProjects (TDB&, T&, Config&);
std::string handleTags (TDB&, T&, Config&);
std::string handleUndelete (TDB&, T&, Config&);
std::string handleVersion (Config&);
std::string handleDelete (TDB&, T&, Config&);
std::string handleStart (TDB&, T&, Config&);
std::string handleStop (TDB&, T&, Config&);
std::string handleUndo (TDB&, T&, Config&);
std::string handleColor (Config&);

// report.cpp
void filter (std::vector<T>&, T&);
std::string handleInfo (TDB&, T&, Config&);
std::string handleCompleted (TDB&, T&, Config&);
std::string handleReportSummary (TDB&, T&, Config&);
std::string handleReportNext (TDB&, T&, Config&);
std::string handleReportHistory (TDB&, T&, Config&);
std::string handleReportGHistory (TDB&, T&, Config&);
std::string handleReportCalendar (TDB&, T&, Config&);
std::string handleReportActive (TDB&, T&, Config&);
std::string handleReportOverdue (TDB&, T&, Config&);
std::string handleReportStats (TDB&, T&, Config&);

std::string handleCustomReport (TDB&, T&, Config&, const std::string&);
void validReportColumns (const std::vector <std::string>&);
void validSortColumns (const std::vector <std::string>&, const std::vector <std::string>&);

// util.cpp
bool confirm (const std::string&);
void wrapText (std::vector <std::string>&, const std::string&, const int);
std::string trimLeft (const std::string& in, const std::string& t = " ");
std::string trimRight (const std::string& in, const std::string& t = " ");
std::string trim (const std::string& in, const std::string& t = " ");
void extractParagraphs (const std::string&, std::vector<std::string>&);
void extractLine (std::string&, std::string&, int);
void split (std::vector<std::string>&, const std::string&, const char);
void split (std::vector<std::string>&, const std::string&, const std::string&);
void join (std::string&, const std::string&, const std::vector<std::string>&);
std::string commify (const std::string&);
std::string lowerCase (const std::string&);
std::string upperCase (const std::string&);
void delay (float);
int autoComplete (const std::string&, const std::vector<std::string>&, std::vector<std::string>&);
void formatTimeDeltaDays (std::string&, time_t);
std::string formatSeconds (time_t);
const std::string uuid ();
const char* optionalBlankLine (Config&);
int convertDuration (const std::string&);
std::string expandPath (const std::string&);

#ifdef SOLARIS
  #define LOCK_SH 1
  #define LOCK_EX 2
  #define LOCK_NB 4
  #define LOCK_UN 8

  int flock (int, int);
#endif

// rules.cpp
void initializeColorRules (Config&);
void autoColorize (T&, Text::color&, Text::color&, Config&);

////////////////////////////////////////////////////////////////////////////////
