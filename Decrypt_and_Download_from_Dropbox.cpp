//
// Created by Zealydalal on 4/18/2016.
//

#include <iostream>
#include "/Dropbox-C-master"

using namespace std;

class Decrypt_and_Download_from_Dropbox
{
public:
    void decryptFunction();
private:
    void displayAccountInfo(drbAccountInfo *info);
};

void Decrypt_and_Download_from_Dropbox::decryptFunction()
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

    // Read account Informations
    output = NULL;
    err = drbGetAccountInfo(cli, &output, DRBOPT_END);
    if (err != DRBERR_OK) {
        printf("Account info error (%d): %s\n", err, (char*)output);
        free(output);
    } else {
        drbAccountInfo* info = (drbAccountInfo*)output;
        displayAccountInfo(info);
        drbDestroyAccountInfo(info);
    }
}



/*!
 * \brief  Display a drbAccountInfo item in stdout.
 * \param  info    account informations to display.
 * \return  void
 */
void Decrypt_and_Download_from_Dropbox::displayAccountInfo(drbAccountInfo* info) {
    if(info) {
        printf("---------[ Account info ]---------\n");
        if(info->referralLink)         printf("referralLink: %s\n", info->referralLink);
        if(info->displayName)          printf("displayName:  %s\n", info->displayName);
        if(info->uid)                  printf("uid:          %d\n", *info->uid);
        if(info->country)              printf("country:      %s\n", info->country);
        if(info->email)                printf("email:        %s\n", info->email);
        if(info->quotaInfo.datastores) printf("datastores:   %u\n", *info->quotaInfo.datastores);
        if(info->quotaInfo.shared)     printf("shared:       %u\n", *info->quotaInfo.shared);
        if(info->quotaInfo.quota)      printf("quota:        %u\n", *info->quotaInfo.quota);
        if(info->quotaInfo.normal)     printf("normal:       %u\n", *info->quotaInfo.normal);
    }
}