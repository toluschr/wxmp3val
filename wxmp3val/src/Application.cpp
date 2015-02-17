/*
 *	  wxMP3val - A free front-end for MP3val.
 *    Copyright (C) 2011  Cristiano Nunes
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/************************************************************************
 * Name:      wxMP3val
 * Purpose:   A free front-end for MP3val.
 * Author:    Cristiano Nunes (cfgnunes@gmail.com)
 * Created:   2011-01-07
 * Copyright: Copyright (C) 2011 Cristiano Nunes
 * License:   licensed under the GNU General Public License, version 3
 *            http://www.gnu.org/licenses/gpl-3.0.html
 ************************************************************************/

#include "Application.h"
#include "Global.h"
#include "GuiMain.h"

#include <wx/image.h>

IMPLEMENT_APP(Application);

bool Application::OnInit() {
    // Load language translation
    m_locale = new wxLocale(wxLANGUAGE_DEFAULT);
    m_locale->AddCatalogLookupPathPrefix(GetResourceDir() + _T("msg"));
    m_locale->AddCatalog(_T("wxmp3val"));

    wxInitAllImageHandlers();
    GuiMain* guiMain = new GuiMain(0);

    // Read command line files
    m_filesCmdLine = new wxArrayString();
    for (int i = 1; i < argc; i++)
        m_filesCmdLine->Add(wxString(argv[i]));
    guiMain->setFilesCmdLine(*m_filesCmdLine);

    guiMain->Show();
    SetTopWindow(guiMain);
    return true;
}