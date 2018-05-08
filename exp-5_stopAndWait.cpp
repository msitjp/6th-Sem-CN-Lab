#include <bits/stdc++.h>
#define MAX_PACKETS 8
#define PACKET_SIZE 1024
#define ERROR_RATE 0.05 // 5% Error Rate

using namespace std;

enum Packet_type {
    Data,
    Acknowledgment
};


class Packet {
    public:
        int length;
        int id;
        int type;
        Packet(int type, int id, int length) {
            this->type = type;
            this->id = id;
            this->length = length;
        }
};

void Print(Packet p, bool error=false) {
    if(error){
        cout<<"Packet [seq_no="<<p.id<<"]["<<PACKET_SIZE<<"B] lost.\n";
    }else if (p.type == Data) {
        cout<<"Packet [seq_no="<<p.id<<"]["<<PACKET_SIZE<<"B] transmitted.\n";        
    }else {
        cout<<"Acknowledgment [seq_no="<<p.id<<"] recieved.\n";        
    }
}

void sendPacket(int seq) {
    Packet p(Data, seq, PACKET_SIZE);
    Print(p);
}

void sendAcknowledment(int seq) {
    Packet p(Acknowledgment, seq, PACKET_SIZE);
    Print(p);
}

void simulate(int seq){
    sendPacket(seq);
    bool error = (rand()%2) <= ERROR_RATE ? true : false;
    if(error){
        Packet a(Data, seq, PACKET_SIZE);
        Print(a, true);
        simulate(seq);
    }else{
        sendAcknowledment(seq);
    }
}

int main() {
    srand(time(NULL));
    for(int i=1; i<=MAX_PACKETS; i++) {
         simulate(i);
    }
    return 0;
}
