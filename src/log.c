/*--- INCLUDE ---*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config.h"
#include "log.h"


/*--- VARS and CONSTS ---*/

static FILE* console_ptr = NULL;
static FILE* file_ptr = NULL;


/*--- FUNCTION ---*/

void log_init(FILE* console, FILE* fichier){
	console_ptr = console;
	file_ptr = fichier;		
}

void log_free(){
	console_ptr = NULL;
	file_ptr = NULL;
}

void log_m(log_state_e type, const char* message){
	FILE *ptrs[] = {console_ptr, file_ptr};

	for(int i = 0; i<sizeof(ptrs) / sizeof(ptrs[0]); i++){
		if(ptrs[i] != NULL){
			char type_s[10] = "";

			switch(type){
				case INFO:
					strcpy(type_s, "info");
					break;
				case WARN:
					strcpy(type_s, "warn");
					break;
				case ERROR:
					strcpy(type_s, "error");
					break;
				case DEBUG:
					strcpy(type_s, "debug");
					break;
				default:
					break;
			}
			

			time_t t = time(NULL);
  			struct tm tm = *localtime(&t);

			fprintf(ptrs[i], "[%s] %02d-%02d-%02d %02d:%02d:%02d -	%s\n",
				type_s,
				tm.tm_mday,
				tm.tm_mon + 1,
				tm.tm_year + 1900,
				tm.tm_hour,
				tm.tm_min,
				tm.tm_sec,
				message
			);

			fflush(ptrs[i]);
		}
	}
}

#if (TEST_APP && TEST_log)
int main(int argc, char** argv){
	/*--- INIT ---*/
	log_init(stdout, fopen((const char*) getenv("LOG_FILE"), "a"));

	/*--- CODE ---*/
	log_m(INFO, (const char*) "log info message");
	log_m(WARN, (const char*) "log warn message");
	log_m(ERROR, (const char*) "log error message");
	log_m(DEBUG, (const char*) "log debug message");

	/*--- END ---*/
	log_free();
	return EXIT_SUCCESS;
}
#endif