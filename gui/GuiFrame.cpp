/*
* This file is part of BRAT 
*
* BRAT is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* BRAT is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "new-gui/brat/stdafx.h"

// For compilers that support precompilation
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

//#include "wx/mimetype.h"

// Include private headers
#include "BratGui.h"
#include "GuiFrame.h"
#include "DirTraverser.h"
#include "WorkspaceDlg.h"

#include "new-gui/Common/ConfigurationKeywords.h"


// WDR: class implementations

//------------------------------------------------------------------------------
// CGuiFrame
//------------------------------------------------------------------------------

// WDR: event table for CGuiFrame

BEGIN_EVENT_TABLE(CGuiFrame,wxFrame)
    EVT_MENU(wxID_ABOUT, CGuiFrame::OnAbout)
    EVT_MENU(wxID_EXIT, CGuiFrame::OnQuit)
    EVT_CLOSE(CGuiFrame::OnCloseWindow)
//    EVT_SIZE(CGuiFrame::OnSize)
//    EVT_UPDATE_UI(-1,CGuiFrame::OnUpdateUI)
    EVT_MENU( ID_WSNEW, CGuiFrame::OnNewWorkspace )
    EVT_MENU( ID_WSOPEN, CGuiFrame::OnOpenWorkspace )
    EVT_MENU( ID_WSIMPORT, CGuiFrame::OnImportWorkspace )
    EVT_MENU( ID_WSRENAME, CGuiFrame::OnRenameWorkspace )
    EVT_MENU( ID_WSDELETE, CGuiFrame::OnDeleteWorkspace )
    EVT_UPDATE_UI( ID_WSRENAME, CGuiFrame::OnRenameWorkspaceUpdateUI )
    EVT_UPDATE_UI( ID_WSDELETE, CGuiFrame::OnDeleteWorkspaceUpdateUI )
    EVT_MENU( ID_WSSAVE, CGuiFrame::OnSaveWorkspace )
    EVT_UPDATE_UI( ID_WSSAVE, CGuiFrame::OnSaveWorkspaceUpdateUI )
    EVT_UPDATE_UI( ID_WSIMPORT, CGuiFrame::OnImportWorkspaceUpdateUI )
    EVT_MENU( ID_DSNEW, CGuiFrame::OnNewDataset )
    EVT_UPDATE_UI( ID_DSNEW, CGuiFrame::OnNewDatasetUpdateUI )
    EVT_MENU( ID_DSDELETE, CGuiFrame::OnDeleteDataset )
    EVT_UPDATE_UI( ID_DSDELETE, CGuiFrame::OnDeleteDatasetUpdateUI )
    EVT_MENU( ID_OPNEW, CGuiFrame::OnNewOperation )
    EVT_UPDATE_UI( ID_OPNEW, CGuiFrame::OnNewOperationUpdateUI )
    EVT_MENU( ID_OPDELETE, CGuiFrame::OnDeleteOperation )
    EVT_UPDATE_UI( ID_OPDELETE, CGuiFrame::OnDeleteOperationUpdateUI )
    EVT_MENU_RANGE( wxID_FILE1, wxID_FILE9, CGuiFrame::OnFileHistory )
    EVT_MENU( ID_VINEW, CGuiFrame::OnNewView )
    EVT_UPDATE_UI( ID_VINEW, CGuiFrame::OnNewViewUpdateUI )
    EVT_MENU( ID_VIDELETE, CGuiFrame::OnDeleteView )
    EVT_UPDATE_UI( ID_VIDELETE, CGuiFrame::OnDeleteViewUpdateUI )
    EVT_MENU( ID_OPDUPLICATE, CGuiFrame::OnDuplicateOperation )
    EVT_UPDATE_UI( ID_OPDUPLICATE, CGuiFrame::OnDuplicateOperationUpdateUI )
    EVT_MENU( ID_HELP_USER_MANUEL, CGuiFrame::OnUserManual )
    EVT_MENU( ID_FIELDSSORTMENU, CGuiFrame::OnSortFieldCtrl )
    EVT_MENU( ID_FIELDSSORTREVMENU, CGuiFrame::OnSortRevFieldCtrl )
    EVT_MENU( ID_OPSORTMENU, CGuiFrame::OnSortOpCtrl )
    EVT_MENU( ID_OPSORTREVMENU, CGuiFrame::OnSortRevOpCtrl )
    EVT_MENU( ID_DISPSORTMENU, CGuiFrame::OnSortDispTreeCtrl )
    EVT_MENU( ID_DISPSORTREVMENU, CGuiFrame::OnSortRevDispTreeCtrl )
    EVT_MENU( ID_ASXMENU, CGuiFrame::OnSetAsX )
    EVT_MENU( ID_ASYMENU, CGuiFrame::OnSetAsY )
    EVT_MENU( ID_ASDATAMENU, CGuiFrame::OnSetAsData )
    EVT_MENU( ID_ASSELECTMENU, CGuiFrame::OnInsertIntoSelect )
    EVT_MENU( ID_INSERTEXPRMENU, CGuiFrame::OnInsertEmptyExpression )
    EVT_MENU( ID_INSERTFIELDMENU, CGuiFrame::OnInsertField )
    EVT_MENU( ID_INSERTFCTMENU, CGuiFrame::OnInsertFunction )
    EVT_MENU( ID_INSERTFORMULAMENU, CGuiFrame::OnInsertFormula )
    EVT_MENU( ID_SAVEASFORMULAMENU, CGuiFrame::OnSaveAsFormula )
    EVT_MENU( ID_DELETEEXPRMENU, CGuiFrame::OnDeleteExpression )
    EVT_MENU( ID_DISPADDTOSEL, CGuiFrame::OnAddToSelected )
    EVT_MENU( ID_DISPEXPANDMENU, CGuiFrame::OnExpandAvailabledispDataTree )
    EVT_MENU( ID_RENAMEEXPRMENU, CGuiFrame::OnRenameExpression )
    EVT_MENU( ID_DISPCOLLAPSEMENU, CGuiFrame::OnCollapseAvailabledispDataTree )
    EVT_MENU( ID_FIELD_ATTR_CHANGE_UNIT, CGuiFrame::OnFieldAttrChangeUnit )
END_EVENT_TABLE()
//----------------------------------------

CGuiFrame::CGuiFrame( wxWindow *parent, wxWindowID id, const wxString &title,
    const wxPoint &position, const wxSize& size, long style ) :
    wxFrame( parent, id, title, position, size, style )
{
  m_menuBar = nullptr;
  m_menuWorkspace = nullptr;
  m_menuHistory = nullptr;

  m_menuBarPopup = nullptr;
  m_menuFieldsTreeCtrl = nullptr;
  m_menuOperationTreeCtrl = nullptr;
  m_menuDisplayTreeCtrl = nullptr;

  CreateMainMenuBar();
  
  CreatePopupMenuBar();
  
  //CreateMainToolBar();
  
  CreateStatusBar(1);
    
  m_guiPanel = new CGuiPanel(this, -1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER );
  wxBoxSizer * sizer = new wxBoxSizer(wxVERTICAL);

  sizer->Add(m_guiPanel, 1, wxEXPAND);
  SetSizer(sizer);

  // insert main window here
  //MainFrameContentFunc(this);

  SetMinSize(GetBestSize());
  SetSize(GetBestSize());

  try
  {
    if (!wxGetApp().GetIconFile().IsEmpty())
    {
      SetIcon(wxIcon(wxGetApp().GetIconFile(), ::wxGetApp().GetIconType()));
    }
    else
    {
      ::wxMessageBox(wxString::Format("WARNING: Unable to find Brat icon file %s",
                                      ::wxGetApp().GetIconFileName().c_str())
                     , "BRAT WARNING");
    }
  }
  catch(...)
  {
    // Do nothing
  }

}

//----------------------------------------
CGuiFrame::~CGuiFrame()
{
}

//----------------------------------------
void CGuiFrame::CreateMainMenuBar()
{
  m_menuBar = MainMenuBarFunc();

  SetMenuBar( m_menuBar );

  m_menuBar->Enable(ID_MENU_FILE_RECENT, false);

  wxMenuItem* menuItemRecent = m_menuBar->FindItem(ID_MENU_FILE_RECENT, &m_menuWorkspace);
  if (menuItemRecent != nullptr)
  {
    m_menuHistory = menuItemRecent->GetSubMenu();
  }

  if (m_menuHistory != nullptr)
  {
    m_wksHistory.UseMenu(m_menuHistory);
    ConfigToFileHistory();

  }



}
//----------------------------------------
void CGuiFrame::CreatePopupMenuBar()
{
	//contexMenusCreated note:
	//
	//	Quick hack caused by upgrade to wxWidgets 3.0.2, which does not allow windows to invoke 
	//	context menus if attached to menu bars, as seems to be the old technique of wxDesigner,
	//	or of the original BRAT authors. Note that wxDesigner is no longer available.
	//	If the menus remain attached to the menu bar, events are not processed.

	static bool contexMenusCreated = false;

	if ( contexMenusCreated )
	{
		assert( false );
		return;
	}

	contexMenusCreated = true;

	m_menuBarPopup = PopupMenuFunc();
	m_menuFieldsTreeCtrl = m_menuBarPopup->GetMenu( 0 );

	m_menuOperationTreeCtrl = m_menuBarPopup->GetMenu( 1 );

	m_menuDisplayTreeCtrl = m_menuBarPopup->GetMenu( 2 );

	m_menuBarPopup->Remove( 2 );
	m_menuBarPopup->Remove( 1 );
	m_menuBarPopup->Remove( 0 );
}

//----------------------------------------
void CGuiFrame::CreateMainToolBar()
{
    wxToolBar *tb = CreateToolBar( wxTB_HORIZONTAL|wxNO_BORDER /* |wxTB_FLAT */ );
    
    MainToolBarFunc( tb );
}
//----------------------------------------
void CGuiFrame::ConfigToFileHistory()
{
	std::vector<std::string> v;
	wxGetApp().LoadFileHistory( v );
	for ( auto &valueString : v )
		AddWorkspaceToHistory(valueString);

  //if (wxGetApp().GetConfig() == nullptr)
  //{
  //  return;
  //}
  //
  //wxFileConfig* config = wxGetApp().GetConfig();

  //config->SetPath("/" + GROUP_WKS_RECENT);

  //long maxEntries = config->GetNumberOfEntries();
  //bool bOk = false;
  //wxString entry;
  //wxString valueString;
  //long i = 0;

  //do
  //{
  //  bOk = config->GetNextEntry(entry, i);
  //  if (bOk)
  //  {
  //    valueString = config->Read(entry);
  //    AddWorkspaceToHistory(valueString);
  //  }
  //}
  //while (bOk);

  m_menuBar->Enable(ID_MENU_FILE_RECENT, v.size() > 0);

}
//----------------------------------------
void CGuiFrame::AddWorkspaceToHistory(const wxString& name)
{
  m_menuBar->Enable(ID_MENU_FILE_RECENT, true);
  m_wksHistory.AddFileToHistory(name);
}

