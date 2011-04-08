#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <curl/curl.h>
#include <string.h> /* Need this header for strcat */

char mesg[140]; /*140 for the tweet */
char status[149]="status=";


char *oauth_gen_nonce() {
  char *nc;
  static int rndinit = 1;
  const char *chars = "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "0123456789_";
  unsigned int max = strlen( chars );
  int i, len;

  if(rndinit) {srand(time(NULL)
#ifndef WIN32 // quick windows check.
    * getpid()
#endif
  ); rndinit=0;} // seed random number generator - FIXME: we can do better ;)

  len=15+floor(rand()*16.0/(double)RAND_MAX);
  nc = (char*) malloc((len+1)*sizeof(char));
  for(i=0;i<len; i++) {
    nc[i] = chars[ rand() % max ];
  }
  nc[i]='\0';
  return (nc);
}

int main(void)
{
fgets(mesg,140,stdin);
strcat(status,mesg);
CURL *curl;
CURLcode res;

curl = curl_easy_init();

if(curl) {

curl_easy_setopt(curl, CURLOPT_URL, "http://user:pass@twitter.com/statuses/update.json");  /*build the url with the username and password */

curl_easy_setopt(curl, CURLOPT_POSTFIELDS, status);

res = curl_easy_perform(curl);

curl_easy_cleanup(curl);

}

return 0;
}
