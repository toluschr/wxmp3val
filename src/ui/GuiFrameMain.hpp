/*
 * This file is part of the wxMP3val and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef GUI_FRAME_MAIN_HPP
#define GUI_FRAME_MAIN_HPP

#include "../AppSettings.hpp"
#include "Gui.h"

#include <wx/dnd.h>

class GuiFrameMain : public FrameMain/*, public wxFileDropTarget */{
  public:
    GuiFrameMain(wxWindow *parent);
    virtual ~GuiFrameMain();

    void setFilesCmdLine(const wxArrayString &filenames);
    // virtual bool OnDropFiles(wxCoord, wxCoord, const wxArrayString &filenames);

  protected:
    void OnlstFilesDeleteItem(wxListEvent &event);
    void OnlstFilesInsertItem(wxListEvent &event);
    void OnlstFilesItemSelect(wxListEvent &event);
    void OnlstFilesItemRClick(wxListEvent &event);
    void OnlstFilesKeyDown(wxListEvent &event);
    void OnlstFilesColClick(wxListEvent& event);
    void OnlstFilesItemActivated(wxListEvent &event);

    void btnProcessStop(wxCommandEvent &event);
    void mnuAddDirectory(wxCommandEvent &event);
    void mnuAddFiles(wxCommandEvent &event);
    void mnuExit(wxCommandEvent &event);
    void mnuRemoveFiles(wxCommandEvent &event);
    void mnuClearList(wxCommandEvent &event);
    void mnuSettings(wxCommandEvent &event);
    void mnuScan(wxCommandEvent &event);
    void mnuRepair(wxCommandEvent &event);
    void mnuWebsite(wxCommandEvent &event);
    void mnuToolWebsite(wxCommandEvent &event);
    void mnuAbout(wxCommandEvent &event);
    void mnuOpenFolder(wxCommandEvent &event);

  private:
    void updateControls();
    void loadResources();
    void processExecute(bool fix);
    void processFile(unsigned long int fileIterator, bool fix);
    int processOutputString(unsigned long int fileIterator, const wxArrayString &inputString);

    int m_lastSortCol = -1;
    AppSettings *mp_appSettings;
    // FileDrop *mp_fileDrop;
    // int m_processType;
    bool m_processRunning;
};

#endif // GUI_FRAME_MAIN_HPP
