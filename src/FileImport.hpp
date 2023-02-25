#ifndef _FILE_IMPORT_HPP_
#define _FILE_IMPORT_HPP_

#include <wx/listctrl.h>

class FileImport {
public:
    static int InsertArray(wxListCtrl *list, const wxArrayString &filenames_and_dirnames);
    static int Insert(wxListCtrl *list, const wxString &filename_or_dirname);

private:
    static int InsertSingleFile(wxListCtrl *list, const wxString &filename);
    static int InsertSingleDir(wxListCtrl *list, const wxString &dirname);
};

#endif // _FILE_IMPORT_HPP_