# Growtopia - Gamepacket
A basic game packet sender for Growtopia private game server that using variantlist.

## - Example:

```cpp
using namespace KHPS;
gamepacket_t msg = { "OnConsoleMessage", "`4OOPS:`` You've forgot to star this repository? Please click star ><." };
msg.m_net_id = -1; // set your net id here, it's -1 by default same as delay one
msg.m_delay = 0; // set your delay time here
ENetPacket* packet = enet_packet_create(msg.get(), msg.lens(), 1);
enet_peer_send(peer, 0x0, packet);
```
