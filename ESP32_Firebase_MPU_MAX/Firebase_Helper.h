#ifndef FIREBASE_HELPER_H
#define FIREBASE_HELPER_H

#include <ESP32Firebase.h>

class FirebaseHelper {
public:
    FirebaseHelper(const char* firebaseId, bool _DEBUG);
    void sendToFirebase(String Header, String message);

private:
    Firebase firebase; // Declare firebase object as a private member variable
    bool DEBUG;
};

#endif
