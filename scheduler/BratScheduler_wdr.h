//------------------------------------------------------------------------------
// Header generated by wxDesigner from file: BratScheduler.wdr
// Do not modify this file, all changes will be lost!
//------------------------------------------------------------------------------

#ifndef __WDR_BratScheduler_H__
#define __WDR_BratScheduler_H__

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma interface "BratScheduler_wdr.h"
#endif

// Include wxWidgets' headers

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/image.h>
#include <wx/statline.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/grid.h>
#include <wx/toolbar.h>
#include <wx/tglbtn.h>

// Declare window functions

const int ID_MAINNOTEBOOK = 10000;
wxSizer *MainNoteBook( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LOGPANEL = 10001;
wxSizer *LogPanel( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_PENDINGPANEL = 10002;
wxSizer *PendingPanel( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_PROCESSINGPANEL = 10003;
wxSizer *ProcessingPanel( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_ENDEDPANEL = 10004;
wxSizer *EndedPanel( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LIST_PENDING = 10005;
const int ID_REMOVE_PENDING = 10006;
const int ID_CLEAR_PENDING = 10007;
wxSizer *PendingListPanel( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LOG_MESS = 10008;
const int ID_LOG_CLEAR = 10009;
wxSizer *LogInfoPanel( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LIST_PROCESSING = 10010;
const int ID_KILL_PROCESSING = 10011;
wxSizer *ProcessingListPanel( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LIST_ENDED = 10012;
const int ID_REMOVE_ENDED = 10013;
const int ID_CLEAR_ENDED = 10014;
const int ID_SHOW_LOG = 10015;
wxSizer *EndedListPanel( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

// Declare menubar functions

const int ID_APPMENU = 10016;
const int ID_VIEW_XML_CONFIG = 10017;
const int ID_MENU = 10018;
const int ID_HELPMENU = 10019;
const int ID_HELP_USER_MANUEL = 10020;
wxMenuBar *MainMenuBarFunc();

// Declare toolbar functions

// Declare bitmap functions

wxBitmap BitmapsList( size_t index );

#endif

// End of generated file