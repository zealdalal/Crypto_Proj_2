#include <iostream>
#include "Encrypt_and_Upload_to_Dropbox.h"
#include "Decrypt_and_Download_from_Dropbox.h"

using namespace std;

int main() {
    cout << "Select from the choices" << endl;
    cout << "1. Encrypt and upload a file:" << endl;
    cout << "2. Decrypt and download a file:" << endl;
    int n;
    cin >> n;
    Encrypt_and_Upload_to_Dropbox encryptfile;
    Decrypt_and_Download_from_Dropbox decryptfile;
    if(n==1)
        encryptfile.encryptFunction();
    else if(n==2)
        decryptfile.decryptFunction();
    return 0;
}