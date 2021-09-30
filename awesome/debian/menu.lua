-- automatically generated file. Do not edit (see /usr/share/doc/menu/html)

local awesome = awesome

Debian_menu = {}

Debian_menu["Debian_Hjælp"] = {
	{"Xman","xman"},
}
Debian_menu["Debian_Programmer_Filhåndtering"] = {
	{"Back In Time","/usr/bin/backintime"},
	{"Back In Time (root)","/usr/bin/su-to-root -X -c /usr/bin/backintime"},
}
Debian_menu["Debian_Programmer_Fremvisere"] = {
	{"Xditview","xditview"},
}
Debian_menu["Debian_Programmer_Grafik"] = {
	{"dotty","/usr/bin/dotty"},
	{"lefty","/usr/bin/lefty"},
	{"X Window Snapshot","xwd | xwud"},
}
Debian_menu["Debian_Programmer_Kommandoskaller"] = {
	{"Bash", "x-terminal-emulator -e ".."/bin/bash --login"},
	{"Dash", "x-terminal-emulator -e ".."/bin/dash -i"},
	{"fish", "x-terminal-emulator -e ".."/usr/bin/fish"},
	{"Sh", "x-terminal-emulator -e ".."/bin/sh --login"},
}
Debian_menu["Debian_Programmer_Netværk_Internetbrowsere"] = {
	{"Dillo","/usr/bin/dillo","/usr/share/pixmaps/dillo.xpm"},
	{"Qutebrowser","qutebrowser","/usr/share/pixmaps/qutebrowser.xpm"},
	{"w3m", "x-terminal-emulator -e ".."/usr/bin/w3m /usr/share/doc/w3m/MANUAL.html"},
}
Debian_menu["Debian_Programmer_Netværk_Kommunikation"] = {
	{"Xbiff","xbiff"},
}
Debian_menu["Debian_Programmer_Netværk"] = {
	{ "Internetbrowsere", Debian_menu["Debian_Programmer_Netværk_Internetbrowsere"] },
	{ "Kommunikation", Debian_menu["Debian_Programmer_Netværk_Kommunikation"] },
}
Debian_menu["Debian_Programmer_System_Administration"] = {
	{"Debian Task selector", "x-terminal-emulator -e ".."su-to-root -c tasksel"},
	{"Editres","editres"},
	{"Logout (obsession)","/usr/bin/obsession-logout"},
	{"Xclipboard","xclipboard"},
	{"Xfontsel","xfontsel"},
	{"Xkill","xkill"},
	{"Xrefresh","xrefresh"},
	{"xxkb","/usr/bin/xxkb"},
}
Debian_menu["Debian_Programmer_System_Hardware"] = {
	{"Xvidtune","xvidtune"},
}
Debian_menu["Debian_Programmer_System_Overvågning"] = {
	{"Pstree", "x-terminal-emulator -e ".."/usr/bin/pstree.x11","/usr/share/pixmaps/pstree16.xpm"},
	{"Top", "x-terminal-emulator -e ".."/usr/bin/top"},
	{"Xconsole","xconsole -file /dev/xconsole"},
	{"Xev","x-terminal-emulator -e xev"},
	{"Xload","xload"},
}
Debian_menu["Debian_Programmer_System_Pakkehåndtering"] = {
	{"Synaptic Package Manager","x-terminal-emulator -e synaptic-pkexec","/usr/share/synaptic/pixmaps/synaptic_32x32.xpm"},
}
Debian_menu["Debian_Programmer_System"] = {
	{ "Administration", Debian_menu["Debian_Programmer_System_Administration"] },
	{ "Hardware", Debian_menu["Debian_Programmer_System_Hardware"] },
	{ "Overvågning", Debian_menu["Debian_Programmer_System_Overvågning"] },
	{ "Pakkehåndtering", Debian_menu["Debian_Programmer_System_Pakkehåndtering"] },
}
Debian_menu["Debian_Programmer_Tekst"] = {
	{"Fortune","sh -c 'while /usr/games/fortune | col -x | xmessage -center -buttons OK:1,Another:0 -default OK -file - ; do :; done'"},
	{"hspell-gui","/usr/bin/hspell-gui"},
	{"hspell-gui (Hebrew UI)","/usr/bin/hspell-gui-heb"},
}
Debian_menu["Debian_Programmer_Tekstredigering"] = {
	{"Xedit","xedit"},
}
Debian_menu["Debian_Programmer_Terminalemulatorer"] = {
	{"Multilingual Terminal (client)","/usr/bin/mlclient","/usr/share/pixmaps/mlterm-icon-24colors-1.xpm"},
	{"Multilingual Terminal (daemon)","/usr/bin/mlterm -j=genuine","/usr/share/pixmaps/mlterm-icon-24colors-1.xpm"},
	{"Multilingual Terminal (normal)","/usr/bin/mlterm","/usr/share/pixmaps/mlterm-icon-24colors-1.xpm"},
	{"xiterm+thai","/usr/bin/txiterm -ls"},
}
Debian_menu["Debian_Programmer_Tilgængelighed"] = {
	{"Xmag","xmag"},
}
Debian_menu["Debian_Programmer_Videnskab_Matematik"] = {
	{"Bc", "x-terminal-emulator -e ".."/usr/bin/bc"},
	{"galculator","/usr/bin/galculator","/usr/share/pixmaps/galculator.xpm"},
	{"Xcalc","xcalc"},
}
Debian_menu["Debian_Programmer_Videnskab"] = {
	{ "Matematik", Debian_menu["Debian_Programmer_Videnskab_Matematik"] },
}
Debian_menu["Debian_Programmer"] = {
	{ "Filhåndtering", Debian_menu["Debian_Programmer_Filhåndtering"] },
	{ "Fremvisere", Debian_menu["Debian_Programmer_Fremvisere"] },
	{ "Grafik", Debian_menu["Debian_Programmer_Grafik"] },
	{ "Kommandoskaller", Debian_menu["Debian_Programmer_Kommandoskaller"] },
	{ "Netværk", Debian_menu["Debian_Programmer_Netværk"] },
	{ "System", Debian_menu["Debian_Programmer_System"] },
	{ "Tekst", Debian_menu["Debian_Programmer_Tekst"] },
	{ "Tekstredigering", Debian_menu["Debian_Programmer_Tekstredigering"] },
	{ "Terminalemulatorer", Debian_menu["Debian_Programmer_Terminalemulatorer"] },
	{ "Tilgængelighed", Debian_menu["Debian_Programmer_Tilgængelighed"] },
	{ "Videnskab", Debian_menu["Debian_Programmer_Videnskab"] },
}
Debian_menu["Debian_Skærm_Lås"] = {
	{"Lock Screen (XScreenSaver)","/usr/bin/xscreensaver-command -lock"},
}
Debian_menu["Debian_Skærm_Pauseskærm"] = {
	{"Activate ScreenSaver (Next)","/usr/bin/xscreensaver-command -next"},
	{"Activate ScreenSaver (Previous)","/usr/bin/xscreensaver-command -prev"},
	{"Activate ScreenSaver (Random)","/usr/bin/xscreensaver-command -activate"},
	{"Demo Screen Hacks","/usr/bin/xscreensaver-command -demo"},
	{"Disable XScreenSaver","/usr/bin/xscreensaver-command -exit"},
	{"Enable XScreenSaver","/usr/bin/xscreensaver"},
	{"Reinitialize XScreenSaver","/usr/bin/xscreensaver-command -restart"},
	{"ScreenSaver Preferences","/usr/bin/xscreensaver-command -prefs"},
}
Debian_menu["Debian_Skærm"] = {
	{ "Lås", Debian_menu["Debian_Skærm_Lås"] },
	{ "Pauseskærm", Debian_menu["Debian_Skærm_Pauseskærm"] },
}
Debian_menu["Debian_Spil_Legetøj"] = {
	{"Oclock","oclock"},
	{"Xclock (analog)","xclock -analog"},
	{"Xclock (digital)","xclock -digital -update 1"},
	{"Xeyes","xeyes"},
	{"Xlogo","xlogo"},
}
Debian_menu["Debian_Spil"] = {
	{ "Legetøj", Debian_menu["Debian_Spil_Legetøj"] },
}
Debian_menu["Debian_Vindueshåndteringer"] = {
	{"awesome",function () awesome.exec("/usr/bin/awesome") end,"/usr/share/pixmaps/awesome.xpm"},
	{"Xmonad",function () awesome.exec("/usr/bin/xmonad") end},
}
Debian_menu["Debian"] = {
	{ "Hjælp", Debian_menu["Debian_Hjælp"] },
	{ "Programmer", Debian_menu["Debian_Programmer"] },
	{ "Skærm", Debian_menu["Debian_Skærm"] },
	{ "Spil", Debian_menu["Debian_Spil"] },
	{ "Vindueshåndteringer", Debian_menu["Debian_Vindueshåndteringer"] },
}

debian = { menu = { Debian_menu = Debian_menu } }
return debian