#include "Scaler.h"

extern int screenWidth;
extern int screenHeight;

bool scaling_enabled = true;

int Scaler::scaleX(const int x) {
	
	return scaling_enabled ? static_cast<int>(x * (screenWidth / REF_SCREEN_WIDTH)) : x;
}


int Scaler::scaleY(const int y) {
	
	return scaling_enabled ? static_cast<int>(y * (screenHeight / REF_SCREEN_HEIGHT)) : y;
}

