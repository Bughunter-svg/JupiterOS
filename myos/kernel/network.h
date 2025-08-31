// kernel/network.h
void init_network();
void send_packet(void* data, int len);
void receive_packet(void* buffer);
