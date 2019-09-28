#include <khepera/khepera.h>
#include <stdlib.h>
#include <string.h>

#define RED   if(color) printf("\x1b[31m")
#define GREEN if(color) printf("\x1b[32m")
#define RESET if(color) printf("\x1b[0m");

/* Device handle */
knet_dev_t* tDSPic;
/* Data buffer */
char pchBuffer[100];
/* Whether to color the output */
int color = 0;
/* Whether to end with a newline */
int nonewline = 0;
/* The threshold */
int threshold = 15;

void battery_main() {
  kh4_battery_status(pchBuffer, tDSPic);
  int nPlugged = kh4_battery_charge(tDSPic);
  if(!nPlugged && (pchBuffer[3] < threshold)) { RED; }
  else { GREEN; }
  printf("(%d%%,%s)",
	 pchBuffer[3],
	 nPlugged ? "plugged" : "unplugged");
  RESET;
}

/* TODO */
/* void battery_lidar() { */
/* } */

int main(int n_argc, char** pch_argv) {
  if(n_argc > 1) {
    int nArg = 1;
    while(nArg < n_argc) {
      if(strcmp(pch_argv[nArg], "--help") == 0) {
	fprintf(stdout, "%s [--color] [--nonewline] [--threshold T]\n\n", pch_argv[0]);
	fprintf(stdout, "   --color         Color the output red if the battery is below its safe charge\n");
	fprintf(stdout, "                   threshold, green otherwise.\n\n");
	fprintf(stdout, "********************************************************************************");
	fprintf(stdout, "   --nonewline     Do not emit a newline in the output.\n\n");
	fprintf(stdout, "   --threshold T   Set the charge threshold to T%%. Default is 15%%.\n\n");
	return 0;
      }
      else if(strcmp(pch_argv[nArg], "--color") == 0) {
	color = 1;
	++nArg;
      }
      else if(strcmp(pch_argv[nArg], "--nonewline") == 0) {
	nonewline = 1;
	++nArg;
      }
      else if(strcmp(pch_argv[nArg], "--threshold") == 0) {
	++nArg;
	if(nArg >= n_argc) {
	  fprintf(stderr, "Missing argument for --threshold\nType '%s --help' for more information.\n\n", pch_argv[0]);
	  return -1;
	}
	char* pchEndPtr;
	threshold = strtol(pch_argv[nArg], &pchEndPtr, 10);
	if(*pchEndPtr != '\0') {
	  fprintf(stderr, "Can't parse '%s' as a numeric value for the threshold\n\n", pch_argv[nArg]);
	  return -1;
	}
	if(threshold < 1 || threshold > 100) {
	  fprintf(stderr, "The threshold value must be within [1,100]\n\n");
	  return -1;
	}
	++nArg;
      }
      else {
	fprintf(stderr, "Unrecognized option '%s'\nType '%s --help' for a list of accepted arguments.\n\n", pch_argv[nArg], pch_argv[0]);
	return -1;
      }
    }
  }
  /* Initialize robot */
  if(kh4_init(0, NULL) != 0) {
    RED;
    printf("(main:no status [init error])");
    RESET;
    return -2;
  }
  /* Connect to robot */
  tDSPic = knet_open("Khepera4:dsPic" , KNET_BUS_I2C, 0, NULL);
  if (tDSPic == NULL) {
    RED;
    printf("(main:no status [open error])");
    RESET;
    return -3;
  }
  /* Display battery status */
  battery_main();
  /* battery_lidar(); */
  /* Add newline? */
  if(!nonewline) printf("\n");
  return 0;
}