//----------------------------------------
void CGuiFrame::RemoveWorkspaceFromHistory(const wxString& name)
{
  for (uint32_t i = 0 ; i < m_wksHistory.GetCount() ; i++)
  {
    if (m_wksHistory.GetHistoryFile(i).CmpNoCase(name) == 0)
    {
      m_wksHistory.RemoveFileFromHistory(i);
      break;
    }
  }
}

//----------------------------------------
void CGuiFrame::LoadFromWorkspaceHistory(int32_t fileNum)
{
  bool bOk = OpenWorkspace(m_wksHistory.GetHistoryFile(fileNum));
  if (bOk == false)
  {
    m_wksHistory.RemoveFileFromHistory(fileNum);
  }
}
//----------------------------------------
void CGuiFrame::FileHistoryToConfig()
{
	if ( !m_menuBar->IsEnabled( ID_MENU_FILE_RECENT ) )
		return;

	std::vector<std::string> v;
	for (uint32_t i =0 ; i < m_wksHistory.GetCount() ; i++)
	{
	  wxFileName fileName;
	  fileName.AssignDir(m_wksHistory.GetHistoryFile(i));
	  fileName.Normalize();

	  v.push_back( fileName.GetPath().ToStdString() );
	}

	wxGetApp().SaveFileHistory( v );

	//if (wxGetApp().GetConfig() == nullptr)
	//{
	//  return;
	//}
	//
	//wxFileConfig* config = wxGetApp().GetConfig();

	//config->SetPath("/");
	//if (m_menuBar->IsEnabled(ID_MENU_FILE_RECENT) == false)
	//{
	//  return;
	//}

	//for (uint32_t i =0 ; i < m_wksHistory.GetCount() ; i++)
	//{
	//  wxFileName fileName;
	//  fileName.AssignDir(m_wksHistory.GetHistoryFile(i));
	//  fileName.Normalize();

	//  config->Write(brathlFmtEntryRecentWksMacro(i), fileName.GetPath() );
	//}
	//
	//config->Flush();

}
//----------------------------------------
void CGuiFrame::OnFileHistory( wxCommandEvent &event )
{
  int32_t fileNum = event.GetId() - wxID_FILE1;
  LoadFromWorkspaceHistory(fileNum);
    
}

