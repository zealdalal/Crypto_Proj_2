//
// Created by Zealydalal on 4/18/2016.
//

#include <iostream>
#include "dropbox.h"
#include "/Dropbox-C-master/memStream/include/memStream.h"

using namespace std;

class Encrypt_and_Upload_to_Dropbox
{
public:
    void encryptFunction();
};

void Encrypt_and_Upload_to_Dropbox::encryptFunction()
{
    char *app_key = "your consumer key";
    char *app_secret = "your consumer secret";

    char *t_key    = NULL; //< access token key
    char *t_secret = NULL;  //< access token secret

    drbInit();

    drbClient* cli = drbCreateClient(app_key, app_secret, t_key, t_secret);

    // Request a AccessToken if undefined (NULL)
    if(!t_key || !t_secret) {
        drbOAuthToken* reqTok = drbObtainRequestToken(cli);

        if (reqTok) {
            char* url = drbBuildAuthorizeUrl(reqTok);
            printf("Please visit %s\nThen press Enter...\n", url);
            free(url);
            fgetc(stdin);

            drbOAuthToken* accTok = drbObtainAccessToken(cli);

            if (accTok) {
                // This key and secret can replace the NULL value in t_key and
                // t_secret for the next time.
                printf("key:    %s\nsecret: %s\n", accTok->key, accTok->secret);
            } else{
                fprintf(stderr, "Failed to obtain an AccessToken...\n");
            }
        } else {
            fprintf(stderr, "Failed to obtain a RequestToken...\n");
        }
    }

    // Set default arguments to not repeat them on each API call
    drbSetDefault(cli, DRBOPT_ROOT, DRBVAL_ROOT_AUTO, DRBOPT_END);




}
