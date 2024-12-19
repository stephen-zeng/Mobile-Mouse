// #include "mousemove_mac.h"
#include <ApplicationServices/ApplicationServices.h>

void makeScroll(const int& x) {
    CGEventRef scrollEvent = CGEventCreateScrollWheelEvent(
        NULL, kCGScrollEventUnitLine, 2, 0, x
        );

    CGEventPost(kCGHIDEventTap, scrollEvent);
    CFRelease(scrollEvent);
}