//----------------------------------------
bool CGuiFrame::SaveWorkspace()
{
	bool bOk = false;

	std::string errorMsg;
	wxGetApp().m_tree.SaveConfig( errorMsg, wxGetApp().GetCurrentWorkspaceOperation(), wxGetApp().GetCurrentWorkspaceDisplay() );		// TODO: save failed but life goes on???
	if ( !errorMsg.empty() )
		wxMessageBox( errorMsg, "Warning", wxOK | wxCENTRE | wxICON_INFORMATION );

	CWorkspace* wks = wxGetApp().GetCurrentWorkspace();

	if ( wks != nullptr )
		AddWorkspaceToHistory( wks->GetPath() );

	return true;
}

CWorkspace* CGuiFrame::LoadTree( const std::string& path )
{
	std::string errorMsg;
	CWorkspace *root = wxGetApp().m_tree.LoadReset( path , errorMsg );		//CreateTree( root, m_tree );
	if ( !errorMsg.empty() )
		wxMessageBox( errorMsg, "Warning", wxOK | wxCENTRE | wxICON_INFORMATION );

	return root;
}
CWorkspace* CGuiFrame::CreateTree( const std::string& name, const std::string& path )
{
	std::string errorMsg;
	CWorkspace *root = wxGetApp().m_tree.CreateReset( name, path , errorMsg );		//CreateTree( root, m_tree );
	if ( !errorMsg.empty() )
		wxMessageBox( errorMsg, "Warning", wxOK | wxCENTRE | wxICON_INFORMATION );

	return root;
}

bool CGuiFrame::LoadWorkspace( const std::string& path )
{
	CWorkspace *wks = LoadTree( path );
	CWorkspace *failed_wks = nullptr;
	std::string errorMsg;
	bool bOk = wxGetApp().m_tree.LoadConfig( 
		failed_wks, wxGetApp().GetCurrentWorkspaceDataset(), wxGetApp().GetCurrentWorkspaceOperation(), wxGetApp().GetCurrentWorkspaceDisplay(), errorMsg );
	if ( !bOk )
	{
		wxMessageBox( errorMsg + "\nUnable to load workspace '" + ( failed_wks ? failed_wks->GetName() : "" ) + "'.",
			"Warning",
			wxOK | wxICON_EXCLAMATION );

		DoEmptyWorkspace();
		return false;
	}

	ResetWorkspace();

	LoadWorkspace();

	EnableCtrlWorkspace();

	if ( wks != nullptr )
		AddWorkspaceToHistory( wks->GetPath() );

	SetTitle();

	return true;
}

