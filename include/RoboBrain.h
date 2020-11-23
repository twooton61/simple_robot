#ifndef ROBO_BRAIN_H
#define ROBO_BRAIN_H

#include <AbstractRoboPart.h>

class RoboBrain {
    class AbstractRoboPartNode {
        AbstractRoboPart* m_robo_part;
        AbstractRoboPartNode* m_next_node;

        public:
        AbstractRoboPartNode(AbstractRoboPart* robo_part) :
            m_robo_part(robo_part),
            m_next_node(NULL)
        {
        }

        inline void set_next_node(AbstractRoboPartNode* next_node) {
            m_next_node = next_node;
        }

        inline AbstractRoboPartNode* get_next_node() {
            return m_next_node;
        }

        inline AbstractRoboPart* get_robo_part() {
            return m_robo_part;
        }
    };

    AbstractRoboPartNode* m_first_part_added_node = NULL;
    AbstractRoboPartNode* m_last_part_added_node = NULL;

    public:

    RoboBrain() :
        m_last_part_added_node(NULL)
    {
    }

    void add_part(AbstractRoboPart* robo_part) {
        AbstractRoboPartNode* new_part_node = new AbstractRoboPartNode(robo_part);

        if(m_first_part_added_node == NULL) {
            m_first_part_added_node = new_part_node;
            m_last_part_added_node = new_part_node;
        }
        else {
            m_last_part_added_node->set_next_node(new_part_node);
            m_last_part_added_node = new_part_node;
        }
    }

    void setup() {
        AbstractRoboPartNode* current_node = m_first_part_added_node;
        while(current_node != NULL) {
            Serial.println("setting up robo part");
            current_node->get_robo_part()->setup();
            current_node = current_node->get_next_node();
        }
    }
};

#endif