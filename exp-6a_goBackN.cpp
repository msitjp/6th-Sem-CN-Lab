#include <bits/stdc++.h>
#define MAX_PACKETS 3
#define PACKET_SIZE 1024
#define ERROR_RATE 0.05 // 5% Error Rate
#define WINDOW_SIZE 3

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

bool sendPacket(int seq) {
    Packet p(Data, seq, PACKET_SIZE);
    Print(p);
    bool error = (rand()%2) <= ERROR_RATE ? true : false;
    return error;
}

void sendAcknowledment(int seq) {
    Packet p(Acknowledgment, seq, PACKET_SIZE);
    Print(p);
}

void simulate(int seq=1){
  bool error[WINDOW_SIZE];
  for(int i=seq; i<=min(MAX_PACKETS, seq+WINDOW_SIZE); i++) error[i-seq] = sendPacket(i);
  int seq_no = std::distance(error, std::find(error, error + WINDOW_SIZE, 0));
  if(seq_no <= min(WINDOW_SIZE, MAX_PACKETS-seq)){
    Packet a(Data, seq + seq_no, PACKET_SIZE);
    Print(a, true);
    simulate(seq + seq_no);
  }else{
    for(int i=seq; i<=min(MAX_PACKETS, seq+WINDOW_SIZE); i++) sendAcknowledment(i);
    if(seq+WINDOW_SIZE <= MAX_PACKETS) simulate(seq+WINDOW_SIZE);
  }
}

int main() {
    srand(time(NULL));
    simulate();
    return 0;
}