//----------------------------------------
// this called a boolean function that always returned true
//
void CGuiFrame::OnNewWorkspace( wxCommandEvent &event )
{
	if ( AskToSave() )
		return;

	CWorkspaceDlg wksDlg( this, -1, "Create a new workspace...", CWorkspaceDlg::wksNew, wxGetApp().GetCurrentWorkspace(), "." );
	int32_t result = wksDlg.ShowModal();
	if ( result != wxID_OK )
		return;

	wxFileName path;
	path.Assign( wksDlg.m_currentDir );
	path.AppendDir( wksDlg.m_name );

	ResetWorkspace();

	CWorkspace* wks = CreateTree( wksDlg.m_name.ToStdString(), path.GetFullPath().ToStdString() );

	std::string errorMsg;
	wxGetApp().m_tree.SaveConfig(errorMsg, wxGetApp().GetCurrentWorkspaceOperation(), wxGetApp().GetCurrentWorkspaceDisplay() );
	if ( !errorMsg.empty() )
		wxMessageBox( errorMsg, "Warning", wxOK | wxCENTRE | wxICON_INFORMATION );

	EnableCtrlWorkspace();

	if ( wks != nullptr )
		AddWorkspaceToHistory( wks->GetPath() );

	SetTitle();
}

//----------------------------------------
bool CGuiFrame::OpenWorkspace( const wxString& path, bool askUser )		//askUser = false 
{
	if ( !askUser && path.IsEmpty() )
	{
		DoEmptyWorkspace();
		return true;
	}

	if ( AskToSave() )
		return true;

	CWorkspaceDlg wksDlg( this, -1, "Open a workspace...", CWorkspaceDlg::wksOpen, wxGetApp().GetCurrentWorkspace(), path );
	if ( askUser )
	{
		if ( wksDlg.ShowModal() != wxID_OK )
			return true;
	}
	else 
	{
		wksDlg.GetWksLoc()->SetValue( path );
		if ( !wksDlg.ValidateData() )
			return false;
	}

	return LoadWorkspace( wksDlg.GetWksLoc()->GetValue().ToStdString() );
}
void CGuiFrame::OnOpenWorkspace( wxCommandEvent &event )
{
	OpenWorkspace( ".", true );
}

