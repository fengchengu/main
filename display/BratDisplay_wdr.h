//------------------------------------------------------------------------------
// Header generated by wxDesigner from file: BratDisplay.wdr
// Do not modify this file, all changes will be lost!
//------------------------------------------------------------------------------

#ifndef __WDR_BratDisplay_H__
#define __WDR_BratDisplay_H__

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma interface "BratDisplay_wdr.h"
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

extern wxSizer *glbSizerAnimation;
const int ID_PLAY = 10000;
const int ID_SLIDER = 10001;
const int ID_RESET = 10002;
const int ID_FRAMECTRL = 10003;
const int ID_LINE = 10004;
const int ID_LOOP = 10005;
const int ID_TEXT = 10006;
const int ID_SPEEDFIELD = 10007;
const int ID_ANIM_ZOOMTO = 10008;
extern wxSizer *glbSizerAnimationDescr;
const int ID_DESCR = 10009;
wxSizer *AnimationToolBar( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_VIEWCTRL = 10010;
const int ID_SAVEVIEW = 10011;
const int ID_CLEARVIEW = 10012;
const int ID_FULLVIEW = 10013;
wxSizer *WPlotViewStatePanel( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern wxSizer *global_wplotViewSizer;
const int ID_VIEW_NOTEBOOK = 10014;
wxSizer *WPlotView( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_ZOOM_LON1 = 10015;
const int ID_ZOOM_LAT1 = 10016;
const int ID_ZOOM_GO = 10017;
const int ID_ZOOM_LON2 = 10018;
const int ID_ZOOM_LAT2 = 10019;
wxSizer *WPlotViewZoomPanel( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_RADIUSCTRL = 10020;
const int ID_FACTORCTRL = 10021;
wxSizer *WPlotViewZPanel( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_CONTOUR_MIN = 10022;
const int ID_CONTOUR_MAX = 10023;
const int ID_CONTOUR_NUMBER = 10024;
const int ID_CONTOUR_LINE_COLOR = 10025;
const int ID_CONTOUR_LINE_WIDTH = 10026;
const int ID_CONTOUR_LABEL = 10027;
const int ID_CONTOUR_LABEL_NUMBER = 10028;
const int ID_CONTOUR_LABEL_COLOR = 10029;
const int ID_CONTOUR_LABEL_COLOR_SAME = 10030;
const int ID_CONTOUR_LABEL_SIZE = 10031;
const int ID_CONTOUR_LABEL_FORMAT = 10032;
const int ID_CONTOUR_CLOSE = 10033;
const int ID_CONTOUR_APPLY = 10034;
wxSizer *ContourPropertiesPanel( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_ZFXYMAINNOTEBOOK = 10035;
wxSizer *ZFXYMainNotebook( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_ZFXYPLOTPROP_TITLE = 10036;
const int ID_ZFXYFULLVIEW = 10037;
const int ID_ZFXYLAYERCHOICE = 10038;
const int ID_ZFXYSHOWSOLIDCOLOR = 10039;
const int ID_ZFXYEDITSOLIDCOLOR = 10040;
const int ID_ZFXYSHOWCONTOUR = 10041;
const int ID_ZFXYEDITCONTOUR = 10042;
const int ID_ZFXYNUMLABELS = 10043;
const int ID_ZFXYRANGEMIN = 10044;
const int ID_ZFXYRANGEMAX = 10045;
const int ID_ZFXYRESETRANGE = 10046;
const int ID_ZFXYAXES = 10047;
wxSizer *ZFXYDataProperties( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_ZFXYTITLEX = 10048;
const int ID_ZFXYLOGX = 10049;
const int ID_ZFXYNUMTICKSX = 10050;
const int ID_ZFXYBASEX = 10051;
const int ID_ZFXYDIGITSX = 10052;
const int ID_ZFXYRANGEXMIN = 10053;
const int ID_ZFXYRANGEXMAX = 10054;
const int ID_ZFXYRESETXRANGE = 10055;
wxSizer *ZFXYAxisXProperties( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_ZFXYTITLEY = 10056;
const int ID_ZFXYLOGY = 10057;
const int ID_ZFXYNUMTICKSY = 10058;
const int ID_ZFXYBASEY = 10059;
const int ID_ZFXYDIGITSY = 10060;
const int ID_ZFXYRANGEYMIN = 10061;
const int ID_ZFXYRANGEYMAX = 10062;
const int ID_ZFXYRESETYRANGE = 10063;
wxSizer *ZFXYAxisYProperties( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

// Declare menubar functions

const int ID_MENU = 10064;
wxMenuBar *BratDisplayMenuBarFunc();

const int ID_MENU_FILE = 10065;
const int ID_MENU_FILE_SAVE = 10066;
const int ID_MENU_FILE_CLOSE = 10067;
const int ID_MENU_VIEW = 10068;
const int ID_MENU_VIEW_PROPS = 10069;
const int ID_MENU_VIEW_COLORBAR = 10070;
const int ID_MENU_VIEW_SLIDER = 10071;
const int ID_MENU_VIEW_CLUTEDIT = 10072;
const int ID_MENU_VIEW_CONTOUR_PROPS = 10073;
wxMenuBar *WorldPlotFrameMenuBarFunc();

const int ID_MENU_FILE_OPEN = 10074;
const int ID_MENU_FILE_RECENT = 10075;
const int ID_MENU_EDIT = 10076;
const int ID_MENU_EDIT_CLEAR = 10077;
const int ID_MENU_EDIT_SETFACET = 10078;
const int ID_MENU_EDIT_LIN = 10079;
const int ID_MENU_EDIT_SQRT = 10080;
const int ID_MENU_EDIT_COS = 10081;
const int ID_MENU_MODE = 10082;
const int ID_MENU_MODE_STANDARD = 10083;
const int ID_MENU_MODE_GRADIENT = 10084;
const int ID_MENU_MODE_CUSTOM = 10085;
wxMenuBar *LUTFrameMenuBarFunc();

const int ID_MENU_FILE_EXPORT = 10086;
wxMenuBar *XYPlotFrameMenuBarFunc();

wxMenuBar *ZFXYPlotFrameMenuBarFunc();

wxMenuBar *ContourFrameMenuBarFunc();

// Declare toolbar functions

void MyToolBarFunc( wxToolBar *parent );

// Declare bitmap functions

#endif

// End of generated file