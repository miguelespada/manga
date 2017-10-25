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

int Assets::getMidiNote(int i){
    switch (i) {
        case 0:
            return 36;
            break;
        case 1:
            return 45;
            break;
        case 2:
            return 46;
            break;
        case 3:
            return 38;
            break;
        case 4:
            return 48;
            break;
        case 5:
            return 51;
            break;
        default:
            break;
    }
    
}
