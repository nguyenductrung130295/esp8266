#include <firebase-service/firebase-service.h>

void connectFirebase(String hostUrl, String authKey){
    //send initial string of led status
    Firebase.begin(hostUrl, authKey);
    // Firebase.reconnectWiFi(true);//optional
}

bool handleReqFb(bool result, FirebaseData *firebaseData) {
    if (!result) {
        Serial.println(firebaseData->errorReason());
    }
    return result;
}