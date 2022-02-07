//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/

	{"| ",   "~/ahawer-debian/dwmblocks/scripts/cpu",  	3,		0}, 
       
	{"",  "~/ahawer-debian/dwmblocks/scripts/cputemp",	5,		0},
	
	{"",  "~/ahawer-debian/dwmblocks/scripts/memory",	10,		0},

	{"",   "~/ahawer-debian/dwmblocks/scripts/disk", 	360,		0},

	{"",   "~/ahawer-debian/dwmblocks/scripts/net_on", 	5,		0},
	
	{"",   "~/ahawer-debian/dwmblocks/scripts/network", 	3,		0},

	{"",   "~/ahawer-debian/dwmblocks/scripts/updates", 	5,		0},
	
	{"",   "~/ahawer-debian/dwmblocks/scripts/weather", 	600,		0},
	
/*	{"",   "~/ahawer-debian/dwmblocks/scripts/weather_temp", 	600,		0},*/
	
	{"",   "~/ahawer-debian/dwmblocks/scripts/volume", 	2,		9},

	{"", "date +'  %R    %a. %d. %b. %Y  |'",			2,		0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