//----------------------------------------
void CGuiFrame::LoadWorkspace()
{
  m_guiPanel->GetDatasetPanel()->LoadDataset();
  //m_guiPanel->GetOperationPanel()->LoadOperation();
  m_guiPanel->GetOperationPanel()->LoadOperation();
  //m_guiPanel->GetDisplayPanel()->LoadDisplay();
  m_guiPanel->GetDisplayPanel()->LoadDisplay();

}
//----------------------------------------
void CGuiFrame::EnableCtrlWorkspace()
{
  m_guiPanel->GetDatasetPanel()->EnableCtrl();
  //m_guiPanel->GetOperationPanel()->EnableCtrl();
  m_guiPanel->GetOperationPanel()->EnableCtrl();
  //m_guiPanel->GetDisplayPanel()->EnableCtrl();
  m_guiPanel->GetDisplayPanel()->EnableCtrl();

}
//----------------------------------------
void CGuiFrame::ResetWorkspace()
{
  m_guiPanel->GetDatasetPanel()->Reset();
  //m_guiPanel->GetOperationPanel()->Reset();
  m_guiPanel->GetOperationPanel()->Reset();
  //m_guiPanel->GetDisplayPanel()->Reset();
  m_guiPanel->GetDisplayPanel()->Reset();

  m_guiPanel->GetDatasetPanel()->ClearAll();
  //m_guiPanel->GetOperationPanel()->ClearAll();
  m_guiPanel->GetOperationPanel()->ClearAll();
  //m_guiPanel->GetDisplayPanel()->ClearAll();
  m_guiPanel->GetDisplayPanel()->ClearAll();

}
//----------------------------------------
void CGuiFrame::DoEmptyWorkspace()
{
  wxGetApp().m_tree.Clear();

  ResetWorkspace();
  
  EnableCtrlWorkspace();

  SetTitle();
    
}
//----------------------------------------
bool CGuiFrame::ImportWorkspace()
{
	bool bOk = false;
	if ( wxGetApp().GetCurrentWorkspace() == nullptr )
		return false;

	wxGetApp().m_treeImport.Clear();

	wxString wksPath = wxGetApp().GetCurrentWorkspace()->GetPath();
	wxFileName currentWksPath;
	currentWksPath.AssignDir( wksPath );
	currentWksPath.MakeAbsolute();

	SaveWorkspace();

	CWorkspaceDlg wksDlg( this, -1, "Import a workspace...", CWorkspaceDlg::wksImport, wxGetApp().GetCurrentWorkspace(), "." );

	wxGetApp().m_tree.GetImportBitSet()->m_bitSet.reset();

	wxString wksPathToImport;
	wxArrayString formulasToImport;

	while ( true )
	{
		int result = wksDlg.ShowModal();
		if ( result != wxID_OK )
		{
			bOk = false;
			break;
		}

		wksPathToImport = wksDlg.GetWksLoc()->GetValue();
		wxFileName importWksPath;
		importWksPath.AssignDir( wksPathToImport );
		importWksPath.MakeAbsolute();

		if ( currentWksPath.GetPath().CmpNoCase( importWksPath.GetPath() ) == 0 )
		{
			wxMessageBox( "You can't import a workspace from itself.",
				"Warning",
				wxOK | wxCENTRE | wxICON_EXCLAMATION );
			bOk = false;
		}
		else
		{
			bOk = true;
			break;
		}
	}

	if ( !bOk )
		return bOk;

	wxGetApp().m_tree.GetImportBitSet()->m_bitSet.set( IMPORT_DATASET_INDEX, wksDlg.GetImportDataset()->GetValue() );
	wxGetApp().m_tree.GetImportBitSet()->m_bitSet.set( IMPORT_FORMULA_INDEX, wksDlg.GetImportFormulas()->GetValue() );
	wxGetApp().m_tree.GetImportBitSet()->m_bitSet.set( IMPORT_OPERATION_INDEX, wksDlg.GetImportOperations()->GetValue() );
	wxGetApp().m_tree.GetImportBitSet()->m_bitSet.set( IMPORT_DISPLAY_INDEX, wksDlg.GetImportViews()->GetValue() );

	wxGetApp().m_treeImport.SetCtrlDatasetFiles( wxGetApp().m_tree.GetImportBitSet()->m_bitSet.test( IMPORT_DATASET_INDEX ) );

	std::string errorMsg;	
	//CWorkspace* wks = wxGetApp().m_treeImport.Reset( wksDlg.GetWksName()->GetValue().ToStdString(), wksPathToImport.ToStdString(), errorMsg , false );	//wxGetApp().CreateTree( wks, wxGetApp().m_treeImport );
	CWorkspace* wks = wxGetApp().m_treeImport.LoadReset( wksPathToImport.ToStdString(), errorMsg );	//wxGetApp().CreateTree( wks, wxGetApp().m_treeImport );
	if ( !errorMsg.empty() )
		wxMessageBox( errorMsg, "Warning", wxOK | wxCENTRE | wxICON_INFORMATION );	

	//-----------------------------------------
	wxGetApp().SetCurrentTree( &( wxGetApp().m_treeImport ) );
	//-----------------------------------------

	CWorkspace *failed_wks = nullptr;
	bOk = wxGetApp().m_treeImport.LoadConfig( failed_wks, wxGetApp().GetCurrentWorkspaceDataset(), wxGetApp().GetCurrentWorkspaceOperation(), wxGetApp().GetCurrentWorkspaceDisplay(), errorMsg );
	if ( !bOk )
	{
		wxMessageBox( errorMsg + "\nUnable to load workspace '" + ( failed_wks ? failed_wks->GetName() : "" ) + "'.",
			"Warning",
			wxOK | wxICON_EXCLAMATION );

		wxGetApp().m_treeImport.Clear();
		wxGetApp().m_tree.Clear();

		bool oldValue = wxGetApp().m_tree.GetCtrlDatasetFiles();
		wxGetApp().m_tree.SetCtrlDatasetFiles( false );

		OpenWorkspace( wksPath );

		wxGetApp().m_tree.SetCtrlDatasetFiles( oldValue );

		return bOk;
	}

	CWorkspaceOperation* wksOpImport = wxGetApp().GetCurrentWorkspaceOperation();

	//-----------------------------------------
	wxGetApp().SetCurrentTree( &( wxGetApp().m_tree ) );
	//-----------------------------------------

	// Retrieve formula to Import
	CWorkspaceFormula* wksFormula = wxGetApp().GetCurrentWorkspaceFormula();

	wksDlg.GetCheckedFormulas( wksFormula->GetFormulasToImport() );


	std::string missingKey;
	errorMsg = "";
	CWorkspaceDisplay* wksd = wxGetApp().GetCurrentWorkspaceDisplay();
	bOk = wxGetApp().m_tree.GetRootData() && wxGetApp().m_tree.Import( &( wxGetApp().m_treeImport ), wksd, wksOpImport, missingKey, errorMsg );
	if ( bOk )
	{
		SaveWorkspace();

		CWorkspaceOperation* wksOp = wxGetApp().GetCurrentWorkspaceOperation();
		if ( ( wksOp != nullptr ) && ( wksOpImport != nullptr ) )
		{
			CDirTraverserCopyFile traverserCopyFile( wksOp->GetPath(), "nc" );
			//path name given to wxDir is locked until wxDir object is deleted
			wxDir dir;

			dir.Open( wksOpImport->GetPath() );
			dir.Traverse( traverserCopyFile );
		}

	}
	else	//femm: original code didn't return on failure; so this else (created to strip out wxMessageBoxes from CTreeWorkspace) won't return also
	{
		if ( !errorMsg.empty() )
			wxMessageBox( errorMsg, "Error", wxOK | wxCENTRE | wxICON_ERROR );

		if ( wxGetApp().m_tree.GetRootData() == nullptr )
		{
			wxMessageBox( "Unable to import workspace. No root found",
				"Warning",
				wxOK | wxCENTRE | wxICON_EXCLAMATION );
		}
		else 
		{
			wxMessageBox( 
				"Unable to import workspace. Workspace '"
				+ wxGetApp().m_tree.GetRootData()->GetName()
				+ "' doesn't contain '"
				+ missingKey
				+ "'",
				"Warning",
				wxOK | wxCENTRE | wxICON_EXCLAMATION );
		}
	}

	wxGetApp().m_treeImport.Clear();
	wxGetApp().m_tree.Clear();

	bool oldValue = wxGetApp().m_tree.GetCtrlDatasetFiles();
	wxGetApp().m_tree.SetCtrlDatasetFiles( false );

	bOk = OpenWorkspace( wksPath );

	wxGetApp().m_tree.SetCtrlDatasetFiles( oldValue );

	return bOk;
}
//----------------------------------------
bool CGuiFrame::RenameWorkspace()
{
	bool bOk = true;
	CWorkspace* wks = wxGetApp().GetCurrentWorkspace();

	if ( wks == nullptr )
	{
		wxMessageBox( "There is no current workspace opened",
			"Warning",
			wxOK | wxCENTRE | wxICON_EXCLAMATION );
		return true;
	}

	CWorkspaceDlg wksDlg( this, -1, "Rename a workspace...",
		CWorkspaceDlg::wksRename, wks, "." );

	int32_t result = wksDlg.ShowModal();
	if ( result != wxID_OK )
	{
		return true;
	}

	wks->SetName( wksDlg.GetWksName()->GetValue().ToStdString() );

	std::string errorMsg;
	wks->SaveConfig( errorMsg, wxGetApp().GetCurrentWorkspaceOperation(), wxGetApp().GetCurrentWorkspaceDisplay() );
	if ( !errorMsg.empty() )
		wxMessageBox( errorMsg, "Warning", wxOK | wxCENTRE | wxICON_INFORMATION );

	return bOk;
}
//----------------------------------------
bool CGuiFrame::DeleteWorkspace()
{  
  bool bOk = true;

  CWorkspace* wks = wxGetApp().GetCurrentWorkspace();

  if (wks == nullptr)
  {
    wxMessageBox("There is no current workspace opened",
                 "Warning",
                  wxOK | wxCENTRE | wxICON_EXCLAMATION);
    return true;
  }

  wxString msg = wxString::Format("Delete workspace '%s' ...", wks->GetName().c_str());

  CWorkspaceDlg wksDlg (this, -1, msg,
                        CWorkspaceDlg::wksDelete, wks, ".");
  
  int32_t result = wksDlg.ShowModal();
  if (result != wxID_OK)
  {
    return true;
  }
  msg = wxString::Format("WARNING - All files under '%s' will be deleted\nAre you sure ?", wks->GetPath().c_str());
  result = wxMessageBox(msg,
                        "Warning",
                        wxYES_NO | wxCENTRE | wxICON_QUESTION);

  if (result != wxYES)
  {
    return true;
  }

  bOk = wks->Rmdir();

  RemoveWorkspaceFromHistory(wks->GetPath());
  
  DoEmptyWorkspace();

  return bOk;
}
//----------------------------------------
bool CGuiFrame::AskToSave()
{
  CWorkspace* wks = wxGetApp().GetCurrentWorkspace();
  bool cancel = false;

  if (wks != nullptr)
  {
    int32_t result = wxMessageBox("Do you want to save the current workspace ?\n"
                                   "Click Yes to save and continue\n"
                                   "Click No to continue without saving\n"
                                   "Click Cancel to cancel operation",
                                 "Question",
                                  wxYES_NO | wxCANCEL | wxCENTRE | wxICON_QUESTION);
    if (result == wxYES)
    {
      SaveWorkspace();    
    }

    cancel = (result == wxCANCEL);
  }

  return cancel;
}
//----------------------------------------
void CGuiFrame::DoSortFieldCtrl(bool reverse)
{
    wxTreeItemId item = GetFieldstreectrl()->GetSelection();

    if (!item)
    {
      return;
    }
    //CHECK_ITEM( item );

    if (!GetFieldstreectrl()->ItemHasChildren(item))
    {
      item = GetFieldstreectrl()->GetItemParent(item);
    }
    GetFieldstreectrl()->DoSortChildren(item, reverse);
}
//----------------------------------------
void CGuiFrame::DoSortDispTreeCtrl(bool reverse)
{
    wxTreeItemId item = GetDispavailtreectrl()->GetSelection();

    if (!item)
    {
      return;
    }
    //CHECK_ITEM( item );

    if (!GetDispavailtreectrl()->ItemHasChildren(item))
    {
      item = GetDispavailtreectrl()->GetItemParent(item);
    }
    GetDispavailtreectrl()->DoSortChildren(item, reverse);
}

