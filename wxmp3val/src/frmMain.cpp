/*
 * This file is part of the wxMP3val and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#include "frmMain.h"

#include "frmSettings.h"
#include "frmAbout.h"
#include "Progress.h"
#include "Global.h"
#include "DndFile.h"

//(*InternalHeaders(frmMain)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

#include <wx/aboutdlg.h>
#include <wx/filedlg.h>
#include <wx/dirdlg.h>

//(*IdInit(frmMain)
const long frmMain::ID_LISTCTRL1 = wxNewId();
const long frmMain::ID_MENUITEM14 = wxNewId();
const long frmMain::ID_MENUITEM2 = wxNewId();
const long frmMain::ID_MENUITEM1 = wxNewId();
const long frmMain::ID_MENUITEM3 = wxNewId();
const long frmMain::ID_MENUITEM4 = wxNewId();
const long frmMain::ID_MENUITEM6 = wxNewId();
const long frmMain::ID_MENUITEM7 = wxNewId();
const long frmMain::ID_MENUITEM8 = wxNewId();
const long frmMain::ID_MENUITEM10 = wxNewId();
const long frmMain::ID_MENUITEM11 = wxNewId();
const long frmMain::ID_MENUITEM9 = wxNewId();
const long frmMain::ID_STATUSBAR1 = wxNewId();
const long frmMain::ID_TOOLBARITEM8 = wxNewId();
const long frmMain::ID_TOOLBARITEM1 = wxNewId();
const long frmMain::ID_TOOLBARITEM2 = wxNewId();
const long frmMain::ID_TOOLBARITEM3 = wxNewId();
const long frmMain::ID_TOOLBARITEM4 = wxNewId();
const long frmMain::ID_TOOLBARITEM5 = wxNewId();
const long frmMain::ID_TOOLBARITEM6 = wxNewId();
const long frmMain::ID_TOOLBARITEM7 = wxNewId();
const long frmMain::ID_TOOLBAR1 = wxNewId();
const long frmMain::ID_MENUITEM15 = wxNewId();
const long frmMain::ID_MENUITEM5 = wxNewId();
const long frmMain::ID_MENUITEM12 = wxNewId();
const long frmMain::ID_MENUITEM13 = wxNewId();
//*)

BEGIN_EVENT_TABLE(frmMain,wxFrame)
    //(*EventTable(frmMain)
    //*)
END_EVENT_TABLE()

frmMain::frmMain(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(frmMain)
    wxMenuItem* MenuItem8;
    wxMenuItem* MenuItem7;
    wxMenuItem* MenuItem5;
    wxMenuItem* MenuItem2;
    wxMenu* Menu3;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem4;
    wxMenuItem* MenuItem11;
    wxMenuItem* MenuItem10;
    wxMenuItem* MenuItem3;
    wxMenuItem* MenuItem6;
    wxMenu* Menu2;
    wxMenuItem* MenuItem9;
    wxMenu* Menu5;
    wxMenu* Menu4;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(763,450));
    Move(wxDefaultPosition);
    lstFiles = new wxListCtrl(this, ID_LISTCTRL1, wxPoint(184,208), wxSize(520,450), wxLC_REPORT, wxDefaultValidator, _T("ID_LISTCTRL1"));
    MenuBar1 = new wxMenuBar();
    Menu2 = new wxMenu();
    MenuItem14 = new wxMenuItem(Menu2, ID_MENUITEM14, _("Add F&older"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem14);
    MenuItem2 = new wxMenuItem(Menu2, ID_MENUITEM2, _("&Add Files"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    Menu2->AppendSeparator();
    MenuItem1 = new wxMenuItem(Menu2, ID_MENUITEM1, _("E&xit"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem1);
    MenuBar1->Append(Menu2, _("&File"));
    Menu3 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu3, ID_MENUITEM3, _("&Remove Files"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem3);
    MenuItem4 = new wxMenuItem(Menu3, ID_MENUITEM4, _("&Clear List"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem4);
    Menu3->AppendSeparator();
    MenuItem6 = new wxMenuItem(Menu3, ID_MENUITEM6, _("&Settings"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem6);
    MenuBar1->Append(Menu3, _("&Edit"));
    Menu4 = new wxMenu();
    MenuItem7 = new wxMenuItem(Menu4, ID_MENUITEM7, _("&Scan"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem7);
    MenuItem8 = new wxMenuItem(Menu4, ID_MENUITEM8, _("Re&pair"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem8);
    MenuBar1->Append(Menu4, _("&Actions"));
    Menu5 = new wxMenu();
    MenuItem12 = new wxMenuItem(Menu5, ID_MENUITEM10, _("&MP3val Website"), wxEmptyString, wxITEM_NORMAL);
    Menu5->Append(MenuItem12);
    MenuItem13 = new wxMenuItem(Menu5, ID_MENUITEM11, _("&wxMP3val Website"), wxEmptyString, wxITEM_NORMAL);
    Menu5->Append(MenuItem13);
    Menu5->AppendSeparator();
    MenuItem9 = new wxMenuItem(Menu5, ID_MENUITEM9, _("&About"), wxEmptyString, wxITEM_NORMAL);
    Menu5->Append(MenuItem9);
    MenuBar1->Append(Menu5, _("&Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, wxST_SIZEGRIP, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[2] = { -10, -10 };
    int __wxStatusBarStyles_1[2] = { wxSB_NORMAL, wxSB_NORMAL };
    StatusBar1->SetFieldsCount(2,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(2,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    ToolBar1 = new wxToolBar(this, ID_TOOLBAR1, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL|wxTB_TEXT|wxNO_BORDER, _T("ID_TOOLBAR1"));
    ToolBarItem1 = ToolBar1->AddTool(ID_TOOLBARITEM8, _("Add folder"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_QUESTION")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBarItem2 = ToolBar1->AddTool(ID_TOOLBARITEM1, _("Add files"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_QUESTION")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBarItem3 = ToolBar1->AddTool(ID_TOOLBARITEM2, _("Remove files"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_QUESTION")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBarItem4 = ToolBar1->AddTool(ID_TOOLBARITEM3, _("Clear files"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_QUESTION")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBar1->AddSeparator();
    ToolBarItem5 = ToolBar1->AddTool(ID_TOOLBARITEM4, _("Scan"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_QUESTION")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBarItem6 = ToolBar1->AddTool(ID_TOOLBARITEM5, _("Repair"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_QUESTION")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBar1->AddSeparator();
    ToolBarItem7 = ToolBar1->AddTool(ID_TOOLBARITEM6, _("Settings"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_QUESTION")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBarItem8 = ToolBar1->AddTool(ID_TOOLBARITEM7, _("About"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_QUESTION")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBar1->Realize();
    SetToolBar(ToolBar1);
    MenuItem15 = new wxMenuItem((&Menu1), ID_MENUITEM15, _("Add F&older"), wxEmptyString, wxITEM_NORMAL);
    Menu1.Append(MenuItem15);
    MenuItem5 = new wxMenuItem((&Menu1), ID_MENUITEM5, _("&Add Files"), wxEmptyString, wxITEM_NORMAL);
    Menu1.Append(MenuItem5);
    MenuItem10 = new wxMenuItem((&Menu1), ID_MENUITEM12, _("&Remove files"), wxEmptyString, wxITEM_NORMAL);
    Menu1.Append(MenuItem10);
    MenuItem11 = new wxMenuItem((&Menu1), ID_MENUITEM13, _("&Clear list"), wxEmptyString, wxITEM_NORMAL);
    Menu1.Append(MenuItem11);
    Center();

    Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&frmMain::OnlstFilesClick);
    Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_DESELECTED,(wxObjectEventFunction)&frmMain::OnlstFilesClick);
    Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&frmMain::OnlstFilesItemRClick);
    Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_INSERT_ITEM,(wxObjectEventFunction)&frmMain::OnlstFilesClick);
    Connect(ID_MENUITEM14,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frmMain::mnuAddDirectory);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frmMain::mnuAddFiles);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frmMain::mnuExit);
    Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frmMain::mnuRemoveFiles);
    Connect(ID_MENUITEM4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frmMain::mnuClearList);
    Connect(ID_MENUITEM6,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frmMain::mnuSettings);
    Connect(ID_MENUITEM7,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frmMain::mnuScan);
    Connect(ID_MENUITEM8,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frmMain::mnuFix);
    Connect(ID_MENUITEM10,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frmMain::mnuToolWebsite);
    Connect(ID_MENUITEM11,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frmMain::mnuWebsite);
    Connect(ID_MENUITEM9,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frmMain::mnuAbout);
    Connect(ID_TOOLBARITEM8,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&frmMain::mnuAddDirectory);
    Connect(ID_TOOLBARITEM1,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&frmMain::mnuAddFiles);
    Connect(ID_TOOLBARITEM2,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&frmMain::mnuRemoveFiles);
    Connect(ID_TOOLBARITEM3,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&frmMain::mnuClearList);
    Connect(ID_TOOLBARITEM4,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&frmMain::mnuScan);
    Connect(ID_TOOLBARITEM5,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&frmMain::mnuFix);
    Connect(ID_TOOLBARITEM6,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&frmMain::mnuSettings);
    Connect(ID_TOOLBARITEM7,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&frmMain::mnuAbout);
    Connect(ID_MENUITEM15,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frmMain::mnuAddDirectory);
    Connect(ID_MENUITEM5,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frmMain::mnuAddFiles);
    Connect(ID_MENUITEM12,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frmMain::mnuRemoveFiles);
    Connect(ID_MENUITEM13,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frmMain::mnuClearList);
    //*)

    // Support Drag & Drop
    lstFiles->SetDropTarget(new DndFile(lstFiles));

    // Configuration file
    configBase = new ConfigBase(APP_NAME);

    // Window title
    SetTitle(APP_NAME_WITH_VERSION);

    // Load resource
    loadResources();

    // Title List
    lstFiles->InsertColumn(0, _("File"), wxLIST_FORMAT_LEFT, 400);
    lstFiles->InsertColumn(1, _("Version"), wxLIST_FORMAT_LEFT, 100);
    lstFiles->InsertColumn(2, _("Tags"), wxLIST_FORMAT_LEFT, 100);
    lstFiles->InsertColumn(3, _("CBR"), wxLIST_FORMAT_LEFT, 40);
    lstFiles->InsertColumn(4, _("State"), wxLIST_FORMAT_LEFT, 80);

    // Updates the status bar
    updateStatusBar();

    // Updates the controls that should be disabled
    updateDisabledControls();
}

frmMain::~frmMain()
{
    //(*Destroy(frmMain)
    //*)

    // Deletes the object configuration file and updates the file / record
    delete configBase;
}

void frmMain::mnuAddFiles(wxCommandEvent& event)
{
    wxArrayString files;
    wxFileDialog FileDialog1(this, _("Select files"), wxEmptyString, wxEmptyString, APP_WILDCARD_EXT, wxFD_OPEN|wxFD_MULTIPLE);

    // Read the last directory used
    FileDialog1.SetDirectory(configBase->getLastOpenDir());

    if (FileDialog1.ShowModal() == wxID_OK)
    {
        SetCursor(wxCURSOR_WAIT);

        // Get the file(s) the user selected
        FileDialog1.GetPaths(files);
        DndFile::InsertFileList(lstFiles, files);

        // Remembers the last used directory
        configBase->setLastOpenDir(FileDialog1.GetDirectory());
        SetCursor(wxCURSOR_ARROW);
    }
}

void frmMain::mnuAddDirectory(wxCommandEvent& event)
{
    wxDirDialog DirDialog1(this, _("Select directory"), wxEmptyString, wxDD_DEFAULT_STYLE);

    // Read the last directory used
    DirDialog1.SetPath(configBase->getLastOpenDir());
    if (DirDialog1.ShowModal() == wxID_OK)
    {
        SetCursor(wxCURSOR_WAIT);
        DndFile::InsertFileListDir(lstFiles, DirDialog1.GetPath());

        // Remembers the last used directory
        configBase->setLastOpenDir(DirDialog1.GetPath());
        SetCursor(wxCURSOR_ARROW);
    }
}

void frmMain::mnuExit(wxCommandEvent& event)
{
    // Terminates the program
    Close();
}

void frmMain::mnuClearList(wxCommandEvent& event)
{
    // Deletes all items from the list
    lstFiles->DeleteAllItems();

    updateDisabledControls();
}

void frmMain::mnuRemoveFiles(wxCommandEvent& event)
{
    int itemCount = lstFiles->GetSelectedItemCount();
    SetCursor(wxCURSOR_WAIT);
    for (int i=0; i<itemCount; i++)
        lstFiles->DeleteItem(lstFiles->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED));
    SetCursor(wxCURSOR_ARROW);

    updateDisabledControls();
}

void frmMain::mnuScan(wxCommandEvent& event)
{
    // Displays the "Progress" window
    Progress Dlg(this, configBase, lstFiles, TOOL_SCAN);
    Dlg.Execute();
}

void frmMain::mnuFix(wxCommandEvent& event)
{
    // Displays the "Progress" window
    Progress Dlg(this, configBase, lstFiles, TOOL_FIX);
    Dlg.Execute();
}

void frmMain::OnlstFilesItemRClick(wxListEvent& event)
{
    updateDisabledControls();

    // Displays the popup menu when you click a list item
    lstFiles->PopupMenu(&Menu1);
}

void frmMain::OnlstFilesClick(wxListEvent& event)
{
    updateDisabledControls();
}

void frmMain::updateDisabledControls()
{
    // Disables the menu item "Remove files" if no item is selected
    Menu1.Enable(ID_MENUITEM12, lstFiles->GetSelectedItemCount() > 0);
    MenuBar1->Enable(ID_MENUITEM3, lstFiles->GetSelectedItemCount() > 0);
    ToolBar1->EnableTool(ID_TOOLBARITEM2, lstFiles->GetSelectedItemCount() > 0);

    // Disables the menu item "Clear list" if there is no item in the list
    Menu1.Enable(ID_MENUITEM13, lstFiles->GetItemCount() > 0);
    MenuBar1->Enable(ID_MENUITEM4, lstFiles->GetItemCount() > 0);
    ToolBar1->EnableTool(ID_TOOLBARITEM3, lstFiles->GetItemCount() > 0);

    // Disables menus Scan and Fix case there is no item in the list
    MenuBar1->Enable(ID_MENUITEM7, lstFiles->GetItemCount() > 0);
    MenuBar1->Enable(ID_MENUITEM8, lstFiles->GetItemCount() > 0);
    ToolBar1->EnableTool(ID_TOOLBARITEM4, lstFiles->GetItemCount() > 0);
    ToolBar1->EnableTool(ID_TOOLBARITEM5, lstFiles->GetItemCount() > 0);
}

void frmMain::mnuSettings(wxCommandEvent& event)
{
    // Displays the "Settings" window
    frmSettings Dlg(this, configBase);
    Dlg.ShowModal();

    // Updates the status bar after closing the window "Settings"
    updateStatusBar();
}


void frmMain::updateStatusBar()
{
    wxArrayString inputString;

    // Execute external application
    wxExecute(configBase->getToolExecutable() + wxT(" -v"), inputString, wxEXEC_NODISABLE);

    // Show the version of tool
    if(!inputString.IsEmpty())
        StatusBar1->SetStatusText(wxT("Using MP3val version: ") + inputString.Item(0).AfterLast(' '), 1);
    else
        StatusBar1->SetStatusText(wxT("MP3val not found!"), 1);
}

void frmMain::mnuAbout(wxCommandEvent& event)
{
    frmAbout Dlg(this);
    Dlg.ShowModal();
}

void frmMain::mnuWebsite(wxCommandEvent& event)
{
    wxLaunchDefaultBrowser(wxT("http://sourceforge.net/projects/wxmp3val/"));
}

void frmMain::mnuToolWebsite(wxCommandEvent& event)
{
    wxLaunchDefaultBrowser(wxT("http://mp3val.sourceforge.net/"));
}

void frmMain::loadResources()
{
    // Window icon
    wxIcon FrameIcon;
    FrameIcon.CopyFromBitmap(wxBitmap(wxImage(RESOURCE_DIR + _T("icon2.ico"))));
    SetIcon(FrameIcon);

    // Toolbar bitmaps
    ToolBar1->SetToolNormalBitmap(ID_TOOLBARITEM1, wxBitmap(wxImage(RESOURCE_DIR + _T("toolbar/add.png"))));
    ToolBar1->SetToolNormalBitmap(ID_TOOLBARITEM2, wxBitmap(wxImage(RESOURCE_DIR + _T("toolbar/remove.png"))));
    ToolBar1->SetToolNormalBitmap(ID_TOOLBARITEM3, wxBitmap(wxImage(RESOURCE_DIR + _T("toolbar/clear.png"))));
    ToolBar1->SetToolNormalBitmap(ID_TOOLBARITEM4, wxBitmap(wxImage(RESOURCE_DIR + _T("toolbar/scan.png"))));
    ToolBar1->SetToolNormalBitmap(ID_TOOLBARITEM5, wxBitmap(wxImage(RESOURCE_DIR + _T("toolbar/fix.png"))));
    ToolBar1->SetToolNormalBitmap(ID_TOOLBARITEM6, wxBitmap(wxImage(RESOURCE_DIR + _T("toolbar/settings.png"))));
    ToolBar1->SetToolNormalBitmap(ID_TOOLBARITEM7, wxBitmap(wxImage(RESOURCE_DIR + _T("toolbar/about.png"))));
    ToolBar1->SetToolNormalBitmap(ID_TOOLBARITEM8, wxBitmap(wxImage(RESOURCE_DIR + _T("toolbar/folder.png"))));
}
