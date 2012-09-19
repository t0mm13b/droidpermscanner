%{
/*
 * droidpermscanner.l
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

extern int permissions_bmp;

static struct option long_opts[] = {
	{ "version", 0, 0, 'v' },
	{ "scan", 1, 0, 's' },
	{ "help", 0, 0, 'h' },
	{ 0, 0, 0, 0}
};

%}

%%


"HttpClient" { permissions_bmp = SetBit(permissions_bmp, INTERNET); }
"HttpPost" { permissions_bmp = SetBit(permissions_bmp, INTERNET); }
"HttpResponse" { permissions_bmp = SetBit(permissions_bmp, INTERNET); }
"InetSocketAddress" { permissions_bmp = SetBit(permissions_bmp, INTERNET); }
"DatagramSocket" { permissions_bmp = SetBit(permissions_bmp, INTERNET); }
"ServerSocket" { permissions_bmp = SetBit(permissions_bmp, INTERNET); }
"Socket" { permissions_bmp = SetBit(permissions_bmp, INTERNET); }

"Settings.System" { permissions_bmp = SetBit(permissions_bmp, SETTINGS); }

"WifiManager" { permissions_bmp = SetBit(permissions_bmp, RW_WIFI); }
"Context.WIFI_SERVICE" { permissions_bmp = SetBit(permissions_bmp, RW_WIFI); }

"BluetoothAdapter" { permissions_bmp = SetBit(permissions_bmp, BLUTOOTH); }
".startDiscovery" { permissions_bmp = SetBit(permissions_bmp, BLUTOOTH); }
".cancelDiscovery" { permissions_bmp = SetBit(permissions_bmp, BLUTOOTH); }
".isDiscovering" { permissions_bmp = SetBit(permissions_bmp, BLUTOOTH); }

"Context.TELEPHONY_SERVICE" { permissions_bmp = SetBit(permissions_bmp, RW_PHONE_STATE); }

"Context.CONNECTIVITY_SERVICE" { permissions_bmp = SetBit(permissions_bmp, RW_NETWORK_STATE); }

"Context.AUDIO_SERVICE" { permissions_bmp = SetBit(permissions_bmp, AUDIO_SETTINGS); }
"AudioManager" { permissions_bmp = SetBit(permissions_bmp, AUDIO_SETTINGS); }

"Context.VIBRATOR_SERVICE" { permissions_bmp = SetBit(permissions_bmp, VIBRATE); }

"Browser.Bookmark" { permissions_bmp = SetBit(permissions_bmp, RW_BROWSER); }

"ContactsContract." { permissions_bmp = SetBit(permissions_bmp, RW_CONTACTS); }
"CallLog." { permissions_bmp = SetBit(permissions_bmp, RW_CONTACTS); }

"SmsManager" { permissions_bmp = SetBit(permissions_bmp, SEND_RCV_SMS); }
"sendTextMessage" { permissions_bmp = SetBit(permissions_bmp, SEND_RCV_SMS); }
"sendDataMessage" { permissions_bmp = SetBit(permissions_bmp, SEND_RCV_SMS); }
"sendMultipartTextMessage" { permissions_bmp = SetBit(permissions_bmp, SEND_RCV_SMS); }
".get(\"pdus\")" { permissions_bmp = SetBit(permissions_bmp, SEND_RCV_SMS); }

"content://sms/" { permissions_bmp = SetBit(permissions_bmp, RW_SMS); }

"Environment.getExternalStorageDirectory" { permissions_bmp = SetBit(permissions_bmp, EXTSTORAGE); }
"EXTERNAL_CONTENT_URI" { permissions_bmp = SetBit(permissions_bmp, EXTSTORAGE); }

"LOCATION_SERVICE"  { permissions_bmp = SetBit(permissions_bmp, GPS); }
"LocationManager.GPS_PROVIDER" { permissions_bmp = SetBit(permissions_bmp, GPS); }
".disableCompass" { permissions_bmp = SetBit(permissions_bmp, GPS); }
".disableMyLocation" { permissions_bmp = SetBit(permissions_bmp, GPS); }

"AccountManager.get" { permissions_bmp = SetBit(permissions_bmp, ACCOUNTS); }
".getAccountsByType" { permissions_bmp = SetBit(permissions_bmp, ACCOUNTS); }

"Context.POWER_SERVICE" { permissions_bmp = SetBit(permissions_bmp, WAKE_LOCK); }

"PhoneStateListener.LISTEN_CALL_STATE" { permissions_bmp = SetBit(permissions_bmp, RW_PHONE_STATE); }
"TYPE_SYSTEM_OVERLAY" { permissions_bmp = SetBit(permissions_bmp, SYS_WIN_ALERT); }
"FLAG_WATCH_OUTSIDE_TOUCH" { permissions_bmp = SetBit(permissions_bmp, SYS_WIN_ALERT); }

[ \t\n]+ 	{ ; /* ignore whitespace */ }

. { ; }

%%

int yywrap(void){
	return 1;
}
int main(int argc, char **argv){
	int argvopt = 0, option_index = 0, c;
	char *self_name = strdup(argv[0]), *scan_path = NULL;
	if (isredirected()) return -1;
	//
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);
	//
	if (argc == 1) show_help(self_name);
	opterr = 0;
	while ((c = getopt_long(argc, argv, "s:vh", long_opts, &option_index)) != -1){
		switch(c){
			case 's' :
				scan_path = strdup(optarg);
				argvopt = 1;
				break;
			case 'h' :
				show_help(self_name);
				break;
			case 'v' :
				show_version();
                break;
			case '?' :
				break;
			default :
				return -2;
		}
	}
	if (c == -1 && !argvopt){
        fprintf(stderr, _("No options given!\n"));
        return -1;
    }
	fprintf(stdout, _("=> BEGIN SCANNING PATH: %s...\n"), scan_path);
	if (scan(scan_path)){
		print_permissions();
	}
	if (self_name) free(self_name);
    return 0;
}
