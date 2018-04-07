
#include <string.h>
#include <stdlib.h>
#include "grammer.h"

#define rn(x)		(rand()%(x))

char *strappend(char *a, char *b) {

	if(b == NULL) {
		// nothing to do
	} else if(a == NULL) {
		a = malloc(strlen(b) + 1);
		memset(a, '\0', strlen(b) + 1);
		strcat(a, b);
		free(b);
	} else {
		a = realloc(a, strlen(a) + strlen(b) + 1);
		strcat(a, b);
		free(b);
	}

	return a;

}

char *s_url() {

	char *url = NULL;

	url = strappend(url, n_protocol());
	url = strappend(url, n_host());
	url = strappend(url, n_path());
	url = strappend(url, n_query());

	return url;

}

char *n_protocol() {

	char *protocol = NULL;

	protocol = strappend(protocol, n_ptype());
	protocol = strappend(protocol, strdup("://"));

	return protocol;

}

char *n_ptype() {

	char *p = NULL;

	switch(rn(1 + JUNK_CHANCE)) {
		case 0:
			p = strappend(p, t_junk());
			break;
		default:
			switch(rn(11)) {
				case 0:
					p = strappend(p, strdup("dict"));
					break;
				case 1:
					p = strappend(p, strdup("file"));
					break;
				case 2:
					p = strappend(p, strdup("ftp"));
					break;
				case 3:
					p = strappend(p, strdup("gopher"));
					break;
				case 4:
					p = strappend(p, strdup("http"));
					break;
				case 5:
					p = strappend(p, strdup("imap"));
					break;
				case 6:
					p = strappend(p, strdup("pop3"));
					break;
				case 7:
					p = strappend(p, strdup("rtsp"));
					break;
				case 8:
					p = strappend(p, strdup("smb"));
					break;
				case 9:
					p = strappend(p, strdup("telnet"));
					break;
				case 10:
					p = strappend(p, strdup("tfpt"));
					break;
			}
	}

	return p;

}

char *n_host() {

	char *host = NULL;

	switch(rn(2)) {
		case 0:
			host = strappend(host, n_userpass());
			host = strappend(host, strdup("@"));
			host = strappend(host, n_fqdn());
			break;
		case 1:
			host = strappend(host, n_fqdn());
			break;
	}

	return host;

}

char *n_userpass() {

	char *userpass = NULL;

	switch(rn(3)) {
		case 0:
			userpass = strappend(userpass, n_username());
			userpass = strappend(userpass, strdup(":"));
			userpass = strappend(userpass, n_password());
			break;
		case 1:
			userpass = strappend(userpass, n_username());
			break;
		case 2:
			// EMPTY
			break;
	}

	return userpass;

}

char *n_username() {

	char *username = NULL;

	switch(rn(1 + JUNK_CHANCE)) {
		case 0:
			username = strappend(username, t_junk());
			break;
		default:
			username = strappend(username, strdup("username"));
			break;
	}

	return username;
}

char *n_password() {

	char *password = NULL;

	switch(rn(1 + JUNK_CHANCE)) {
		case 0:
			password = strappend(password, t_junk());
			break;
		default:
			password = strappend(password, strdup("password"));
			break;
	}

	return password;

}

char *n_fqdn() {

	char *fqdn = NULL;

	fqdn = strappend(fqdn, n_subdomain());
	fqdn = strappend(fqdn, n_domain());
	fqdn = strappend(fqdn, n_tld());

	return fqdn;

}

char *n_subdomain() {

	char *subdomain = NULL;
	int i, len;

	len = rn(3);
	for(i=0; i<len; i++) {
		switch(rn(1 + JUNK_CHANCE)) {
			case 0:
				subdomain = strappend(subdomain, t_junk());
				subdomain = strappend(subdomain, strdup("."));
				break;
			default:
				subdomain = strappend(subdomain, strdup("sub"));
				subdomain = strappend(subdomain, strdup("."));
				break;
		}
	}

	return subdomain;

}

char *n_domain() {

	char *domain = NULL;

	switch(rn(1 + JUNK_CHANCE)) {
		case 0:
			domain = strappend(domain, t_junk());
			break;
		default:
			domain = strappend(domain, strdup("domain"));
			break;
	}

	return domain;

}

char *n_tld() {

	char *tld = NULL;

	switch(rn(1 + JUNK_CHANCE)) {
		case 0:
			tld = strappend(tld, strdup("."));
			tld = strappend(tld, t_junk());
			break;
		default:
			tld = strappend(tld, strdup("."));
			tld = strappend(tld, strdup("tld"));
			break;
	}

	return tld;

}

char *n_path() {

	char *path = NULL;
	int i, len;

	path = strappend(path, strdup("/"));

	len = rn(3);
	for(i=0; i<len; i++) {
		switch(rn(1 + JUNK_CHANCE)) {
			case 0:
				path = strappend(path, t_junk());
				path = strappend(path, strdup("/"));
				break;
			default:
				path = strappend(path, strdup("path"));
				path = strappend(path, strdup("/"));
				break;
		}
	}

	switch(rn(1 + JUNK_CHANCE)) {
		case 0:
			path = strappend(path, t_junk());
			break;
		default:
			path = strappend(path, strdup("file.html"));
			break;
	}

	return path;

}

char *n_query() {

	char *query = NULL;
	int i, len;

	query = strappend(query, strdup("?"));

	len = rn(3);
	for(i=0; i<len; i++) {
		switch(rn(1 + JUNK_CHANCE)) {
			case 0:
				query = strappend(query, t_junk());
				break;
			default:
				query = strappend(query, strdup("key=val"));
				break;
		}
		query = strappend(query, strdup("&"));
	}

	return query;

}

char *t_junk() {

	char *junk;
	int i, len;

	len = rn(16);
	junk = malloc(len + 1);

	for(i=0; i<len; i++)
		junk[i] = (char)(rn(96) + 0x20);

	junk[len] = '\0';

	return junk;

}