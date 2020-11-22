#ifndef ROBO_BRAIN_H
#define ROBO_BRAIN_H

#include <AbstractRoboPart.h>

class RoboBrain {
    static const int MAX_PARTS = 100;

    AbstractRoboPart* m_robo_parts[MAX_PARTS];
    int m_total_parts = 0;

    public:

    RoboBrain() {
    }

    void add_part(AbstractRoboPart* robo_part) {
        if(m_total_parts == MAX_PARTS) {
            Serial.println("too many parts");
            return;
        }

        m_robo_parts[m_total_parts++] = robo_part;
    }

    void setup() {
        for(int i = 0; i < m_total_parts; i++) {
            AbstractRoboPart* arp = m_robo_parts[i];
            arp->setup();
        }
    }
};

#endif