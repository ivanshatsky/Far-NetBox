/**************************************************************************
 *  NetBox plugin for FAR 2.0 (http://code.google.com/p/farplugs)         *
 *  Copyright (C) 2011 by Artem Senichev <artemsen@gmail.com>             *
 *  Copyright (C) 2011 by Michael Lukashov <michael.lukashov@gmail.com>   *
 *                                                                        *
 *  This program is free software: you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by  *
 *  the Free Software Foundation, either version 3 of the License, or     *
 *  (at your option) any later version.                                   *
 *                                                                        *
 *  This program is distributed in the hope that it will be useful,       *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *  GNU General Public License for more details.                          *
 *                                                                        *
 *  You should have received a copy of the GNU General Public License     *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 **************************************************************************/

#include "FarTexts.h"

#ifdef _AFXDLL
#include "afxdll.h"
#endif

#include "stdafx.h"
#include "EasyURL.h"
#include "resource.h"
#include "Common.h"

//---------------------------------------------------------------------------
extern TCustomFarPlugin *CreateFarPlugin(HINSTANCE HInst);

//---------------------------------------------------------------------------
class TFarPluginGuard : public TFarPluginEnvGuard, public TGuard
{
public:
  inline TFarPluginGuard() :
    TGuard(FarPlugin->GetCriticalSection())
  {
  }
};

