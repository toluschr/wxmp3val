/*
 * This file is part of the wxMP3val and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef LIST_MANAGER_HPP
#define LIST_MANAGER_HPP

#include "FileData.hpp"

#include <list>
#include <wx/arrstr.h>
#include <wx/filename.h>
#include <wx/listctrl.h>

class ListManager {
  public:
    ListManager(wxListCtrl *listCtrl);
    virtual ~ListManager();

    void insertFilesAndDir(const wxArrayString &filenames);
    void insertFiles(const wxArrayString &filenames);
    void insertFile(const wxString &filename);
    void insertDir(const wxString &dirname);

  private:
    wxListCtrl *mp_listCtrl;
};

#endif // LIST_MANAGER_HPP
