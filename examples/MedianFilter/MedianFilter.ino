#include "MedianFilter.h"

MedianFilter<int, 7> filter;

void setup() {
    Serial.begin(9600);

    for (int i = 0; i < 1000; i++) {
        int s = rand() % 100;
        filter.addSample(s);

        if (filter.isReady()) {
            Serial.println(filter.getMedian());
        }
    }
}

void loop() {

}
