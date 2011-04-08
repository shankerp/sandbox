#include <stdio.h>
#include <string.h>

void parseUrl(unsigned char *p_u8_url)
{
    char *p_ch_ptr = NULL;
    char *p_ch_dummy = NULL;
    int s32_var = 0;

    char a_ch_lid[1024];
    char a_ch_return[1024];
    char a_ch_playpos[1024];

    memset(a_ch_lid, 0, 1024);
    memset(a_ch_return, 0, 1024);
    memset(a_ch_playpos, 0, 1024);

    p_ch_ptr = (char *)strcasestr((char *)p_u8_url, "Return=");
    if (p_ch_ptr) {
        /* Move ptr ahead of the string Return= */
        p_ch_ptr += 7;
        strcpy(a_ch_return, p_ch_ptr);
    }

    p_ch_ptr = (char *)strcasestr((char *)p_u8_url, "LID=");
    if (p_ch_ptr) {
        printf("Got LID\n");
        /* Move ptr ahead of the string LID= */
        p_ch_ptr += 4;
        if (strncasecmp(p_ch_ptr, "none", 4) != 0) {
            p_ch_dummy = strchr(p_ch_ptr, '&');
            if(p_ch_dummy != NULL)
            {
                s32_var = p_ch_dummy - p_ch_ptr;
                memcpy(a_ch_lid, p_ch_ptr, s32_var);
                a_ch_lid[s32_var] = '\0';
            }
        } else {
            printf("LID none\n");
        }
    }

    p_ch_ptr = (char *)strcasestr(p_u8_url, "PlayPos=");
    if (p_ch_ptr) {
        /* Move ptr ahead of the string PlayPos= */
        p_ch_ptr += 8;
        p_ch_dummy = strchr(p_ch_ptr, '&');
        if(p_ch_dummy != NULL)
        {
            s32_var = p_ch_dummy - p_ch_ptr;
            memcpy(a_ch_playpos, p_ch_ptr, s32_var);
            a_ch_playpos[s32_var] = '\0';
        }
    }

    printf("LID: %s\n", a_ch_lid);
    printf("PlayPos: %s\n", a_ch_playpos);
    printf("Return: %s\n\n", a_ch_return);
}

int main()
{
    parseUrl("http://192.168.112.106/ib08/video/v1.cpc?Return=http://192.168.112.106/ib08/vod_index.html");
    parseUrl("http://192.168.112.106/ib08/video/v2.cpc?LID=none&Return=http://192.168.112.106/ib08/vod_index.html");
    parseUrl("http://192.168.112.106/ib08/video/v1.cpc?LID=none&Return=http://192.168.112.106/ib08/vod_index.html");
    parseUrl("http://192.168.112.106/ib08/video/v1.cpc?LID=0000&PlayPos=12.4&Return=http://192.168.112.106/ib08/vod_index.html");
    parseUrl("http://192.168.112.106/ib08/video/v1.cpc?LID=none&Return=http://192.168.112.106/ib08/vod_index.html");
}