//----------------------------------------
void CGuiFrame::DoSortOpCtrl(bool reverse)
{
    wxTreeItemId item = GetOperationtreectrl()->GetSelection();

    if (!item)
    {
      return;
    }
    //CHECK_ITEM( item );

    if (!GetOperationtreectrl()->ItemHasChildren(item))
    {
      item = GetOperationtreectrl()->GetItemParent(item);
    }
    GetOperationtreectrl()->DoSortChildren(item, reverse);

}
//----------------------------------------
// WDR: handler implementations for CGuiFrame

//----------------------------------------
void CGuiFrame::OnFieldAttrChangeUnit( wxCommandEvent &event )
{
  m_guiPanel->GetOperationPanel()->FieldAttrChangeUnit();            
}
//----------------------------------------
void CGuiFrame::OnRenameExpression( wxCommandEvent &event )
{
  m_guiPanel->GetOperationPanel()->RenameExpression();            
}

//----------------------------------------
void CGuiFrame::OnCollapseAvailabledispDataTree( wxCommandEvent &event )
{
  m_guiPanel->GetDisplayPanel()->GetDispavailtreectrl()->CollapseItemsRecurse();            
    
}
//----------------------------------------
void CGuiFrame::OnExpandAvailabledispDataTree( wxCommandEvent &event )
{
  m_guiPanel->GetDisplayPanel()->GetDispavailtreectrl()->ExpandItemsRecurse();            
}
//----------------------------------------
void CGuiFrame::OnAddToSelected( wxCommandEvent &event )
{
  m_guiPanel->GetDisplayPanel()->AddField(); 
}

