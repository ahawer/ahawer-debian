/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 2500;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cpu_perc            cpu usage in percent            NULL
 * cpu_freq            cpu frequency in MHz            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/")
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * separator           string to echo                  NULL
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 *                                                     NULL on OpenBSD
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 */
static const struct arg args[] = {
	/* function format          argument */
/*	{ cpu_perc,	"^c#98c379^ |   %s%%  | ",  NULL  },
	{ ram_used,	"^c#655eed^  %s  | ",  NULL  },
	{ disk_free,	"^c#E06C75^   / %s   ",  "/" },
	{ disk_free,	"^c#E06C75^ ~ %s  | ",  "/home/andreas/" }, */
/*	{ netspeed_rx,	"^c#56B6C2^ > %sB/s ", "eno1" },
        { netspeed_tx,	"^c#56B6C2^ < %sB/s | ", "eno1" }, */
        { run_command,  "^c#98c379^|%2s  ", "/home/andreas/ahawer-debian/dwmblocks/scripts/cpu" }, 
        { run_command,  "^c#98c379^%2s | ", "/home/andreas/ahawer-debian/dwmblocks/scripts/cputemp" }, 
        { run_command,  "^c#655eed^%2s | ", "/home/andreas/ahawer-debian/dwmblocks/scripts/memory" }, 
        { run_command,  "^c#E06C75^%2s | ", "/home/andreas/ahawer-debian/dwmblocks/scripts/disk" }, 
        { run_command,  "^c#56B6C2^%2s  ", "/home/andreas/ahawer-debian/dwmblocks/scripts/net_on" }, 
        { run_command,  "^c#56B6C2^%2s | ", "/home/andreas/ahawer-debian/dwmblocks/scripts/network" }, 
	{ run_command,  "^c#e5c07b^%2s | ", "/home/andreas/ahawer-debian/dwmblocks/scripts/weather" },  /* "sed 24q /home/andreas/.config/weather.txt | grep value | awk '{print $2" "$3" "$4" "$5}'" }, */
	{ run_command,  "^c#33b03f^%2s | ", "/home/andreas/ahawer-debian/dwmblocks/scripts/updates" },  /* "sed 24q /home/andreas/.config/weather.txt | grep value | awk '{print $2" "$3" "$4" "$5}'" }, */
       /* { run_command,  "^c#ABB2BF^   %2s | ", "sed 24q /home/andreas/.config/weather.txt | grep temp_C | awk '{print $2}' | sed 's/,/ C/g'" }, */
	{ run_command,	"^c#be83f3^     %2s | ", "amixer sget Master | awk -F\"[][]\" '/%/ { print $2 }' | head -n1" },	
/*	{ datetime,	"^c#61afef^ %s",	"%a, %b %d,  %R | " },  */
        { run_command,  "^c#61afef^ %s",	"date +'    %R    %a. %d. %b. %Y  |'" },
};		
