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