//----------------------------------------
void CGuiFrame::OnDeleteExpression( wxCommandEvent &event )
{
  m_guiPanel->GetOperationPanel()->DeleteExpression();        
}

//----------------------------------------
void CGuiFrame::OnSaveAsFormula( wxCommandEvent &event )
{

  m_guiPanel->GetOperationPanel()->SaveCurrentFormulaAs();
    
}

//----------------------------------------
void CGuiFrame::OnInsertFormula( wxCommandEvent &event )
{
  m_guiPanel->GetOperationPanel()->InsertFormula();            
}

//----------------------------------------
void CGuiFrame::OnInsertFunction( wxCommandEvent &event )
{
  m_guiPanel->GetOperationPanel()->InsertFunction();                
}

//----------------------------------------
void CGuiFrame::OnInsertField( wxCommandEvent &event )
{
  m_guiPanel->GetOperationPanel()->InsertField();    

}

//----------------------------------------
void CGuiFrame::OnInsertEmptyExpression( wxCommandEvent &event )
{
  m_guiPanel->GetOperationPanel()->InsertEmptyExpression();       
}
//----------------------------------------

void CGuiFrame::OnInsertIntoSelect( wxCommandEvent &event )
{    
  CField* field = GetFieldstreectrl()->GetCurrentField();    
  if (field == nullptr)
  {
    return;
  }

  GetOperationtreectrl()->Add(GetOperationtreectrl()->GetSelectRootId(), field);  
}
//----------------------------------------

void CGuiFrame::OnSetAsData( wxCommandEvent &event )
{    
  CField* field = GetFieldstreectrl()->GetCurrentField();    
  if (field == nullptr)
  {
    return;
  }

  GetOperationtreectrl()->Add(GetOperationtreectrl()->GetDataRootId(), field);  
}
//----------------------------------------

void CGuiFrame::OnSetAsY( wxCommandEvent &event )
{
  CField* field = GetFieldstreectrl()->GetCurrentField();    
  if (field == nullptr)
  {
    return;
  }

  GetOperationtreectrl()->Add(GetOperationtreectrl()->GetYRootId(), field);  
    
}
//----------------------------------------

void CGuiFrame::OnSetAsX( wxCommandEvent &event )
{
  CField* field = GetFieldstreectrl()->GetCurrentField();    
  if (field == nullptr)
  {
    return;
  }

  GetOperationtreectrl()->Add(GetOperationtreectrl()->GetXRootId(), field);
  
}
//----------------------------------------

void CGuiFrame::OnSortRevDispTreeCtrl( wxCommandEvent &event )
{
  DoSortDispTreeCtrl(true);            
    
}
//----------------------------------------

void CGuiFrame::OnSortDispTreeCtrl( wxCommandEvent &event )
{
  DoSortDispTreeCtrl();            
}

//----------------------------------------
void CGuiFrame::OnSortRevOpCtrl( wxCommandEvent &event )
{
  DoSortOpCtrl(true);    
}

//----------------------------------------
void CGuiFrame::OnSortOpCtrl( wxCommandEvent &event )
{
  DoSortOpCtrl();        
}

//----------------------------------------
void CGuiFrame::OnSortRevFieldCtrl( wxCommandEvent &event )
{
  DoSortFieldCtrl(true);
}

//----------------------------------------
void CGuiFrame::OnSortFieldCtrl( wxCommandEvent &event )
{
  DoSortFieldCtrl();    
}

//----------------------------------------
void CGuiFrame::OnUserManual( wxCommandEvent &event )
{

  wxGetApp().ViewUserManual();

 }

//----------------------------------------
void CGuiFrame::OnDuplicateOperationUpdateUI( wxUpdateUIEvent &event )
{
  /*
  bool enable = wxGetApp().GetCurrentWorkspace() 
                && m_guiPanel->GetOperationPanel()->HasOperation(); 
*/
  bool enable = wxGetApp().GetCurrentWorkspace() 
                && m_guiPanel->GetOperationPanel()->HasOperation(); 

  event.Enable(enable);    
    
}

//----------------------------------------
void CGuiFrame::OnDuplicateOperation( wxCommandEvent &event )
{
  wxGetApp().GotoOperationPage();
  //m_guiPanel->GetOperationPanel()->DuplicateOperation();         
  m_guiPanel->GetOperationPanel()->DuplicateOperation();         
}

//----------------------------------------
void CGuiFrame::OnDeleteViewUpdateUI( wxUpdateUIEvent &event )
{
  event.Enable(wxGetApp().IsDeleteViewEnable());    
    
}

//----------------------------------------
void CGuiFrame::OnDeleteView( wxCommandEvent &event )
{
  wxGetApp().GotoDisplayPage();
  //m_guiPanel->GetDisplayPanel()->DeleteDisplay();     
  m_guiPanel->GetDisplayPanel()->DeleteDisplay();     
    
}

//----------------------------------------
void CGuiFrame::OnNewViewUpdateUI( wxUpdateUIEvent &event )
{
  event.Enable(wxGetApp().IsNewViewEnable() );            
}

