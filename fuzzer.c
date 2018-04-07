#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "curl/curl.h"
#include "config.h"
#include "grammer.h"

void run_test(CURL *curl, char *url) {

	CURLcode res;

	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	} else {
		fprintf(stderr, "Failed to initialize curl\n");
	}

	exit(0);

}

char *generate_test() {

	return s_url();

}

void log_crash(char *url) {

	FILE *fp;
	char *filename;

	mkdir(CRASH_DIR, 0755);

	filename = malloc(strlen(CRASH_DIR) + 10);
	sprintf(filename, "%s/%c%c%c%c%c%c", CRASH_DIR,
		(char)((rand() % 26) + 'a'),
		(char)((rand() % 26) + 'a'),
		(char)((rand() % 26) + 'a'),
		(char)((rand() % 26) + 'a'),
		(char)((rand() % 26) + 'a'),
		(char)((rand() % 26) + 'a')
	);


	fp = fopen(filename, "w");
	fprintf(fp, "%s", url);
	fclose(fp);

}

int main(int argc, char *argv[]) {

	char *test;
	CURL *curl;
	pid_t pid;
	int status;

	srand(time(0));
	curl = curl_easy_init();

	while(1) {

		test = generate_test();

		if((pid = fork())) {
			waitpid(pid, &status, 0);
			if(status != 0) {
				log_crash(test);
				printf("Crash!!!  (%s)\n", test);
			}
			free(test);
		} else {
			run_test(curl, test);
		}

	}

}