//---------------------------------------------------------------------------
extern "C"
{

int WINAPI GetMinFarVersionW()
{
    assert(FarPlugin);
    TFarPluginGuard Guard;
    return FarPlugin->GetMinFarVersion();
}

void WINAPI SetStartupInfoW(const struct PluginStartupInfo *psi)
{
    assert(FarPlugin);
    TFarPluginGuard Guard;
    CFarPlugin::Initialize(psi);

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    curl_global_init(CURL_GLOBAL_ALL);
    FarPlugin->SetStartupInfo(psi);
}

void WINAPI ExitFARW()
{
    assert(FarPlugin);
    TFarPluginGuard Guard;
    curl_global_cleanup();
    WSACleanup();

    FarPlugin->ExitFAR();
}

void WINAPI GetPluginInfoW(PluginInfo *pi)
{
    assert(FarPlugin);
    TFarPluginGuard Guard;
    FarPlugin->GetPluginInfo(pi);
}

int WINAPI ConfigureW(int item)
{
    assert(FarPlugin);
    TFarPluginGuard Guard;
    return FarPlugin->Configure(item);
}

HANDLE WINAPI OpenPluginW(int openFrom, INT_PTR item)
{
  assert(FarPlugin);
  TFarPluginGuard Guard;
  return FarPlugin->OpenPlugin(openFrom, item);
}

void WINAPI ClosePluginW(HANDLE plugin)
{
    assert(FarPlugin);
    TFarPluginGuard Guard;
    FarPlugin->ClosePlugin(plugin);
}

void WINAPI GetOpenPluginInfoW(HANDLE plugin, OpenPluginInfo *pluginInfo)
{
    assert(FarPlugin);
    TFarPluginGuard Guard;
    FarPlugin->GetOpenPluginInfo(plugin, pluginInfo);
}

int WINAPI GetFindDataW(HANDLE plugin, PluginPanelItem **panelItem, int *itemsNumber, int opMode)
{
    assert(FarPlugin);
    TFarPluginGuard Guard;
    return FarPlugin->GetFindData(plugin, panelItem, itemsNumber, opMode);
}

void WINAPI FreeFindDataW(HANDLE plugin, PluginPanelItem *panelItem, int itemsNumber)
{
    assert(FarPlugin);
    TFarPluginGuard Guard;
    FarPlugin->FreeFindData(plugin, panelItem, itemsNumber);
}

int WINAPI ProcessHostFileW(HANDLE Plugin,
  struct PluginPanelItem * PanelItem, int ItemsNumber, int OpMode)
{
  assert(FarPlugin);
  TFarPluginGuard Guard;
  return FarPlugin->ProcessHostFile(Plugin, PanelItem, ItemsNumber, OpMode);
}

int WINAPI ProcessKeyW(HANDLE plugin, int key, unsigned int controlState)
{
    assert(FarPlugin);
    TFarPluginGuard Guard;
    return FarPlugin->ProcessKey(plugin, key, controlState);
}

int WINAPI ProcessEventW(HANDLE Plugin, int Event, void * Param)
{
    assert(FarPlugin);
    TFarPluginGuard Guard;
    return FarPlugin->ProcessEvent(Plugin, Event, Param);
}

int WINAPI SetDirectoryW(HANDLE plugin, const wchar_t *dir, int opMode)
{
    DEBUG_PRINTF(L"begin, dir = %s", dir);
    assert(FarPlugin);
    TFarPluginGuard Guard;
    int result = FarPlugin->SetDirectory(plugin, dir, opMode);
    DEBUG_PRINTF(L"end, result = %d", result);
    return result;
}

int WINAPI MakeDirectoryW(HANDLE plugin, const wchar_t **name, int opMode)
{
    DEBUG_PRINTF(L"begin, name = %s", *name);
    assert(FarPlugin);
    TFarPluginGuard Guard;
    int result = FarPlugin->MakeDirectory(plugin, (wchar_t *)*name, opMode);
    DEBUG_PRINTF(L"end, result = %d", result);
    return result;
}

int WINAPI DeleteFilesW(HANDLE plugin, PluginPanelItem *panelItem, int itemsNumber, int opMode)
{
    assert(FarPlugin);
    TFarPluginGuard Guard;
    return FarPlugin->DeleteFiles(plugin, panelItem, itemsNumber, opMode);
}

int WINAPI GetFilesW(HANDLE plugin, PluginPanelItem *panelItem, int itemsNumber,
    int move, const wchar_t **destPath, int opMode)
{
    assert(FarPlugin);
    TFarPluginGuard Guard;
    return FarPlugin->GetFiles(plugin, panelItem, itemsNumber,
        move, destPath, opMode);
}

int WINAPI PutFilesW(HANDLE plugin, PluginPanelItem *panelItem, int itemsNumber, int move, const wchar_t *srcPath, int opMode)
{
    DEBUG_PRINTF(L"begin, srcPath = %s", srcPath);
    assert(FarPlugin);
    TFarPluginGuard Guard;
    int result = FarPlugin->PutFiles(plugin, panelItem, itemsNumber,
        move, opMode);
    DEBUG_PRINTF(L"end, result = %d", result);
    return result;
}

int WINAPI ProcessEditorEventW(int Event, void * Param)
{
    assert(FarPlugin);
    TFarPluginGuard Guard;
    return FarPlugin->ProcessEditorEvent(Event, Param);
}

int WINAPI ProcessEditorInputW(const INPUT_RECORD *Rec)
{
    assert(FarPlugin);
    TFarPluginGuard Guard;
    return FarPlugin->ProcessEditorInput(Rec);
}

HANDLE WINAPI OpenFilePluginW(const wchar_t *fileName, const unsigned char *fileHeader, int fileHeaderSize, int /*opMode*/)
{
    assert(FarPlugin);
    TFarPluginGuard Guard;
    if (!fileName)
    {
        return INVALID_HANDLE_VALUE;
    }

    const size_t fileNameLen = wcslen(fileName);
    if (fileNameLen < 8 || _wcsicmp(fileName + fileNameLen - 7, L".netbox") != 0)
    {
        return INVALID_HANDLE_VALUE;
    }
    if (fileHeaderSize > 4 && strncmp(reinterpret_cast<const char *>(fileHeader), "<?xml", 5) != 0)
    {
        return INVALID_HANDLE_VALUE;
    }
    /*
    PSession session = CSession::Load(fileName);
    if (!session.get())
    {
        return INVALID_HANDLE_VALUE;
    }
    PProtocol proto = session->CreateClient();
    if (!proto.get())
    {
        return reinterpret_cast<HANDLE>(-2);
    }
    CPanel *panelInstance = new CPanel(false);
    if (panelInstance->OpenConnection(proto.get()))
    {
        proto.release();
        m_PanelInstances.push_back(panelInstance);
        return panelInstance;
    }
    */
    return reinterpret_cast<HANDLE>(-2);
}

//---------------------------------------------------------------------------
static int Processes = 0;
//---------------------------------------------------------------------------
void DllProcessAttach(HINSTANCE HInst)
{
    // DEBUG_PRINTF(L"HInst = %u", HInst);
    FarPlugin = CreateFarPlugin(HInst);

    assert(!Processes);
    Processes++;
#ifdef _AFXDLL
    InitExtensionModule(HInst);
#endif
 // DEBUG_PRINTF(L"DllProcessAttach: end");
}

//---------------------------------------------------------------------------
void DllProcessDetach()
{
  // DEBUG_PRINTF(L"DllProcessDetach: start");
  assert(Processes);
  Processes--;
  if (!Processes)
  {
    assert(FarPlugin);
    SAFE_DESTROY(FarPlugin);
#ifdef _AFXDLL
    TermExtensionModule();
#endif
  }
  // DEBUG_PRINTF(L"DllProcessDetach: end");
}

//---------------------------------------------------------------------------
BOOL WINAPI DllMain(HINSTANCE HInst, DWORD Reason, LPVOID /*ptr*/ )
{
  // DEBUG_PRINTF(L"DllEntryPoint: start");
  switch (Reason)
  {
    case DLL_PROCESS_ATTACH:
      DllProcessAttach(HInst);
      break;

    case DLL_PROCESS_DETACH:
      DllProcessDetach();
      break;
  }
  // DEBUG_PRINTF(L"DllEntryPoint: end");
  return true;
}

}
