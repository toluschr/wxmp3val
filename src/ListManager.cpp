/*
 * This file is part of the wxMP3val and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#include "ListManager.hpp"
#include "Constants.hpp"

#include <wx/dir.h>
#include <wx/tokenzr.h>

ListManager::ListManager(wxListCtrl *listCtrl) : mp_listCtrl(listCtrl) {
    // mp_filesData = new std::list<FileData>();
}

ListManager::~ListManager() {
    // delete mp_filesData;
}

void ListManager::insertFilesAndDir(const wxArrayString &filenames) {
    wxArrayString files;

    // Check if is a directory or a file
    for (unsigned long int n = 0; n < filenames.GetCount(); n++) {
        wxString filename = filenames[n];
        if (wxFileName::DirExists(filename))
            insertDir(filename);
        else
            files.Add(filename);
    }
    insertFiles(files);
}

void ListManager::insertFiles(const wxArrayString &filenames) {
    unsigned long int nFiles = filenames.GetCount();

    // Add files in wxListCtrl
    for (unsigned long int n = 0; n < nFiles; n++) {
        wxFileName file(filenames[n]);

        if (file.GetExt().CmpNoCase("mp3") != 0)
            continue;

        // Don't insert repeated filenames
        bool duplicate = false;
        int foundAt = -1;
        while ((foundAt = mp_listCtrl->FindItem(-1, file.GetFullName())) != wxNOT_FOUND) {
            if (((FileData *)mp_listCtrl->GetItemData(foundAt))->getFileName().SameAs(file)) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate) {
            int idx = mp_listCtrl->GetItemCount();
            mp_listCtrl->InsertItem(idx, file.GetFullName());
            mp_listCtrl->SetItem(idx, ID_LIST_FOLDER, file.GetPath());
            mp_listCtrl->SetItemPtrData(idx, (wxUIntPtr)new FileData(file));
        }
    }
}

void ListManager::insertDir(const wxString &dirname) {
    wxArrayString files;
    wxDir::GetAllFiles(dirname, &files);

    insertFiles(files);
}
