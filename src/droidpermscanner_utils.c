/*
 * droidpermscanner_utils.c
 * This file is part of <droidpermscanner>
 *
 * Copyright (C) 2012 - Tom Brennan.
 *
 * <droidpermscanner> is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * <droidpermscanner> is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with <droidpermscanner>. If not, see <http://www.gnu.org/licenses/>.
 */
#include "../include/droidpermscanner.h"

void show_help(const char *self_binary){
	fprintf(stdout, _("%s - Android's Java source code scanner and deduces appropriate AndroidManifest.xml's permissions required\n\n"), PACKAGE_STRING);
	fprintf(stdout, _("Usage: %s [-s path] [-h] [-v]\n\n"), self_binary);
	fprintf(stdout, _("-s, --scan   \tscan specified directory source\n"));
	fprintf(stdout, _("-v, --version\tprint version then exit\n"));
	fprintf(stdout, _("-h, --help   \tprint this help and exit\n"));
	fprintf(stdout, _("\nReport bugs to <%s>\n\n"), PACKAGE_BUGREPORT);
	exit(1);
}
void show_version(void){
	fprintf(stdout, _("%s.\n"), PACKAGE_STRING);
	fprintf(stdout, _("Copyright (C) 2012 Tom Brennan\n"));
	fprintf(stdout, _("License GPLv3: GNU GPL Version 3 or later <http://gnu.org/licenses/gpl.html>\n"));
	fprintf(stdout, _("This is free software: You are free to change and redistribute it.\n"));
	fprintf(stdout, _("There is NO WARRANTY, to the extent permitted by law.\n\nWritten by Tom Brennan <%s>\n\n"), PACKAGE_BUGREPORT);
	exit(2);
}
void panic(int errcode, const char *fmt, ...){
    char buf[PANIC_BUF_LEN];
    va_list argptr;
    va_start(argptr, fmt);
    vsprintf(buf, fmt, argptr);
    va_end(argptr);
	fprintf(stderr, buf);
    exit(errcode);
}
int isredirected(void){
    if (!isatty(fileno(stdout))) return 1;
    return 0;
}
