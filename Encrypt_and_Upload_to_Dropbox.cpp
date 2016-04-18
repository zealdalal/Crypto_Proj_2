//
// Created by Zealydalal on 4/18/2016.
//

#include <iostream>
#include "/Dropbox-C-master/Dropbox/include/dropbox.h"
#include "/Dropbox-C-master/memStream/include/memStream.h"
#include "/Dropbox-C-master/Dropbox/include/"

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



    flow = dropbox.client.DropboxOAuth2FlowNoRedirect(app_key, app_secret)
}
