#include "FileImport.hpp"
#include "FileData.hpp"

#include "Constants.hpp"

#include <wx/filename.h>
#include <wx/dir.h>

int FileImport::InsertArray(wxListCtrl *list, const wxArrayString &filenames_and_dirnames)
{
    int error_count = 0;
    for (size_t i = 0; i < filenames_and_dirnames.GetCount(); i++) {
        error_count += FileImport::Insert(list, filenames_and_dirnames[i]);
    }

    return error_count;
}

int FileImport::Insert(wxListCtrl *list, const wxString &filename_or_dirname)
{
    // XXX handle symbolic links (not a problem here only care about windows atm)
    if (wxDir::Exists(filename_or_dirname)) {
        return FileImport::InsertSingleDir(list, filename_or_dirname);
    }

    if (wxFile::Exists(filename_or_dirname)) {
        return FileImport::InsertSingleFile(list, filename_or_dirname);
    }

    return 1;
}

int FileImport::InsertSingleDir(wxListCtrl *list, const wxString &dirname)
{
    wxDir dir{dirname};

    int error_count = 0;
    wxString filename_or_dirname;

    for (bool r = dir.GetFirst(&filename_or_dirname, "", wxDIR_FILES | wxDIR_DIRS | wxDIR_HIDDEN); r != false; r = dir.GetNext(&filename_or_dirname)) {
        error_count += FileImport::Insert(list, dirname + _T("/") + filename_or_dirname);
    }

    return error_count;
}

int FileImport::InsertSingleFile(wxListCtrl *list, const wxString &filename)
{
    wxFileName file{filename};
    if (file.GetExt().CmpNoCase("mp3") != 0) {
        return 1;
    }

    // XXX Don't insert repeated filenames
    int idx = list->GetItemCount();
    list->InsertItem(idx, file.GetFullName());
    list->SetItem(idx, ID_LIST_FOLDER, file.GetPath());
    list->SetItemPtrData(idx, (wxUIntPtr)new FileData(file));
    return 0;
}
