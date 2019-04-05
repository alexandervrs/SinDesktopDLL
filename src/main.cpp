
#ifndef UNICODE
	#undef _UNICODE
#else
	#ifndef _UNICODE
		#define _UNICODE
	#endif
#endif

#define _WIN32_WINNT 0x0500
#define _WIN32_IE 0x0500

#include "main.h"
#include <windows.h>
#include <shlobj.h>
#include <iostream>
#include <vector>

static std::string utf16ToUTF8( const std::wstring &s )
{
    const int size = ::WideCharToMultiByte( CP_UTF8, 0, s.c_str(), -1, NULL, 0, 0, NULL );

    std::vector<char> buf( size );
    ::WideCharToMultiByte( CP_UTF8, 0, s.c_str(), -1, &buf[0], size, 0, NULL );

    return std::string( &buf[0] );
}

static std::wstring utf8ToUTF16(const std::string &utf8)
{
    // Special case of empty input string
	if (utf8.empty()) {
		return std::wstring();
	}

	// Get length (in wchar_t's) of resulting UTF-16 string
	const int utf16_length = ::MultiByteToWideChar(
		CP_UTF8,            // convert from UTF-8
		0,                  // default flags
		utf8.data(),        // source UTF-8 string
		utf8.length(),      // length (in chars) of source UTF-8 string
		NULL,               // unused - no conversion done in this step
		0                   // request size of destination buffer, in wchar_t's
	);

	if (utf16_length == 0) {
		// Error
		DWORD error = ::GetLastError();
		throw ;
	}


	// // Allocate properly sized destination buffer for UTF-16 string
	std::wstring utf16;
	utf16.resize(utf16_length);

	// // Do the actual conversion from UTF-8 to UTF-16
	if ( ! ::MultiByteToWideChar(
		CP_UTF8,            // convert from UTF-8
		0,                  // default flags
		utf8.data(),        // source UTF-8 string
		utf8.length(),      // length (in chars) of source UTF-8 string
		&utf16[0],          // destination buffer
		utf16.length()      // size of destination buffer, in wchar_t's
		) )
	{
		DWORD error = ::GetLastError();
		throw;
	}

	return utf16;
}


char special_directory_buffer[(MAX_PATH*4)+1];

export const char* sin_desktop_get_folder()
{
    wchar_t path[MAX_PATH+1] = {0};
	
    if (SHGetFolderPathW(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, path) != S_OK)
    {
        //MessageBoxW(NULL, L"ERROR in SHGetFolderPathW", L"TEST", MB_OK);
        return NULL;
    }

	wcscat(path, L"\\"); // trailing slash
	
    //MessageBoxW(NULL, path, L"Special Directory", MB_OK);

    int buflen = WideCharToMultiByte(CP_UTF8, 0, path, lstrlenW(path), special_directory_buffer, MAX_PATH*4, NULL, NULL);
    if (buflen <= 0)
    {
        //MessageBoxW(NULL, L"ERROR in WideCharToMultiByte", L"TEST", MB_OK);
        return NULL;
    }

    special_directory_buffer[buflen] = 0;

    return special_directory_buffer;
}

export double sin_desktop_icons_hide()
{
	HWND desk = FindWindowEx(NULL, NULL, L"Progman", NULL); // desktop
	EnableWindow(desk, FALSE);                              // disable the desktop, use TRUE to undo
	ShowWindow(desk, FALSE);                                // hide the desktop use TRUE to undo
	return 1;
}

export double sin_desktop_icons_show()
{
	HWND desk = FindWindowEx(NULL, NULL, L"Progman", NULL); // desktop
	EnableWindow(desk, TRUE);                               // disable the desktop, use TRUE to undo
	ShowWindow(desk, TRUE);                                 // hide the desktop use TRUE to undo
	return 1;
}

export double sin_desktop_get_handle()
{
	HWND desk = FindWindowEx(NULL, NULL, L"Progman", NULL); //desktop
	return (DWORD)desk;
}

