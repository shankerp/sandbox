#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h> /* Need this header for strcat */

char mesg[140]; /*140 for the tweet */
char status[149]="status=";

int main(void)
{
fgets(mesg,140,stdin);
strcat(status,mesg);
CURL *curl;
CURLcode res;

res = curl_global_init(CURL_GLOBAL_ALL);
if (res != 0)
{
    printf("Something went wrong\n");
    exit (-1);
}
curl = curl_easy_init();

if(curl)
{

     curl_easy_setopt(curl, CURLOPT_USERNAME, "celestialsys");
     curl_easy_setopt(curl, CURLOPT_PASSWORD, "welcome1");
curl_easy_setopt(curl, CURLOPT_URL, "http://twitter.com/statuses/update.json");  /*build the url with the username and password */
// curl_easy_setopt(curl, CURLOPT_URL, "http://celestialsys:welcome1@twitter.com/statuses/update.json");  /*build the url with the username and password */

printf("Curl easy setopt done\n");
curl_easy_setopt(curl, CURLOPT_POSTFIELDS, status);

printf("Curl easy setopt POSTFIEDLSdone\n");
res = curl_easy_perform(curl);

printf("Curl Performed\n");
curl_easy_cleanup(curl);

printf("Cleanup\n");
}
curl_global_cleanup();
return 0;
}
