#define sinDesktopDefine
/* SIN DESKTOP DLL | VERSION 1.2.0 */

/* initialize the DLL, call this script before you use any functions from the DLL */

//DLL Path
var_sin_desktop_dll = working_directory + "\sin-desktop.dll";


//Declare functions available
global.var_sin_desktop_get_folder = external_define(var_sin_desktop_dll, "sin_desktop_get_folder", dll_cdecl, ty_string, 0);

global.var_sin_desktop_get_wallpaper = external_define(var_sin_desktop_dll, "sin_desktop_get_wallpaper", dll_cdecl, ty_string, 0);
global.var_sin_desktop_set_wallpaper = external_define(var_sin_desktop_dll, "sin_desktop_set_wallpaper", dll_cdecl, ty_real, 2, ty_string, ty_real);

global.var_sin_desktop_get_x = external_define(var_sin_desktop_dll, "sin_desktop_get_x", dll_cdecl, ty_real, 0);
global.var_sin_desktop_get_y = external_define(var_sin_desktop_dll, "sin_desktop_get_y", dll_cdecl, ty_real, 0);
global.var_sin_desktop_get_width = external_define(var_sin_desktop_dll, "sin_desktop_get_width", dll_cdecl, ty_real, 0);
global.var_sin_desktop_get_height = external_define(var_sin_desktop_dll, "sin_desktop_get_height", dll_cdecl, ty_real, 0);

global.var_sin_desktop_taskbar_get_x = external_define(var_sin_desktop_dll, "sin_desktop_taskbar_get_x", dll_cdecl, ty_real, 0);
global.var_sin_desktop_taskbar_get_y = external_define(var_sin_desktop_dll, "sin_desktop_taskbar_get_y", dll_cdecl, ty_real, 0);
global.var_sin_desktop_taskbar_get_width = external_define(var_sin_desktop_dll, "sin_desktop_taskbar_get_width", dll_cdecl, ty_real, 0);
global.var_sin_desktop_taskbar_get_height = external_define(var_sin_desktop_dll, "sin_desktop_taskbar_get_height", dll_cdecl, ty_real, 0);

global.var_sin_desktop_taskbar_hide = external_define(var_sin_desktop_dll, "sin_desktop_taskbar_hide", dll_cdecl, ty_real, 0);
global.var_sin_desktop_taskbar_show = external_define(var_sin_desktop_dll, "sin_desktop_taskbar_show", dll_cdecl, ty_real, 0);

global.var_sin_desktop_icons_hide = external_define(var_sin_desktop_dll, "sin_desktop_icons_hide", dll_cdecl, ty_real, 0);
global.var_sin_desktop_icons_show = external_define(var_sin_desktop_dll, "sin_desktop_icons_show", dll_cdecl, ty_real, 0);

global.var_sin_desktop_is_locked = external_define(var_sin_desktop_dll, "sin_desktop_is_locked", dll_cdecl, ty_real, 0);

global.var_sin_desktop_get_handle = external_define(var_sin_desktop_dll, "sin_desktop_get_handle", dll_cdecl, ty_real, 0);
global.var_sin_desktop_taskbar_get_handle = external_define(var_sin_desktop_dll, "sin_desktop_taskbar_get_handle", dll_cdecl, ty_real, 0);
global.var_sin_desktop_startbutton_get_handle = external_define(var_sin_desktop_dll, "sin_desktop_startbutton_get_handle", dll_cdecl, ty_real, 0);

global.var_sin_desktop_get_username = external_define(var_sin_desktop_dll, "sin_desktop_get_username", dll_cdecl, ty_string, 0);

#define sinDesktopGetFolder

return external_call(global.var_sin_desktop_get_folder);

#define sinDesktopGetHandle

return external_call(global.var_sin_desktop_get_handle);

#define sinDesktopGetHeight

return external_call(global.var_sin_desktop_get_height);

#define sinDesktopStartButtonGetHandle

return external_call(global.var_sin_desktop_startbutton_get_handle);

#define sinDesktopTaskbarGetHandle

return external_call(global.var_sin_desktop_taskbar_get_handle);

#define sinDesktopGetWallpaper

return external_call(global.var_sin_desktop_get_wallpaper);

#define sinDesktopGetWidth

return external_call(global.var_sin_desktop_get_width);

#define sinDesktopGetX

return external_call(global.var_sin_desktop_get_x);

#define sinDesktopGetY

return external_call(global.var_sin_desktop_get_y);

#define sinDesktopIconsHide

return external_call(global.var_sin_desktop_icons_hide);

#define sinDesktopIconsShow

return external_call(global.var_sin_desktop_icons_show);

#define sinDesktopIsLocked

return external_call(global.var_sin_desktop_is_locked);

#define sinDesktopSetWallpaper

return external_call(global.var_sin_desktop_set_wallpaper, argument[0], argument[1]);

#define sinDesktopTaskbarGetHeight

return external_call(global.var_sin_desktop_taskbar_get_height);

#define sinDesktopTaskbarGetWidth

return external_call(global.var_sin_desktop_taskbar_get_width);

#define sinDesktopTaskbarGetX

return external_call(global.var_sin_desktop_taskbar_get_x);

#define sinDesktopTaskbarGetY

return external_call(global.var_sin_desktop_taskbar_get_y);

#define sinDesktopTaskbarHide

return external_call(global.var_sin_desktop_taskbar_hide);

#define sinDesktopTaskbarShow

return external_call(global.var_sin_desktop_taskbar_show);

#define sinDesktopGetUsername

return external_call(global.var_sin_desktop_get_username);

