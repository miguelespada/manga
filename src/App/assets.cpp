#include "assets.h"

void Assets::loadAssets(){
}


int Assets::getLocalPort(){
    return getData("local_port").asInt();
}

int Assets::getXpos(){
    return getData("x_pos").asInt();
}

string Assets::getServer(){
    return getData("server").asString();
}

int Assets::getInactivityTime(){
    return getData("inactivityTime").asInt();;
}

int Assets::getMaxIdleTime(){
    return 10;
}

int Assets::getRemotePort(){
    return getData("remote_port").asInt();
}

string Assets::getRemoteHost(){
    return getData("remote_host").asString();
}
int Assets::getControllerPort(){
    return getData("controller_port").asInt();
}

string Assets::getControllerHost(){
    return getData("controller_host").asString();
}

bool Assets::getAutoUpdatePredictions(){
    return getData("updatePredictions").asBool();
}

int Assets::getMidiNote(int i, bool bInverse){
    int notes[6] = {48, 46, 51, 46, 38, 36};
    if(bInverse) return notes[5 - i];
    return notes[i];
}