//----------------------------------------
void CGuiFrame::OnNewView( wxCommandEvent &event )
{
  wxGetApp().GotoDisplayPage();
  //m_guiPanel->GetDisplayPanel()->NewDisplay();     
  m_guiPanel->GetDisplayPanel()->NewDisplay();     
}

//----------------------------------------
void CGuiFrame::OnDeleteOperationUpdateUI( wxUpdateUIEvent &event )
{
  event.Enable(wxGetApp().IsDeleteOperationEnable());    
}

//----------------------------------------
void CGuiFrame::OnDeleteOperation( wxCommandEvent &event )
{
  wxGetApp().GotoOperationPage();
  //m_guiPanel->GetOperationPanel()->DeleteOperation();     
  m_guiPanel->GetOperationPanel()->DeleteOperation();     
    
}

//----------------------------------------
void CGuiFrame::OnNewOperationUpdateUI( wxUpdateUIEvent &event )
{
  event.Enable( wxGetApp().IsNewOperationEnable() );        
}
//----------------------------------------
void CGuiFrame::OnNewOperation( wxCommandEvent &event )
{
  wxGetApp().GotoOperationPage();
  //m_guiPanel->GetOperationPanel()->NewOperation();     
  m_guiPanel->GetOperationPanel()->NewOperation();     
    
}

//----------------------------------------
void CGuiFrame::OnDeleteDatasetUpdateUI( wxUpdateUIEvent &event )
{
  event.Enable(wxGetApp().IsDeleteDatasetEnable());    
}

//----------------------------------------
void CGuiFrame::OnDeleteDataset( wxCommandEvent &event )
{
  wxGetApp().GotoDatasetPage();
  m_guiPanel->GetDatasetPanel()->DeleteDataset();         
}

//----------------------------------------
void CGuiFrame::OnNewDatasetUpdateUI( wxUpdateUIEvent &event )
{
  event.Enable(wxGetApp().IsNewDatasetEnable());          
}

//----------------------------------------
void CGuiFrame::OnNewDataset( wxCommandEvent &event )
{
  wxGetApp().GotoDatasetPage();
  m_guiPanel->GetDatasetPanel()->NewDataset();     
}
//----------------------------------------

void CGuiFrame::OnImportWorkspaceUpdateUI( wxUpdateUIEvent &event )
{
  event.Enable(wxGetApp().GetCurrentWorkspace() != nullptr);        
}

//----------------------------------------
void CGuiFrame::OnSaveWorkspaceUpdateUI( wxUpdateUIEvent &event )
{
  event.Enable(wxGetApp().GetCurrentWorkspace() != nullptr);        
}

//----------------------------------------
void CGuiFrame::OnDeleteWorkspaceUpdateUI( wxUpdateUIEvent &event )
{
  event.Enable(wxGetApp().GetCurrentWorkspace() != nullptr);        
}

//----------------------------------------
void CGuiFrame::OnRenameWorkspaceUpdateUI( wxUpdateUIEvent &event )
{
  event.Enable(wxGetApp().GetCurrentWorkspace() != nullptr);        
}

//----------------------------------------
void CGuiFrame::OnSaveWorkspace( wxCommandEvent &event )
{
  SaveWorkspace();    
}

//----------------------------------------
void CGuiFrame::OnDeleteWorkspace( wxCommandEvent &event )
{
  DeleteWorkspace(); 
}

//----------------------------------------
void CGuiFrame::OnRenameWorkspace( wxCommandEvent &event )
{
  RenameWorkspace(); 
}

//----------------------------------------
void CGuiFrame::OnImportWorkspace( wxCommandEvent &event )
{
  ImportWorkspace();
}

//----------------------------------------

#if defined(_WIN64) || defined(__LP64__) || defined(__x86_64__) 
	#define PROCESSOR_ARCH wxT("64 bit") 
#else
	#define PROCESSOR_ARCH wxT("32 bit") 
#endif

void CGuiFrame::OnAbout( wxCommandEvent &event )
{
    wxMessageDialog dialog( this, wxT("Welcome to BRAT ") wxT(BRAT_VERSION)  wxT(" - ") PROCESSOR_ARCH wxT("\n(C)opyright CNES/ESA"),
        wxT("About BRAT"), wxOK|wxICON_INFORMATION );
    dialog.ShowModal();
}

//----------------------------------------
void CGuiFrame::OnQuit( wxCommandEvent &event )
{
     Close();
}

//----------------------------------------
void CGuiFrame::OnCloseWindow( wxCloseEvent &event )
{
  GetFieldstreectrl()->DeInstallEventListeners();
  
  bool cancel = AskToSave();

  if (cancel)
  {
    event.Veto();
    return;
  }

  FileHistoryToConfig();
  
  if (m_menuBarPopup != nullptr)
  {
    delete m_menuBarPopup;
    m_menuBarPopup = nullptr;
  }
  // if ! saved changes -> return
  Destroy();
}

//----------------------------------------
void CGuiFrame::OnSize( wxSizeEvent &event )
{
    event.Skip( TRUE );
}

//----------------------------------------
void CGuiFrame::OnUpdateUI( wxUpdateUIEvent &event )
{
    event.Skip( TRUE );
}

//----------------------------------------
void CGuiFrame::SetTitle()
{
  wxString title = BRATGUI_TITLE;
  CWorkspace* wks =wxGetApp().GetCurrentWorkspace();
  if (wks != nullptr)
  {
    title += " - " + wks->GetName();
  }

  wxTopLevelWindow::SetTitle(title);
}
