#include "Firebase_Helper.h"

FirebaseHelper::FirebaseHelper(const char* firebaseId, bool _DEBUG) : firebase(firebaseId), DEBUG(_DEBUG) {
    // Constructor implementation remains unchanged
}

void FirebaseHelper::sendToFirebase(String Header, String message) {
    String key = "", tmp = "";
    for(int i = 0 ; i < message.length() ; ++i){
        if(message[i] == ':'){  
            key = tmp;
            tmp = "";
        } else if(message[i] == ';'){  
            firebase.setFloat(Header + "/" + key, atof(tmp.c_str()));
            if(DEBUG){
              Serial.println("[Success]" + Header + "[" + key + "] = " + tmp);
            }
            tmp = "";
        } else {
            tmp += message[i];
        }
    }
}
