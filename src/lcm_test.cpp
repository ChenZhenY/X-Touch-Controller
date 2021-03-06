#include <stdio.h>

#include "lcm/lcm-cpp.hpp"
#include "XTouch_Parameter.hpp"
#include "humanoid_menu_data_lcmt.hpp"

class Handler 
{
    public:
        ~Handler() {}
        void handleMessage(const lcm::ReceiveBuffer* rbuf,
                const std::string& chan, 
                const XTouchMsg::XTouch_Parameter* msg)
        {
            int i;
            printf("Received message on channel \"%s\":\n", chan.c_str());
            // printf("  timestamp   = %lld\n", (long long)msg->timestamp);
            printf("name = %s\n", msg->channel_name[6].c_str());
            printf("value = %f\n", msg->channel_value[6]);
            // printf("  position    = (%f, %f, %f)\n",
            //         msg->position[0], msg->position[1], msg->position[2]);
            // printf("  orientation = (%f, %f, %f, %f)\n",
            //         msg->orientation[0], msg->orientation[1], 
            //         msg->orientation[2], msg->orientation[3]);
            // printf("  ranges:");
            // for(i = 0; i < msg->num_ranges; i++)
            //     printf(" %d", msg->ranges[i]);
            // printf("\n");
            // printf("  name        = '%s'\n", msg->name.c_str());
            // printf("  enabled     = %d\n", msg->enabled);
        }

        void handleMenuMessage(const lcm::ReceiveBuffer* rbuf,
                const std::string& chan, 
                const XTouchMsg::humanoid_menu_data_lcmt* msg)
        {
            int i;
            // printf("Received message on channel \"%s\":\n", chan.c_str());
            // printf("  timestamp   = %lld\n", (long long)msg->timestamp);
            printf("Kd_body x = %f\n", msg->Kd_body[0]);
            printf("Kd_cam x = %f\n", msg->Kd_cam[0]);
        }
};

int main(int argc, char** argv)
{
    lcm::LCM lcm;
    if(!lcm.good())
        return 1;
    Handler handlerObject;
    lcm.subscribe("XTouch", &Handler::handleMenuMessage, &handlerObject);
    while(0 == lcm.handle());
    return 0;
}