export double sin_desktop_taskbar_get_handle()
{
	HWND taskhwnd = FindWindow(L"Shell_traywnd", NULL); //taskbar
	return (DWORD)taskhwnd;
}

export double sin_desktop_startbutton_get_handle()
{
	HWND srthwnd = FindWindowEx(NULL, NULL, L"Button", NULL); //start button
	return (DWORD)srthwnd;
}

export double sin_desktop_taskbar_hide()
{
	HWND taskhwnd = FindWindow(L"Shell_TrayWnd", NULL); //taskbar
	HWND startbt = FindWindowEx(NULL, NULL, L"Button", NULL); //start button

	EnableWindow(taskhwnd, FALSE); //disable the taskbar, use TRUE to undo
	ShowWindow(taskhwnd, FALSE); //hide the taskbar, use TRUE to undo
	EnableWindow(startbt, FALSE); //disable the start button, use TRUE to undo
	ShowWindow(startbt, FALSE); //hide the start button, use TRUE to undo

	return 1;
}

export double sin_desktop_taskbar_show()
{
	HWND taskhwnd = FindWindow(L"Shell_TrayWnd", NULL); //taskbar
	HWND startbt  = FindWindowEx(NULL,NULL,L"Button", NULL); //start button

	EnableWindow(taskhwnd, TRUE); //disable the taskbar, use TRUE to undo
	ShowWindow(taskhwnd, TRUE); //hide the taskbar, use TRUE to undo
	EnableWindow(startbt, TRUE); //disable the start button, use TRUE to undo
	ShowWindow(startbt, TRUE); //hide the start button, use TRUE to undo

	return 1;
}

export double sin_desktop_get_x()
{
	RECT wrect = {0, 0, 0, 0};
	SystemParametersInfo(SPI_GETWORKAREA, 0, &wrect, 0);
	return wrect.left;
}

export double sin_desktop_get_y()
{
	RECT wrect = {0, 0, 0, 0};
	SystemParametersInfo(SPI_GETWORKAREA, 0, &wrect, 0);
	return wrect.top;
}

export double sin_desktop_get_width()
{
	RECT wrect = {0, 0, 0, 0};
	SystemParametersInfo(SPI_GETWORKAREA, 0, &wrect, 0);
	return wrect.right;
}

export double sin_desktop_get_height()
{
	RECT wrect = {0, 0, 0, 0};
	SystemParametersInfo(SPI_GETWORKAREA, 0, &wrect, 0);
	return wrect.bottom;
}

export double sin_desktop_taskbar_get_x()
{
	HWND taskhwnd = FindWindow(L"Shell_traywnd", NULL);
	RECT wrect = {0, 0, 0, 0};

    if (taskhwnd && GetWindowRect(taskhwnd, &wrect)) {
		return wrect.left;
    } else {
		return -1;
	}
	
}

export double sin_desktop_taskbar_get_y()
{
	HWND taskhwnd = FindWindow(L"Shell_traywnd", NULL);
	RECT wrect = {0, 0, 0, 0};

    if (taskhwnd && GetWindowRect(taskhwnd, &wrect)) {
		return wrect.top;
    } else {
		return -1;
	}
	
}

export double sin_desktop_taskbar_get_width()
{
	HWND taskhwnd = FindWindow(L"Shell_traywnd", NULL);
	RECT wrect = {0, 0, 0, 0};

    if (taskhwnd && GetWindowRect(taskhwnd, &wrect)) {
		return wrect.right;
    } else {
		return -1;
	}
	
}

export double sin_desktop_taskbar_get_height()
{
	HWND taskhwnd = FindWindow(L"Shell_traywnd", NULL);
	RECT wrect = {0, 0, 0, 0};

    if (taskhwnd && GetWindowRect(taskhwnd, &wrect)) {
		return wrect.bottom;
    } else {
		return -1;
	}
	
}

