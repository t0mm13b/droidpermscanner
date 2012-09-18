/*
 * droidpermscanner_main.c
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

extern int yylex(void);
extern FILE *yyin;

int count_perms = 0, permissions_bmp = 0;
static void permissions_lookup(int *, int);

/* MUST match mask_perms defined in header! */
static char *permissions[] = {
	"SEND_SMS|RECEIVE_SMS",
	"READ_SMS|WRITE_SMS",
	"READ_CONTACTS|WRITE_CONTACTS",
	"MODIFY_PHONE_STATE|READ_PHONE_STATE",
	"ACCESS_NETWORK_STATE|CHANGE_NETWORK_STATE",
	"READ_HISTORY_BOOKMARKS|WRITE_HISTORY_BOOKMARKS",
	"ACCESS_WIFI_STATE|CHANGE_WIFI_STATE",
	"ACCESS_COARSE_LOCATION|ACCESS_FINE_LOCATION",
	"AUTHENTICATE_ACCOUNTS|GET_ACCOUNTS|MANAGE_ACCOUNTS",
	"CALL_PHONE|PROCESS_OUTGOING_CALLS",
	"BLUETOOTH|BLUETOOTH_ADMIN|ACCESS_BLUETOOTH_SHARE",
	"INTERNET",
	"WRITE_EXTERNAL_STORAGE",
	"WRITE_SETTINGS",
	"MODIFY_AUDIO_SETTINGS",
	"VIBRATE",
	"WAKE_LOCK",
	"SYSTEM_ALERT_WINDOW",
	NULL
};
static void permissions_lookup(int *count_ptr, int mask_perms){
	char *permission_str = strdup(permissions[mask_perms]);
	char *tokenptr = strtok(permission_str, STR_PERMISSION_DELIM);
	if (!tokenptr){
		fprintf(stdout, XML_PERMISSION, permission_str);
		*count_ptr += 1;
	}else{
		fprintf(stdout, XML_PERMISSION, tokenptr);
		*count_ptr += 1;
		do{
			tokenptr = strtok(NULL, STR_PERMISSION_DELIM);
			if (tokenptr){
				fprintf(stdout, XML_PERMISSION, tokenptr);
				*count_ptr += 1;
			}
		}while (tokenptr);
	}
}
int scan(const char *pathstart){
	DIR *scandir = NULL;
	char *scanning_path = strdup(pathstart), *temp_path = NULL, *token = NULL;
	struct dirent *scanfile = NULL;
	struct stat scannedfile_stat;
	int scandir_len = 0;
	if (!(scandir = opendir(scanning_path))) panic(-1, "Error @ %s:%d:scan(...) - Failed to open %s", __FILE__, __LINE__, scanning_path);
	while ((scanfile = readdir(scandir))){
		if (!strcmp(scanfile->d_name, ".") || !strcmp(scanfile->d_name, "..")) continue;
		scandir_len += strlen(scanfile->d_name) + 1; // include the /
		scandir_len += strlen(scanning_path);
		if (!(temp_path = malloc(scandir_len + 1))) panic(-2, "Error @ %s:%d:scan(...) - Failed to malloc(...)", __FILE__, __LINE__);
		strcpy(temp_path, scanning_path);
		strcat(temp_path, "/");
		strcat(temp_path, scanfile->d_name);
		temp_path[strlen(temp_path)] = '\0';
		if (stat(temp_path, &scannedfile_stat) < 0) panic(-3, "Error @ %s:%d:scan(...) - Failed to get stat on %s", __FILE__, __LINE__, temp_path);
		if (S_ISDIR(scannedfile_stat.st_mode)){
			scan(temp_path);
			if (temp_path) free(temp_path);
			if (scanning_path) free(scanning_path);
			scanning_path = strdup(pathstart);
		}
		if (S_ISREG(scannedfile_stat.st_mode)){
			token = strstr(temp_path, JAVA_SRC_EXT);
			if (token){
				fprintf(stdout, "Scanning: %s\n", temp_path);
				if (!(yyin = fopen(temp_path, "r"))) panic(-4, "Error @ %s:%d:scan(...) - Failed to open %s for scanning", __FILE__, __LINE__, temp_path);
				else{
					yylex();
					fclose(yyin);
				}
			}
		}

	}
	if (closedir(scandir) < 0) panic(-5, "Error @ %s:%d:scan(...) - Failed to close %s",  __FILE__, __LINE__, scanning_path);
	return 1;
}
void print_permissions(void){
	fprintf(stdout, "=> END SCANNING...\n\n");
	if (permissions_bmp > 0){
		fprintf(stdout, "=> RESULT(S):\n");
		if (TestBit(permissions_bmp, SEND_RCV_SMS)) permissions_lookup(&count_perms, SEND_RCV_SMS);
		if (TestBit(permissions_bmp, RW_SMS)) permissions_lookup(&count_perms, RW_SMS);
		if (TestBit(permissions_bmp, RW_CONTACTS)) permissions_lookup(&count_perms, RW_CONTACTS);
		if (TestBit(permissions_bmp, RW_PHONE_STATE)) permissions_lookup(&count_perms, RW_PHONE_STATE);
		if (TestBit(permissions_bmp, RW_NETWORK_STATE)) permissions_lookup(&count_perms, RW_NETWORK_STATE);
		if (TestBit(permissions_bmp, RW_BROWSER)) permissions_lookup(&count_perms, RW_BROWSER);
		if (TestBit(permissions_bmp, RW_WIFI))	permissions_lookup(&count_perms, RW_WIFI);
		if (TestBit(permissions_bmp, GPS)) permissions_lookup(&count_perms, GPS);
		if (TestBit(permissions_bmp, ACCOUNTS)) permissions_lookup(&count_perms, ACCOUNTS);
		if (TestBit(permissions_bmp, INOUT_CALL)) permissions_lookup(&count_perms, INOUT_CALL);
		if (TestBit(permissions_bmp, BLUTOOTH))	permissions_lookup(&count_perms, BLUTOOTH);
		if (TestBit(permissions_bmp, INTERNET)) permissions_lookup(&count_perms, INTERNET);
		if (TestBit(permissions_bmp, SETTINGS)) permissions_lookup(&count_perms, SETTINGS);
		if (TestBit(permissions_bmp, EXTSTORAGE)) permissions_lookup(&count_perms, EXTSTORAGE);
		if (TestBit(permissions_bmp, AUDIO_SETTINGS)) permissions_lookup(&count_perms, AUDIO_SETTINGS);
		if (TestBit(permissions_bmp, VIBRATE)) permissions_lookup(&count_perms, VIBRATE);
		if (TestBit(permissions_bmp, WAKE_LOCK)) permissions_lookup(&count_perms, WAKE_LOCK);
		if (TestBit(permissions_bmp, SYS_WIN_ALERT)) permissions_lookup(&count_perms, SYS_WIN_ALERT);
	}
	if (count_perms > 0){
		fprintf(stdout, "\n=> Total POSSIBLE permissions required: %d\n", count_perms);
		fprintf(stdout, "\nPLEASE DOUBLE-CHECK to VERIFY that the above permissions ARE required!\n\n");
	}else{
		fprintf(stdout, "\nNO recognized possible permissions required!\n\n");
	}
}
