const unsigned int interval = 1000;

static const char unknown_str[] = "n/a";

#define MAXLEN 2048

static const struct arg args[] = {
	/* function format          argument */
	{ cpu_perc, "  %s%%", NULL },
	{ ram_used, "  %s", NULL },
	{ ram_total, "/%s", NULL },
//	{ battery_perc, "  %s%%", "BAT0" },
//      { wifi_essid, "  %s", "wlp0s20f3" },
//	{ datetime, "  %s", "%d/%m/%Y 󰥔 %H:%M 󰣇 " },
	{ datetime, "  %s", "%d/%m/%Y 󰥔 %H:%M:%S 󰣇 " },
};
