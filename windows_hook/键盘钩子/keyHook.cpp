// keyHook.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

#pragma data_seg("Shared")
HHOOK g_hHook2= NULL;
HHOOK g_hHook = NULL;    //钩子
//HWND  g_ExeHwnd = NULL;
#pragma data_seg()
#pragma comment (linker, "/section:Shared,RWS")

extern "C" __declspec(dllexport) bool SetHook(bool isInstall);


HINSTANCE g_Inst;

LRESULT CALLBACK KeyHookProc(int nCode ,WPARAM wParam,LPARAM lParam)  
{  
	if(nCode<0||nCode==HC_NOREMOVE)  
	{ 
		return CallNextHookEx(g_hHook,nCode,wParam,lParam);  
	}  

	if(lParam&0x40000000)//只对WM_DOWN进行响应。  
    {  
     
		char buffer[256]={0};
		GetKeyNameText(lParam,buffer,256);
		MessageBox(0,buffer,0,0);
	}      

    return CallNextHookEx(g_hHook,nCode,wParam,lParam);  
}
 


 bool SetHook(bool IsInstall)
{  
  //  ::g_ExeHwnd=hWnd;//将当前窗口句柄赋给DLL共线段内的窗口句柄。  
    if(IsInstall)  
    {  
        g_hHook=SetWindowsHookEx( WH_KEYBOARD,KeyHookProc,g_Inst,0);  
		return true;  
    }  
    else  
    {  
        UnhookWindowsHookEx(g_hHook);  
        return true;  
    }  
}





BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	g_Inst=(HINSTANCE)hModule;
    return TRUE;
}

