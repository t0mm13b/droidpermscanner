/*
 * droidpermscanner.h
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

#ifndef __DROIDPERMSCANNER_H__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <getopt.h>
#include <dirent.h>
#include <sys/stat.h>
#ifdef __gnu_linux__
#include <error.h>
#endif
#include <config.h>
#include <locale.h>
#include "gettext.h"
#define _(string) gettext(string)

#define JAVA_SRC_EXT			".java"
#define PANIC_BUF_LEN			250
#define XML_PERMISSION			"<uses-permission android:name=\"%s\" />\n"
#define STR_PERMISSION_DELIM	"|"

#define CheckBit(x) (!(!(x)))
#define SetBit(arg,posn) ((arg) | (1L << (posn)))
#define TestBit(arg,posn) CheckBit((arg) & (1L << (posn)))

typedef enum {
	SEND_RCV_SMS = 0,	/* [SEND|RECEIVE]_SMS */
	RW_SMS,				/* [READ|WRITE]_SMS */
	RW_CONTACTS, 		/* [READ|WRITE]_CONTACTS */
	RW_PHONE_STATE, 	/* [MODIFY|READ]_PHONE_STATE */
	RW_NETWORK_STATE, 	/* [ACCESS|CHANGE]_NETWORK_STATE */
	RW_BROWSER,			/* [READ|WRITE]_HISTORY_BOOKMARKS */
	RW_WIFI, 			/* [ACCESS|CHANGE]_WIFI_STATE */
	GPS,				/* [ACCESS_[COARSE|FINE]_LOCATION */
	ACCOUNTS,			/* [AUTHENTICATE|GET|MANAGE]_ACCOUNTS */
	INOUT_CALL,			/* [CALL_PHONE|PROCESS_OUTGOING_CALLS] */
	BLUTOOTH,			/* [BLUETOOTH|BLUETOOTH_ADMIN|ACCESS_BLUETOOTH_SHARE] */
	INTERNET,			/* INTERNET */
	EXTSTORAGE,			/* WRITE_EXTERNAL_STORAGE */
	SETTINGS,			/* WRITE_SETTINGS */
	AUDIO_SETTINGS,		/* MODIFY_AUDIO_SETTINGS */
	VIBRATE,			/* VIBRATE */
	WAKE_LOCK,			/* WAKE_LOCK */
	SYS_WIN_ALERT,		/* SYSTEM_ALERT_WINDOW */
	UNKNOWN				/* EXACTLY! */
}mask_perms;

/* droidpermscanner_utils.c */
void show_help(const char *self_binary);
void show_version(void);
void panic(int errcode, const char *fmt, ...);
int isredirected(void);

/* droidpermscanner_main.c */
void print_permissions(void);
int scan(const char *pathstart);

#endif /* __DROIDPERMSCANNER_H__ */
