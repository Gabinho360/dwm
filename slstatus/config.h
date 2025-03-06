const unsigned int interval = 1000;

static const char unknown_str[] = "n/a";

#define MAXLEN 2048

static const struct arg args[] = {
	/* function format          argument */
	{ cpu_perc,             "  %s%%",      NULL },
	{ ram_used,             "  %s",         NULL },	
	{ ram_total,             "/%s",         NULL },	
	{ datetime, "  %s",           "%Y-%d-%m %H:%M:%S " },
};
