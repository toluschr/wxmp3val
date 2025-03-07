/*
 * This file is part of the wxMP3val and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/string.h>

const wxString APP_NAME = _T("wxMP3val");
const wxString APP_VERSION = _T("4.1");
const wxString APP_NAME_WITH_VERSION = APP_NAME + _T(" v") + APP_VERSION;

const wxString APP_COPYRIGHT = _T("(C) 2011-2023 Cristiano Fraga G. Nunes <cfgnunes@gmail.com>");
const wxString APP_WEBSITE = _T("https://github.com/cfgnunes/wxmp3val");

const wxString APP_TOOL_EXECUTABLE = _T("mp3val");
const wxString APP_WILDCARD_EXT = _T("MP3 files (*.mp3)|*.mp3;*.MP3");
const wxString APP_OPEN_EXT = _T("mp3");

enum ProcessTypeValues {
    TOOL_SCAN,
    TOOL_FIX
};

enum StateMP3Values {
    STATE_MP3_OK,
    STATE_MP3_PROBLEM,
    STATE_MP3_FIXED,
    STATE_MP3_UNKNOWN
};

// Config Group Strings
const wxString CONFIG_GROUP_SYSTEM = _T("/System/");
const wxString CONFIG_GROUP_GENERAL = _T("/General/");

// Config Strings
const wxString CONFIG_STR_AppVersion = _T("AppVersion");
const wxString CONFIG_STR_LastOpenDir = _T("LastOpenDir");

const wxString CONFIG_STR_DeleteBackup = _T("DeleteBackup");

// Default Values
const wxString DEFAULT_VALUE_LastOpenDir = wxFileName::GetHomeDir();
const bool DEFAULT_VALUE_DeleteBackup = true;

// ID for title in wxListCtrl
int const ID_LIST_FILE = 0;
int const ID_LIST_FOLDER = 1;
int const ID_LIST_VERSION = 2;
int const ID_LIST_TAGS = 3;
int const ID_LIST_CBR = 4;
int const ID_LIST_BITRATE = 5;
int const ID_LIST_STATE = 6;

inline wxString getDataDir() {
    wxString executablePath = wxStandardPaths::Get().GetExecutablePath();
    wxFileName executableFilename(executablePath);
    wxString dataDirName = _T("/data/");
    wxDir dir;
    wxString dataDir;

#ifdef __LINUX__
    dataDir = _T("/usr/share/wxlame") + dataDirName;
    if (dir.Exists(dataDir))
        return dataDir;
#endif

    dataDir = _T(".") + dataDirName;
    if (dir.Exists(dataDir))
        return dataDir;

    dataDir = _T("..") + dataDirName;
    if (dir.Exists(dataDir))
        return dataDir;

    return executableFilename.GetPath() + dataDirName;
}

#endif // CONSTANTS_HPP
