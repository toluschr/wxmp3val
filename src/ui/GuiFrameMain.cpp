/*
 * This file is part of the wxMP3val and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#include "GuiDialogSettings.hpp"
#include "GuiFrameMain.hpp"

#include "../Constants.hpp"
#include "../Process.hpp"

#include <wx/aboutdlg.h>
#include <wx/dirdlg.h>
#include <wx/filedlg.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/msgdlg.h>

GuiFrameMain::GuiFrameMain(wxWindow *parent) : FrameMain(parent), m_processRunning(false) {
    // Disable status bar pane used to display menu and toolbar help
    SetStatusBarPane(-1);

    // File list manager
    mp_listManager = new ListManager(gui_lstFiles);

    // List Drag & Drop
    mp_fileDrop = new FileDrop(mp_listManager);
    gui_lstFiles->SetDropTarget(mp_fileDrop);

    // Title List
    gui_lstFiles->InsertColumn(ID_LIST_FILE, _("File"), wxLIST_FORMAT_LEFT, 200);
    gui_lstFiles->InsertColumn(ID_LIST_FOLDER, _("Folder"), wxLIST_FORMAT_LEFT, 200);
    gui_lstFiles->InsertColumn(ID_LIST_VERSION, _("Version"), wxLIST_FORMAT_LEFT, 100);
    gui_lstFiles->InsertColumn(ID_LIST_TAGS, _("Tags"), wxLIST_FORMAT_LEFT, 100);
    gui_lstFiles->InsertColumn(ID_LIST_CBR, _("CBR"), wxLIST_FORMAT_LEFT, 70);
    gui_lstFiles->InsertColumn(ID_LIST_BITRATE, _("Bitrate"), wxLIST_FORMAT_LEFT, 70);
    gui_lstFiles->InsertColumn(ID_LIST_STATE, _("State"), wxLIST_FORMAT_LEFT, 70);

    // Set statusbar widths
    const int wxStatusBarWidths[3] = {-10, -10, -5};
    gui_mainStatusBar->SetStatusWidths(3, wxStatusBarWidths);

    // Configuration file
    mp_appSettings = new AppSettings(APP_NAME);

    // Window title
    SetTitle(APP_NAME_WITH_VERSION);

    // Load resource
    loadResources();

    // Updates the controls
    updateControls();

    wxArrayString stdoutString;
    wxExecute(APP_TOOL_EXECUTABLE + _T(" -v"), stdoutString, wxEXEC_NODISABLE | wxEXEC_SYNC);

    // Show the version of tool
    if (!stdoutString.IsEmpty())
        gui_mainStatusBar->SetStatusText(_("Using MP3val version: ") + stdoutString.Item(0).AfterLast(' '), 0);
    else
        gui_mainStatusBar->SetStatusText(_("MP3val not found!"), 0);
}

GuiFrameMain::~GuiFrameMain() {
    delete mp_listManager;
    delete mp_appSettings;
}

void GuiFrameMain::OnlstFilesDeleteItem(wxListEvent &event) {
    if (!m_processRunning) {
        delete (FileData*)gui_lstFiles->GetItemData(event.GetIndex());
        updateControls();
    }
    event.Skip();
}

void GuiFrameMain::OnlstFilesInsertItem(wxListEvent &event) {
    if (!m_processRunning) {
        updateControls();
    }
    event.Skip();
}

void GuiFrameMain::OnlstFilesItemSelect(wxListEvent &event) {
    if (!m_processRunning) {
        updateControls();
    }
    event.Skip();
}

void GuiFrameMain::OnlstFilesItemRClick(wxListEvent &event) {
    if (!m_processRunning) {
        updateControls();
        // Displays the popup menu when you click a list item
        gui_lstFiles->PopupMenu(gui_menu);
    }
    event.Skip();
}

void GuiFrameMain::OnlstFilesKeyDown(wxListEvent &event) {
    if (!m_processRunning) {
        // Remove files with Delete key
        int keyCode = event.GetKeyCode();
        if (keyCode == WXK_DELETE)
            mnuRemoveFiles(event);
    }
    event.Skip();
}

struct compare_data {
    int col;
    int order;
    wxListCtrl *ctrl;
};

static wxCALLBACK int lstFiles_compare(wxIntPtr item1, wxIntPtr item2, wxIntPtr data) {
    auto cmp = (struct compare_data *)data;

    long item1_idx = cmp->ctrl->FindItem(-1, item1);
    long item2_idx = cmp->ctrl->FindItem(-1, item2);

    return cmp->order * cmp->ctrl->GetItemText(item1_idx, cmp->col).compare(cmp->ctrl->GetItemText(item2_idx, cmp->col));
}

void GuiFrameMain::OnlstFilesColClick(wxListEvent &event) {
    if (!m_processRunning) {
        struct compare_data cmp;
        cmp.col = event.GetColumn();
        cmp.order = (cmp.col == m_lastSortCol) ? -1 : +1;
        cmp.ctrl = gui_lstFiles;
        m_lastSortCol = cmp.col;

        // gui_lstFiles->SetWindowStyleFlag(wxLC_REPORT | wxLC_SORT_ASCENDING);
        gui_lstFiles->SortItems(lstFiles_compare, (wxIntPtr)&cmp);
        updateControls();
    }

    event.Skip();
}

void GuiFrameMain::btnProcessStop(wxCommandEvent &event) {
    m_processRunning = false;
    gui_btnStop->Enable(false);
    event.Skip(false);
}

void GuiFrameMain::mnuAddDirectory(wxCommandEvent &event) {
    wxString msg = _("Select directory");
    wxDirDialog dirDialog(this, msg, wxEmptyString, wxDD_DEFAULT_STYLE);

    // Read the last directory used
    dirDialog.SetPath(mp_appSettings->getLastOpenDir());
    if (dirDialog.ShowModal() == wxID_OK) {
        SetCursor(wxCURSOR_WAIT);
        mp_listManager->insertDir(dirDialog.GetPath());

        // Remembers the last used directory
        mp_appSettings->setLastOpenDir(dirDialog.GetPath());
        SetCursor(wxCURSOR_ARROW);
    }
    event.Skip(false);
}

void GuiFrameMain::mnuAddFiles(wxCommandEvent &event) {
    wxArrayString files;
    wxString msg = _("Select file");
    wxFileDialog fileDialog(this, msg, wxEmptyString, wxEmptyString, APP_WILDCARD_EXT, wxFD_OPEN | wxFD_MULTIPLE);

    // Read the last directory used
    fileDialog.SetDirectory(mp_appSettings->getLastOpenDir());

    if (fileDialog.ShowModal() == wxID_OK) {
        SetCursor(wxCURSOR_WAIT);

        // Get the file(s) the user selected
        fileDialog.GetPaths(files);
        mp_listManager->insertFiles(files);

        // Remembers the last used directory
        mp_appSettings->setLastOpenDir(fileDialog.GetDirectory());
        SetCursor(wxCURSOR_ARROW);
    }
    event.Skip(false);
}

void GuiFrameMain::mnuExit(wxCommandEvent &event) {
    // Terminates the program
    Close();
    event.Skip(false);
}

void GuiFrameMain::mnuRemoveFiles(wxCommandEvent &event) {
    int itemCount = gui_lstFiles->GetSelectedItemCount();
    SetCursor(wxCURSOR_WAIT);
    for (int i = 0; i < itemCount; i++) {
        long item = gui_lstFiles->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        gui_lstFiles->DeleteItem(item);
    }
    SetCursor(wxCURSOR_ARROW);

    updateControls();
    event.Skip(false);
}

void GuiFrameMain::mnuClearList(wxCommandEvent &event) {
    long itemIndex = -1;

    while ((itemIndex = gui_lstFiles->GetNextItem(itemIndex)) != wxNOT_FOUND) {
        delete (FileData *)gui_lstFiles->GetItemData(itemIndex);
    }

    gui_lstFiles->DeleteAllItems();
    updateControls();
    event.Skip(false);
}

void GuiFrameMain::mnuSettings(wxCommandEvent &event) {
    // Displays the "Settings" window
    GuiDialogSettings guiSettings(this, mp_appSettings);
    guiSettings.ShowModal();

    updateControls();
    event.Skip(false);
}

void GuiFrameMain::mnuScan(wxCommandEvent &event) {
    processExecute(false);
    event.Skip(false);
}

void GuiFrameMain::mnuRepair(wxCommandEvent &event) {
    processExecute(true);
    event.Skip(false);
}

void GuiFrameMain::mnuToolWebsite(wxCommandEvent &event) {
    wxLaunchDefaultBrowser(_T("http://mp3val.sourceforge.net/"));
    event.Skip(false);
}

void GuiFrameMain::mnuWebsite(wxCommandEvent &event) {
    wxLaunchDefaultBrowser(APP_WEBSITE);
    event.Skip(false);
}

void GuiFrameMain::mnuAbout(wxCommandEvent &event) {
    wxAboutDialogInfo aboutInfo;
    aboutInfo.SetName(APP_NAME);
    aboutInfo.SetVersion(APP_VERSION);
    aboutInfo.SetDescription(_("Free front-end for the MP3val"));
    aboutInfo.SetCopyright(APP_COPYRIGHT);
    aboutInfo.SetWebSite(APP_WEBSITE);
    wxString dataDir = getDataDir();
    aboutInfo.SetIcon(wxIcon(dataDir + _T("icons/app.ico"), wxBITMAP_TYPE_ICO));
    wxAboutBox(aboutInfo);
    event.Skip(false);
}

void GuiFrameMain::loadResources() {
    wxString dataDir = getDataDir();

    // Window icon
    SetIcon(wxIcon(dataDir + _T("icons/app.ico"), wxBITMAP_TYPE_ICO));

    // Toolbar bitmaps
    gui_toolBar->SetToolNormalBitmap(ID_ADD_FILES, wxBitmap(wxImage(dataDir + _T("toolbar/add-file.png"))));
    gui_toolBar->SetToolNormalBitmap(ID_ADD_FOLDER, wxBitmap(wxImage(dataDir + _T("toolbar/add-folder.png"))));
    gui_toolBar->SetToolNormalBitmap(ID_REMOVE_FILES, wxBitmap(wxImage(dataDir + _T("toolbar/remove.png"))));
    gui_toolBar->SetToolNormalBitmap(ID_CLEAR_LIST, wxBitmap(wxImage(dataDir + _T("toolbar/clear.png"))));
    gui_toolBar->SetToolNormalBitmap(ID_SCAN, wxBitmap(wxImage(dataDir + _T("toolbar/scan.png"))));
    gui_toolBar->SetToolNormalBitmap(ID_REPAIR, wxBitmap(wxImage(dataDir + _T("toolbar/fix.png"))));
    gui_toolBar->SetToolNormalBitmap(ID_SETTINGS, wxBitmap(wxImage(dataDir + _T("toolbar/settings.png"))));
    gui_toolBar->SetToolNormalBitmap(ID_ABOUT, wxBitmap(wxImage(dataDir + _T("toolbar/about.png"))));
}

void GuiFrameMain::updateControls() {
    wxString strNFiles = wxString::Format(_T("%i files"), gui_lstFiles->GetItemCount());
    gui_mainStatusBar->SetStatusText(strNFiles, 1);

    for (size_t i = 0; i < gui_menuBar->GetMenuCount(); i++)
        gui_menuBar->EnableTop(i, !m_processRunning);

    gui_toolBar->Enable(!m_processRunning);

    // show if process not running
    bool enableAfterImport = gui_lstFiles->GetItemCount() > 0 && !m_processRunning;

    gui_toolBar->EnableTool(ID_SCAN, enableAfterImport);
    gui_toolBar->EnableTool(ID_CLEAR_LIST, enableAfterImport);

    gui_menuBar->Enable(ID_SCAN, enableAfterImport);
    gui_menuBar->Enable(ID_CLEAR_LIST, enableAfterImport);

    gui_btnStop->Enable(m_processRunning);

    bool enableActions = gui_lstFiles->GetSelectedItemCount() > 0 && !m_processRunning;
    gui_menu->Enable(ID_REMOVE_FILES, enableActions);
    gui_menu->Enable(ID_CLEAR_LIST, enableActions);

    gui_menuBar->Enable(ID_REMOVE_FILES, enableActions);
    gui_menuBar->Enable(ID_REPAIR, enableActions);

    gui_toolBar->EnableTool(ID_REMOVE_FILES, enableActions);
    gui_toolBar->EnableTool(ID_REPAIR, enableActions);
}

void GuiFrameMain::setFilesCmdLine(const wxArrayString &filenames) {
    mp_listManager->insertFilesAndDir(filenames);
}

void GuiFrameMain::processExecute(bool fix) {
    m_processRunning = true;
    updateControls();

    unsigned long int total = gui_lstFiles->GetItemCount();
    unsigned long int fileIdx;
    wxString msg;

    gui_gugProgress->SetRange((int)total);
    for (fileIdx = 0; fileIdx < total; fileIdx++) {
        processFile(fileIdx, fix);
        gui_gugProgress->SetValue((int)fileIdx + 1);

        if (!m_processRunning) {
            msg = _("Do you want to stop process now?");
            if (wxMessageBox(msg, APP_NAME, wxYES_NO | wxICON_QUESTION) == wxYES) {
                fileIdx++;
                break;
            }
            m_processRunning = true;
            gui_btnStop->Enable(true);
        }
    }

    msg = wxString::Format(_("Processed %lu files of %lu."), fileIdx, total);
    wxMessageBox(msg, APP_NAME, wxOK | wxICON_INFORMATION);

    gui_gugProgress->SetValue(0);

    m_processRunning = false;
    updateControls();
}

void GuiFrameMain::processFile(unsigned long int fileIterator, bool fix) {
    // wxSemaphore pc{};
    // auto p = new Process(NULL);

    // p->Redirect();
    // wxExecute(APP_TOOL_EXECUTABLE + _T(" -v"), wxEXEC_NODISABLE | wxEXEC_ASYNC , p);

    // pc.Wait();

    // return;
    FileData &fileData = *(FileData *)gui_lstFiles->GetItemData(fileIterator);

    // Do not process OK MP3's again
    if (fileData.getStateMP3() == STATE_MP3_OK)
        return;

    wxString cmd = APP_TOOL_EXECUTABLE + _T(" \"") + fileData.getFileName().GetFullPath() + _T("\"");

    if (fix)
        cmd += _T(" -f ") + mp_appSettings->getStringToolOptions();

    wxArrayString stdoutString;
    wxExecute(cmd, stdoutString, wxEXEC_NODISABLE | wxEXEC_SYNC);

    // Process output string and updates the list
    fileData.setStateMP3(processOutputString(fileIterator, stdoutString));
    gui_mainStatusBar->SetStatusText(wxString::Format(_("Processed %lu files of %d."), fileIterator + 1, gui_lstFiles->GetItemCount()), 1);
}

int GuiFrameMain::processOutputString(unsigned long int fileIterator, const wxArrayString &inputString) {
    if (inputString.IsEmpty())
        return STATE_MP3_OK;

    int stateMP3 = STATE_MP3_OK;
    int warningCount = 0;

    for (unsigned long int i = 0; i < inputString.GetCount(); i++) {
        wxString tempString = inputString.Item(i);

        if (tempString.Find(_T("MPEG frames")) != wxNOT_FOUND) {
            // Cut the string for: "MPEG frames"
            tempString = tempString.Right(tempString.Len() - tempString.Find(_T("MPEG frames")));

            // Update Version column
            if (tempString.AfterFirst('(').BeforeFirst(')').Find(_T("MPEG")) != wxNOT_FOUND)
                gui_lstFiles->SetItem(fileIterator, ID_LIST_VERSION, tempString.AfterFirst('(').BeforeFirst(')'));

            // Update Tags column
            gui_lstFiles->SetItem(fileIterator, ID_LIST_TAGS, tempString.AfterFirst(',').BeforeFirst(','));

            // Update CBR column
            if (tempString.AfterFirst(',').AfterFirst(',').Find(_T("CBR")) != wxNOT_FOUND)
                gui_lstFiles->SetItem(fileIterator, ID_LIST_CBR, _T("CBR"));
            else
                gui_lstFiles->SetItem(fileIterator, ID_LIST_CBR, _T("VBR"));

            int semicolonAt = tempString.Find("; ");
            if (semicolonAt != -1)
                gui_lstFiles->SetItem(fileIterator, ID_LIST_BITRATE, tempString.substr(semicolonAt + 2));
        }

        if (tempString.StartsWith(_T("WARNING: ")))
            warningCount++;

        if (tempString.Find(_T("tags in the file")) != wxNOT_FOUND)
            warningCount--;

        if (tempString.StartsWith(_T("FIXED: ")))
            stateMP3 = STATE_MP3_FIXED;
    }

    if (stateMP3 == STATE_MP3_OK && warningCount > 0)
        stateMP3 = STATE_MP3_PROBLEM;

    // Update State column
    switch (stateMP3) {
    default:
    case STATE_MP3_OK:
        gui_lstFiles->SetItem(fileIterator, ID_LIST_STATE, _("OK"));
        gui_lstFiles->SetItemTextColour(fileIterator, *wxBLACK);
        break;
    case STATE_MP3_PROBLEM:
        gui_lstFiles->SetItem(fileIterator, ID_LIST_STATE, _("PROBLEM"));
        gui_lstFiles->SetItemTextColour(fileIterator, *wxRED);
        break;
    case STATE_MP3_FIXED:
        gui_lstFiles->SetItem(fileIterator, ID_LIST_STATE, _("FIXED"));
        gui_lstFiles->SetItemTextColour(fileIterator, *wxBLACK);
        break;
    }

    return stateMP3;
}