export double sin_desktop_is_locked()
{

	wchar_t DesktopName[8] = L"default";

	HDESK hDesktop = OpenDesktop(DesktopName, 0, false, DESKTOP_SWITCHDESKTOP);
	int rtn = 0;
	
	if (hDesktop != 0) {
		rtn = SwitchDesktop(hDesktop);
		if (rtn == 0) {
			// Locked
			CloseDesktop(hDesktop);
			return 1;
		} else {
			// Not locked
			CloseDesktop(hDesktop);
			return 0;
		}
	} else {
		return 0;
	}

}

char wallpaper_buffer[(MAX_PATH*4)+1];

export const char* sin_desktop_get_wallpaper()
{
	
	wchar_t path[MAX_PATH+1] = {0};
	
    SystemParametersInfo(SPI_GETDESKWALLPAPER, MAX_PATH+1, path, 0);

    int buflen = WideCharToMultiByte(CP_UTF8, 0, path, lstrlenW(path), wallpaper_buffer, MAX_PATH*4, NULL, NULL);
    if (buflen <= 0)
    {
        //MessageBoxW(NULL, L"ERROR in WideCharToMultiByte", L"TEST", MB_OK);
        return "";
    }

    wallpaper_buffer[buflen] = 0;

    return wallpaper_buffer;
	
}

double sin_desktop_mode_wallpaper_center = 0;
double sin_desktop_mode_wallpaper_tiled = 1;
double sin_desktop_mode_wallpaper_stretched = 2;

export double sin_desktop_set_wallpaper(char* fname, double mode)
{

	std::string fname_string(fname);

	std::wstring file = utf8ToUTF16(fname_string); 
	std::wstring* filename = &file; // change path to pointer
	
	HRESULT retn = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (LPVOID)filename->c_str(), SPIF_SENDCHANGE | SPIF_UPDATEINIFILE);
	
	std::string WallPaperStyle = "0\0";
	std::string TileWallPaper = "0\0";
	
	if (mode == sin_desktop_mode_wallpaper_stretched) { WallPaperStyle = "2\0"; }
	
	double isTiled = 0;
	if (mode == sin_desktop_mode_wallpaper_tiled) { WallPaperStyle = "1\0"; TileWallPaper = "1\0"; isTiled = 1; }
	
	// string to LPBYTE (unsigned char *)
	unsigned char *val1 = new unsigned char[WallPaperStyle.length()+1];
	strcpy((char *)val1, WallPaperStyle.c_str());
	
	unsigned char *val2 = new unsigned char[TileWallPaper.length()+1];
	strcpy((char *)val2, TileWallPaper.c_str());
	
	//MessageBoxW(NULL, utf8ToUTF16("Wallpaper style is "+WallPaperStyle).c_str(), L"TEST", MB_OK);
	//MessageBoxW(NULL, utf8ToUTF16("Tile wallpaper is "+TileWallPaper).c_str(), L"TEST", MB_OK);
	
	// update registry
	HKEY WallpaperSettings;
	RegOpenKeyEx(HKEY_CURRENT_USER, (LPCWSTR)L"Control Panel\\Desktop", 0, KEY_ALL_ACCESS, &WallpaperSettings);
		RegSetValueEx(WallpaperSettings, (LPCWSTR)L"WallpaperStyle", 0, REG_SZ, (LPBYTE)val1, mode); //0=center, 1=tiled, 2=stretch, 
		RegSetValueEx(WallpaperSettings, (LPCWSTR)L"TileWallpaper", 0, REG_SZ, (LPBYTE)val2, isTiled); // 0=notile, 1=tiled
	RegCloseKey(WallpaperSettings); 
	
	if (retn) {
		// refresh background
		SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, NULL, SPIF_UPDATEINIFILE); 
		return 1;
	} else {
		return 0;
	}
}

export const char* sin_desktop_get_username()
{

	std::wstring username;
	
    wchar_t nbtName[32767];
    DWORD length = 32767;
    GetUserName(nbtName, &length);
    username = nbtName;
	
	std::string utf8String = utf16ToUTF8( username );
	const char* outstring = utf8String.c_str();
	
	return outstring;

}
