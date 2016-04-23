//
// Created by Zealydalal on 4/18/2016.
//

#include <iostream>
#include <string>
#include <dropbox.h>
#include <memStream.h>

using namespace std;

class Decrypt_and_Download_from_Dropbox
{
public:
    void decryptFunction();
private:
    void displayAccountInfo(drbAccountInfo *info);
    void displayMetadata(drbMetadata *meta, char *title);
    void displayMetadataList(drbMetadataList* list, char* title);
};

void Decrypt_and_Download_from_Dropbox::decryptFunction()
{
    int err;
    void *output;

    char *app_key = "your consumer key";
    char *app_secret = "your consumer secret";

    char *t_key    = NULL; //< access token key
    char *t_secret = NULL;  //< access token secret

    char *filename = NULL;  //name of file to be downloaded
    string directory = "/Download/";  //default directory

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

    // List root directory files
    output = NULL;
    err = drbGetMetadata(cli, &output,
                         DRBOPT_PATH, "/",
                         DRBOPT_LIST, true,
            //                     DRBOPT_FILE_LIMIT, 100,
                         DRBOPT_END);
    if (err != DRBERR_OK) {
        printf("Metadata error (%d): %s\n", err, (char*)output);
        free(output);
    } else {
        drbMetadata* meta = (drbMetadata*)output;
        displayMetadata(meta, "Metadata");
        drbDestroyMetadata(meta, true);
    }

    //Getting the filename the user wish to download
    cout << "Input the name of file you want to download:";
    cin >> filename;
    FILE *file = fopen(directory+"tmp", "w"); // Write it in temp file
    output = NULL;
    err = drbGetFile(cli, &output,
                     DRBOPT_PATH, "/tmp",
                     DRBOPT_IO_DATA, file,
                     DRBOPT_IO_FUNC, fwrite,
                     DRBOPT_END);
    fclose(file);

    if (err != DRBERR_OK) {
        printf("Get File error (%d): %s\n", err, (char*)output);
        free(output);
    } else {
        displayMetadata((drbMetadata*)output, "Get File Result");
        drbDestroyMetadata((drbMetadata*)output, true);
    }


    //Decrypt the downloaded file and write into dest file



    // Free all client allocated memory
    drbDestroyClient(cli);

    // Global Cleanup
    drbCleanup();
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

const char* strFromBool(bool b) { return b ? "true" : "false"; }

/*!
 * \brief  Display a drbMetadata item in stdout.
 * \param  meta    metadata to display.
 * \param   title   display the title before the metadata.
 * \return  void
 */
void Decrypt_and_Download_from_Dropbox::displayMetadata(drbMetadata* meta, char* title) {
    if (meta) {
        if(title) printf("---------[ %s ]---------\n", title);
        if(meta->hash)        printf("hash:        %s\n", meta->hash);
        if(meta->rev)         printf("rev:         %s\n", meta->rev);
        if(meta->thumbExists) printf("thumbExists: %s\n", strFromBool(*meta->thumbExists));
        if(meta->bytes)       printf("bytes:       %d\n", *meta->bytes);
        if(meta->modified)    printf("modified:    %s\n", meta->modified);
        if(meta->path)        printf("path:        %s\n", meta->path);
        if(meta->isDir)       printf("isDir:       %s\n", strFromBool(*meta->isDir));
        if(meta->icon)        printf("icon:        %s\n", meta->icon);
        if(meta->root)        printf("root:        %s\n", meta->root);
        if(meta->size)        printf("size:        %s\n", meta->size);
        if(meta->clientMtime) printf("clientMtime: %s\n", meta->clientMtime);
        if(meta->isDeleted)   printf("isDeleted:   %s\n", strFromBool(*meta->isDeleted));
        if(meta->mimeType)    printf("mimeType:    %s\n", meta->mimeType);
        if(meta->revision)    printf("revision:    %d\n", *meta->revision);
        if(meta->contents)    displayMetadataList(meta->contents, "Contents");
    }
}

/*!
 * \brief  Display a drbMetadataList item in stdout.
 * \param  list    list to display.
 * \param   title   display the title before the list.
 * \return  void
 */
void Decrypt_and_Download_from_Dropbox::displayMetadataList(drbMetadataList* list, char* title) {
    if (list){
        printf("---------[ %s ]---------\n", title);
        for (int i = 0; i < list->size; i++) {

            displayMetadata(list->array[i], list->array[i]->path);
        }
    }
}